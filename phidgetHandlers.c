//
//  phidgetHandlers.c
//  DP
//
//  Created by Magnus Knaedal on 30.01.2018.
//  Copyright 2018 Magnus Knaedal. All rights reserved.
//

#include "phidgetHandlers.h"

static void CCONV onAttachHandlers(PhidgetHandle handle, void *ctx) {
    
    Phidget_DeviceID deviceID;
    PhidgetReturnCode res;
    char const *errs;
    int serial;
    int channel;
    
    /* Get channel for device */
    res = Phidget_getChannel(handle, &channel);
    if (res != EPHIDGET_OK){
        Phidget_getErrorDescription(res, &errs);
        fprintf(stderr, "Failed to get device channel number: %s\n", errs);
        return;
    }
    
    /* Get Serial number for device */
    res = Phidget_getDeviceSerialNumber( (PhidgetHandle) handle, &serial);
    if (res != EPHIDGET_OK) {
        Phidget_getErrorDescription(res, &errs);
        fprintf(stderr, "Failed to get device serial number: %s\n", errs);
        return;
    }
    
    /* Get device ID */
    res = Phidget_getDeviceID(handle, &deviceID);
    if (res != EPHIDGET_OK){
        Phidget_getErrorDescription(res, &errs);
        fprintf(stderr, "Failed to get device ID: %s\n", errs);
    }
    
    /* PHIDID_1000 = servo */
    if(deviceID == PHIDID_1000){
        printf("Servo %d is attached to channel %d\n", serial, channel);
    }
    else{
        printf("Voltage %d is attached to channel %d\n", serial, channel);
    }
    
}

static void CCONV onDetachHandlers(PhidgetHandle handle, void *ctx) {
    
    Phidget_DeviceID deviceID;
    PhidgetReturnCode res;
    char const *errs;
    int serial;
    int channel;
    
    /* Get channel for device */
    res = Phidget_getChannel(handle, &channel);
    if (res != EPHIDGET_OK){
        Phidget_getErrorDescription(res, &errs);
        fprintf(stderr, "Failed to get device channel number: %s\n", errs);
        return;
    }
    
    /* Get Serial number for device */
    res = Phidget_getDeviceSerialNumber( (PhidgetHandle) handle, &serial);
    if (res != EPHIDGET_OK) {
        Phidget_getErrorDescription(res, &errs);
        fprintf(stderr, "Failed to get device serial number: %s\n", errs);
        return;
    }
    
    /* Get device ID */
    res = Phidget_getDeviceID(handle, &deviceID);
    if (res != EPHIDGET_OK){
        Phidget_getErrorDescription(res, &errs);
        fprintf(stderr, "Failed to get device ID: %s\n", errs);
    }
    
    /* PHIDID_1000 = servo */
    if(deviceID == PHIDID_1000){
        printf("Servo %d is detached from channel %d\n", serial, channel);
    }
    else{
        printf("Voltage %d is detached to channel %d\n", serial, channel);
    }
    
}

static void CCONV errorHandler(PhidgetHandle handle, void *ctx, Phidget_ErrorEventCode errorCode, const char *errorString) {
    printf("Error: %s (%d)\n", errorString, errorCode);
}

PhidgetReturnCode CCONV initializeChannel(PhidgetHandle handle){
    
    Phidget_DeviceID deviceID;
    PhidgetReturnCode res;
    char const *errs;
    
    /* Sets attach handlers */
    res = Phidget_setOnAttachHandler(handle, onAttachHandlers, NULL);
    if (res != EPHIDGET_OK){
        Phidget_getErrorDescription(res, &errs);
        fprintf(stderr, "Failed to attach handler: %s\n", errs);
        return res;
    }
    
    /* Sets detach handlers */
    res = Phidget_setOnDetachHandler(handle, onDetachHandlers, NULL);
    if (res != EPHIDGET_OK){
        Phidget_getErrorDescription(res, &errs);
        fprintf(stderr, "Failed to detach handler: %s\n", errs);
        return res;
    }
    
    /* Sets error handlers */
    res = Phidget_setOnErrorHandler(handle, errorHandler, NULL);
    if (res != EPHIDGET_OK){
        Phidget_getErrorDescription(res, &errs);
        fprintf(stderr, "Failed to set error handler\n: %s", errs);
        return res;
    }
    
    /* Get device ID */
    res = Phidget_getDeviceID(handle, &deviceID);
    if (res != EPHIDGET_OK){
        Phidget_getErrorDescription(res, &errs);
        fprintf(stderr, "Failed to get device ID: %s\n", errs);
    }
    
    /* PHIDID_1000 = servo */
    if(deviceID == PHIDID_1000){
        
        /* Set channel for servo */
        res = Phidget_setChannel(handle, 0);
        if (res != EPHIDGET_OK){
            Phidget_getErrorDescription(res, &errs);
            printf("Failed to set channel for servo\n: %s", errs);
            return res;
        }
    }
    
    else{
        
        /* Set channel for voltage */
        res = Phidget_setChannel(handle, 2);
        if (res != EPHIDGET_OK){
            Phidget_getErrorDescription(res, &errs);
            printf("Failed to set channel for voltage\n: %s", errs);
            return res;
        }
    }
    
    return EPHIDGET_OK;
}




