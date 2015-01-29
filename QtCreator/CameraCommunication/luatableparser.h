#ifndef LUATABLEPARSER_H
#define LUATABLEPARSER_H

/**
{
  [1]={is_file=false,mtime=315533800,name="100___01",ctime=315533800,attrib=16,is_dir=true,size=0,}
, [2]={is_file=false,mtime=315533808,name="CANONMSC",ctime=315533808,attrib=16,is_dir=true,size=0,}
,
}

*/

#include "common.h"
#include "remoteinode.h"

class LuaTableValue
{
public:
    virtual bool isString() = 0;
    virtual bool isTable() = 0;
    virtual void print() = 0;
};

class StringValue : public LuaTableValue
{
    string value_;

public:
    StringValue(string const& value)
        : value_(value)
    {}

    bool isString() override {
        return true;
    }

    bool isTable() override {
        return false;
    }

    string& value() {
        return value_;
    }

    void print() override {
        cout << value_ << endl;
    }
};

class LuaTable : public LuaTableValue
{
    map<string, LuaTableValue*> elements_;

public:
    bool isString() override {
        return false;
    }

    bool isTable() override {
        return true;
    }

    void add(string const& key, LuaTableValue* value) {
        elements_.insert(std::pair<string, LuaTableValue*>(key, value));
    }

    bool hasKey(string const& key) {
        return elements_.find(key) != elements_.end();
    }

    /**
     * TODO: Implement this
    */
    LuaTableValue* get(string const& key) {
        return NULL;
    }

    void print() override;

    void getRemoteInodes(vector<RemoteInode>& nodes);
    bool toRemoteInode(RemoteInode& inode);
};


class LuaTableParser
{
    char last_;

    bool parseString(stringstream& ss, string& str, char stop);
    bool parseKey(stringstream& ss, string& key);
    bool parseValue(stringstream& ss, LuaTableValue** value);
    bool parseElement(stringstream&ss, LuaTable& table);
    bool parseTable(stringstream& ss, LuaTable& table);

public:
    bool parse(string const& strTable, LuaTable& luaTable);
};

#endif // LUATABLEPARSER_H
