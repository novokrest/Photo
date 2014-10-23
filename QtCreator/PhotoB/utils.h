#ifndef UTILS_H
#define UTILS_H

#include <cstdio>
#include <cstring>
#include <algorithm>

#ifdef WINDOWS
    #include <direct.h>
    #define getExecutableDir getWindowsExecutableDir
#else
    #include <unistd.h>
    #define getExecutableDir getPosixExecutableDir
#endif //WINDOWS

//TBD: getExecutablePath
//std::string getWindowsExecutableDir()
//{
//    char pBuf[MAX_PATH];
//    HMODULE hModule = GetModuleHandle(NULL);
//    if (hModule != NULL)
//    {
//        int bytes = GetModuleFileName(hModule, pBuf, sizeof(pBuf));
//        if (bytes == 0) {
//            return "";
//        }
//    }
//    return pBuf;
//}

//TBD: getExecutablePath
//std::string getPosixExecutableDir()
//{
//    char pBuf[FILENAME_MAX];
//    char szTmp[32];
//    sprintf(szTmp, "/proc/%d/exe", getpid());
//    int bytes = std::min((int)readlink(szTmp, pBuf, FILENAME_MAX), FILENAME_MAX - 1);
//    if (bytes >= 0) {
//        pBuf[bytes] = '\0';
//    }
//    return pBuf;
//}



#endif // UTILS_H
