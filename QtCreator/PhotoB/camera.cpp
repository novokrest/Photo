#include "camera.h"
#include "chdkptpmanager.h"

#include <QtCore/QString>
#include <QtCore/QDebug>
#include <QtConcurrent/QtConcurrent>

#include <sstream>

#include <unistd.h>
#include <utils.h>

using namespace LuaIntf;
using std::stringstream;


Camera::Camera()
    : QObject()
    , m_chdkptp(nullptr)
{
    connect(&m_serialNumberWatcher, SIGNAL(finished()), this, SLOT(slotSerialNumberFutureReady()));
}

Camera::Camera(const Camera& o)
    : QObject()
    , m_bus(o.m_bus)
    , m_dev(o.m_dev)
    , m_vendorId(o.m_vendorId)
    , m_productId(o.m_productId)
    , m_index(o.m_index)
    , m_chdkptp(o.m_chdkptp)
    , m_propResolver(o.m_propResolver)
{
    connect(&m_serialNumberWatcher, SIGNAL(finished()), this, SLOT(slotSerialNumberFutureReady()));
}

Camera::~Camera()
{
    disconnect(&m_serialNumberWatcher, SIGNAL(finished()), this, SLOT(slotSerialNumberFutureReady()));
}


/*
 * TODO: it is very expensive to store for each camera
 * its own PropertyResolver, because almost all cameras have same PropertyResolvers
*/

void Camera::initPropertyResolver()
{
    LuaRef propSet = execWait(QString("return get_propset()"));
    m_propResolver.setPropset(propSet.toValue<int>());
    qDebug() << "propset: " << propSet.toValue<int>();

    LuaRef properties = execWait(QString("return require('propcase')"));
    if (!properties.isTable()) {
        qDebug() << "initPropertyResolver(): no propertyTable was returned";
        return;
    }

    for (auto& it: properties) {
        string propName = it.key<string>();
        int propID = it.value<int>();

        bool status = m_propResolver.registerProperty(propName, propID);
        if (!status) {
            qDebug() << QString("Collision: propName = %1, propID = %2")
                        .arg(QString::fromStdString(propName))
                        .arg(QString::number(propID));
        }
    }
}

void Camera::setPropValue(QString propName, int propValue)
{
    int propID = m_propResolver.resolve(propName.toStdString());

    return setPropValue(propID, propValue);
}

void Camera::setPropValue(int propID, int propValue)
{
    LuaRef retValue = execWait(QString("return set_prop(%1, %2)").arg(propID).arg(propValue));
    qDebug() << "setPropValue: return = " << retValue.typeName();
}

Camera& Camera::operator=(const Camera& o)
{
    m_bus = o.m_bus;
    m_dev = o.m_dev;
    m_vendorId = o.m_vendorId;
    m_productId = o.m_productId;
    m_chdkptp = o.m_chdkptp;
    m_index = o.m_index;
    m_propResolver = o.m_propResolver;
    
    return *this;
}

void Camera::setChdkPtpManager(ChdkPtpManager* ptr)
{
    m_chdkptp = ptr;
}

// static
Camera Camera::fromLuaRef(const LuaRef& info)
{
    Camera c;
    c.m_bus = QString::fromUtf8(info.get<std::string>("bus").c_str());
    c.m_dev = QString::fromUtf8(info.get<std::string>("dev").c_str());
    c.m_vendorId = info.get<int>("vendor_id"); // 0x04a9 for Canon A1400
    c.m_productId = info.get<int>("product_id"); // 0x3264 for Canon A1400

    return c;
}

LuaRef Camera::toLuaRef(lua_State* luaState) const
{
    LuaRef t = LuaRef::createTable(luaState);
    t["bus"] = m_bus.toStdString();
    t["dev"] = m_dev.toStdString();
    t["vendor_id"] = m_vendorId;
    t["product_id"] = m_productId;

    return t;
}

