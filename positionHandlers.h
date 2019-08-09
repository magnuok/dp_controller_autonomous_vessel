//
//  positionHandlers.h
//  DP
//
//  Created by Magnus Knaedal on 19.04.2018.
//  Copyright 2018 Magnus Knaedal. All rights reserved.
//
/**********************************************************************
 * Purpose:
 - Recive voltage position from voltage, and set pulse duty for servo. CCONV = Calling convention. A defined term in Phidget22 that makes sure the function is called with the proper prefix for the compiler that's being used.

 * Rutines:
 - getPosition: Get new voltage position.
        Input: PhidgetHandle for voltage.
        Output: double new voltage position.
 - set_duty: Sets calculated pulse duty.
        Input: PhidgetHandle for servo, double New calculated voltage duty.
        Output: PhidgetReturnCode.
 
 ********************************************************************/

#ifndef positionHandlers_h
#define positionHandlers_h

/******************************LIBRARIES******************************/
#include <Phidget22/phidget22.h>    // phidget-library.
#include <stdio.h>                  // I/O-library.

/******************************RUTINES******************************/
double getPosition(PhidgetVoltageInputHandle *handle_voltage);
PhidgetReturnCode CCONV setDuty(PhidgetRCServoHandle *handle_servo, double voltage_duty);

#endif /* positionHandlers_h */
