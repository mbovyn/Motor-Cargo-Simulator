/*** Jun Allard jun.allard@uci.edu                   ***/

//Basic librarys and functions to include
#include <math.h>
#include <stdlib.h>
//#include <time.h>
#include <stdio.h>
#include <string.h>
#include "twister.c"

/*******************************************************************************/
//  INCLUDES
/*******************************************************************************/

#include "motors.h" //header which intializes all variables
#include "getInputParams.c" //reads parameter file
#include "dataCollection.c" //writes data to file
#include "motorHelpers_setup.c" //file with functions to compute motor actions
#include "motorHelpers_rates.c"
#include "motorHelpers_sODE.c"
#include "simulate_cargo.c" //main simulation

/*******************************************************************************/
//  MAIN
/*******************************************************************************/

// arguments: parameter_file_name run_name verboseness_number
int main( int argc, char *argv[] )
{
    if(argv[1]) // parameter file suffix
        strcpy(paramFileName, argv[1]);

    // output runName
    if(argv[2]) // runName for output files
        strcpy(runName, argv[2]);

    // IF verboseTF = 0,
    // IF verboseTF = 1,
    verboseTF = 0;
    if(argv[3]) // Verbose Output
        verboseTF = atoi(argv[3]);

    // Intialize random number generator (twister.c)
    RanInit(0);
    if(verboseTF>0){
        //if ever see two that are the same, know iSEED wasn't updated
        printf("The test rand is %f, ",RAND);
    }

    //can bring D_m[0] and eps_0[0] in from the command line here
    //if they are not input they are read from the parameter file
    D_m[0]=NAN;
    if(argc>4){
        D_m[0]=atof(argv[4]);
    }

    eps_0[0]=NAN;
    if(argc>5){
        eps_0[0]=atof(argv[5]);
    }

    pi_0[0]=NAN;
    if(argc>6){
        pi_0[0]=atof(argv[6]);
    }

    // load parameters
    getInputParams();
    //Print out last thing we read in
    //this makes sure everything was read in correctly
    //(if any are off they last will be too as they are sequential)
    if(verboseTF>2){
        printf("Read in StopOnTime as %g\n",StopOnTime);
    }

    if(verboseTF>0){
        printf("Running D = %g, eps_0 = %g, pi_0 = %g\n",D_m[0],eps_0[0],pi_0[0]);
    }

    int result;
    int successes=0;
    int j;

    //call simulation function
    // for(j=0;j<10;j++){
    //     result=simulate_cargo();
    //     if(result==2){
    //         successes++;
    //     }
    // }
    //
    // printf("%d\n",successes );

    while(successes<1000){
        result=simulate_cargo();
        if(result==3){
            successes++;
        }
    }

    //printf("%d\n",successes );

    return 0;

} // finished main
