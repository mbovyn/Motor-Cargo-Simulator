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

//in the preprocessor, select which equation files to include
//want to do this because the equation files with large numbers of motors
//take a long time to compile
#if (0 <= NMOTORSMAX && NMOTORSMAX <= 5)
    #include "stochasticequations5.c" //genearated by mathematica
    #include "beadequations5.c"
#elif (5 < NMOTORSMAX && NMOTORSMAX <= 10)
    #include "stochasticequations10.c" //genearated by mathematica
    #include "beadequations10.c"
#elif (10 < NMOTORSMAX && NMOTORSMAX <= 20)
    #include "stochasticequations20.c" //genearated by mathematica
    #include "beadequations20.c"
#elif (20 < NMOTORSMAX && NMOTORSMAX <=50)
    #include "stochasticequations5.c" //genearated by mathematica
    #include "beadequations50.c"
#else
    #include "stochasticequations5.c" //genearated by mathematica
    #include "beadequations101.c"
#endif

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

    if (verboseTF>4){
        printf("\n-------------------------------------------------\n");
        printf("\nBeginning new run\n\n");
        printf("-------------------------------------------------\n\n");
    }

    // Intialize random number generator (twister.c)
    RanInit(0); //can set RanInit(1) to use same seed every time
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

    N[0]=NAN;
    if(argc>10){
        N[0]=atof(argv[10]);
    }

    Ftrap[0]=NAN;
    if(argc>11){
        Ftrap[0]=atof(argv[11]);
    }

    theta_c=NAN;
    if(argc>12){
        theta_c=atof(argv[12]);
    }

    // load parameters

    if (verboseTF>4)
        printf("\nReading in Parameters\n\n");


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

    initializeDataCollection();

    //call simulation function in loop

    for(j=0;j<repeats;j++){

        result=simulate_cargo();

    }

    finalizeDataCollection();

    //print the final score
    if(verboseTF>0){
        printf("There were %d successes in %d trials, where success is ",successes,repeats );
        if(success_mode==1){
            switch(success){
                case 0:
                    printf("not possible\n");
                    break;
                case 1:
                    printf("type0motor0 being bound at the last step\n");
                    break;
                default:
                    printf("not defined\n");
            }
        }else{
            printf("stopping by condition %d\n",success);
        }
    }

    return 0;

} // finished main
