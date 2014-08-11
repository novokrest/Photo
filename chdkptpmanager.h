#ifndef CHDKPTPMANAGER_H
#define CHDKPTPMANAGER_H

#include <QList>
#include <QString>
#include <QObject>
#include <QStringList>
#include <QMetaType>
#include <QMutex>

extern "C" {

#include <lua5.2/lua.h>
#include <lua5.2/lualib.h>
#include <lua5.2/lauxlib.h>

lua_State *chdkptp_init(int argc, char ** argv);
int chdkptp_exit(lua_State *L);

}

#include <LuaIntf/LuaIntf.h>

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

// Directory or file on the remote file system
class RemoteInode
{
public:
    bool is_file;
    bool is_dir;
    QString name;
    unsigned long long size;
//     unsigned long long ctime;
//     unsigned long long mtime;
//     unsigned int attrib;
};

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
    void startDownloadRecent();

    void setTv96(int tv96);
    void setAv96(int av96);
    void setSv96(int sv96);

signals:
    void queryCamerasReady(CameraInfoList cameras);
    void downloadRecentReady(PhotoFile photos);

    void shootingProgress();
    void shootingDone(QList<PhotoFile> files);
    void shootingFailed();

protected:
    // These functions are not thread-safe
    int execLuaString(const char *luacode);

    QList<RemoteInode> listRemoteDir(LuaIntf::LuaRef& lcon, const QString& path);
    QString getLatestPhotoPath(LuaIntf::LuaRef& lcon);

    bool multicamCmdWait(const QString& cmd);

private:
    lua_State *m_lua;
    QMutex m_mutex;

    int m_tv96;
    int m_av96;
    int m_sv96;
};

#endif // CHDKPTPMANAGER_H
