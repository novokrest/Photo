#ifndef CHDHKPTP_HEADER_H
#define CHDHKPTP_HEADER_H

extern "C" {

struct usb_device *find_device_by_path(const char *find_bus, const char *find_dev);
int open_camera_dev_usb(struct usb_device *dev, PTP_CON_STATE *ptp_cs, PTPParams *params);
uint16_t ptp_chdk_exec_lua(PTPParams* params, char *script, int flags, int *script_id, int *status);
uint16_t ptp_chdk_write_script_msg(PTPParams* params, char *data, unsigned size, int target_script_id, int *status);
uint16_t ptp_chdk_read_script_msg(PTPParams* params, ptp_chdk_script_msg **msg);
uint16_t ptp_chdk_download(PTPParams* params, char *remote_fn, char *local_fn);
}

#endif // CHDHKPTP_HEADER_H
