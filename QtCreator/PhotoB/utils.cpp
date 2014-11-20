#include "utils.h"
#include <sstream>
#include <QtCore/QDebug>

using std::string;
using std::stringstream;

static void luaTableToString(LuaRef table, stringstream& out, string indent = "");

void printCountdown(int count) {
    assert(count > 0);

    int i = count;
    while (i > 0) {
        sleep(1);
        --i;
        qDebug() << QString("%1...").arg(i);
    }
}

void printKeys(LuaRef const & table, string indent)
{
    for (auto& e: table) {
        std::string key = e.key<std::string>();
        qDebug() << indent.c_str() << key.c_str();
        LuaRef value = e.value<LuaRef>();
        if (value.isTable()) {
            printKeys(value, indent + "\t");
        }
    }
}

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
