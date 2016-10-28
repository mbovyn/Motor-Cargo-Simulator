/*** Matt Bovyn mbovyn@uci.edu  ***/

//Basic librarys and functions to include
#include <math.h>
#include <stdlib.h>
//#include <time.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "twister.c"

/*******************************************************************************/
//  INCLUDES
/*******************************************************************************/

#include "motors.h" //header which intializes all variables
#include "getInputParams.c" //reads parameter file
#include "dataCollection.c" //writes data to file
#include "motorHelpers_setup.c" //file with functions for setup
#include "motorHelpers_rates.c" //functions for finding stepping rates
#include "stochasticequations.c" //genearated by mathematica
#include "motorHelpers_sODE.c" //functions for setting up the solve
#include "simulate_cargo.c" //main simulation

/*******************************************************************************/
//  MAIN
/*******************************************************************************/

// arguments: parameter_file_name run_name repeats verboseness_number D eps_0 pi_0
int main( int argc, char *argv[] )
{
    // parameter file name
    if(argv[1])
        strcpy(paramFileName, argv[1]);

    // runName string, to label output files
    if(argv[2])
        strcpy(runName, argv[2]);

    //number of times to repeat simulation - default to 1
    repeats=1;
    if(argv[3])
        repeats=atoi(argv[3]);

    // IF verboseTF = 0, will not output anything
    // IF verboseTF = 1, will echo input parameters and say number of successes
    // if =2, will additionally every simulation - stop condition
    // if =3, will output a bunch of error checking things and important events
    // if =4, will output every time step
    verboseTF = 0;
    if(argv[4]) // Verbose Output
        verboseTF = atoi(argv[4]);

    // Intialize random number generator (twister.c)
    RanInit(0);
    if(verboseTF>0){
        //if ever see two that are the same, know iSEED wasn't updated
        printf("The test rand is %f\n",RAND);
    }

    //can bring D_m[0] and eps_0[0] in from the command line here
    //if they are not input they are read from the parameter file
    D_m[0]=NAN;
    if(argc>5){
        D_m[0]=atof(argv[5]);
    }

    eps_0[0]=NAN;
    if(argc>6){
        eps_0[0]=atof(argv[6]);
    }

    pi_0[0]=NAN;
    if(argc>7){
        pi_0[0]=atof(argv[7]);
    }

    z_MT_offset=NAN;
    if(argc>8){
        z_MT_offset=atof(argv[8]);
    }

    R=NAN;
    if(argc>9){
        R=atof(argv[9]);
    }

    // load parameters
    getInputParams();
    //Print out last thing we read in
    //this makes sure everything was read in correctly
    //(if any are incorrectly read in the last will be too as they are sequential)
    if(verboseTF>0){
        printf("Read in StopOnTime as %g\n",StopOnTime);
    }
    //print number of motors and parameters we're running
    if(verboseTF>0){
        printf("Running with %ld kinesins and %ld dyneins\n",N[0],N[1]);
        printf("Running D = %g, eps_0 = %g, pi_0 = %g\n",D_m[0],eps_0[0],pi_0[0]);
        printf("Running %d repeats\n",repeats );
    }

    //open summary file
    strcpy(summaryName,runName);
    strcat(summaryName,"_Summary");
    strcat(summaryName,".txt");

    //if summary file exists from another call, open it
    //otherwise, create it and write the header
    if( access( summaryName, F_OK ) != -1 ) {
        //file exists
        fSummary = fopen(summaryName, "a");
    } else {
        // file doesn't exist
        fSummary = fopen(summaryName, "w");
        fInUse=fSummary;
        writeBaseHeader();
        writeSummaryHeader();
        writeCenterLocsHeader();
        fprintf(fSummary, "\n");
    }

    //call simulation function in loop

    for(j=0;j<repeats;j++){
        result=simulate_cargo();
        //count up number of results we've labeled as success for this trial
        if(result==2){
            successes++;
        }
    }

    fclose(fSummary);

    //print the final score
    if(verboseTF>0){
        printf("There were %d successes in %d trials\n",successes,repeats );
    }

    return 0;

} // finished main
