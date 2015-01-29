#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>
#include <usb.h>

#include "devicemanager.h"
#include "luatableparser.h"
#include "cameracommunication_utils.h"

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
    LuaTable table;
    LuaTableParser parser;
    //    parser.parse("{status=true, cmd=\"rec\",}", table);

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

    deviceManager.readAllMessages();

    deviceManager.listUsbCameras();
    deviceManager.closeUsbConnections();

    cout << MESSAGE_FOR_SHOOT << endl;
    cin.get();
}

// "A/DCIM/100___01/IMG_0057.JPG"
// delete -nodirs DCIM
static void download()
{
    DeviceManager deviceManager;
    print(MESSAGE_FIND_USB_DEVICES);
    deviceManager.listUsbCameras();
    print(MESSAGE_CONNECT_TO_CAMERAS);
    deviceManager.connectUsbCameras();
    deviceManager.readAllMessages();

    print(MESSAGE_START_DOWNLOAD);
    sleep(1);
    deviceManager.downloadLastPhotos();
    print(MESSAGE_END_DOWNLOAD);
    deviceManager.closeUsbConnections();
}

static void shoot_download()
{
    DeviceManager deviceManager;

    deviceManager.listUsbCameras();
    deviceManager.connectUsbCameras();
    sleep(1);
    deviceManager.clearReadBuffers();
    sleep(1);

    deviceManager.startMulticamMode();
    print("rec");
    deviceManager.writeMulticamCommand("rec");
    sleep(7);
    deviceManager.readStatus("rec");
    sleep(1);

    print("preshoot");
    deviceManager.writeMulticamCommand("preshoot");
    sleep(1);
    deviceManager.readStatus("preshoot");
    sleep(1);

    print("shootremote");
    deviceManager.clearReadBuffers();
    deviceManager.writeMulticamCommand("shootremote");
    sleep(1);

    print("READY FOR SHOOT!\nNow you must disconnect cameras from usb.\nAfter shooting reconnect cameras to usb and press <ENTER>");
    cin.get();
    countdown(3);

    deviceManager.listUsbCameras();
    deviceManager.connectUsbCameras();
    sleep(1);
    deviceManager.readStatus("shootremote");
    deviceManager.clearReadBuffers();

    print("start downloading");
    deviceManager.downloadLastPhotos();
    print("downloads completed");

    print("delete photos from cameras");
    deviceManager.deletePhotos();
    print("photos has been deleted");
    sleep(1);

    deviceManager.clearReadBuffers();
}

int main(int argc, char* argv[])
{
    if (argc == 1) {
        print("SHOOT && DOWNLOAD mode");
        shoot_download();
    }
    else if (argc == 2) {
        if (!strcmp(argv[1], "shoot")) {
            print("SHOOT mode");
            shoot();
        }
        else if (!strcmp(argv[1], "download")) {
            print("DOWNLOAD mode");
            download();
        }
        else {
            print(MESSAGE_ERROR_INCORRECT_ARG);
            return 1;
        }
    }
    else {
        print(MESSAGE_ERROR_INCORRECT_ARG);
        return 1;
    }

    return 0;
}

