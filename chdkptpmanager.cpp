#include "chdkptpmanager.h"

#include <LuaIntf/LuaIntf.h>

#include <stdexcept>

#include <iostream> // for debugging

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
    LuaIntf::LuaRef mcCams(m_lua, "mc.cams");

    // Traverse the table of cameras
    for (auto& e : mcCams) {
        CameraInfo cam;

        cam.index = e.key<int>();

        // Access mc.cams[i].ptpdev
        LuaIntf::LuaRef value = e.value<LuaIntf::LuaRef>();
        LuaIntf::LuaRef ptpdev = value["ptpdev"];
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

    // Get list of files and figure out the latest file written:
    // con:listdir(path,{stat='*'})

    // Download file:
    // con:download_pcall(remotepath,filedlg.value)
}
