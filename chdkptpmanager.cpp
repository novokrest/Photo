#include "chdkptpmanager.h"
#include "camera.h"

#include <LuaIntf/LuaIntf.h>

#include <QtConcurrent/QtConcurrent>
#include <QDir>
#include <QDebug>

#include <stdexcept>

#include <sstream>
#include <iostream> // for debugging
#include <unistd.h>

using namespace LuaIntf;

ChdkPtpManager::ChdkPtpManager()
{
    QMutexLocker locker(&m_mutex);

    // Pass "argc" and "argv" for empty command line
    m_lua = chdkptp_init(0, NULL);

    execLuaString("package.path = package.path .. ';/home/aspotashev/chdkptp/lua/?.lua'");
//  execLuaString("require('main')");

    execLuaString("util = require('util')");
    execLuaString("util:import()");
    execLuaString("chdku = require('chdku')");
    execLuaString("prefs = require('prefs')");
    execLuaString("cli = require('cli')");

    // Are these optional?
    execLuaString("ustime = require('ustime')");
    execLuaString("errutil = require('errutil')");
    execLuaString("con = chdku.connection()");

    execLuaString("mc = require('multicam')");

//     int top = lua_gettop(L);
//     luaL_loadstring(L, "return 3, 4, 5");
//     int R = lua_pcall(L, 0, LUA_MULTRET, 0);
//     int nresults = lua_gettop(L) - top;
//
//     execLuaString("cli:run()");

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

// con=chdku.connection()
// dngcli.init_cli()

}

