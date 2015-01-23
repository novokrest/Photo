#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>
#include <usb.h>

#include "devicemanager.h"
#include "luatableparser.h"

using namespace std;

using namespace photobooth;

static const char* MESSAGE_ERROR_INCORRECT_ARG = "Incorrect arguments! \nUse: ./CameraCommunication [ shoot | download ]";
static const char* MESSAGE_FIND_USB_DEVICES = "Searching usb devices...";
static const char* MESSAGE_CONNECT_TO_CAMERAS = "Connecting to cameras...";
static const char* MESSAGE_CMD_PRESHOOT = "Preshoot...";
static const char* MESSAGE_START_MULTICAM_MODE = "Starting multicam mode...";
static const char* MESSAGE_APPLY_SETTINGS = "Applying settings to cameras...";
static const char* MESSAGE_READY_SHOOT = "Ready to shoot!";
static const char* MESSAGE_FOR_SHOOT = "Disconnect cameras from USB and reload after shooting.\nPress ENTER for exit.";
static const char* MESSAGE_START_DOWNLOAD = "Start downloading...";
static const char* MESSAGE_END_DOWNLOAD = "Downloading completed!";

static void print(const char* message)
{
    cout << message << endl;
}

static void shoot()
{
    DeviceManager deviceManager;
    print(MESSAGE_FIND_USB_DEVICES);
    deviceManager.listUsbCameras();
    print(MESSAGE_CONNECT_TO_CAMERAS);
    deviceManager.connectUsbCameras();

    print(MESSAGE_START_MULTICAM_MODE);
    deviceManager.startMulticamMode();

    print(MESSAGE_APPLY_SETTINGS);
    sleep(1);
    deviceManager.writeMulticamCommand("rec");
    print(MESSAGE_CMD_PRESHOOT);
    sleep(1);
    deviceManager.writeMulticamCommand("preshoot");
    sleep(1);
    deviceManager.writeMulticamCommand("shootremote");
    sleep(1);
    print(MESSAGE_READY_SHOOT);

    deviceManager.closeUsbConnections();

    cout << MESSAGE_FOR_SHOOT << endl;
    cin.get();
}

static void download()
{
    DeviceManager deviceManager;
    print(MESSAGE_FIND_USB_DEVICES);
    deviceManager.listUsbCameras();
    print(MESSAGE_CONNECT_TO_CAMERAS);
    deviceManager.connectUsbCameras();

    print(MESSAGE_START_DOWNLOAD);
    sleep(1);
    deviceManager.downloadLastPhotos();
    print(MESSAGE_END_DOWNLOAD);
    deviceManager.closeUsbConnections();
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        cout << MESSAGE_ERROR_INCORRECT_ARG << endl;
        return 1;
    }

    if (!strcmp(argv[1], "shoot")) {
        shoot();
    }
    else if (!strcmp(argv[1], "download")) {
        download();
    }
    else {
        cout << MESSAGE_ERROR_INCORRECT_ARG << endl;
        return 1;
    }

    return 0;
}

