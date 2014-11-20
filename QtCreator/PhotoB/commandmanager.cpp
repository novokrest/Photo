#include "commandmanager.h"
#include <ostream>


CommandManager::CommandManager()
{
    CommandMap commonCommands;
    createCommonCommands(commonCommands);

    CommandMap commandsA1400;
    createCommandsA1400(commandsA1400);

    CommandMap commandsSX150;
    createCommandsSX150(commandsSX150);

    commands_[CANON_PS_A1400] = commandsA1400;
    commands_[CANON_PS_SX150_IS] = commandsSX150;
}

void CommandManager::createCommandsA1400(CommandMap& commandsA1400)
{
    commandsA1400[FLASH_MODE_ON];
    commandsA1400[FLASH_MODE_OFF];
    commandsA1400[FLASH_MODE_AUTO];
    commandsA1400[MANUAL_FOCUS_MODE];
    commandsA1400[AUTO_FOCUS_MODE];
//    commandsA1400[FOCUS_VALUE];
//    commandsA1400[ZOOM_VALUE];
//    commandsA1400[AV_VALUE];
//    commandsA1400[TV_VALUE];
//    commandsA1400[ISO_VALUE];
}

void CommandManager::createCommandsSX150(CommandMap& commandsSX150)
{
    commandsSX150[FLASH_MODE_ON] = "set_prop(143, 1)";
    commandsSX150[FLASH_MODE_OFF] = "set_prop(143, 2)";
    commandsSX150[FLASH_MODE_AUTO] = "set_prop(143, 0)";
    commandsSX150[GET_FLASH_MODE] = "return get_prop(143)";

    commandsSX150[MANUAL_FOCUS_MODE] = "post_levent_for_npt('PressSw1AndMF')";
    commandsSX150[AUTO_FOCUS_MODE] = "post_levent_for_npt('PressSw1AndMF')";
//    commandsSX150[FOCUS_VALUE] = "set_focus(<value>)";
//    commandsSX150[ZOOM_VALUE] = ;
//    commandsSX150[AV_VALUE];
//    commandsSX150[TV_VALUE];
//    commandsSX150[ISO_VALUE];
}

CommandManager::CommandManager(const string& configPath)
{
    parseConfig(configPath);
}

bool CommandManager::parseConfig(const string& configPath)
{
    return false;
}

string CommandManager::commandForSingle(CameraModel model, CommandType commandType)
{
    string command = commands_[model][commandType];

    return command;
}

string CommandManager::commandForMulticam(CameraModel model, CommandType commandType)
{
    string command = "call ";
    command += commandForSingle(model, commandType);

    return command;
}
