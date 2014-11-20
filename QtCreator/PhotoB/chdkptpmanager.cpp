#include "chdkptpmanager.h"
#include "camera.h"
#include "utils.h"
#include "properties.h"

#include <LuaIntf/LuaIntf.h>

#include <QtConcurrent/QtConcurrent>
#include <QtCore/QDir>
#include <QtCore/QDebug>

#include <stdexcept>

#include <sstream>
#include <iostream>
#include <unistd.h>
#include <cstring>

using std::string;
using namespace LuaIntf;

//static const std::string CHDKPTP_LUA_PATH


/*
    util=require'util'
    util:import()
    errutil=require'errutil'
    ustime=require'ustime'
    fsutil=require'fsutil'
    prefs=require'prefs'
    chdku=require'chdku'
    cli=require'cli'
    exp=require'exposure'
    dng=require'dng'
    dngcli=require'dngcli'
*/

Settings::Settings()
{
    setDefault();
}

void Settings::setDefault()
{
    multicamMode = true;
    preshoot = true;
    flash = true;

    av96 = 0;
    tv96 = 0;
    sv96 = 0;

    manualFocus = false;
    focus = 0;

    zoom = 0;
    delay = 0;
}

ChdkPtpManager::ChdkPtpManager()
    : m_mutex(QMutex::Recursive)
{
    initLuaChdkptp("");
}

void ChdkPtpManager::initLuaChdkptp(const string& chdkptpLibPath)
{
    QMutexLocker locker(&m_mutex);

    // Pass "argc" and "argv" for empty command line
    m_lua = chdkptp_init(0, NULL);

    execLuaString("package.path = package.path .. ';/home/knovokreshchenov/Github/chdkptp/lua/?.lua'");

    execLuaString("util = require('util')");
    execLuaString("util:import()");
    execLuaString("chdku = require('chdku')");
    execLuaString("prefs = require('prefs')");
    execLuaString("cli = require('cli')");

    execLuaString("ustime = require('ustime')");
    execLuaString("errutil = require('errutil')");
    execLuaString("con = chdku.connection()");
    execLuaString("mc = require('multicam')");

    //     int top = lua_gettop(L);
    //     luaL_loadstring(L, "return 3, 4, 5");
    //     int R = lua_pcall(L, 0, LUA_MULTRET, 0);
    //     int nresults = lua_gettop(L) - top;

    //     execLuaString("cli:run()");

    //     con=chdku.connection()
    //     dngcli.init_cli()
}

ChdkPtpManager::~ChdkPtpManager()
{
    chdkptp_exit(m_lua);
}

void ChdkPtpManager::listCameras()
{
    QMutexLocker locker(&m_mutex);

    m_cameras.clear();

    CameraVec cameras;
    LuaRef listUsbDevices(m_lua, "chdk.list_usb_devices");
    LuaRef devices = listUsbDevices.call<LuaRef>();

    int index = 0;
    for (auto& devinfo : devices) {
        LuaRef dev = devinfo.value<LuaRef>();
        Camera camera = Camera::fromLuaRef(dev);

        camera.setIndex(index);
        camera.setChdkPtpManager(this);
        cameras.push_back(camera);

        ++index;
    }

    m_cameras = cameras;

    emit signalCamerasListReady();
}

void ChdkPtpManager::getAdditionalCamerasInfo()
{
    QMutexLocker locker(&m_mutex);

    for (CameraVec::iterator cameraIt = m_cameras.begin(); cameraIt != m_cameras.end(); ++cameraIt) {
        cameraIt->queryAdditionalInfo();
        cameraIt->initPropertyResolver();
    }

    emit signalAdditionalCamerasInfoReady();
}

void ChdkPtpManager::setSettings(const Settings& settings)
{
    m_settings = settings;
}

void ChdkPtpManager::applySettings()
{
    QMutexLocker locker(&m_mutex);

    if (m_settings.multicamMode) {
        //applySettingsMulticam(CANON_PS_SX150_IS);
    }
    else {
        applySettingsPerSingle();
    }
//    configureFlash();
//    configureFocus();
//    configureZoom();
//    configureAv();
//    configureTv();
//    configureSv();

    //TODO: apply settings to different or same cameras

    emit signalSettingsApplied();
}