LuaRef Camera::getLuaRefConnection()
{
    LuaRef chdkuConnection(m_chdkptp->m_lua, "chdku.connection");

    if (m_lcon.isNull()) {
        m_lcon.reset(new LuaRef(chdkuConnection.call<LuaRef>(toLuaRef(m_chdkptp->m_lua))));
        (*m_lcon)["mc_id"] = uid().toStdString();
    }

    LuaRef lcon = *m_lcon;

    LuaRef isConnected = lcon.get<LuaRef>("is_connected");
    if (isConnected.call<bool>(lcon)) {
        qDebug() << "already connected";
    }
    else {
        // lcon:connect()
        // This is a member function call, therefore we have to pass "lcon" as 1st argument.
        LuaRef lconConnect = lcon.get<LuaRef>("connect");
        lconConnect(lcon);

        qDebug() << "is_connected = " << isConnected.call<bool>(lcon);
    }

    return (*m_lcon);
}

LuaRef Camera::execWait(QString cmd)
{
    string command = cmd.toStdString();

    LuaRef lcon = getLuaRefConnection();
    LuaRef lconExecWait = lcon.get<LuaRef>("execwait");
    qDebug() << "execWait: " << lconExecWait.typeName();
    LuaRef result = lconExecWait.call<LuaRef>(lcon, command.c_str());

    return result;
}

QString Camera::bus() const
{
    return m_bus;
}

QString Camera::dev() const
{
    return m_dev;
}

int Camera::vendorId() const
{
    return m_vendorId;
}

int Camera::productId() const
{
    return m_productId;
}

void Camera::startSerialNumberQuery()
{
    m_serialNumberFuture = QtConcurrent::run(this, &Camera::querySerialNumber);
    m_serialNumberWatcher.setFuture(m_serialNumberFuture);
}

QString Camera::querySerialNumber()
{
    if (m_serialNumber.size() > 0)
        return m_serialNumber;
    if (!m_chdkptp)
        return QString("?");

    QMutexLocker locker(&m_chdkptp->m_mutex);

    // lcon = chdku.connection(devinfo)
    LuaRef lcon = getLuaRefConnection();

    qDebug() << uid();

    LuaRef isConnected = lcon.get<LuaRef>("is_connected");
    if (isConnected.call<bool>(lcon)) {
        qDebug() << "already connected";
    }
    else {
        // lcon:connect()
        // This is a member function call, therefore we have to pass "lcon" as 1st argument.
        LuaRef lconConnect = lcon.get<LuaRef>("connect");
        lconConnect(lcon);

        qDebug() << "is_connected = " << isConnected.call<bool>(lcon);
    }

    // Get camera serial number
    lcon.get<LuaRef>("update_connection_info")(lcon);
    QString serialNumber = QString::fromStdString(lcon.get<LuaRef>("ptpdev").get<std::string>("serial_number"));
    qDebug() << serialNumber;

    return serialNumber;
}

QString Camera::queryProp(int reg)
{
    std::stringstream command;
    command << "return get_prop(" << reg << ")";

    LuaRef lcon = getLuaRefConnection();

    // Get reference to method "lcon.execwait"
    LuaRef execWait = lcon.get<LuaRef>("execwait");
    qDebug() << "execWait: " << execWait.typeName();

    usleep(30000);

    LuaRef result = execWait.call<LuaRef>(lcon, command.str());

    return QString("%1").arg(result.toValue<int>());
}

int Camera::getPropValue(QString propName)
{
    int propId = m_propResolver.resolve(propName.toStdString());

    std::stringstream command;
    command << "return get_prop(" << propId << ")";

    LuaRef lcon = getLuaRefConnection();
    LuaRef execWait = lcon.get<LuaRef>("execwait");

    LuaRef result = execWait.call<LuaRef>(lcon, command.str());
    if (result.type() != LuaTypeID::Number) {
        return -1;
    }

    return result.toValue<int>();
}

