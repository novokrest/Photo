#include "scriptloader.h"
#include <fstream>
#include <iostream>

namespace photobooth {

ScriptLoader::ScriptLoader(const string &dirpath)
{
    string path;

#define LOAD_SCRIPT(key, file) \
    path = dirpath + #file; \
    load(path, SCRIPT_##key); \
    \

    FOR_SCRIPTS(LOAD_SCRIPT)
#undef LOAD_SCRIPT
}

void ScriptLoader::load(const string& path, Script key)
{
    std::ifstream fin(path);
    if (fin.is_open()) {
        string script((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
        scripts_[key] = script;
    }
}

const string& ScriptLoader::get(Script script)
{
    return scripts_[script];
}

}
