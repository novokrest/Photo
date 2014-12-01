#include "devicemanager.h"
#include <sstream>
#include <algorithm>

using std::cout;
using std::endl;

namespace photobooth {

Camera::Camera(const string& bus, const string& dev, uint16_t vendor, uint16_t product)
    : bus_(bus), dev_(dev), vendor_(vendor), product_(product)
{
    ptpCS_ = (PTP_CON_STATE*)malloc(sizeof(PTP_CON_STATE));
    memset(ptpCS_,0,sizeof(PTP_CON_STATE));
    ptpCS_->timeout = USB_TIMEOUT;
    ptpCS_->con_type = PTP_CON_USB;
    params_.data = ptpCS_;
}

Camera::~Camera()
{
    closeUsbConnection();
}

string Camera::bus() const
{
    return bus_;
}

string Camera::dev() const
{
    return dev_;
}

uint16_t Camera::vendor() const
{
    return vendor_;
}

uint16_t Camera::product() const
{
    return product_;
}

string Camera::toString() const
{
    std::stringstream ss;
    ss << "bus=" << bus_ << "; dev=" << dev_ << "; vendor=" << vendor_ << "; product=" << product_;

    return ss.str();
}

void Camera::connect()
{
    struct usb_device* dev = find_device_by_path(bus_.c_str(), dev_.c_str());

    if (open_camera_dev_usb(dev, ptpCS_, &params_)) {
        return;
    }
    else {
        std::cout << "NOT CONNECTED: " << "camera=" << toString() << std::endl;
    }
}

//TODO: make correct close connection otherwise there are memory leaks
void Camera::closeUsbConnection()
{}

//TODO: implement error handling
void Camera::execute(const string &script) {
    int status;
    ptp_chdk_exec_lua(&params_,
                      (char*)(script.c_str()),
                      PTP_CHDK_SL_LUA,
                      &ptpCS_->script_id,
                      &status);
}

//TODO: implement erro handling
void Camera::writeMsg(const string &message) {
    int status;
    ptp_chdk_write_script_msg(&params_,
                              (char*)message.c_str(),
                              message.length(),
                              ptpCS_->script_id,
                              &status);
}

void Camera::readMsg(ptp_chdk_script_msg **msg)
{
    ptp_chdk_read_script_msg(&params_, msg);
}

void Camera::downloadLastPhoto(const string &remotePath, const string &localPath)
{
    ptp_chdk_download(&params_, (char*)remotePath.c_str(), (char*)localPath.c_str());
}

DeviceManager::DeviceManager()
    : scriptLoader_(new ScriptLoader("/home/knovokreshchenov/Github/Photo/QtCreator/PhotoB/communication/commands/"))
{
    usb_init();
}

DeviceManager::~DeviceManager()
{
    closeUsbConnections();

    delete scriptLoader_;
}

struct usb_bus* DeviceManager::getBusses()
{
    usb_find_busses();
    usb_find_devices();
    return usb_get_busses();
}

void DeviceManager::addCamera(struct usb_device *dev)
{
    char* bus_name = dev->bus->dirname;
    char* dev_name = dev->filename;
    uint16_t id_vendor = dev->descriptor.idVendor;
    uint16_t id_product = dev->descriptor.idProduct;

    Camera camera(bus_name, dev_name, id_vendor, id_product);
    cameras_.push_back(camera);
}

Camera& DeviceManager::getCamera(uint16_t id)
{
    return cameras_[id];
}

size_t DeviceManager::camerasCount()
{
    return cameras_.size();
}


void DeviceManager::listUsbCameras()
{
    closeUsbConnections();
    cameras_.clear();

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
                addCamera(dev);
                ++found;
            }
        }
    }
}

void DeviceManager::connectUsbCameras()
{
    for (CameraVec::iterator cameraIt = cameras_.begin(); cameraIt != cameras_.end(); ++cameraIt) {
        cameraIt->connect();
    }
}

void DeviceManager::printUsbCameras(std::ostream& out)
{
    for (CameraVec::const_iterator cameraIt = cameras_.begin(); cameraIt != cameras_.end(); ++cameraIt) {
        out << cameraIt->toString() << std::endl;
    }
}

void DeviceManager::startMulticamMode()
{
    const string script = scriptLoader_->get(SCRIPT_MULTICAM_START);
    for (CameraVec::iterator cameraIt = cameras_.begin(); cameraIt != cameras_.end(); ++cameraIt) {
        cameraIt->execute(script);
    }
}

void DeviceManager::writeMulticamCommand(const string& script)
{
    for (CameraVec::iterator cameraIt = cameras_.begin(); cameraIt != cameras_.end(); ++cameraIt) {
        cameraIt->writeMsg(script);
    }
}

void DeviceManager::closeUsbConnections()
{
    for (CameraVec::iterator cameraIt = cameras_.begin(); cameraIt != cameras_.end(); ++cameraIt) {
        cameraIt->closeUsbConnection();
    }
}

RemoteInodeVec Camera::listRemoteDir(const string &listdirScript)
{
    ptp_chdk_script_msg* msg;
    int i = 0;

    execute(listdirScript);

    do {
        sleep(1);
        readMsg(&msg);
        ++i;
    }
    while (!(msg->type == PTP_CHDK_S_MSGTYPE_USER && msg->subtype == PTP_CHDK_TYPE_TABLE)
           && i < 5);

    RemoteInodeVec listDir = parse_listdir_lua_table(msg->data);
    return listDir;
}

void DeviceManager::downloadLastPhotos()
{
    int num = 0;
    for (CameraVec::iterator cameraIt = cameras_.begin(); cameraIt != cameras_.end(); ++cameraIt) {
        const string listdirScript = scriptLoader_->get(SCRIPT_LISTDIR);
        const string listDirDCIM = listdirScript + "\n return ls('A/DCIM', {stat=\"*\",})";

        RemoteInodeVec dcim = cameraIt->listRemoteDir(listDirDCIM);
        std::sort(dcim.begin(), dcim.end(), [](const RemoteInode& a, const RemoteInode& b) {
            return a.name > b.name;
        });
        auto firstDir = std::find_if(dcim.begin(), dcim.end(),
                                     [](const RemoteInode& f)
        {
            // Test if first character of directory name is a digit
            return isdigit(f.name[0]);
        });

        if (firstDir == dcim.end()) {
            continue;
        }

        string latestDirPathScript = listdirScript + string("\n return ls('A/DCIM/") + firstDir->name + string("', {stat=\"*\",})");
        RemoteInodeVec files = cameraIt->listRemoteDir(latestDirPathScript);
        std::sort(files.begin(), files.end(), [](const RemoteInode& a, const RemoteInode& b)
        {
            return a.name > b.name;
        });

        auto firstJPG = std::find_if(files.begin(), files.end(), [](const RemoteInode& f)
        {
            return f.name.back() == 'G';
        });

        if (firstJPG != files.end()) {
            string remotePath = string("A/DCIM/") + firstDir->name + string("/") + firstJPG->name;
            cameraIt->downloadLastPhoto(remotePath, "/home/knovokreshchenov/PHOTOBOOTH_PHOTOS" + std::to_string(num));
            ++num;
        }
    }
}

RemoteInodeVec parse_listdir_lua_table(const string& table)
{
    return RemoteInodeVec();
}

}

