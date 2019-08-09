//
//  gnuplot.h
//  DP
//
//  Created by Magnus Knaedal on 16.04.2018.
//  Copyright 2018 Magnus Knaedal. All rights reserved.
//
/**********************************************************************
 * Purpose:
 - Creates pipe to Gnuplot and plots error and set-point as a function of time (Error(t), Set-point(t)).
 
 * Rutines:
 - plotResults: Plots results to Gnuplot.
    Input: void.
    Output: void.
 
 **********************************************************************/

#ifndef gnuplot_h
#define gnuplot_h

/******************************LIBRARIES******************************/
#include <stdio.h>  // I/O-library.

/******************************METHODS*******************************/
void plotResults(void);

#endif /* gnuplot_h */
