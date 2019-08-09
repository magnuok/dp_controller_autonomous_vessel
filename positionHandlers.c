//
//  positionHandlers.c
//  DP
//
//  Created by Magnus Knaedal on 07.02.2018.
//  Copyright 2018 Magnus Knaedal. All rights reserved.
//

#include "positionHandlers.h"

double getPosition(PhidgetVoltageInputHandle *handleVoltage){
    
    PhidgetReturnCode res;
    const char *errs;
    double newVoltagePosition;
    
    /* Get voltage position */
    res = PhidgetVoltageInput_getVoltage(*handleVoltage, &newVoltagePosition);
    if( res != EPHIDGET_OK){
        Phidget_getErrorDescription(res, &errs);
        fprintf(stderr, "Failed to get voltage: %s\n", errs);
    }
    
   return newVoltagePosition;
}

PhidgetReturnCode CCONV setDuty(PhidgetRCServoHandle *handleServo, double voltageDuty){
    
    PhidgetReturnCode res;
    const char *errs;
    
    /* Set duty servo */
    res = PhidgetRCServo_setTargetPosition(*handleServo, voltageDuty);
    if (res != EPHIDGET_OK) {
        Phidget_getErrorDescription(res, &errs);
        fprintf(stderr, "Could not set target position to %f: %s\n", voltageDuty, errs);
    }
    
    return res;
}

