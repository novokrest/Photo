#include "chdkptpmanager.h"

#include <LuaIntf/LuaIntf.h>

#include <QtConcurrent/QtConcurrent>

#include <stdexcept>

#include <iostream> // for debugging
#include <unistd.h>

using namespace LuaIntf;

ChdkPtpManager::ChdkPtpManager()
{
    QMutexLocker locker(&m_mutex);

    // Pass "argc" and "argv" for empty command line
    m_lua = chdkptp_init(0, NULL);

    execLuaString("package.path = package.path .. ';/home/aspotashev/work/rt00049-canon-a1400/chdkptp/lua/?.lua'");
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

void ChdkPtpManager::startQueryCameras()
{
    QMutexLocker locker(&m_mutex);

    execLuaString("mc:connect()");

    CameraInfoList cameras;
    LuaRef mcCams(m_lua, "mc.cams");

    // Traverse the table of cameras
    for (auto& e : mcCams) {
        CameraInfo cam;

        cam.index = e.key<int>();

        // Access mc.cams[i].ptpdev
        LuaRef value = e.value<LuaRef>();
        LuaRef ptpdev = value["ptpdev"];
        cam.serialNumber = QString::fromStdString(ptpdev.get<std::string>("serial_number"));

        cameras.append(cam);
    }

    emit queryCamerasReady(cameras);
}

void ChdkPtpManager::startShooting()
{
    QMutexLocker locker(&m_mutex);

    // Perform standard command sequence according to the header in chdkptp/lua/multicam.lua

    // TBD: get a fresh list of cameras right after this "mc:connect()" call
    // to assiciate photos with cameras (and their serial numbers).
    execLuaString("mc:connect()");

    execLuaString("mc:start()");
    execLuaString("return mc:cmdwait('rec')");
    execLuaString("return mc:cmdwait('preshoot')");
    execLuaString("return mc:cmdwait('shoot')");
    execLuaString("return mc:cmdwait('play')");
    execLuaString("mc:cmd('exit')");

    QtConcurrent::run(this, &ChdkPtpManager::startDownloadRecent);
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

    return QString("%1/%2").arg(latestDirPath).arg(files[0].name);
}

void ChdkPtpManager::startDownloadRecent()
{
    QMutexLocker locker(&m_mutex);

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
        sleep(1);

        QString remotePath = getLatestPhotoPath(lcon);
        std::cout << "downloading from: " << remotePath.toStdString() << std::endl;

        // Get camera serial number
        lcon.get<LuaRef>("update_connection_info")(lcon);
        QString serialNumber = QString::fromStdString(lcon.get<LuaRef>("ptpdev").get<std::string>("serial_number"));

        // lcon:download_pcall(source, destination)
        // This is a member function call, therefore we have to pass "lcon" as 1st argument.
        LuaRef downloadPCall = lcon.get<LuaRef>("download_pcall");
        downloadPCall(lcon, remotePath.toStdString(), QString("/tmp/myphoto_ser%1.jpeg").arg(serialNumber).toStdString());
    }
}
