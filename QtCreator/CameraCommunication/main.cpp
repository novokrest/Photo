#include <iostream>
#include <cstring>
#include <vector>
#include <usb.h>

#include "devicemanager.h"

using namespace std;

int main()
{
    DeviceManager deviceManager;
    deviceManager.listUsbDevices();
    deviceManager.printUsbDevices();
    deviceManager.collectConnections();

    cout << ((PTP_CON_STATE*)(deviceManager.getDevice(0).params.data))->connected << endl;

    deviceManager.connectToDevices();

    cout << ((PTP_CON_STATE*)(deviceManager.getDevice(0).params.data))->connected << endl;

    string s = "111";
    return 0;
}

