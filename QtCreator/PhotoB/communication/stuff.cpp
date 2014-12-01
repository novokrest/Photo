
//int open_camera_dev_usb(struct usb_device *dev, PTP_CON_STATE *ptp_cs, PTPParams *params)
//{
//    uint16_t devstatus[2] = {0,0};
//    int ret;
//    if(!dev) {
//        printf("open_camera_dev_usb: NULL dev\n");
//        return 0;
//    }
//    find_endpoints(dev,&ptp_cs->usb.inep,&ptp_cs->usb.outep,&ptp_cs->usb.intep);
//    if(!init_ptp_usb(params, ptp_cs, dev)) {
//        printf("open_camera_dev_usb: init_ptp_usb 1 failed\n");
//        return 0;
//    }

//    ret = ptp_opensession(params,1);
//    if(ret!=PTP_RC_OK) {
//// TODO temp debug - this appears to be needed on linux if other stuff grabbed the dev
//        printf("open_camera_dev_usb: ptp_opensession failed 0x%x\n",ret);
//        ret = usb_ptp_device_reset(ptp_cs);
//        if (ret<0)perror ("open_camera_dev_usb:usb_ptp_device_reset()");
//        /* get device status (devices likes that regardless of its result)*/
//        ret = usb_ptp_get_device_status(ptp_cs,devstatus);
//        if (ret<0)
//            perror ("usb_ptp_get_device_status()");
//        else	{
//            if (devstatus[1]==PTP_RC_OK)
//                printf ("Device status OK\n");
//            else
//                printf ("Device status 0x%04x\n",devstatus[1]);
//        }

//        close_usb(ptp_cs, dev);
//        find_endpoints(dev,&ptp_cs->usb.inep,&ptp_cs->usb.outep,&ptp_cs->usb.intep);
//        if(!init_ptp_usb(params, ptp_cs, dev)) {
//            printf("open_camera_dev_usb: init_ptp_usb 2 failed\n");
//            return 0;
//        }
//        ret=ptp_opensession(params,1);
//        if(ret!=PTP_RC_OK) {
//            printf("open_camera_dev_usb: ptp_opensession 2 failed: 0x%x\n",ret);
//            return 0;
//        }

//    }
//    if (ptp_getdeviceinfo(params,&params->deviceinfo)!=PTP_RC_OK) {
//        // TODO do we want to close here ?
//        printf("Could not get device info!\n");
//        close_camera(ptp_cs, params);
//        return 0;
//    }
//    // TODO we could check camera CHDK, API version, etc here
//    ptp_cs->connected = 1;
//    return 1;
//}

//void
//find_endpoints(struct usb_device *dev, int* inep, int* outep, int* intep)
//{
//    int i,n;
//    struct usb_endpoint_descriptor *ep;

//    ep = dev->config->interface->altsetting->endpoint;
//    n=dev->config->interface->altsetting->bNumEndpoints;

//    for (i=0;i<n;i++) {
//    if (ep[i].bmAttributes==USB_ENDPOINT_TYPE_BULK)	{
//        if ((ep[i].bEndpointAddress&USB_ENDPOINT_DIR_MASK)==USB_ENDPOINT_DIR_MASK)
//        {
//            *inep=ep[i].bEndpointAddress;
//            if (verbose>1)
//                fprintf(stderr, "Found inep: 0x%02x\n",*inep);
//        }
//        if ((ep[i].bEndpointAddress&USB_ENDPOINT_DIR_MASK)==0)
//        {
//            *outep=ep[i].bEndpointAddress;
//            if (verbose>1)
//                fprintf(stderr, "Found outep: 0x%02x\n",*outep);
//        }
//        } else if ((ep[i].bmAttributes==USB_ENDPOINT_TYPE_INTERRUPT) &&
//            ((ep[i].bEndpointAddress&USB_ENDPOINT_DIR_MASK)==
//                USB_ENDPOINT_DIR_MASK))
//        {
//            *intep=ep[i].bEndpointAddress;
//            if (verbose>1)
//                fprintf(stderr, "Found intep: 0x%02x\n",*intep);
//        }
//    }
//}
