#ifndef CHDKPTPMANAGER_H
#define CHDKPTPMANAGER_H

#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QObject>
#include <QtCore/QStringList>
#include <QtCore/QMetaType>
#include <QtCore/QMutex>

#include "luaapi.h"
#include "camera.h"
#include "commandmanager.h"
#include <cstring>

using std::string;

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

// Directory or file on the remote file system
class RemoteInode
{
public:
    bool is_file;
    bool is_dir;
    QString name;
    unsigned long long size;
};

class PhotoFile
{
public:
    CameraInfo cam;
    QString path;
};

struct Settings
{
    bool multicamMode;

    bool preshoot;
    bool flash;

    int av96;
    int tv96;
    int sv96;

    bool manualFocus;
    int focus;

    int zoom;

    int delay;

    Settings();
    void setDefault();
};

class ChdkPtpManager : public QObject
{
    Q_OBJECT

    typedef std::vector<Camera> CameraVec;

public:
    ChdkPtpManager();
    ~ChdkPtpManager();

    void initLuaChdkptp(const string& chdkptpLibPath);

    void listCameras();
    void getAdditionalCamerasInfo();

    void setSettings(const Settings& settings);
    void applySettings();
    void applySettingsPerSingle();
    void applySettingsMulticam(CameraModel model);

    void configureFlash();
    void configureFocus();
    void configureZoom();
    void configureAv();
    void configureTv();
    void configureSv();

    void startSinglecamShooting();
    void startMulticamShooting();

    QList<RemoteInode> listRemoteDir(LuaIntf::LuaRef& lcon, const QString& path);
    QString getLatestPhotoPath(LuaIntf::LuaRef& lcon);
    void startDownloadRecentPhotos();

    void startSelectedCameraShooting();
    void setSelectedCamera(int index);


    void startDiagnose();
    void startConfigureStaticProps();

    void shutdownAll();

    void setTv96(int tv96);
    void setAv96(int av96);
    void setSv96(int sv96);

    void setFlashMode(bool mode);
    void setPreshootMode(bool mode);

    void setDelay(int delay);
    void delay();

    void highlightCamera(int index);

    void runCustomScript();

signals:
    void signalCamerasListReady();
    void signalAdditionalCamerasInfoReady();
    void signalSettingsApplied();
    void signalShootingDone();
    void signalDownloadPhotosDone();

    void downloadRecentReady(PhotoFile photos);

    void shootingProgress();
    void shootingDone(QList<PhotoFile> files);
    void shootingFailed();

protected:
    // These functions are not thread-safe
    int execLuaString(const char *luacode);

    void multicamCmdStart();
    void multicamCmdExit();
    bool multicamCmd(QString const& cmd);
    bool multicamCmdWait(const QString& cmd);
    //bool multicamCmdWait(const string& cmd);
    void multicamExecWait(CameraList& cameras, const QString& cmd);

    void initCamerasPropertyResolvers();
    void setCamerasProperty(QString const& propName, int propValue);

    void populateMcCams();
    void populateMcCams(CameraList cameras);

    void configureCameras();

    bool reconnectToCameras();

    void shootAfterUsbDisconnect();

    void setFocus(int focusValue);
    void setMulticamFocus(int focusValue);

private:
    friend void Camera::queryAdditionalInfo();
    friend void Camera::hightlightCamera();
    friend LuaIntf::LuaRef Camera::getLuaRefConnection();
    friend void Camera::configureStaticProps();
    friend void Camera::multicamCmdWaitSeq(const QVector<QString>& seq);

    lua_State *m_lua;
    QMutex m_mutex;

    Settings m_settings;
    CommandManager m_commandManager;

    int m_tv96;
    int m_av96;
    int m_sv96;
    int m_delay;

    bool m_preshoot;
    bool m_flash;

    bool m_manualFocus;
    int m_manualFocusValue;
    bool m_isManualMode;
    
public:
    CameraVec m_cameras;
};

#endif // CHDKPTPMANAGER_H
