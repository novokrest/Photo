#ifndef CAMERA_H
#define CAMERA_H

#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QSharedPointer>
#include <QtCore/QFuture>
#include <QtCore/QFutureWatcher>

#include "luaapi.h"
#include "commandmanager.h"
#include "propertyresolver.h"

using LuaIntf::LuaRef;
using std::string;

class ChdkPtpManager;

class Camera : public QObject
{
    Q_OBJECT

public:

    Camera();
    Camera(const Camera& o);
    ~Camera();

    void initPropertyResolver();
    
    Camera& operator=(const Camera& o);

    void setChdkPtpManager(ChdkPtpManager* ptr);

    static Camera fromLuaRef(const LuaIntf::LuaRef& info);
    LuaIntf::LuaRef toLuaRef(lua_State* luaState) const;
    LuaIntf::LuaRef getLuaRefConnection();

    void queryAdditionalInfo();

    QString bus() const;
    QString dev() const;
    int vendorId() const;
    int productId() const;

    QString serial() const;
    CameraModel model() const;
    QString modelName() const;
    QString deviceV() const;
    QString manufacturer() const;
    QString toString() const;
    
    QString uid() const;
    
    bool operator==(const Camera& o) const;

    void startSerialNumberQuery();

    QString querySerialNumber();
    QString queryProp(int reg);

    int getPropValue(QString propName);
    void setPropValue(QString propName, int propValue);
    void setPropValue(int propID, int propValue);

    LuaRef execWait(QString cmd);

    void hightlightCamera();

    void setIndex(int index);
    int index() const;

    void shutDown();

    void configureStaticProps();

    void multicamCmdWaitSeq(const QVector<QString>& seq);

    void configureFocus(int requiredFocusMode);
    void setFocus(int focusValue);
    int getFocus();

protected slots:
    void slotSerialNumberFutureReady();

signals:
    void serialNumberReady();

private:
    int m_index;

    QString m_bus;
    QString m_dev;
    int m_vendorId;
    int m_productId;

    QString m_serial;
    CameraModel m_model;
    QString m_modelName;
    QString m_deviceV;
    QString m_manufacturer;

    QFuture<QString> m_serialNumberFuture;
    QFutureWatcher<QString> m_serialNumberWatcher;

    QSharedPointer<LuaIntf::LuaRef> m_lcon;

    ChdkPtpManager* m_chdkptp;
    PropertyResolver m_propResolver;
};

typedef QSharedPointer<Camera> CameraPtr;
typedef QList<Camera> CameraList;

#endif // CAMERA_H
