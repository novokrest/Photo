#ifndef SCRIPTLOADER_H
#define SCRIPTLOADER_H

#include <map>

using std::string;

namespace photobooth {

#define FOR_SCRIPTS(DO) \
    DO(MULTICAM_START, multicam_start.script) \
    DO(REC, rec.script) \
    DO(SHOOT, shoot.script) \
    DO(PLAY, play.script) \
    DO(DOWNLOAD, download.script) \
    DO(LISTDIR, listdir.script) \
    DO(DELETE_PHOTOS, delete_photos.script)

enum Script
{
#define ENUM_SCRIPT(name, path) SCRIPT_##name,
    FOR_SCRIPTS(ENUM_SCRIPT)
#undef ENUM_SCRIPT
    NO_SCRIPT
};


class ScriptLoader
{
    typedef std::map<Script, string> ScriptMap;
    ScriptMap scripts_;

    void load(const string& path, Script key);

public:
    ScriptLoader(const string& dirpath);
    const string& get(Script script);
};

}

#endif // SCRIPTLOADER_H
