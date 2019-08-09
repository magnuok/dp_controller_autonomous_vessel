//
//  main.c
//  DP
//
//  Created by Magnus Knaedal on 24.01.2018.
//  Copyright 2018 Magnus Knaedal. All rights reserved.
//

#include "main.h"

/* Global variables */
PhidgetRCServoHandle handleServo;
PhidgetVoltageInputHandle handleVoltage;
static _PIDvalues PIDvalues;
static int rounds = 0;
static int quit = FALSE;
static FILE * gnuplotFile;
static FILE * vtfFile;

static void regulator(){
    
    /* Initialize variables */
    struct timeval tic, toc;
    long long lapTime=0, totalTime=0;
    
    while(quit != TRUE){
        
        gettimeofday(&tic, NULL);
        
        /* New position-value */
        PIDvalues.newVoltagePosition = getPosition(&handleVoltage);
        
        /* Calculate new pulse */
        PIDvalues.pulseDuty = pulseDutyChange(&PIDvalues);
        
        /* Set new pulse */
        setDuty(&handleServo, PIDvalues.pulseDuty);
        
        /* Add new result to VTF-file */
        resultsVTF(vtfFile, PIDvalues.newVoltagePosition, rounds);
        rounds++;
        
        gettimeofday(&toc, NULL);
        
        /* Calculate loop-time in milliseconds */
        lapTime = (toc.tv_sec*1000LL + toc.tv_usec/1000) - (tic.tv_sec*1000LL + tic.tv_usec/1000);
        
        /* Round up if laptime < 1 milliseconds */
        if(lapTime < 1){
            lapTime = 1;
        }

        totalTime += lapTime;
        
        /* Add result to Gnuplot-file */
        fprintf(gnuplotFile, "%lld %f %f %f\n", totalTime, PIDvalues.setPoint+PIDvalues.error ,PIDvalues.setPoint, PIDvalues.pulseDuty);
        
        /* sleep for 10 milliseconds to get a fixed DT */
        if(lapTime < DT){
            usleep((int)(DT-lapTime)*1000);
        }
    }
}

static void program() {
    
    /* Initialize variables */
    time_t start, end;
    const time_t timeIntervall = 10;
    double input = -1;
    
    printf("\n\n ----------Dynamic positioning program----------\n\n"
           "Initial position set to: %lf\n\n", PIDvalues.setPoint);
    
    /* Consol menu */
    while (input != 0) {
        printf("1. Press 1 to change position\n"
               "2. Press 2 to look at relevant values for 10 seconds\n"
               "3. Press 0 to exit program\n");
        scanf("%lf", &input);
        
        /* 1. */
        if(input == 1){
            printf("Change position:\n"
                   "Value between 5 - back of tank, and 4 - front of tank\n");
            scanf("%lf", &PIDvalues.setPoint);
        }
        
        /* 2. */
        else if(input == 2){
            start = time(NULL);
            end = start + timeIntervall;
            while(start < end){
                start = time(NULL);
                printf("\nNew position [V]: %f\n"
                       "Error [V]: %f\n\n"
                       "P_term: %f\n"
                       "I_term: %f\n"
                       "D_term: %lf\n"
                       "Calculated pulse: %f\n\n", PIDvalues.newVoltagePosition, PIDvalues.error, PIDvalues.Pterm, PIDvalues.Iterm, PIDvalues.Dterm, PIDvalues.pulseDuty);
                
                /* Get a time gap between each print */
                usleep(1000);
            }
        }
        
        /* 3. */
        else if(input == 0){
            quit = TRUE;
        }
    }
}

int main() {
    
    /* Initialize variables */
    PIDvalues.setPoint = 4.2;
    PIDvalues.oldError = 0;
    PIDvalues.Itemporary = 0;
    PIDvalues.pulseTemporary = 85.990;
    pthread_t thread_2;
    
    /* Open files */
    vtfFile = fopen(FILEPATH_VTF, "w");
    if(vtfFile == 0) {
        perror("File opening failed: VTF-file");
        exit(1);
    }
    gnuplotFile = fopen(FILPATH_GNUPLOT, "w");
    if(gnuplotFile == 0) {
        perror("File opening failed: Gnuplot-file");
        exit(1);
    }
    
    makeVTF(vtfFile);
    
    /* Open and initialize phidgets */
    openPhidgets(&handleServo, &handleVoltage);
    
    /* Create a second thread to executes Loop-method */
    if(pthread_create(&thread_2, NULL, (void*)regulator, NULL)) {
        fprintf(stderr, "Error creating thread\n");
        exit(1);
    }
    
    program();
    
    /* Joins threads before program ends */
    if(pthread_join(thread_2, NULL)) {
        fprintf(stderr, "Error joining thread\n");
        exit(1);
    }
    
    /* Close phidgets */
    closePhidgets(&handleServo, &handleVoltage);
    
    /* Prints vector of results to VTF-file */
    vectorVTF(vtfFile, rounds);
    
    /* Close files */
    fclose(vtfFile);
    fclose(gnuplotFile);
    
    /* Plot results to gnuPlot */
    plotResults();
    
    return 0;
}




