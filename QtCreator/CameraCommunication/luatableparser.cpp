#include "luatableparser.h"
#include "cameracommunication_utils.h"

static const char TABLE_START = '{';
static const char TABLE_END = '}';
static const char KEY_VALUE_DELIMITER = '=';
static const char ELEMENTS_DELIMITER = ',';

void LuaTable::print()
{
    cout << TABLE_START << endl;

    for (map<string, LuaTableValue*>::const_iterator elemIt = elements_.begin(); elemIt != elements_.end(); ++elemIt) {
        cout << elemIt->first << KEY_VALUE_DELIMITER;
        elemIt->second->print();
        cout << ELEMENTS_DELIMITER << endl;
    }

    cout << TABLE_END << endl;
}

void LuaTable::getRemoteInodes(vector<RemoteInode> &nodes)
{
    for (map<string, LuaTableValue*>::const_iterator elemIt = elements_.begin(); elemIt != elements_.end(); ++elemIt) {
        if (elemIt->second->isTable()) {
            LuaTable* table = dynamic_cast<LuaTable*>(elemIt->second);
            RemoteInode inode;
            if (table->toRemoteInode(inode)) {
                nodes.push_back(inode);
            }
        }
    }
}

bool LuaTable::toRemoteInode(RemoteInode& inode)
{
    map<string, LuaTableValue*>::iterator it;

    it = elements_.find("is_file");
    if (it == elements_.end()) {
        return false;
    }
    inode.is_file = stringToBool(dynamic_cast<StringValue*>(it->second)->value());

    it = elements_.find("is_dir");
    if (it == elements_.end()) {
        return false;
    }
    inode.is_dir = stringToBool(dynamic_cast<StringValue*>(it->second)->value());

    it = elements_.find("name");
    if (it == elements_.end()) {
        return false;
    }
    inode.name = dynamic_cast<StringValue*>(it->second)->value();

    it = elements_.find("size");
    if (it == elements_.end()) {
        return false;
    }
    inode.size = atoi(dynamic_cast<StringValue*>(it->second)->value().c_str());

    return true;
}

bool LuaTableParser::parse(const string &strTable, LuaTable& luaTable)
{
    if (strTable.size() == 0) {
        return false;
    }
    stringstream ss(strTable);
    ss >> last_;
    parseTable(ss, luaTable);

    return true;
}

bool LuaTableParser::parseTable(stringstream &ss, LuaTable& luaTable)
{
    if (last_ != TABLE_START) {
        throw std::runtime_error("Unable to parse table: expected ='{', actual = '" + to_string(last_) + "'");
    }
    ss >> last_;
    while (last_ != TABLE_END) {
        parseElement(ss, luaTable);
        ss >> last_;
    }
    ss >> last_;

    return true;
}

bool LuaTableParser::parseElement(stringstream& ss, LuaTable& luaTable)
{
    string key;
    LuaTableValue* value = NULL;

    parseKey(ss, key);
    ss >> last_;
    parseValue(ss, &value);
    luaTable.add(key, value);

    return true;
}

bool LuaTableParser::parseKey(stringstream& ss, string& key)
{
    return parseString(ss, key, KEY_VALUE_DELIMITER);
}

bool LuaTableParser::parseValue(stringstream& ss, LuaTableValue** value)
{
    if (last_ == TABLE_START) {
        *value = new LuaTable();
        parseTable(ss, *(dynamic_cast<LuaTable*>(*value)));
    }
    else {
        string str;
        parseString(ss, str, ELEMENTS_DELIMITER);
        *value = new StringValue(str);
    }

    return true;
}

bool LuaTableParser::parseString(stringstream& ss, string& value, char stop)
{
    while (last_ != stop) {
        value += last_;
        ss >> last_;
    }

    if (value.size() > 1 && *value.begin() == '\"' && *(value.end() - 1) == '\"') {
        value = value.substr(1, value.size() - 2);
        //value = std::copy(value.begin() + 1, value.end() - 1);
    }

    return true;
}

