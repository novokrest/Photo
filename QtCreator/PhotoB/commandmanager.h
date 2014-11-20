#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include <cstring>
#include <map>

using std::string;
using std::map;

enum CameraModel
{
    CANON_PS_SX150_IS,
    CANON_PS_A1400
};

enum CommandType
{
    FLASH_MODE_ON
    , FLASH_MODE_OFF
    , FLASH_MODE_AUTO
    , GET_FLASH_MODE

    , MANUAL_FOCUS_MODE
    , AUTO_FOCUS_MODE
    , SET_FOCUS_VALUE
    , GET_FOCUS_MODE
    , GET_FOCUS_STATE
    , GET_FOCUS_OK
    , GET_DOFINFO

    , SET_ZOOM_VALUE
    , GET_ZOOM_VALUE
    , GET_ZOOM_STEPS

    , SET_AV_VALUE
    , GET_AV_VALUE
    , SET_TV_VALUE
    , GET_TV_VALUE
    , SET_ISO_VALUE
    , GET_ISO_VALUE
};

//TODO: Initialization via config file
class CommandManager
{
    typedef map<CommandType, string> CommandMap;
    typedef map<CameraModel, CommandMap> CameraCommandMap;

    CameraCommandMap commands_;

    bool parseConfig(const string& configPath);

    void createCommandsA1400(CommandMap& commandsA1400);
    void createCommandsSX150(CommandMap& commandsSX150);

public:
    CommandManager();
    CommandManager(const string& configPath);

    string commandForSingle(CameraModel model, CommandType commandType);
    string commandForMulticam(CameraModel model, CommandType commandType);
};

#endif // COMMANDMANAGER_H
