//
//  open_closePhidgets.c
//  DP
//
//  Created by Magnus Knaedal on 26.04.2018.
//  Copyright 2018 Magnus Knaedal. All rights reserved.
//

#include "open_closePhidgets.h"

void openPhidgets(PhidgetRCServoHandle *handleServo, PhidgetVoltageInputHandle *handleVoltage){
    
    PhidgetReturnCode res;
    char const *errs;
    
    /* Create servo handle */
    res = PhidgetRCServo_create(handleServo);
    if(res != EPHIDGET_OK){
        Phidget_getErrorDescription(res, &errs);
        fprintf(stderr, "Could not creat channel: %s\n", errs);
        exit(1);
    }
    
    /* Initialize servo handle */
    res = initializeChannel((PhidgetHandle) *handleServo);
    if(res != EPHIDGET_OK){
        Phidget_getErrorDescription(res, &errs);
        fprintf(stderr, "Could not initilize channel: %s\n", errs);
        exit(1);
    }
    
    /* Create voltage handle */
    res = PhidgetVoltageInput_create(handleVoltage);
    if(res != EPHIDGET_OK){
        Phidget_getErrorDescription(res, &errs);
        fprintf(stderr, "Could not creat channel: %s\n", errs);
        exit(1);
    }
    
    /* Initialize servo handle */
    res = initializeChannel((PhidgetHandle) *handleVoltage);
    if(res != EPHIDGET_OK){
        Phidget_getErrorDescription(res, &errs);
        fprintf(stderr, "Could not initilize channel: %s\n", errs);
        exit(1);
    }
    
    /* Waiting 5 seconds for servo motor to attach */
    res = Phidget_openWaitForAttachment((PhidgetHandle) *handleServo, 5000);
    if (res != EPHIDGET_OK) {
        if (res == EPHIDGET_TIMEOUT) {
            printf("\nServo channel did not attach after 5 seconds: please check that the device is attached\n");
            exit(1);
        } else {
            Phidget_getErrorDescription(res, &errs);
            printf("Failed to open channel:%s\n", errs);
            exit(1);
        }
    }
    
    /* Waiting 5 seconds for voltage to attach */
    res = Phidget_openWaitForAttachment((PhidgetHandle) *handleVoltage, 5000);
    if (res != EPHIDGET_OK) {
        if (res == EPHIDGET_TIMEOUT) {
            printf("\nVoltage channel did not attach after 5 seconds: please check that the device is attached\n");
            exit(1);
        } else {
            Phidget_getErrorDescription(res, &errs);
            printf("Failed to open channel:%s\n", errs);
            exit(1);
        }
    }
    
    /* Initial position before engage */
    res = setDuty(handleServo, 0);
    if (res != EPHIDGET_OK) {
        Phidget_getErrorDescription(res, &errs);
        fprintf(stderr, "Failed to set initial position: %s \n", errs);
        exit(1);
    }
    
    /* Allows servo motor to be positioned */
    res = PhidgetRCServo_setEngaged(*handleServo, 1);
    if (res != EPHIDGET_OK) {
        Phidget_getErrorDescription(res, &errs);
        fprintf(stderr, "Failed to set engange: %s \n", errs);
        exit(1);
    }
}

void closePhidgets(PhidgetRCServoHandle *handleServo, PhidgetVoltageInputHandle *handleVoltage){
    
    PhidgetReturnCode res;
    char const *errs;
    
    /* Close servo handle */
    res = Phidget_close((PhidgetHandle) handleServo);
    if (res != EPHIDGET_OK) {
        Phidget_getErrorDescription(res, &errs);
        fprintf(stderr, "Failed to close servo moter channel: %s \n", errs);
    }
    
    /* Delete servo handle from memory */
    res = PhidgetRCServo_delete(handleServo);
    if (res != EPHIDGET_OK) {
        Phidget_getErrorDescription(res, &errs);
        fprintf(stderr, "Failed to delete servo moter channel: %s \n", errs);
    }
    
    /* Close voltage handle */
    res = Phidget_close((PhidgetHandle) handleVoltage);
    if (res != EPHIDGET_OK) {
        Phidget_getErrorDescription(res, &errs);
        fprintf(stderr, "Failed to close voltage channel: %s \n", errs);
    }
    
    /* Delete voltage handle from memory */
    res = PhidgetVoltageInput_delete(handleVoltage);
    if (res != EPHIDGET_OK) {
        Phidget_getErrorDescription(res, &errs);
        fprintf(stderr, "Failed to delete voltage channel: %s \n", errs);
    }
    
}
