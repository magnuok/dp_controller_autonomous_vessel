//
//  dutyCalculation.c
//  DP
//
//  Created by Magnus Knaedal on 22.02.2018.
//  Copyright 2018 Magnus Knaedal. All rights reserved.
//

#include "dutyCalculation.h"
#include <stdio.h>

/* Global constants */
static const float Kp = 25;
static const float Ki = 4;
static const float Kd = 1.15;
static const double iMAX = 6;
static const double iMIN = -6;
static const double OVERSHOOT = 140;
static const double UNDERSHOOT = 73;

double pulseDutyChange(_PIDvalues *PIDvalues){
    
    /* Calcluates error value */
    PIDvalues->error = (PIDvalues->setPoint - PIDvalues->newVoltagePosition);
    
    /* Calculates Proportional term */
    PIDvalues->Pterm = Kp * PIDvalues->error;
    
    /* Calculates Integral term */
    PIDvalues->Iterm += Ki * (PIDvalues->error * DT);
    
    /* Prevents integral wind-up */
    if (PIDvalues->Iterm > iMAX){
        PIDvalues->Iterm = iMAX;
    }
    else if (PIDvalues->Iterm < iMIN){
        PIDvalues->Iterm = iMIN;
    }
    
    /* Calculates Derivative term */
    PIDvalues->Dterm = Kd * ((PIDvalues->oldError - PIDvalues->error)/DT);
    
    PIDvalues->oldError = PIDvalues->error;
    
    /* Calculate pulse duty */
    PIDvalues->pulseDuty = PIDvalues->pulseTemporary - (PIDvalues->Pterm + PIDvalues->Iterm + PIDvalues->Dterm);

    /* Pulse over/under-shoot prevention */
    if (PIDvalues->pulseDuty < UNDERSHOOT ||PIDvalues->pulseDuty > OVERSHOOT){
        PIDvalues->pulseDuty = PIDvalues->pulseTemporary;
    }
    
    /* Assigns new pulse to temprory pulse */
    PIDvalues->pulseTemporary = PIDvalues->pulseDuty;
    
    return PIDvalues->pulseDuty;
}
