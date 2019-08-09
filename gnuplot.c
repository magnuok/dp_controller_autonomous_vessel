//
//  gnuplot.c
//  DP
//
//  Created by Magnus Knaedal on 16.04.2018.
//  Copyright 2018 Magnus Knaedal. All rights reserved.
//

# include "gnuplot.h"

void plotResults(){
    
    /* Open pipe to Gnuplot. */
    FILE * gnuplotPipe = popen ("/usr/local/bin/gnuplot -persist", "w");
    
    /* Set terminal x11 0 for plotting position. */
    fprintf(gnuplotPipe, "set term x11 0\n");
    
    /* Specify graphics */
    fprintf(gnuplotPipe, "set title \"Position\" font \",20\"\n");
    fprintf(gnuplotPipe, "set key fixed left top vertical Right noreverse enhanced autotitle box lt black linewidth 1.000 dashtype solid\n");
    fprintf(gnuplotPipe, "set xlabel \"time [ms]\"\n");
    fprintf(gnuplotPipe, "set ylabel \"Error [V]\"\n");
    fprintf(gnuplotPipe, "set samples 50\n");
    fprintf(gnuplotPipe, "set style data lines\n");
    
    /* Plotting error */
    fprintf(gnuplotPipe, "cd \"/Users/magnusknaedal/dmet/DP/DP\"\n");
    fprintf(gnuplotPipe, "plot 'gnuplot_error.temp' using 1:2 title \"Error(t)\"\n");
    fprintf(gnuplotPipe, "replot 'gnuplot_error.temp' using 3 title \"Set point\"\n");
    
    /* Set terminal x11 1 for plotting pulse. */
    fprintf(gnuplotPipe, "set term x11 1\n");
    
    /* Specify graphics */
    fprintf(gnuplotPipe, "set title \"Pulse\" font \",20\"\n");
    fprintf(gnuplotPipe, "set key fixed left top vertical Right noreverse enhanced autotitle box lt black linewidth 1.000 dashtype solid\n");
    fprintf(gnuplotPipe, "set xlabel \"time [ms]\"\n");
    fprintf(gnuplotPipe, "set ylabel \"Pulse [-]\"\n");
    fprintf(gnuplotPipe, "set samples 50\n");
    fprintf(gnuplotPipe, "set style data lines\n");
    
    /* Plotting pulse */
    fprintf(gnuplotPipe, "cd \"/Users/magnusknaedal/dmet/DP/DP\"\n");
    fprintf(gnuplotPipe, "plot 'gnuplot_error.temp' using 1:4 title \"Error(t)\"\n");
    
    fflush(gnuplotPipe);
    pclose(gnuplotPipe);
}
