//
//  dutyCalculation.h
//  DP
//
//  Created by Magnus Knaedal on 19.04.2018.
//  Copyright 2018 Magnus Knaedal. All rights reserved.
//
/**********************************************************************
 * Purpose:
 - Calculates the new pulse with a PID-controller.
 
 * Theory:
 - The PID-controller is derived in the corresponding report.
 
 * Rutines:
 - pulseDuty_change: Calculates the new pulse with a PID-controller.
        Input: struct _PIDvalues containing necessary pid parameters.
        Output: double new calculated pulseDuty.
 
 * Global variables:
 - Kp: Proportional gain.
 - Ki: Integral gain.
 - Kd: Differential gain.
 - iMAX: Used to prevent integral wind-up.
 - iMIN: Used to prevent integral wind-up.
 - OVERSHOOT: Used to prevent pulse wind_up.
 - UNDERSHOOT: Used to prevent pulse wind_up.
 
 ********************************************************************/

#ifndef dutyCalculation_h
#define dutyCalculation_h

/******************************CONSTANTS******************************/
static const double DT = 0.01;  // Small time intervall [s].

/******************************STRUCTS*******************************/
typedef struct{
    double error;               // Holds the calculated Error value.
    double Pterm;               // Holds the calculated Proportional value.
    double Iterm;               // Holds the calculated Integral value.
    double Dterm;               // Holds the calculated Differential value.
    double oldError;            // This stores the old error value.
    double Itemporary;          // This stores the accumulated Integral value.
    double pulseTemporary;      // Holdes temporary pulse.
    double setPoint;            // Holdes the wanted position/set_point.
    double newVoltagePosition;  // Holds new voltage value returned from get_position.
    double pulseDuty;           // New calculated pulse_duty.
} _PIDvalues;

/******************************METHODS******************************/
double pulseDutyChange(_PIDvalues *PIDvalues);

#endif /* dutyCalculation_h */
