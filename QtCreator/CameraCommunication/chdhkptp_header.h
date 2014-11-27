#ifndef CHDHKPTP_HEADER_H
#define CHDHKPTP_HEADER_H

extern "C" {

int open_camera_dev_usb(struct usb_device *dev, PTP_CON_STATE *ptp_cs, PTPParams *params);
struct usb_device *find_device_by_path(const char *find_bus, const char *find_dev);

}

#endif // CHDHKPTP_HEADER_H
