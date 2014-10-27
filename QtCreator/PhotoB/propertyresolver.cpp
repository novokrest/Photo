#include "propertyresolver.h"


PropertyResolver::PropertyResolver()
{

}

PropertyResolver::PropertyResolver(int digic, int propset)
    : digic_(digic), propset_(propset)
{

}

void PropertyResolver::setDigic(int digic)
{
    digic_ = digic;
}

void PropertyResolver::setPropset(int propset)
{
    propset_ = propset;
}

int PropertyResolver::resolve(string const& propName)
{
    if (propMap_.find(propName) != propMap_.end()) {
        int propID = propMap_[propName];
        return propID;
    }

    return -1;
}

bool PropertyResolver::registerProperty(string const& propName, int propID)
{
    bool isCollision = false;
    if (propMap_.find(propName) != propMap_.end()) {
        isCollision = true;
    }

    propMap_[propName] = propID;

    return !isCollision;
}
