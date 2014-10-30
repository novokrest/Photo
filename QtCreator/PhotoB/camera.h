#ifndef CAMERA_H
#define CAMERA_H

#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QSharedPointer>
#include <QtCore/QFuture>
#include <QtCore/QFutureWatcher>

#include "luaapi.h"
#include "propertyresolver.h"

using LuaIntf::LuaRef;

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

    QString bus() const;
    QString dev() const;
    QString serial() const;
    int vendorId() const;
    int productId() const;
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

protected slots:
    void slotSerialNumberFutureReady();

signals:
    void serialNumberReady(const QString& sn);

private:
    QString m_bus;
    QString m_dev;
    QString m_serialNumber;
    int m_vendorId;
    int m_productId;

    int m_index;

    QFuture<QString> m_serialNumberFuture;
    QFutureWatcher<QString> m_serialNumberWatcher;

    QSharedPointer<LuaIntf::LuaRef> m_lcon;

    ChdkPtpManager* m_chdkptp;
    PropertyResolver m_propResolver;
};

typedef QSharedPointer<Camera> CameraPtr;
typedef QList<Camera> CameraList;

#endif // CAMERA_H
