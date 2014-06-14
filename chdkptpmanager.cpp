#include "chdkptpmanager.h"

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

    CameraInfoList cameras;

    execLuaString("mc:connect()");

    lua_getglobal(m_lua, "mc");
    lua_pushstring(m_lua, "cams");
    lua_gettable(m_lua, -2);

    if (!lua_istable(m_lua, -1))
        throw std::runtime_error("'mc.cams' was expected to be a table");

    // Traverse the table of cameras
    // http://lua-users.org/lists/lua-l/2004-04/msg00201.html
    lua_pushnil(m_lua);

    std::cout << "gettop: " << lua_gettop(m_lua) << std::endl;

    while (lua_next(m_lua, -2) != 0) {
        CameraInfo cam;

        if (!lua_isnumber(m_lua, -2))
            throw std::runtime_error("Keys in 'mc.cams' should be integer numbers");

        cam.index = lua_tointeger(m_lua, -2);

        if (!lua_istable(m_lua, -1))
            throw std::runtime_error("Values in 'mc.cams' should be tables");

        // Access mc.cams[i].ptpdev
        lua_pushstring(m_lua, "ptpdev");
        lua_gettable(m_lua, -2);

        if (!lua_istable(m_lua, -1))
            throw std::runtime_error("mc.cams[i].ptpdev should be tables");

        // Access mc.cams[i].ptpdev
        lua_pushstring(m_lua, "serial_number");
        lua_gettable(m_lua, -2);

        if (!lua_isstring(m_lua, -1))
            throw std::runtime_error("serial_number should be a string");

        cam.serialNumber = QString(lua_tostring(m_lua, -1));

        lua_pop(m_lua, 3);

        std::cout << "gettop: " << lua_gettop(m_lua) << std::endl;

        cameras.append(cam);
    }

    lua_pop(m_lua, 2);

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
