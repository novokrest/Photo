#include "utils.h"
#include <sstream>

using std::stringstream;

static void luaTableToString(LuaRef table, stringstream& out, string indent = "");


string luaRefToString(LuaRef luaObj)
{
    stringstream out;

    if (luaObj.isTable()) {
        luaTableToString(luaObj, out);
    }

    return out.str();
}

static void luaTableToString(LuaRef table, stringstream& out, string indent)
{
    out << indent << "{\n";

    for (auto& it: table) {
        out << indent;

        string key = it.key<string>();
        out << key << " = ";

        LuaRef value = it.value<LuaRef>();
        if (value.isTable()) {
            out << "\n";
            luaTableToString(table, out, indent + "\t");
        }
        else {
            out << value.toValue<string>() << "\n";
        }
    }

    out << indent << "}\n";
}