ChdkPtpManager::~ChdkPtpManager()
{
    chdkptp_exit(m_lua);
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

CameraList ChdkPtpManager::listCameras()
{
    QMutexLocker locker(&m_mutex);

    CameraList cameras;

    LuaRef mcCams(m_lua, "mc.cams");
    mcCams = LuaRef::createTable(m_lua);

    // Set up shooting parameters
    LuaRef listUsbDevices(m_lua, "chdk.list_usb_devices");
    LuaRef devices = listUsbDevices.call<LuaRef>();

    int index = 0;
    for (auto& devinfo : devices) {
        LuaRef dev = devinfo.value<LuaRef>();
        mcCams[index] = dev;

        Camera c = Camera::fromLuaRef(dev);
        c.setChdkPtpManager(this);
        c.setIndex(index);
        cameras.append(c);

        index++;

//         std::cout << "    dev = " << c.dev().toStdString() << std::endl;
//         std::cout << "    bus = " << c.bus().toStdString() << std::endl;
//         std::cout << "    product_id = " << c.productId() << std::endl;
//         std::cout << "    vendor_id = " << c.vendorId() << std::endl;
//   dev="087",
//   bus="002",
//   product_id=12900,
//   vendor_id=1193,
    }

    return cameras;

//     execLuaString("mc:connect()");
// 
//     LuaRef mcCams(m_lua, "mc.cams");
// 
//     // Traverse the table of cameras
//     for (auto& e : mcCams) {
//         CameraInfo cam;
// 
//         cam.index = e.key<int>();
// 
//         // Access mc.cams[i].ptpdev
//         LuaRef value = e.value<LuaRef>();
//         LuaRef ptpdev = value["ptpdev"];
//         cam.serialNumber = QString::fromStdString(ptpdev.get<std::string>("serial_number"));
// 
//         cameras.append(cam);
//     }
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

    if (resState.isTable()) {
        // TBD: parse table
    }

    return true;
}

QString ChdkPtpManager::getProp(LuaRef& lcon, int index)
{
    // !return con:execwait("return get_prop(500)")
    // get_config_value(226)

    std::stringstream command;
    command << "return get_prop(" << index << ")";

    // Get reference to method "lcon.execwait"
    LuaRef execWait = lcon.get<LuaRef>("execwait");
    LuaRef result = execWait.call<LuaRef>(lcon, command.str());

    return QString("%1").arg(result.toValue<int>());
}

void ChdkPtpManager::startShooting()
{
    QMutexLocker locker(&m_mutex);

    // Set up shooting parameters
    LuaRef listUsbDevices(m_lua, "chdk.list_usb_devices");
    LuaRef devices = listUsbDevices.call<LuaRef>();
    for (auto& devinfo : devices) {
        // lcon = chdku.connection(devinfo)
        LuaRef chdkuConnection(m_lua, "chdku.connection");
        LuaRef lcon = chdkuConnection.call<LuaRef>(devinfo.value<LuaRef>());


        LuaRef isConnected = lcon.get<LuaRef>("is_connected");
        if (isConnected.call<bool>(lcon)) {
            std::cout << "already connected" << std::endl;
        }
        else {
            // lcon:connect()
            // This is a member function call, therefore we have to pass "lcon" as 1st argument.
            LuaRef lconConnect = lcon.get<LuaRef>("connect");
            lconConnect(lcon);

            std::cout << "is_connected = " << isConnected.call<bool>(lcon) << std::endl;
        }

        // This delay is necessary: the con:listdir() method hangs otherwise.
        //
        // The source of the problem may be that con:listdir() is too close
        // in time to chdku.connection().
        // See implementation of chdk_connection() in "chdkptp/chdkptp.cpp".
        usleep(30000);

        std::cerr << getProp(lcon, 133).toStdString() << std::endl;
    }

    // Perform standard command sequence according to the header in chdkptp/lua/multicam.lua

    // TBD: get a fresh list of cameras right after this "mc:connect()" call
    // to assiciate photos with cameras (and their serial numbers).
    execLuaString("mc:connect()");

    execLuaString("mc:start()");

    multicamCmdWait("rec"); // TBD: check return value from each mc:cmdwait(...) call

    // Manual mode (MODE_M = 5, MODE_P = 2)
//     execLuaString(QString("return mc:cmdwait('call set_capture_mode(%1);')").arg(5).toStdString().c_str());

    // turn off flash
    multicamCmdWait(QString("call set_prop(143, 2);"));

    // Try to set manual focus; this does not work on PowerShot A1400 for a yet unknown reason
//     // TBD: use "get_sd_over_modes()" to determine whether we need to call set_aflock() or set_mf()
//     execLuaString(QString("return mc:cmdwait('call set_aflock(1);')").toStdString().c_str());
//     // Set focus distance in mm
//     execLuaString(QString("return mc:cmdwait('call set_focus(%1);')").arg(2000).toStdString().c_str());

//     multicamCmdWait("preshoot");

//     multicamCmdWait(QString("call set_mf(1);"));

//     multicamCmdWait(QString("call set_av96_direct(%1);").arg(m_av96));
//     multicamCmdWait(QString("call set_av96_direct(%1);").arg(576)); // 6.00  576 ( 576) f/8.0
//     multicamCmdWait(QString("call set_user_av96(%1);").arg(576)); // 6.00  576 ( 576) f/8.0
//     multicamCmdWait(QString("call set_av96(%1);").arg(576)); // 6.00  576 ( 576) f/8.0

    // 0.33   32 (  32)   1/1.26  0.793700526
    // 4.00  384 ( 384)  1/16.00  0.062500000
    // 8.00  768 ( 768) 1/256.00  0.003906250

//     multicamCmdWait(QString("call set_tv96_direct(%1);").arg(m_tv96));

//     multicamCmdWait(QString("call set_tv96(%1);").arg(m_tv96));
//     multicamCmdWait(QString("call set_user_tv96(%1);").arg(m_tv96));

    // 3.0 -> 5.6mm
    // 50.0 -> 18.7mm
    // 23.0 -> 9.9mm
    // 15.0 -> 8.0mm
    // 20.0 -> 9.2mm
    multicamCmdWait(QString("call set_zoom(%1);").arg(23));

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

    multicamCmdWait("preshoot");

//     execLuaString("return mc:cmdwait('shoot')");
    multicamCmdWait("shoot");

    double timeSec = pow(2, static_cast<double>(m_tv96) / (-96.0));
    sleep(5 + static_cast<int>(ceil(timeSec)));

    multicamCmdWait("play");

    execLuaString("mc:cmd('exit')");

//     QtConcurrent::run(this, &ChdkPtpManager::startDownloadRecent);
    startDownloadRecent();
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

    QString latestDirPath = QString("%1/%2").arg(dcimPath).arg(dcim[0].name);
    QList<RemoteInode> files = listRemoteDir(lcon, latestDirPath);
    qSort(files.begin(), files.end(), [](const RemoteInode& a, const RemoteInode& b) -> bool {
        return a.name > b.name;
    });

    auto firstJPG = std::find_if(files.begin(), files.end(), [](const RemoteInode& f) -> bool {
        return f.name.endsWith(QLatin1String(".JPG"));
    });

    if (firstJPG == files.end())
        return QString();
    else
        return QString("%1/%2").arg(latestDirPath).arg(firstJPG->name);
}

void ChdkPtpManager::startDownloadRecent()
{
//     QMutexLocker locker(&m_mutex);

    // Get list of files and figure out the latest file written:
    // con:listdir(path,{stat='*'})
    //
    // Example:
    // con> !return con:listdir('A/DCIM', {stat='*'})
    // ={
    //  [1]={
    //   is_file=false,
    //   ctime=1402844676,
    //   name="100___06",
    //   mtime=1402844676,
    //   attrib=16,
    //   size=0,
    //   is_dir=true,
    //  },
    //  [2]={
    //   is_file=false,
    //   ctime=315532814,
    //   name="101___01",
    //   mtime=315532814,
    //   attrib=16,
    //   size=0,
    //   is_dir=true,
    //  },
    // }
    // con 3>
    //
    // How to call member functions (thiscall):
    //   http://lua-users.org/lists/lua-l/2006-08/msg00269.html

    // Prepare directory for saving the photos
    QDir dir = QDir::home();
    std::cout << "QDir::home() = " << dir.absolutePath().toStdString() << " ; QDir::exists() = " << dir.exists() << std::endl;
    QString subdirName = QString("photobooth_%1_tv_%2").arg(QTime::currentTime().toString().replace(':', '-')).arg(m_tv96);
    qDebug() << dir.mkdir(subdirName);
    std::cout << "subdirName = " << subdirName.toStdString() << std::endl;
    QString destPath = dir.filePath(subdirName);

    // Enumerate devices and do stuff with each of them.
    // See also implementation of the "connect" command in "chdkptp/lua/cli.lua".
    LuaRef listUsbDevices(m_lua, "chdk.list_usb_devices");
    LuaRef devices = listUsbDevices.call<LuaRef>();
    for (auto& devinfo : devices) {
        // lcon = chdku.connection(devinfo)
        LuaRef chdkuConnection(m_lua, "chdku.connection");
        LuaRef lcon = chdkuConnection.call<LuaRef>(devinfo.value<LuaRef>());


        LuaRef isConnected = lcon.get<LuaRef>("is_connected");
        if (isConnected.call<bool>(lcon)) {
            std::cout << "already connected" << std::endl;
        }
        else {
            // lcon:connect()
            // This is a member function call, therefore we have to pass "lcon" as 1st argument.
            LuaRef lconConnect = lcon.get<LuaRef>("connect");
            lconConnect(lcon);

            std::cout << "is_connected = " << isConnected.call<bool>(lcon) << std::endl;
        }

        // This delay is necessary: the con:listdir() method hangs otherwise.
        //
        // The source of the problem may be that con:listdir() is too close
        // in time to chdku.connection().
        // See implementation of chdk_connection() in "chdkptp/chdkptp.cpp".
        usleep(30000);

        // Get camera serial number
        lcon.get<LuaRef>("update_connection_info")(lcon);
        QString serialNumber = QString::fromStdString(lcon.get<LuaRef>("ptpdev").get<std::string>("serial_number"));

        QString remoteFile = getLatestPhotoPath(lcon);
        QString localFile = QString("%1/myphoto_ser%2.jpg").arg(destPath).arg(serialNumber);
        std::cout << "downloading from: " << remoteFile.toStdString() << std::endl;
        std::cout << "saving to: " << localFile.toStdString() << std::endl;

        // lcon:download_pcall(source, destination)
        // This is a member function call, therefore we have to pass "lcon" as 1st argument.
        LuaRef downloadPCall = lcon.get<LuaRef>("download_pcall");
        downloadPCall(lcon, remoteFile.toStdString(), localFile.toStdString());
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

void ChdkPtpManager::startDiagnose()
{
    QMutexLocker locker(&m_mutex);

    // Set up shooting parameters
    LuaRef listUsbDevices(m_lua, "chdk.list_usb_devices");
    LuaRef devices = listUsbDevices.call<LuaRef>();
    for (auto& devinfo : devices) {
        std::cout << "=== devinfo dump ===" << std::endl;

        Camera c = Camera::fromLuaRef(devinfo.value<LuaRef>());
        std::cout << "    dev = " << c.dev().toStdString() << std::endl;
        std::cout << "    bus = " << c.bus().toStdString() << std::endl;
        std::cout << "    product_id = " << c.productId() << std::endl;
        std::cout << "    vendor_id = " << c.vendorId() << std::endl;
//   dev="087",
//   bus="002",
//   product_id=12900,
//   vendor_id=1193,


//         // lcon = chdku.connection(devinfo)
//         LuaRef chdkuConnection(m_lua, "chdku.connection");
//         LuaRef lcon = chdkuConnection.call<LuaRef>(devinfo.value<LuaRef>());
// 
// 
//         LuaRef isConnected = lcon.get<LuaRef>("is_connected");
//         if (isConnected.call<bool>(lcon)) {
//             std::cout << "already connected" << std::endl;
//         }
//         else {
//             // lcon:connect()
//             // This is a member function call, therefore we have to pass "lcon" as 1st argument.
//             LuaRef lconConnect = lcon.get<LuaRef>("connect");
//             lconConnect(lcon);
// 
//             std::cout << "is_connected = " << isConnected.call<bool>(lcon) << std::endl;
//         }
// 
//         // This delay is necessary: the con:listdir() method hangs otherwise.
//         //
//         // The source of the problem may be that con:listdir() is too close
//         // in time to chdku.connection().
//         // See implementation of chdk_connection() in "chdkptp/chdkptp.cpp".
//         usleep(30000);
// 
//         std::cerr << getProp(lcon, 133).toStdString() << std::endl;
    }
}

void ChdkPtpManager::highlightCamera(int index)
{
    m_cameras[index].hightlightCamera();
}
