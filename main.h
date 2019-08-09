//
//  main.h
//  DP
//
//  Created by Magnus Knaedal on 30.01.2018.
//  Copyright 2018 Magnus Knaedal. All rights reserved.
//
/**********************************************************************
 * Purpose:
 - Runs the main program. Two threads is created. One for the regulator, one for the program.
 
 * Rutines:
 - main(): Runs the whole program.
        Input: void.
        Output: int. If program runs successful return = 0, else return = 1.

 * Subrutines:
- regulator(): Runs the closed loop regulation of the boat.
        Input: void.
        Output: void.
- program(): Runs the consol program.
        Input: void.
        Output: void.
 
 * Global variables :
 - handleServo: Handle for the PhidgetServo 1-Motor.
 - handleVoltage: PhidgetInterfaceKit 8/8/8.
 - PIDvalues: Struct containing PID-controller values.
 - rounds: Count loops done by regulator().
 - quit: flag for stopping program.
 - gnuplotFile: File for plotting time respons and pulse in Gnuplot
 - vtfFile: File for 3D-visualization in GLview
 
**********************************************************************/

#ifndef header_h
#define header_h

/******************************LIBRARIES******************************/
#include <stdio.h>                  // I/O-library.
#include <stdlib.h>                 // exit-library.
#include <unistd.h>                 // sleep-library.
#include <time.h>                   // time-library.
#include "sys/time.h"               // time-library.
#include <Phidget22/phidget22.h>    // phidget-library.
#include <pthread.h>                // thread-library.
#include "open_closePhidgets.h"
#include "dutyCalculation.h"
#include "makeVTFfile.h"
#include "gnuplot.h"

/******************************CONSTANTS*****************************/
#define TRUE  (1==1)    // Define True.
#define FALSE (!TRUE)   // Define False.

#define FILEPATH_VTF "/Users/magnusknaedal/dmet/DP/DP/vtfFile.vtf"          // Define filpath for vtfFile.
#define FILPATH_GNUPLOT "/Users/magnusknaedal/dmet/DP/DP/gnuplotFile.temp"  // Define filepath for gnuplotFile.

/******************************RUTINES******************************/
int main(void);

#endif /* header_h */



