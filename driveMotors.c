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
    #if defined(keepseed)
        int seed_option=1;
    #else
        int seed_option=0;
    #endif
    RanInit(seed_option); //can set RanInit(1) to use same seed every time

    if(verboseTF>1){
        //if ever see two that are the same, know iSEED wasn't updated
        printf("The test rand is %f\n",RAND);
    }else{
        RAND;
    }

    //can bring D_m[0] and eps_0[0] in from the command line here
    //if they are not input they are read from the parameter file
    D_m[0]=NAN;
    if(argc>5){
        D_m[0]=atof(argv[5]);
        // printf("read in D as %s\n",argv[5]);
        // printf("read in D as %f\n",atof(argv[5]));
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

    N[0]=-1;
    if(argc>10){
        N[0]=atoi(argv[10]);
    }

    Ftrap[0]=NAN;
    if(argc>11){
        Ftrap[0]=atof(argv[11]);
    }

    theta_c=NAN;
    if(argc>12){
        theta_c=atof(argv[12]);
    }

    MT_angle=NAN;
    if(argc>13){
        MT_angle=atof(argv[13]);
    }

    // load parameters

    if (verboseTF>3)
        printf("\nReading in Parameters\n\n");


    getInputParams();

    //print number of motors and parameters we're running
    if(verboseTF>0){
        printf("Running with %d kinesins and %d dyneins\n",N[0],N[1]);

        printf("Parameters for type0 motors are:\n");
        printf("     D = %g\n",D_m[0]);
        printf("     eps_0 = %g\n",eps_0[0]);
        printf("     pi_0 = %g\n",pi_0[0]);
        printf("Global parameters are:\n");
        printf("     MT_offset = %g\n",z_MT_offset);
        printf("     R = %g\n",R);
        printf("     Trap force x component = %g\n",Ftrap[0]);
        printf("     Critical Angle theta_c = %g\n",theta_c);

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
                case 2:
                    printf("went more than 10 microns\n");
                    break;
                case 3:
                    printf("underwent tug of war\n");
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
