//
//  makeVTFfile.c
//  DP
//
//  Created by Magnus Knaedal on 07.03.2018.
//  Copyright 2018 Magnus Knaedal. All rights reserved.
//

#include "makeVTFfile.h"

static double voltageToCentimeter(double voltagePosition){
    
    double centimeterPosition = ((-voltagePosition + 4.3) / 1.4) * 150;
    
    return centimeterPosition;
}

void resultsVTF(FILE *vtfFile, double newVoltagePosition, int round){
    
    static int counter=0;
    
    /* Convert volt to centimeter */
    double newCmPosition = voltageToCentimeter(newVoltagePosition);
    
    /* Add result for hull */
    fprintf(vtfFile, "*RESULTS %d\n", round + 4 + counter);
    fprintf(vtfFile, "%%DIMENSION 3\n");
    fprintf(vtfFile, "%%PER_NODE #2\n");
    fprintf(vtfFile , "%f %f %f\n" , newCmPosition + (2*L_VESSEL)/3, B_VESSEL/2, 0.);
    fprintf(vtfFile , "%f %f %f\n" , newCmPosition + (2*L_VESSEL)/3, -B_VESSEL/2, 0.);
    fprintf(vtfFile , "%f %f %f\n" , newCmPosition, -B_VESSEL/2,0.);
    fprintf(vtfFile , "%f %f %f\n" , newCmPosition, B_VESSEL/2, 0.);
    fprintf(vtfFile , "%f %f %f\n" , newCmPosition + (2*L_VESSEL)/3, B_VESSEL/2, H_VESSEL);
    fprintf(vtfFile , "%f %f %f\n" , newCmPosition + (2*L_VESSEL)/3, -B_VESSEL/2, H_VESSEL);
    fprintf(vtfFile , "%f %f %f\n" , newCmPosition, -B_VESSEL/2, H_VESSEL);
    fprintf(vtfFile , "%f %f %f\n" , newCmPosition, B_VESSEL/2, H_VESSEL);
    fprintf(vtfFile, "\n\n");
    
    /* Add result for bow */
    fprintf(vtfFile, "*RESULTS %d\n", round + 5 + counter);
    fprintf(vtfFile, "%%DIMENSION 3\n");
    fprintf(vtfFile, "%%PER_NODE #3\n");
    fprintf(vtfFile , "%f %f %f\n" , newCmPosition + (2*L_VESSEL)/3, B_VESSEL/2, H_VESSEL);
    fprintf(vtfFile , "%f %f %f\n" , newCmPosition + (2*L_VESSEL)/3, B_VESSEL/2, 0.);
    fprintf(vtfFile , "%f %f %f\n" , newCmPosition + L_VESSEL, B_VESSEL/2, H_VESSEL);
    fprintf(vtfFile , "%f %f %f\n" , newCmPosition + (2*L_VESSEL)/3, -B_VESSEL/2, H_VESSEL);
    fprintf(vtfFile , "%f %f %f\n" , newCmPosition + (2*L_VESSEL)/3, -B_VESSEL/2, 0.);
    fprintf(vtfFile , "%f %f %f\n" , newCmPosition + L_VESSEL, -B_VESSEL/2, H_VESSEL);
    fprintf(vtfFile, "\n\n");
    
    counter++;
}

void vectorVTF(FILE *vtfFile, int round){
    
    static int counter=0;
    
    /* Print vector to file */
    fprintf(vtfFile, "*GLVIEWVECTOR 1\n");
    for (int i=1; i<=(round); i++) {
        fprintf(vtfFile, "%%STEP %d\n", i);
        fprintf(vtfFile, "%d %d %d\n", 1, i+4+counter,i+5+counter);
        counter++;
    }
}

