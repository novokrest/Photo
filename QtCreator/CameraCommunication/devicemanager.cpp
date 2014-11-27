#include "devicemanager.h"
#include <sstream>

using std::cout;
using std::endl;

Device::Device(const string& bus, const string& dev, uint16_t vendor, uint16_t product)
    : bus_(bus), dev_(dev), vendor_(vendor), product_(product)
{}

string Device::bus() const
{
    return bus_;
}

string Device::dev() const
{
    return dev_;
}

uint16_t Device::vendor() const
{
    return vendor_;
}

uint16_t Device::product() const
{
    return product_;
}

string Device::toString() const
{
    std::stringstream ss;
    ss << "bus=" << bus_ << "; dev=" << dev_ << "; vendor=" << vendor_ << "; product=" << product_;

    return ss.str();
}

PtpConnectionState::PtpConnectionState()
    : scriptId(-1), timeout(-1), connected(false), write_count(-1), read_count(-1)
{}

DeviceManager::DeviceManager()
{
    usb_init();
}

DeviceManager::~DeviceManager()
{
}

struct usb_bus* DeviceManager::getBusses()
{
    usb_find_busses();
    usb_find_devices();
    return usb_get_busses();
}

Device& DeviceManager::getDevice(uint16_t id)
{
    return devices_[id];
}

void DeviceManager::pushUsbDevInfo(struct usb_device *dev)
{
    char* bus_name = dev->bus->dirname;
    char* dev_name = dev->filename;
    uint16_t id_vendor = dev->descriptor.idVendor;
    uint16_t id_product = dev->descriptor.idProduct;

    Device device(bus_name, dev_name, id_vendor, id_product);
    devices_.push_back(device);
}


void DeviceManager::listUsbDevices()
{
    devices_.clear();

    struct usb_bus* bus;
    struct usb_device* dev;
    int found = 0;

    bus = getBusses();
    for (; bus; bus = bus->next) {
        for (dev = bus->devices; dev; dev = dev->next) {
            if (!dev->config) {
                continue;
            }

            if (dev->config->interface->altsetting->bInterfaceClass == USB_CLASS_PTP) {
                pushUsbDevInfo(dev);
                ++found;
            }
        }
    }
}

void DeviceManager::printUsbDevices(std::ostream& out)
{
    for (DeviceVec::const_iterator deviceIt = devices_.begin(); deviceIt != devices_.end(); ++deviceIt) {
        out << deviceIt->toString() << std::endl;
    }
}

void DeviceManager::makeConnection(Device &device) {
    char conKey[LIBUSB_PATH_MAX*2 + 4];
    sprintf(conKey, "usb:%s/%s", device.bus().c_str(), device.dev().c_str());

//    if (connectionByKey.find(string(conKey)) != connectionByKey.end()) {
//        return;
//    }

    PTPParams& devParams = device.params;

    PTP_CON_STATE* ptp_cs = (PTP_CON_STATE*)malloc(sizeof(PTP_CON_STATE));
    memset(ptp_cs,0,sizeof(PTP_CON_STATE));
    ptp_cs->timeout = USB_TIMEOUT;
    ptp_cs->con_type = PTP_CON_USB;

    devParams.data = ptp_cs;

//    connectionByKey[string(conKey)] = devParams;
}

void DeviceManager::collectConnections()
{
    for (DeviceVec::iterator deviceIt = devices_.begin(); deviceIt != devices_.end(); ++deviceIt) {
        makeConnection(*deviceIt);
    }
}

void DeviceManager::connectToDevices()
{
    for (DeviceVec::iterator deviceIt = devices_.begin(); deviceIt != devices_.end(); ++deviceIt) {
        connectCamUsb(*deviceIt);
    }
}

void DeviceManager::connectCamUsb(Device& device) {
    struct usb_device* dev = find_device_by_path(device.bus().c_str(), device.dev().c_str());

    if (!dev) {
        return; //exception
    }

    PTPParams* params = &(device.params);

    if (open_camera_dev_usb(dev, (PTP_CON_STATE*)params->data, params)) {
        return;
    }
    else {
    }
}

struct usb_device* DeviceManager::findDeviceByPath(const string &findBus, const string &findDev)
{
    struct usb_bus* bus;
    struct usb_device* dev;

    bus = getBusses();

    for (; bus; bus = bus->next) {
        if (strcmp(findBus.c_str(), bus->dirname) != 0) {
            continue;
        }
        for (dev = bus->devices; dev; dev = dev->next) {
            if (dev->config
                    && dev->config->interface->altsetting->bInterfaceClass == USB_CLASS_PTP
                    && strcmp(findDev.c_str(), dev->filename) == 0) {
                return dev;
            }
        }
    }

    return 0;
}







