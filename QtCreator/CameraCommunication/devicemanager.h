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

#define USB_TIMEOUT 5000

using std::string;


class Device
{
    string bus_;
    string dev_;

    uint16_t vendor_;
    uint16_t product_;

public:
    PTPParams params;

    Device(const string& bus, const string& dev, uint16_t vendor, uint16_t product);

    string bus() const;
    string dev() const;
    uint16_t vendor() const;
    uint16_t product() const;

    string toString() const;
};

struct PtpUsb
{
    usb_dev_handle* handle;
    int inep;
    int outep;
    int intep;
    string bus;
    string dev;
};

struct PtpConnectionState
{
    int scriptId;
    int timeout;
    int connected;

    uint64_t write_count;
    uint64_t read_count;

    PtpUsb usb;

    PtpConnectionState();
};

struct PtpConnection
{
    PtpConnectionState state;
};

class DeviceManager
{
    typedef std::vector<Device> DeviceVec;
    typedef std::vector<PtpConnection> ConnectionVec;

//    typedef std::map<string, PTPParams&> ConnectionMap;

    DeviceVec devices_;
    ConnectionVec connections_;
//    ConnectionMap connectionByKey;

    struct usb_bus* getBusses();
    void pushUsbDevInfo(struct usb_device* dev);

public:
    DeviceManager();
    ~DeviceManager();

    Device& getDevice(uint16_t id);

    void listUsbDevices();
    struct usb_device* findDeviceByPath(string const& findBus, string const& findDev);
    void printUsbDevices(std::ostream& out = std::cout);

    void makeConnection(Device& device);
    void collectConnections();

    void connectCamUsb(Device& device);
    void connectToDevices();

};

#endif // DEVICEMANAGER_H