void ChdkPtpManager::applySettingsMulticam(CameraModel model)
{
    populateMcCams();
    multicamCmdStart();
    multicamCmdWait("rec");

    QString setFlashCommand = "";
    QString setFocusCommand = "";
    QString setZoomCommand = "";
    QString setAvCommand = "";
    QString setTvCommand = "";
    QString setIsoCommand = "";

    multicamCmdWait(setFlashCommand);
    multicamCmdWait(setFocusCommand);
    multicamCmdWait(setZoomCommand);
    multicamCmdWait(setAvCommand);
    multicamCmdWait(setTvCommand);
    multicamCmdWait(setIsoCommand);

    //multicamCmdWait("play"); //after "play" settings are discarded
    multicamCmdExit();
}

void ChdkPtpManager::applySettingsPerSingle()
{}

/*
 * For cameras 'CanonPS A1400' and 'CanonPS SX150 IS' props.FLASH_MODE = 143
 * 0 - flash auto
 * 1 - flash on
 * 2 - flash off
*/
void ChdkPtpManager::configureFlash()
{
    multicamCmdWait(QString("call set_prop(143, %1);").arg(m_settings.flash ? 1 : 2));
}

/*
 * For cameras 'CanonPS A1400' transition to manual mode (and back) carries out by following sequence command:
 * set_aflock(1) - MF on
 * set_focus(<value>) - 0(auto), -1(inf)
 * set_aflock(0) - MF off
 *
 * For cameras 'CanonPS SX150 IS' transition to manual mode (and back) carries out by following sequence command:
 * post_levent_for_npt("PressSw1AndMF") - MF on
 * set_focus(<value>) - 0(auto), -1(inf)
 * post_levent_for_npt("PressSw1AndMF") - MF off
 *
 * Useful commands:
 * get_focus_mode() - 0=auto, 1=MF, 3=inf., 4=macro, 5=supermacro
 * get_focus_state() - returns focus status, > 0 focus successful, =0 not successful, < 0 MF
 * get_focus_ok() - returns 0=focus not ok, 1=ok if get_focus_state<>0 and get_shooting=1
 * get_dofinfo() - returns table for all dof related values
*/
void ChdkPtpManager::configureFocus()
{
    for (auto& camera: m_cameras) {
        camera.configureFocus(m_isManualMode);
    }
}

void ChdkPtpManager::configureZoom()
{}

void ChdkPtpManager::configureAv()
{}

void ChdkPtpManager::configureTv()
{}

void ChdkPtpManager::configureSv()
{}

void ChdkPtpManager::startSinglecamShooting()
{}

void ChdkPtpManager::startMulticamShooting()
{
    QMutexLocker locker(&m_mutex);

    delay();

    //if after applySettingsMulticam we can skip this
    populateMcCams();
    multicamCmdStart();
    multicamCmdWait("rec");
    configureFlash();

    if (m_settings.preshoot) {
        multicamCmdWait("preshoot");
    }
    multicamCmdWait("shootremote");

    emit signalShootingDone();

//    printCountdown(20);
//    reconnectToCameras();
}

QList<RemoteInode> ChdkPtpManager::listRemoteDir(LuaRef& lcon, const QString& path)
{
    QList<RemoteInode> result;

    LuaRef opts = LuaRef::createTable(m_lua);
    opts["stat"] = "*";

    LuaRef listDir = lcon.get<LuaRef>("listdir");
    LuaRef dirContents = listDir.call<LuaRef>(lcon, path.toStdString(), opts);
    for (auto& entry : dirContents) {
        LuaRef stat = entry.value<LuaRef>();

        RemoteInode inode;
        inode.is_file = stat.get<bool>("is_file");
        inode.is_dir = stat.get<bool>("is_dir");
        inode.name = QString::fromStdString(stat.get<std::string>("name"));
        inode.size = stat.get<unsigned long long>("size");

        result.append(inode);
    }

    return result;
}

