#ifndef CAMERA_H
#define CAMERA_H

#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QSharedPointer>
#include <QtCore/QFuture>
#include <QtCore/QFutureWatcher>

#include "luaapi.h"

class ChdkPtpManager;

class Camera : public QObject
{
    Q_OBJECT

public:
    Camera();
    Camera(const Camera& o);
    ~Camera();
    
    Camera& operator=(const Camera& o);

    void setChdkPtpManager(ChdkPtpManager* ptr);

    static Camera fromLuaRef(const LuaIntf::LuaRef& info);
    LuaIntf::LuaRef toLuaRef(lua_State* luaState) const;
    LuaIntf::LuaRef getLuaRefConnection();

    QString bus() const;
    QString dev() const;
    int vendorId() const;
    int productId() const;
    
    QString uid() const;
    
    bool operator==(const Camera& o) const;

    void startSerialNumberQuery();

    QString querySerialNumber();

    void hightlightCamera();

    void setIndex(int index);
    int index() const;

protected slots:
    void slotSerialNumberFutureReady();

signals:
    void serialNumberReady(const QString& sn);

private:
    QString m_bus;
    QString m_dev;
    int m_vendorId;
    int m_productId;

    int m_index;

    QString m_serialNumber;
    QFuture<QString> m_serialNumberFuture;
    QFutureWatcher<QString> m_serialNumberWatcher;

    QSharedPointer<LuaIntf::LuaRef> m_lcon;

    ChdkPtpManager* m_chdkptp;
};

typedef QSharedPointer<Camera> CameraPtr;
typedef QList<Camera> CameraList;

#endif // CAMERA_H
