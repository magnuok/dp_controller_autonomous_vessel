//
//  makeVTFfile.h
//  DP
//
//  Created by Magnus Knaedal on 19.04.2018.
//  Copyright 2018 Magnus Knaedal. All rights reserved.
//
/**********************************************************************
 * Purpose: Create VTF-file for 3D-visualisation in GLview.
 
 * Rutines:
 - make_vtf: Initialize VTF-file.
        Input: file vtfFile for initilizing.
        Output: void.
 - results_vtf: Adds results after each controller-loop.
        Input: file vtfFile for writing results to, double newVoltagePosition.
        Output: void.
 - vector_vtf: Adds vector of results.
        Input: file vtfFile for writing vector to, int rounds for writing how many vectors.
        Output: void.
 
 * Subrutines:
 - voltageToCentimeter: Convert volt to centimenter.
        Input: double voltagePosition.
        Output: double centimeterPosition.
 
 ********************************************************************/

#ifndef makeVTFfile_h
#define makeVTFfile_h

/******************************LIBRARIES******************************/
#include <stdio.h>  // I/O-library.

/******************************CONSTANTS******************************/
#define L_VESSEL  65.0  // Length of vessel [cm].
#define B_VESSEL 18.0   // Breath of vessel [cm].
#define H_VESSEL 10.0   // Hight of vessel [cm].
#define L_FLAT 150.0    // Length of flat [cm].
#define B_FLAT 50.0     // Breath of flat [cm].

/******************************METHODS******************************/
void resultsVTF(FILE *vtfFile, double new_voltage_value, int round);
void vectorVTF(FILE *vtfFile, int rounds);
void makeVTF(FILE *vtfFile);

#endif /* makeVTFfile_h */
