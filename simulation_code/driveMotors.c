/*** Matt Bovyn mbovyn@uci.edu  ***/

//Error codes:
//1: Unable to open one of the input files
//2: Unsupported compile parameters
//3: Mismatch between parameter file and read in functions
//4: Bad input from parameter file
//5: Bad Gillespie result
//6: Graceful exit for one reason or another

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

//in the preprocessor, select which equation files to include
//want to do this because the equation files with large numbers of motors
//take a long time to compile
#if defined(bead5)
    #include "beadequations5.c"
    int available_motors_bead=5;
#elif defined(bead10)
    #include "beadequations10.c"
    int available_motors_bead=10;
#elif defined(bead20)
    #include "beadequations20.c"
    int available_motors_bead=20;
#elif defined(bead50)
    #include "beadequations50.c"
    int available_motors_bead=50;
#elif defined(bead101)
    #include "beadequations101.c"
    int available_motors_bead=101;
#else
    #include "beadequations5.c"
    int available_motors_bead=5;
#endif

#if defined(free5)
    #include "stochasticequations5.c"
    int available_motors_free=5;
#elif defined(free10)
    #include "stochasticequations10.c"
    int available_motors_free=10;
#elif defined(free20)
    #include "stochasticequations20.c"
    int available_motors_free=20;
#else
    #include "stochasticequations5.c"
    int available_motors_free=5;
#endif

#include "getInputParams.c" //reads parameter file
#include "dataCollection.c" //writes data to file
#include "motorHelpers_setup.c" //file with functions for setup
#include "motorHelpers_rates.c" //functions for finding stepping rates
#include "stop_conditions.c"

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
    if(argv[3]){
        repeats=atoi(argv[3]);
        //printf("read in repeats as %s\n",argv[3]);
    }

    // IF verboseTF = 0, will not output anything
    // IF verboseTF = 1, will output running params
    // if =2, will say more and additionally output a few lines per repeat
    // if =3, will additionally output important events but not every time step
    //        will also output lines to follow what's going on
    // if =4, will output every time step
    // if =5, will output every time certain functions are called
    verboseTF = 0;
    if(argv[4]) // Verbose Output
        verboseTF = atoi(argv[4]);

    if(verboseTF>1){
        printf("Run name:      %s\nInstance name: %s\n",paramFileName,runName);
    }

    if (verboseTF>2){
        printf("\n-------------------------------------------------\n");
        printf("\nBeginning new run\n\n");
        printf("-------------------------------------------------\n\n");
    }

    // Intialize random number generator (twister.c)
    #if defined(keepseed)
        int seed_option=1;
    #else
        int seed_option=0;
    #endif
    RanInit(seed_option); //can set RanInit(1) to use same seed every time

    if(verboseTF>1){
        //if ever see two that are the same, know iSEED wasn't updated
        if(seed_option){
            printf("Random Seed won't be updated\n");
        } else {
            printf("Random Seed will be updated\n");
        }
        printf("    The test rand is %f\n",RAND);
    }else{
        RAND;
    }

    // load parameters

    if (verboseTF>2)
        printf("\nReading in Parameters\n\n");


    getInputParams();

    if (verboseTF>1)
        printf("Initial location passed in is (%g,%g,%g)\n",
            center_initial[0],center_initial[1],center_initial[2]);

    //print number of motors and parameters we're running
    if(verboseTF>0){
        printf("\nRunning with %d kinesins and %d dyneins\n",N[0],N[1]);

        printf("Parameters for type0 motors are:\n");
        printf("     D = %g\n",D_m[0]);
        printf("     eps_0 = %g\n",eps_0[0]);
        printf("     pi_0 = %g\n",pi_0[0]);
        printf("     F_d = %g\n",F_d[0]);
        printf("     k_m = %g\n",k_m[0]);
        printf("Global parameters are:\n");
        //printf("     MT_offset = %g\n",z_MT_offset);
        printf("     R = %g\n",R);
        //printf("     External force z component = %g\n",Ftrap[2]);
        //printf("     Critical Angle theta_c = %g\n",theta_c);
        //printf("     MT Angle = %g\n",MT_angle);
        printf("     eta = %g\n",eta);
        printf("     dt_max_base = %g\n",dt_max_base);

        printf("Running %d repeats\n\n",repeats );
    }

    //set up for data collection
    initializeDataCollection();

    //call simulation function in loop
    for(j=0;j<repeats;j++){

        result=simulate_cargo();

    }

    //close files
    finalizeDataCollection();

    //print the final score
    // if(verboseTF>0){
    //     printf("There were %d successes in %d trials, where success is ",
    //         successes,repeats );
    //     if(success_mode==1){
    //         switch(success){
    //             case 0:
    //                 printf("not possible\n");
    //                 break;
    //             case 1:
    //                 printf("type0motor0 being bound at the last step\n");
    //                 break;
    //             case 2:
    //                 printf("went more than 10 microns\n");
    //                 break;
    //             case 3:
    //                 printf("underwent tug of war\n");
    //                 break;
    //             default:
    //                 printf("not defined\n");
    //         }
    //     }else{
    //         printf("stopping by condition %d\n",success);
    //     }
    // }

    return 0;

} // finished main
