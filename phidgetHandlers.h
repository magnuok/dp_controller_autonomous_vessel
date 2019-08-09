//
//  phidgetHandlers.h
//  DP
//
//  Created by Magnus Knaedal on 19.04.2018.
//  Copyright 2018 Magnus Knaedal. All rights reserved.
//
/**********************************************************************
 * Purpose:
 - Initialize and attach/detach handlers for the phidgets. CCONV = Calling convention. A defined term in Phidget22 that makes sure the function is called with the proper prefix for the compiler that's being used.
 
 * Rutines:
 - initializeChannel: Sets attach/detach/error handler for the phidget. Also sets channel for connection.
        Input: PhidgetHandle.
        Output: PhidgetReturnCode.
 
 * Subrutines:
 - onAttachHandlers: Attach handlers for phidgets
        Input: PhidgetHandle, void context.
        Output: void.
 - onDetachHandlers: Detach handlers for phidget
        Input: PhidgetHandle, void context.
        Output: void.
 - errorHandler: Attach error handlers for phidget
        Input: PhidgetHandle, void context.
        Output: void.
 
 *********************************************************************/

#ifndef phidgetHandlers_h
#define phidgetHandlers_h

/******************************LIBRARIES******************************/
#include <stdlib.h>                 // exit-library.
#include <Phidget22/phidget22.h>    // phidget-library.
#include "positionHandlers.h"

/******************************RUTINES********************************/
PhidgetReturnCode CCONV initializeChannel(PhidgetHandle handle);

#endif /* phidgetHandlers_h */