QString ChdkPtpManager::getLatestPhotoPath(LuaRef& lcon)
{
    QString dcimPath = QLatin1String("A/DCIM");
    QList<RemoteInode> dcim = listRemoteDir(lcon, dcimPath);
    qSort(dcim.begin(), dcim.end(), [](const RemoteInode& a, const RemoteInode& b) -> bool {
        return a.name > b.name;
    });

    auto firstDir = std::find_if(dcim.begin(), dcim.end(),
                                 [](const RemoteInode& f)
    {
        // Test if first character of directory name is a digit
        return QRegExp("\\d").indexIn(f.name) == 0;
    });

    if (firstDir == dcim.end()) {
        qDebug() << "No photo directories found in A/DCIM";
        return QString();
    }

    qDebug() << "Entering directory:" << firstDir->name;

    QString latestDirPath = QString("%1/%2").arg(dcimPath).arg(firstDir->name);
    QList<RemoteInode> files = listRemoteDir(lcon, latestDirPath);
    qSort(files.begin(), files.end(), [](const RemoteInode& a, const RemoteInode& b)
    {
        return a.name > b.name;
    });

    auto firstJPG = std::find_if(files.begin(), files.end(), [](const RemoteInode& f)
    {
        return f.name.endsWith(QLatin1String(".JPG"));
    });

    qDebug() << QString("Selecting file:") << firstJPG->name;

    if (firstJPG == files.end())
        return QString();
    else
        return QString("%1/%2").arg(latestDirPath).arg(firstJPG->name);
}

void ChdkPtpManager::startDownloadRecentPhotos()
{
    QMutexLocker locker(&m_mutex);

    // Get list of files and figure out the latest file written:
    // con:listdir(path,{stat='*'})

    QDir dir;
    QString subPath = QString("downloaded_photos") + QDir::separator() + QDateTime::currentDateTime().toString(QString("dd.MM.yyyy_hh:mm:ss")); // + QChar('_') + QDate::currentDate().toString(QString("hh:mm:ss"));
    dir.mkpath(subPath);
    QString destPath = dir.filePath(subPath);

    for (Camera& cam : m_cameras) {
        LuaRef lcon = cam.getLuaRefConnection();
        usleep(30000);
        cam.queryAdditionalInfo();

        QString remoteFile = getLatestPhotoPath(lcon);
        QString localFile = QString("%1/serial_%2.jpg").arg(destPath).arg(cam.serial());

        LuaRef downloadPCall = lcon.get<LuaRef>("download_pcall");
        downloadPCall(lcon, remoteFile.toStdString(), localFile.toStdString());

        LuaRef targets = LuaRef::createTable(m_lua);
        targets[1] = remoteFile.toStdString();
        usleep(30000);
        LuaRef deletePCall = lcon.get<LuaRef>("mdelete");
        deletePCall(lcon, targets);

        std::cout << "downloading from: " << remoteFile.toStdString() << std::endl;
        std::cout << "saving to: " << localFile.toStdString() << std::endl;
    }
}

void ChdkPtpManager::multicamCmdStart()
{
    //execLuaString("mc:start()");
    LuaRef mc(m_lua, "mc");
    mc.get<LuaRef>("start").call<void>(mc);
}

void ChdkPtpManager::multicamCmdExit()
{
    multicamCmdWait("exit");
}

int ChdkPtpManager::execLuaString(const char *luacode)
{
    int r = luaL_loadstring(m_lua, luacode);
    if (r) {
        fprintf(stderr, "loadstring failed %d\n", r);
        fprintf(stderr, "error %s\n", lua_tostring(m_lua, -1));
    }
    else {
        r = lua_pcall(m_lua, 0, LUA_MULTRET, 0);
        if (r) {
            fprintf(stderr, "pcall failed %d\n", r);
            fprintf(stderr, "error %s\n", lua_tostring(m_lua, -1));
            // TODO should get stack trace
        }
    }

    return r == 0;
}

void ChdkPtpManager::populateMcCams()
{
    LuaRef mcCams = LuaRef::createTable(m_lua);
    for (Camera& cam : m_cameras)
        mcCams[cam.index() + 1] = cam.getLuaRefConnection();

    LuaRef mc(m_lua, "mc");
    mc["cams"] = mcCams;
}

void ChdkPtpManager::populateMcCams(CameraList cameras)
{
    LuaRef mcCams = LuaRef::createTable(m_lua);

    int index = 1;
    for (Camera& cam: cameras) {
        mcCams[index] = cam.getLuaRefConnection();
        ++index;
    }

    LuaRef mc(m_lua, "mc");
    mc["cams"] = mcCams;
}

