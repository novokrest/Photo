#ifndef REMOTEINODE_H
#define REMOTEINODE_H

#include "common.h"

class RemoteInode
{
public:
    bool is_file;
    bool is_dir;
    string name;
    unsigned long long size;
};

#endif // REMOTEINODE_H
