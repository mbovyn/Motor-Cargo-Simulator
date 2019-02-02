/*** Matt Bovyn mbovyn@uci.edu  ***/

//Returns:
//0: Completed successfully
//1: Unable to open one of the input files
//2: Unsupported compile parameters
//3: Mismatch between parameter file and read in functions
//4: Bad input from parameter file on mode choice
//5: Bad Gillespie result

/******************************************************************************/
//  INCLUDES
/******************************************************************************/

//Basic librarys and functions to include
#include <math.h>
#include <stdlib.h>
//#include <time.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

//local files
#include "twister.c" //does random number generation
#include "motors.h" //header which intializes all variables

//in the preprocessor, select which equation files to include
//want to do this because the equation files with large numbers of motors
//take a long time to compile

//must compile with correct keyword. Ex:
// gcc -O3 driveMotors.c -o motors.x -lm -Dbead5

//bead motors
#if defined(bead0) //Any number of motors between 0 and 5
    #include "beadequations0.c"
    int available_motors_bead=0;
#elif defined(bead5) //Any number of motors between 0 and 5
    #include "beadequations5.c"
    int available_motors_bead=5;
#elif defined(bead10) //Any number of motors between 0 and 10
    #include "beadequations10.c"
    int available_motors_bead=10;
#elif defined(bead20) //Any number of motors between 0 and 20
    #include "beadequations20.c"
    int available_motors_bead=20;
#elif defined(bead50) //Any number of motors between 0 and 50
    #include "beadequations50.c"
    int available_motors_bead=50;
#elif defined(bead101) //1, 11, 21, 31, ... 91, or 101 motors
    #include "beadequations101.c"
    int available_motors_bead=101;
#else //otherwise define an empty function and set no motors availiable
    void bead_equations(){};
    int available_motors_bead=0;
#endif
//free motors
#if defined(free0) //Any number of motors between 0 and 5
    #include "stochasticequations0.c"
    int available_motors_free=0;
#elif defined(free5) //Any number of motors between 0 and 5
    #include "stochasticequations5.c"
    int available_motors_free=5;
#elif defined(free10) //Any number of motors between 0 and 10
    #include "stochasticequations10.c"
    int available_motors_free=10;
#elif defined(free20) //Any number of motors between 0 and 20
    #include "stochasticequations20.c"
    int available_motors_free=20;
#else
    void stochastic_equations(){};
    int available_motors_free=0;
#endif

#include "getInputParams.c" //reads parameter file
#include "dataCollection.c" //writes data to file
#include "motorHelpers_setup.c" //file with functions for setup
#include "motorHelpers_rates.c" //functions for finding stepping rates
#include "stop_conditions.c"
#include "motorHelpers_sODE.c" //functions for setting up the solve
#include "aggregate_numbers.c"
#include "simulate_cargo.c" //main simulation

/*******************************************************************************/
//  MAIN
/*******************************************************************************/

// arguments: run_name repeats verboseness_number keep_seed
int main( int argc, char *argv[] )
{
    // runName string, label of parameter and output files
    if(argv[1])
        strcpy(runName, argv[1]);

    //number of times to repeat simulation - default to 1
    repeats=1;
    if(argv[2]){
        repeats=atoi(argv[2]);
        //printf("read in repeats as %s\n",argv[3]);
    }

    //Verbosity
    // IF verboseTF = 0, will not output anything
    // IF verboseTF = 1, will output general things, nothing inside repeat loop
    // if =2, will say more and additionally output a few lines per repeat
    // if =3, will additionally output important events but not every time step
    //        will also output lines to follow what's going on
    // if =4, will output every time step
    // if =5, will output every time certain functions are called
    verboseTF = 1;
    if(argv[3]) // Verbose Output
        verboseTF = atoi(argv[3]);

    // Intialize random number generator (twister.c)
    //can set RanInit(1) to use same seed every time
    //otherwise the seed is updated and the next run will use the new seed
    //default to new seed every time
    keep_seed=0;
    if(argv[4]){
        keep_seed=atoi(argv[4]);
    }

    // for hpc runs in job arrays
    //passed in as which number repeat this is
    rpt_start=0;
    if(argv[5]){
        rpt_start=atoi(argv[5]);
    }

    //if on hpc in job array, make sure the repeats aren't on the rand stream by
    // generating rpt_start random variables before starting code
    if(rpt_start){
        RanInit(1); //twister.c
        for(i=0;i<rpt_start;i++){
            RAND;
        }
    }else{
        //initialize normally
        RanInit(keep_seed); //twister.c
    }

    if (verboseTF>2){
        printf("\n-------------------------------------------------\n");
        printf("\nBeginning new run\n\n");
        printf("-------------------------------------------------\n");
    }
    if(verboseTF>0 && rpt_start<2)
        printf("\nStarting %s\n",runName);

    // load parameters
    if (verboseTF>2)
        printf("\nReading in Parameters\n");
    getInputParams(); //getInputParams.c

    if (verboseTF>2)
        printf("Done with reading in Parameters\n\n");

    //print number of motors and parameters we're running
    if(verboseTF>0 && rpt_start<2){
        //printf("%s:\n",runName);
        if(keep_seed){
            printf("Random Seed won't be updated\n");
        } else {
            printf("Random Seed will be updated\n");
        }
        printf("    The test rand is %f\n",RAND);
        printf("Running with %d kinesins and %d dyneins\n",N[0],N[1]);

        printf("Initial cargo location is (%g,%g,%g)\n",
            center_initial[0],center_initial[1],center_initial[2]);

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
        if(external_force>1){
            printf("     External force parameters are: %g %g %g\n",Fin[0],Fin[1],Fin[2] );
        }
        if(external_torque>1){
            printf("     External force parameters are: %g %g %g\n",TorqeExt[0],TorqeExt[1],TorqeExt[2] );
        }

        printf("Running %d repeats in group %d\n",repeats,rpt_start );
    }else{
        RAND; //need this to keep number of RAND calls the same
    }

    //set up for data collection
    if (verboseTF>2)
        printf("\nInitializing data collection\n");
    initializeDataCollection(); //dataCollection.c

    if(verboseTF>0 && rpt_start<2)
        printf("\n");

    //call simulation function for each repeat
    for(j=0;j<repeats;j++){
        result=simulate_cargo(); //simulate_cargo.c
    }

    //close files
    if (verboseTF>2)
        printf("\nFinalizing data collection\n");
    finalizeDataCollection(); //dataCollection.c

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

    if(verboseTF>0 && rpt_start<1){
        printf("\n%s: Finished all %d repeats in group %d\n\n",runName,repeats,rpt_start+1);
    }

    return 0;

} // finished main
