#ifndef CHDKPTPMANAGER_H
#define CHDKPTPMANAGER_H

#include <QList>
#include <QString>
#include <QObject>
#include <QStringList>
#include <QMetaType>
#include <QMutex>

extern "C" {

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

lua_State *chdkptp_init(int argc, char ** argv);
int chdkptp_exit(lua_State *L);

}

// Sample "mc.cams":
//
// ={
//  [1]={
//   apiver={
//    MAJOR=2,
//    MINOR=6,
//   },
//   mc_id="1:Canon PowerShot A1400",
//   _con="userdata: 0xf6c998",
//   ptpdev={
//    device_version="1-14.0.1.0",
//    serial_number="63837765ED604B39BEC7A4E198C06001",
//    max_packet_size=512,
//    model="Canon PowerShot A1400",
//    manufacturer="Canon Inc.",
//   },
//   condev={
//    dev="089",
//    transport="usb",
//    product_id=12900,
//    vendor_id=1193,
//    bus="001",
//   },
//  },
// }
class CameraInfo
{
public:
    int index;
    QString serialNumber;
};

typedef QList<CameraInfo> CameraInfoList;

class PhotoFile
{
public:
    CameraInfo cam;
    QString path;
};

class ChdkPtpManager : public QObject
{
    Q_OBJECT

public:
    ChdkPtpManager();
    ~ChdkPtpManager();

    // These functions are thread-safe (using m_mutex)
    void startShooting();
    void startQueryCameras();

signals:
    void queryCamerasReady(CameraInfoList cameras);

    void shootingProgress();
    void shootingDone(QList<PhotoFile> files);
    void shootingFailed();

protected:
    // These functions are not thread-safe
    int execLuaString(const char *luacode);

private:
    lua_State *m_lua;
    QMutex m_mutex;
};

#endif // CHDKPTPMANAGER_H