bool ChdkPtpManager::multicamCmdWait(const QString& cmd)
{
    // Get reference to method "mc.cmdwait"
    LuaRef mc(m_lua, "mc");

    LuaRef cmdWait = mc.get<LuaRef>("cmdwait");

    bool resBool;
    LuaRef resState;
    std::tie(resBool, resState) = cmdWait.call<std::tuple<bool, LuaRef>>(mc, cmd.toStdString());

    if (!resBool) {
        std::cerr << "mc:cmdwait() failed for argument: " << cmd.toStdString() << std::endl;
        return false;
    }

    qDebug() << resState.typeName();

    if (resState.isTable()) {
        //TODO: parse results
    }

    return true;
}

//bool ChdkPtpManager::multicamCmdWait(const std::string &cmd)
//{
//    return multicamCmdWait(QString::fromStdString(cmd));
//}

bool ChdkPtpManager::multicamCmd(QString const& cmd)
{
    LuaRef mc(m_lua, "mc");
    LuaRef cmdMethod = mc.get<LuaRef>("cmd");

    bool resBool;
    LuaRef resState;
    std::tie(resBool, resState) = cmdMethod.call<std::tuple<bool, LuaRef>>(mc, cmd.toStdString());

    if (!resBool) {
        qDebug() << QString::fromStdString("mc:cmd failed with argument: ") << cmd;
        return false;
    }

    return true;
}


void ChdkPtpManager::delay()
{
    qDebug() << "delay start";
    if (m_settings.delay > 0) {
        sleep(m_delay);
    }
    qDebug() << "delay end";
}


bool ChdkPtpManager::reconnectToCameras()
{
    size_t camerasCount = m_cameras.size();
    m_cameras.clear();

    qDebug() << "Try reconnect to cameras";

    int i = 60;
    while (m_cameras.size() != camerasCount && i > 0) {
        sleep(1);
        listCameras();
        --i;
        qDebug() << QString("%1...").arg(i);
    }

    if (m_cameras.empty()) {
        qDebug() << "Couldn't find any camera";
        return false;
    }

    qDebug() << "Cameras has been found. Total: " << m_cameras.size();
    return true;
}

