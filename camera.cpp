#include "camera.h"
#include "chdkptpmanager.h"

#include <QtCore/QString>
#include <QtCore/QDebug>
#include <QtConcurrent/QtConcurrent>

using namespace LuaIntf;

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
    , m_chdkptp(o.m_chdkptp)
    , m_index(o.m_index)
{
    connect(&m_serialNumberWatcher, SIGNAL(finished()), this, SLOT(slotSerialNumberFutureReady()));
}

Camera::~Camera()
{
    disconnect(&m_serialNumberWatcher, SIGNAL(finished()), this, SLOT(slotSerialNumberFutureReady()));
}

Camera& Camera::operator=(const Camera& o)
{
    m_bus = o.m_bus;
    m_dev = o.m_dev;
    m_vendorId = o.m_vendorId;
    m_productId = o.m_productId;
    m_chdkptp = o.m_chdkptp;
    m_index = o.m_index;
    
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
        m_lcon.reset(new LuaRef());
        (*m_lcon) = chdkuConnection.call<LuaRef>(toLuaRef(m_chdkptp->m_lua));
        (*m_lcon)["mc_id"] = uid().toStdString();
    }

    return (*m_lcon);
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

    // This delay is necessary: the con:listdir() method hangs otherwise.
    //
    // The source of the problem may be that con:listdir() is too close
    // in time to chdku.connection().
    // See implementation of chdk_connection() in "chdkptp/chdkptp.cpp".
//     usleep(30000);

    // Get camera serial number
    lcon.get<LuaRef>("update_connection_info")(lcon);
    QString serialNumber = QString::fromStdString(lcon.get<LuaRef>("ptpdev").get<std::string>("serial_number"));
    qDebug() << serialNumber;

    return serialNumber;

//     QString remoteFile = getLatestPhotoPath(lcon);
//     QString localFile = QString("%1/myphoto_ser%2.jpg").arg(destPath).arg(serialNumber);
//     std::cout << "downloading from: " << remoteFile.toStdString() << std::endl;
//     std::cout << "saving to: " << localFile.toStdString() << std::endl;
// 
//     // lcon:download_pcall(source, destination)
//     // This is a member function call, therefore we have to pass "lcon" as 1st argument.
//     LuaRef downloadPCall = lcon.get<LuaRef>("download_pcall");
//     downloadPCall(lcon, remoteFile.toStdString(), localFile.toStdString());
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
    m_chdkptp->multicamCmdWait("rec");
    m_chdkptp->multicamCmdWait("play");
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
