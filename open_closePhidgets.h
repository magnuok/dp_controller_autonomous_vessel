//
//  open_closePhidgets.h
//  DP
//
//  Created by Magnus Knaedal on 26.04.2018.
//  Copyright 2018 Magnus Knaedal. All rights reserved.
//
/**********************************************************************
* Purpose:
- Open and close the phidgets.

* Rutines:
- openPhidgets: Opens and initialize phidgets.
        Input: PhidgetHandle for servo and voltage.
        Output: void.
- closePhidgets: Close and delete phidgets.
        Input: PhidgetHandle for servo and voltage.
        Output: void.
 
********************************************************************/

#ifndef open_closePhidgets_h
#define open_closePhidgets_h

/******************************LIBRARIES******************************/
#include <stdio.h>                  // I/O-library.
#include <stdlib.h>                 // exit-library.
#include <Phidget22/phidget22.h>    // phidget-library.
#include "phidgetHandlers.h"

/******************************RUTINES******************************/
void openPhidgets(PhidgetRCServoHandle *handle_servo, PhidgetVoltageInputHandle *handle_voltage);
void closePhidgets(PhidgetRCServoHandle *handle_servo, PhidgetVoltageInputHandle *handle_voltage);
#endif /* open_closePhidgets_h */