void ChdkPtpManager::configureCameras()
{
    configureFlash();
    return;

    // Manual mode (MODE_M = 5, MODE_P = 2)
    execLuaString(QString("return mc:cmdwait('call set_capture_mode(%1);')").arg(5).toStdString().c_str());

    multicamCmdWait(QString("call set_zoom(%1);").arg(20));//23

    // turn off flash
    multicamCmdWait(QString("call set_prop(143, 1);"));

    //     multicamCmdWait(QString("call set_prop(49, -32764);"));
    //     multicamCmdWait(QString("call set_prop(50, -32764);"));
    //     multicamCmdWait(QString("call set_prop(61, 3841);"));
    //     multicamCmdWait(QString("call set_prop(157, 2);"));
    //     multicamCmdWait(QString("call set_prop(254, 20);")); // focus (was: 15)
    //     multicamCmdWait(QString("call set_prop(271, 4);"));
    //     multicamCmdWait(QString("call set_prop(295, 0);"));
    //     multicamCmdWait(QString("call set_prop(317, 0);"));

    // This actually sets ISO speed
    multicamCmdWait(QString("call set_prop(149, 100);"));


    m_manualFocus = false;
    //     m_manualFocusValue = 900;

    if (m_manualFocus)
        multicamCmdWait(QString("call set_prop(12, 0);"));

    //     multicamCmdWait(QString("call set_prop(298, 0);"));


    //     multicamCmdWait(QString("call press('shoot_half');"));
    //     usleep(2 * 1000 * 1000); // wait for focus attempt to complete, TBD: use get_focus_ok() to know for sure
    //     multicamCmdWait(QString("call click('left');"));
    //     usleep(100 * 1000);
    //     multicamCmdWait(QString("call press('shoot_half');"));
    //     usleep(100 * 1000);

    // Disable ND filter
    // 0 = auto; 1 = filter in; 2 = filter out
    multicamCmdWait(QString("call set_nd_filter(2);"));

    // Try to set manual focus; this does not work on PowerShot A1400 for a yet unknown reason
    //     // TBD: use "get_sd_over_modes()" to determine whether we need to call set_aflock() or set_mf()
    execLuaString(QString("return mc:cmdwait('call set_aflock(%1);')").arg(m_manualFocus ? 1 : 0).toStdString().c_str());

    multicamCmdWait(QString("call set_prop(11, %1);").arg(m_manualFocus ? 1 : 0)); // set_prop(props.AF_LOCK,1)

    //     // Set focus distance in mm
    if (m_manualFocus) {
        // 1000 -> 104
        // 900 -> 94
        // 1140 -> 118
        execLuaString(QString("return mc:cmdwait('call set_focus(%1);')").arg(m_manualFocusValue).toStdString().c_str());

        sleep(1);
    }

    //     multicamCmdWait(QString("call set_mf(1);")); // set_mf is not available in CHDK for A1400

    // 0.33   32 (  32)   1/1.26  0.793700526
    // 4.00  384 ( 384)  1/16.00  0.062500000
    // 5.33  512 ( 512)  1/40.32  0.024803141
    // 6.00  576 ( 576)  1/64.00  0.015625000
    // 8.00  768 ( 768) 1/256.00  0.003906250

    //     multicamCmdWait(QString("call set_tv96_direct(%1);").arg(m_tv96));
    multicamCmdWait(QString("call set_tv96_direct(%1);").arg(512));

    //     multicamCmdWait(QString("call set_tv96(%1);").arg(m_tv96));
    //     multicamCmdWait(QString("call set_user_tv96(%1);").arg(m_tv96));

    // 3.0 -> 5.6mm
    // 50.0 -> 18.7mm
    // 23.0 -> 9.9mm
    // 15.0 -> 8.0mm
    // 20.0 -> 9.2mm
    //     multicamCmdWait(QString("call set_zoom(%1);").arg(23));

    // ISO
    //  4.00  384 ( 384)    50.00
    //  5.00  480 ( 480)   100.00
    //  6.00  576 ( 576)   200.00
    // 10.00  960 ( 960)  3200.00

    //     multicamCmdWait(QString("call set_sv96(%1);").arg(m_sv96));
    //     multicamCmdWait(QString("call set_iso_mode(%1);").arg(100));

    // manual focus
    // // //     multicamCmdWait(QString("call set_aflock(%1);").arg(1));
    //     multicamCmdWait(QString("call call_event_proc('SS.MFOn');"));

    // // //     multicamCmdWait(QString("call set_prop(6, 4);"));

    // set_focus(100) -> 18 (units?)
    // set_focus(500) -> 52 (units?)
    // set_focus(800) -> 84 (units?)
    // // //     multicamCmdWait(QString("call set_focus(%1);").arg(800));
}






void ChdkPtpManager::setMulticamFocus(int focusValue)
{
    multicamCmdWait(QString("call set_focus(%1)").arg(focusValue));
}

void ChdkPtpManager::setFocus(int focusValue)
{
    for (auto& camera: m_cameras) {
        camera.configureFocus(focusValue);
    }
}

//maybe add to multicam.cmds.shootremote 'play()' and 'exit'
void ChdkPtpManager::shootAfterUsbDisconnect()
{}

void ChdkPtpManager::startSelectedCameraShooting()
{
    qDebug() << "selected cameras shooting";
}

void ChdkPtpManager::setCamerasProperty(QString const& propName, int propValue)
{
    for (auto& camera: m_cameras) {
        camera.setPropValue(propName, propValue);
    }
}

void ChdkPtpManager::setTv96(int tv96)
{
    m_tv96 = tv96;
}

void ChdkPtpManager::setAv96(int av96)
{
    m_av96 = av96;
}

void ChdkPtpManager::setSv96(int sv96)
{
    m_sv96 = sv96;
}

void ChdkPtpManager::setDelay(int delay)
{
    m_delay = delay;
}