void makeVTF(FILE *vtfFile){
    
    fprintf(vtfFile, "*VTF-1.00\n\n");
    
    /* Flat nodes */
    fprintf(vtfFile, "*NODES 1\n");
    fprintf(vtfFile , "%f %f %f\n" , L_FLAT/2, B_FLAT/2, -0.1);
    fprintf(vtfFile , "%f %f %f\n" , L_FLAT/2, -B_FLAT/2, -0.1);
    fprintf(vtfFile , "%f %f %f\n" , -L_FLAT/2, -B_FLAT/2, -0.1);
    fprintf(vtfFile , "%f %f %f\n" , -L_FLAT/2, B_FLAT/2, -0.1);
    fprintf(vtfFile, "\n\n");
    
    /* VESSEL nodes */
    fprintf(vtfFile, "*NODES 2\n");
    fprintf(vtfFile , "%f %f %f\n" , (2*L_VESSEL)/3, B_VESSEL/2, 0.);
    fprintf(vtfFile , "%f %f %f\n" , (2*L_VESSEL)/3, -B_VESSEL/2, 0.);
    fprintf(vtfFile , "%f %f %f\n" , 0., -B_VESSEL/2, 0.);
    fprintf(vtfFile , "%f %f %f\n" , 0., B_VESSEL/2, 0.);
    fprintf(vtfFile , "%f %f %f\n" , (2*L_VESSEL)/3, B_VESSEL/2, H_VESSEL);
    fprintf(vtfFile , "%f %f %f\n" , (2*L_VESSEL)/3, -B_VESSEL/2, H_VESSEL);
    fprintf(vtfFile , "%f %f %f\n" , 0., -B_VESSEL/2, H_VESSEL);
    fprintf(vtfFile , "%f %f %f\n" , 0., B_VESSEL/2, H_VESSEL);
    fprintf(vtfFile, "\n\n");
    
    fprintf(vtfFile, "*NODES 3\n");
    fprintf(vtfFile , "%f %f %f\n" , (2*L_VESSEL)/3, B_VESSEL/2, H_VESSEL);
    fprintf(vtfFile , "%f %f %f\n" , (2*L_VESSEL)/3, B_VESSEL/2, 0.);
    fprintf(vtfFile , "%f %f %f\n" , L_VESSEL, B_VESSEL/2, H_VESSEL);
    fprintf(vtfFile , "%f %f %f\n" , (2*L_VESSEL)/3, -B_VESSEL/2, H_VESSEL);
    fprintf(vtfFile , "%f %f %f\n" , (2*L_VESSEL)/3, -B_VESSEL/2, 0.);
    fprintf(vtfFile , "%f %f %f\n" , L_VESSEL, -B_VESSEL/2, H_VESSEL);
    fprintf(vtfFile, "\n\n");
    
    /* Create flat element */
    fprintf(vtfFile, "*ELEMENTS 1\n");
    fprintf(vtfFile, "%%NODES #1\n");
    fprintf(vtfFile, "%%QUADS\n");
    fprintf(vtfFile, "1 2 3 4\n");
    fprintf(vtfFile, "\n\n");
    
    /* Create vessel elements
       The hull */
    fprintf(vtfFile, "*ELEMENTS 2\n");
    fprintf(vtfFile, "%%NODES #2\n");
    fprintf(vtfFile, "%%HEXAHEDRONS\n");
    fprintf(vtfFile, "1 2 3 4 5 6 7 8\n");
    fprintf(vtfFile, "\n\n");
    
    /* The bow */
    fprintf(vtfFile, "*ELEMENTS 3\n");
    fprintf(vtfFile, "%%NODES #3\n");
    fprintf(vtfFile, "%%PENTAHEDRONS \n");
    fprintf(vtfFile, "1 2 3 4 5 6\n");
    fprintf(vtfFile, "\n\n");
    
    /* Create geometry from elements */
    fprintf(vtfFile, "*GLVIEWGEOMETRY 1\n");
    fprintf(vtfFile, "%%ELEMENTS\n");
    fprintf(vtfFile, "1 2 3\n");
    fprintf(vtfFile, "\n\n");
    
    /* Result flat */
    fprintf(vtfFile, "*RESULTS 1\n");
    fprintf(vtfFile, "%%DIMENSION 3\n");
    fprintf(vtfFile, "%%PER_NODE #1\n");
    fprintf(vtfFile , "%f %f %f\n" , L_FLAT/2, B_FLAT/2, 0.);
    fprintf(vtfFile , "%f %f %f\n" , L_FLAT/2, -B_FLAT/2, 0.);
    fprintf(vtfFile , "%f %f %f\n" , -L_FLAT/2, -B_FLAT/2, 0.);
    fprintf(vtfFile , "%f %f %f\n" , -L_FLAT/2, B_FLAT/2, 0.);
    fprintf(vtfFile, "\n\n");
    
    /* Result vessel */
    /*  The hull */
    fprintf(vtfFile, "*RESULTS 2\n");
    fprintf(vtfFile, "%%DIMENSION 3\n");
    fprintf(vtfFile, "%%PER_NODE #2\n");
    fprintf(vtfFile , "%f %f %f\n" , (2*L_VESSEL)/3, B_VESSEL/2, 0.);
    fprintf(vtfFile , "%f %f %f\n" , (2*L_VESSEL)/3, -B_VESSEL/2, 0.);
    fprintf(vtfFile , "%f %f %f\n" , 0., -B_VESSEL/2, 0.);
    fprintf(vtfFile , "%f %f %f\n" , 0., B_VESSEL/2, 0.);
    fprintf(vtfFile , "%f %f %f\n" , (2*L_VESSEL)/3, B_VESSEL/2, H_VESSEL);
    fprintf(vtfFile , "%f %f %f\n" , (2*L_VESSEL)/3, -B_VESSEL/2, H_VESSEL);
    fprintf(vtfFile , "%f %f %f\n" , 0., -B_VESSEL/2, H_VESSEL);
    fprintf(vtfFile , "%f %f %f\n" , 0., B_VESSEL/2, H_VESSEL);
    fprintf(vtfFile, "\n\n");
    
    /* The bow */
    fprintf(vtfFile, "*RESULTS 3\n");
    fprintf(vtfFile, "%%DIMENSION 3\n");
    fprintf(vtfFile, "%%PER_NODE #3\n");
    fprintf(vtfFile , "%f %f %f\n" , (2*L_VESSEL)/3, B_VESSEL/2, H_VESSEL);
    fprintf(vtfFile , "%f %f %f\n" , (2*L_VESSEL)/3, B_VESSEL/2, 0.);
    fprintf(vtfFile , "%f %f %f\n" , L_VESSEL, B_VESSEL/2, H_VESSEL);
    fprintf(vtfFile , "%f %f %f\n" , (2*L_VESSEL)/3, -B_VESSEL/2, H_VESSEL);
    fprintf(vtfFile , "%f %f %f\n" , (2*L_VESSEL)/3, -B_VESSEL/2, 0.);
    fprintf(vtfFile , "%f %f %f\n" , L_VESSEL, -B_VESSEL/2, H_VESSEL);
    fprintf(vtfFile, "\n\n");
}

