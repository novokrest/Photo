#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>
#include <usb.h>

#include "devicemanager.h"
#include "luatableparser.h"

using namespace std;

using namespace photobooth;

void simpleScript()
{
    DeviceManager deviceManager;
//    deviceManager.listUsbCameras();
//    deviceManager.connectUsbCameras();
//    deviceManager.startMulticamMode();

//    deviceManager.writeMulticamCommand("rec");
//    deviceManager.writeMulticamCommand("call set_prop(143, 1)");
//    deviceManager.writeMulticamCommand("preshoot");
//    deviceManager.writeMulticamCommand("shootremote");
//    deviceManager.closeUsbConnections();

    deviceManager.listUsbCameras();
    deviceManager.connectUsbCameras();
    deviceManager.downloadLastPhotos();
    deviceManager.closeUsbConnections();

//    string remotePath = "A/DCIM/100___01/IMG_0039.JPG";
//    string localPath = "/home/knovokreshchenov/bbbbb";
//    cam.downloadLastPhoto(remotePath, localPath);
    int i = 1;
}

int main()
{
    simpleScript();

    return 0;
}