void ChdkPtpManager::startDiagnose()
{
    QMutexLocker locker(&m_mutex);

    for (Camera& cam : m_cameras) {
        //         if (cam.querySerialNumber() != QString("63837765ED604B39BEC7A4E198C06001"))
        //             continue;

        //qDebug() << cam.querySerialNumber();

        //         for (int reg = 0; reg <= 349; ++reg)
        //             qDebug() << "[" << reg << "] = " << cam.queryProp(reg);

        int reg;

        reg = 12;
        qDebug() << "[" << reg << "] = " << cam.queryProp(reg);
        reg = 49;
        qDebug() << "[" << reg << "] = " << cam.queryProp(reg);
        reg = 50;
        qDebug() << "[" << reg << "] = " << cam.queryProp(reg);
        reg = 61;
        qDebug() << "[" << reg << "] = " << cam.queryProp(reg);
        reg = 105;
        qDebug() << "[" << reg << "] = " << cam.queryProp(reg);
        reg = 143;
        qDebug() << "[" << reg << "] = " << cam.queryProp(reg);
        reg = 149;
        qDebug() << "[" << reg << "] = " << cam.queryProp(reg);
        reg = 157;
        qDebug() << "[" << reg << "] = " << cam.queryProp(reg);
        reg = 219;
        qDebug() << "[" << reg << "] = " << cam.queryProp(reg);
        reg = 254;
        qDebug() << "[" << reg << "] = " << cam.queryProp(reg);
        reg = 271;
        qDebug() << "[" << reg << "] = " << cam.queryProp(reg);
        reg = 295;
        qDebug() << "[" << reg << "] = " << cam.queryProp(reg);
        reg = 298;
        qDebug() << "[" << reg << "] = " << cam.queryProp(reg);
        reg = 317;
        qDebug() << "[" << reg << "] = " << cam.queryProp(reg);
    }
}

void ChdkPtpManager::highlightCamera(int cameraIndex)
{
    m_cameras[cameraIndex].hightlightCamera();
}

void ChdkPtpManager::shutdownAll()
{
    QMutexLocker locker(&m_mutex);

    for (Camera& cam : m_cameras)
        cam.shutDown();
}

void ChdkPtpManager::startConfigureStaticProps()
{
    for (Camera& cam : m_cameras)
        cam.configureStaticProps();
}

void ChdkPtpManager::multicamExecWait(CameraList& cameras, QString const& cmd)
{
    for (Camera& cam: cameras) {
        qDebug() << "execWait for " << cam.toString();
        cam.execWait(cmd);
    }
}

void ChdkPtpManager::runCustomScript()
{
    static const QString A1400_TESTCAMERA_SERIAL = "C14D00A48868475CBFF4189B5377D0BE";
    static const QString A3300_TESTCAMERA_SERIAL = "BAFA22A11DD74AC7B55C04DCFF971CC1";
    static const QString SX150_TESTCAMERA_SERIAL = "407EA869E8A44FC896DCB04EBCED1D66";

    CameraList testCameras;
    for (Camera& cam: m_cameras) {
        if (cam.serial() == A1400_TESTCAMERA_SERIAL
                || cam.serial() == A3300_TESTCAMERA_SERIAL
                || cam.serial() == SX150_TESTCAMERA_SERIAL) {
            testCameras.append(cam);
        }
    }

    qDebug() << "amount of active cameras: " << testCameras.size();

    //multicamExecWait(testCameras, "set_prop(143, 1)");

    //    populateMcCams(testCameras);
    //    sleep(3);
    //    execLuaString("mc:start()");
    //    sleep(3);

    //    multicamCmdWait("rec");
    //    sleep(3);
    //    execLuaString("mc:cmdwait('exit')");

    multicamExecWait(testCameras, "switch_mode_usb(1)");
    multicamExecWait(testCameras, "set_prop(143, 1)");



    //multicamCmdWait("call set_prop(143,1);");
    populateMcCams(testCameras);
    sleep(3);
    execLuaString("mc:start()");
    multicamCmdWait("preshoot");
    //sleep(3);
    multicamCmdWait("shoot");
    sleep(5);
    multicamCmdWait("play");
    sleep(3);
    execLuaString("mc:cmd('exit')");

}

void ChdkPtpManager::setFlashMode(bool mode)
{
    m_flash = mode;
}

void ChdkPtpManager::setPreshootMode(bool mode)
{
    m_preshoot = mode;
}
