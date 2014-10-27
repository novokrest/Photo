#ifndef PROPERTYRESOLVER_H
#define PROPERTYRESOLVER_H

#include <map>
#include <cstring>

using std::map;
using std::string;

struct CameraHardwareInfo
{
    int digic_;
    int propset_;
};

class PropertyResolver
{
    int digic_;
    int propset_;
    map<string, int> propMap_;

public:
    PropertyResolver();
    PropertyResolver(int digic, int propset);

    void setDigic(int digic);
    void setPropset(int propset);

    int resolve(string const& propName);
    bool registerProperty(string const& propName, int propID);
};

#endif // PROPERTYRESOLVER_H