void Camera::hightlightCamera()
{
    if (!m_chdkptp)
        return;

    QMutexLocker locker(&m_chdkptp->m_mutex);

    // Narrow "mc.cams" to only one camera
    LuaRef mcCams = LuaRef::createTable(m_chdkptp->m_lua);
    mcCams[1] = getLuaRefConnection();

    LuaRef mc(m_chdkptp->m_lua, "mc");
    mc["cams"] = mcCams;

    m_chdkptp->execLuaString("mc:start()");
    m_chdkptp->multicamCmdWait(QString("call set_prop(143, 2);"));
    m_chdkptp->multicamCmdWait("rec");
    m_chdkptp->multicamCmdWait("preshoot");

    sleep(1);

    m_chdkptp->multicamCmdWait("shoot");
    m_chdkptp->multicamCmdWait("play");

    m_chdkptp->execLuaString("mc:cmd('exit')");

    /* Bus/Dev = 002/091
     * SerialNumber=BAFA22A11DD74AC7B55C04DCFF971CC1
     */
}

QString Camera::uid() const
{
    return QString("%1/%2").arg(bus()).arg(dev());
}

bool Camera::operator==(const Camera& o) const
{
    return uid() == o.uid();
}

void Camera::slotSerialNumberFutureReady()
{
    m_serialNumber = m_serialNumberFuture.result();
    emit serialNumberReady(m_serialNumber);
}

void Camera::setIndex(int index)
{
    m_index = index;
}

int Camera::index() const
{
    return m_index;
}

void Camera::shutDown()
{
    std::stringstream command;
    command << "shut_down()";

    LuaRef lcon = getLuaRefConnection();

    // Get reference to method "lcon.execwait"
    LuaRef execWait = lcon.get<LuaRef>("execwait");

    usleep(30000);

    execWait.call<LuaRef>(lcon, command.str());
}

void Camera::multicamCmdWaitSeq(const QVector<QString>& seq)
{
    sleep(1);
    for (const QString& key : seq) {
        m_chdkptp->multicamCmdWait(QString("call click('%1');").arg(key));
        sleep(1);
    }
}

void Camera::configureStaticProps()
{
    if (!m_chdkptp)
        return;

    QMutexLocker locker(&m_chdkptp->m_mutex);

    // Narrow "mc.cams" to only one camera
    LuaRef mcCams = LuaRef::createTable(m_chdkptp->m_lua);
    mcCams[1] = getLuaRefConnection();

    LuaRef mc(m_chdkptp->m_lua, "mc");
    mc["cams"] = mcCams;

    m_chdkptp->multicamCmdWait("exit");

    QString r49 = queryProp(49);
    qDebug() << "r49: " << r49;

    m_chdkptp->execLuaString("mc:start()");
    m_chdkptp->multicamCmdWait("play");
    m_chdkptp->multicamCmdWait("rec");

    sleep(2);

    // Go to Menu -> Settings, select "Reset All..." and confirm.
    multicamCmdWaitSeq({"menu", "right", "up", "set", "right", "set"});

    // TBD: set date and time on the camera

    // Disable power saving
//     multicamCmdWaitSeq({"menu", "right", "down", "down", "down", "down", "down", "down", "down", "set", "right", "menu", "menu"});

    // Menu -> Settings -> Mute: On
    multicamCmdWaitSeq({"menu", "right", "down", "left", "menu"});

    if (r49 == QString("-32768"))
        // if in AUTO mode
        m_chdkptp->multicamCmdWait(QString("call click('up');"));

    m_chdkptp->multicamCmdWait("exit");
    QString r49_noauto = queryProp(49);
    qDebug() << "r49_noauto: " << r49_noauto;
    m_chdkptp->execLuaString("mc:start()");

    if (r49_noauto == QString("-32198")) {
        // LIVE -> P
        multicamCmdWaitSeq(QVector<QString>({"set", "set", "up", "set"}));
    }

    m_chdkptp->multicamCmdWait("exit");

    shutDown();
}
