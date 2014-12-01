#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <usb.h>
#include <ptp.h>
#include <ptpcam.h>

#include "chdhkptp_header.h"
#include "scriptloader.h"

#define USB_TIMEOUT 5000

using std::string;

namespace photobooth {

class RemoteInode
{
public:
    bool is_file;
    bool is_dir;
    string name;
    unsigned long long size;
};

typedef std::vector<RemoteInode> RemoteInodeVec;
RemoteInodeVec parse_listdir_lua_table(const string& table);

class Camera
{
    string bus_;
    string dev_;

    uint16_t vendor_;
    uint16_t product_;

    PTPParams params_;
    PTP_CON_STATE* ptpCS_;

public:
    Camera(const string& bus, const string& dev, uint16_t vendor, uint16_t product);
    ~Camera();

    string bus() const;
    string dev() const;
    uint16_t vendor() const;
    uint16_t product() const;

    string toString() const;

    void connect();
    void closeUsbConnection();

    void execute(const string& script);
    void writeMsg(const string& message);
    void readMsg(ptp_chdk_script_msg** msg);

    RemoteInodeVec listRemoteDir(const string& script);
    void downloadLastPhoto(const string& remotePath, const string& localPath);
};

class DeviceManager
{
    typedef std::vector<Camera> CameraVec;
    CameraVec cameras_;

    ScriptLoader* scriptLoader_;

    struct usb_bus* getBusses();
    void addCamera(struct usb_device* dev);

public:
    DeviceManager();
    ~DeviceManager();

    Camera& getCamera(uint16_t id);
    size_t camerasCount();

    void listUsbCameras();
    void printUsbCameras(std::ostream& out = std::cout);

    void connectUsbCameras();
    void closeUsbConnections();

    void startMulticamMode();
    void writeMulticamCommand(const string& script);

    void downloadLastPhotos();
};

}

#endif // DEVICEMANAGER_H
