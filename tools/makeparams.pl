#!/usr/bin/perl
# creates a bunch of parameter text files with different values

#need to change values in here --------------------------------------------

#define run name (match parameter files)
my $run_name = "set this!";

#define base, max and increment values
my $val1Base = "set this!";
my $val2Base = "set this!";
my $val1Max = "set this!";
my $val2Max = "set this!";
my $val1increment = "set this!";
my $val2increment = "set this!";

#variable business using symbolic reference
#http://www.perlmonks.org/?node_id=724856

#defaults (leave these)
my $L = "LPassthrough";
my $eta = "etaPassthrough"
#values to be passed through
our $LPassthrough=.08;
our $etaPassthrough=8.9E-4;

#set params to be swept to param1 and param2 here
#if only sweeping one parameter, set first to $throwaway
my $set_this="param1";
my $set_this="param2";

#in case another, non-sweep value needs to passed through
#our $otherpassthrough=150;
#overwrite previous value
#my $MT_angle="otherpassthrough";


#need to change values in here --------------------------------------------

# make pubs ###########################################################

#check if counter values are set (otherwise loop is infinite)
$val1Max != 0 || die "Error: val1max string or 0\n";
$val2Max != 0 || die "Error: val2max string or 0\n";
$val1increment != 0 || die "Error: val1increment string or 0\n";
$val2increment != 0 || die "Error: val2increment string or 0\n";

#define begining values
my $ctr1=1;
my $ctr2=1;
my $val1=$val1Base;
my $val2=$val2Base;
#loop until values have reached their max
while ( $val1 <= $val1Max )
{

    our $param1 = $val1;

    while ( $val2 <= $val2Max )
    {

        our $param2 = $val2;

        #specific name for each instance that will run
        my $instance_name=$run_name . "." . $ctr1 . "." . $ctr2;
        #pub file name
        my $file_name=$instance_name . ".txt";
        #open file for writing and print the following
        open (FOOD, ">$file_name" );
        print FOOD << "EOF";
//
// Demonstration parameters
//
// 3 motor run length for a bead
//
//
//

//Input parameters------------------------------------------------------------

//Motor Parameters
//entry 1 for kinesins, entry 2 for dynein

N      3 0 //number of motors

//Muller Sim
F_s    5 5 //stall force (pN) 5
F_d    4 4 //detachment force (pN) 4
eps_0  1 1 //base unbinding rate (1/sec) 1
pi_0   5 5 //base binding rate (1/sec) 5
v_f    1 -1 //unloaded forward velocity (microns/s) 1
v_b    -.006 .006 //max backward velocity (microns/s) .006

//Kunwar Sim
a         1.07 1.07  //superstall parameter 1.07
b         .186 .186  //superstall parameter .186
w         2 2        //force-velocity curve exponent 2
L         $$L .08      //motor spring rest length (microns) .1
k_m       320 320    //motor spring constant (pN/micron) 320
step_size .008 -.008  //length of a motor step (microns) .008

//Bovyn Sim
D_m       0 3   //diffusion constant of the anchor (microns^2/s) 3-5

//Cargo Parameters

center  0 0 0 //initial location of center of Cargo [0 0 0]
R       .5   //Cargo Radius (microns) .25
eta     $$eta //Dynamic viscosity of surrounding fluid (10x water) 10*8.9E-4

//Microtubule Parameters

n_MTs   1    // number of MTs in simulation
kcMT    40000  //steric spring to keep cargo out of MT (pN/micron) 40000

//Keyword Arguments------------------------------------------------------------

//Motor Location

InitialLocations 4 0 0
/*
1:
2: Uniform Random on the surface of the sphere
3: Top
4: Bottom
5: Uniform random, rotate so type0motor0 is on top
6: Uniform random, rotate so motor with most close neighbors is on top
7: Start at a defined elevation (specify in 3rd input in degrees)
8:
9:
10:

second parameter: 1  - kin at bottom, 2 for dyn, 3 - kin on top, 4 for dyn
third parameter used to pass in angle (degrees)
 */

MotorDiffusion 10
/*
1: no drag - Diffuse all motors by legacy function
2: no drag - Only diffuse non-attached motors by legacy function
3: free motors - deterministic (cargo trans and rot, motor diffusion set to 0)
4: free motors
5: free motors - cargo diffusion (rot and trans) set to 0
6: free motors - cargo rot and anchor diffusion set to 0
7: free motors - cargo trans and anchor diffusion set to 0
8: free motors - debugging case
9: free motors - anchor diffusion set to 0
10: bead motors
11: bead motors - deterministic (cargo trans and rot, motor diffusion set to 0)
12:
13:
14:
15:
 */

//Interaction of motors with MT

InitialBinding 2 0
/*
1: Bind all in range
2: Bind only 1 Kin
3: Don’t bind
4: Bind 1 dyn
5: Force all motors to bind (debugging)
6:
7:
8:
9:
10:
 */

Binding 1 .5
/*
1: set given binding rate if in range
2: motors don’t bind
3: always bind if in range
4: (not implemented yet) set binding rate if between L and inner limit (fraction*L)
5: Normal binding, but excluded in region for 0nm MT crossings
6:
7:
8:
9:
10:
 */

Unbinding 1
/*
1: Ambarish Unbinding
2: unbind at constant rate eps_0
3: NoUnbinding
4: different between assisting and hindering
5:
6:
7:
8:
9:
10:
 */

Stepping 2 999999999
/*
1: Step at rate determined by unloaded velocity
2: Stepping rate depends on force (Ambarish)
3: no stepping
4: override stepping rate with second input (999999999 for always step)
5: Don’t step into excluded in region for 0nm MT crossings
6:
7:
8:
9:
10:
 */

InitialNucleotideBehavior 1
/*
1: All start ready
2: All start not ready
3:
4:
5:
6:
7:
8:
9:
10:
 */

NucleotideBehavior 0 300 300
/*
1: No nucleotide exchange (explicit)
2: set constant nucleotide exchange rate (give in arguments 2 and 3)
3:
4:
5:
6:
7:
8:
9:
10:
second and third arguments are nucleotide exchange rates
if first argument is set to 0, nucleotide exchange is ignored
 */

//Bound motor behavior

MotorLoading 1
/*
1: Load by stretch of necks
2: Force always 0
*/

//Cargo Behavior

CargoBehavior 1
/*
1: Cargo moves normally
2: On rail - cargo moves only in x
3: stuck - cargo can’t move at all
4:
5:
6:
7:
8:
9:
10:
 */

ExternalForce 1 0 0 -.07
/*
1: no external forces
2: external force given by next three values (x y z)
3: force given by optical trap (not implemented yet)
*/

ExternalTorque 1 0 0 100
/*
1: no external torque
2: external torque given by next three values (x y z)

*/

UseSteric 1
/*
1: Use steric force
0: Don’t use steric force

Note: steric force spring constant specified in kcMT
/*

//Output

ReturnDetails 4 1 0 1
/* create text files with records of anchor and head locations
0: Don’t return any details during simulation
1: Return details every step
2: Return details only when something important happens (step, attachment, etc.)
3: Return details every 100 steps
4: Return details every .001 seconds
5:
set second value to 1 to return file with head locations, 0 for no
set third value to 1 to return file with forces, 0 for no
set fourth value to 1 to return file with rotation of cargo
*/

ReturnFinalState 1
/*
Not implemented

*/

//Simulation end conditions (1=yes,0=no)
RequireAttached 0
StopOnMotor2Attach 0
StopOnAllAttached 0
StopOnStep 0                //0 for don’t stop, otherwise enter step
StopOnTime 0                //0 for don’t stop, otherwise enter time
StopOnDistance 0            //0 for don’t stop, otherwise enter distance in microns
StopBelowThetaC 0 -1        //2nd value elevation in radians -pi/2 to pi/2
multiMT_assay 0             //1 for switch, 2 for ToW
StopOnBeadDissociation 1    //stop if bead is > 500nm from all MTs

//Success Conditions
Success 0 1
/*success success_mode - if mode=0, success if result==success
0: Nothing counts as success
1: type0motor0 is bound
2: went > 10 microns
3: underwent a tug of war
4:
5:
6:
7:
8:
9:
*/

//debugging
dt_override 0 //set this to 0 for no override, otherwise overrides set dt

//check for correct read in
checkbit 732
checkbit2 576

EOF
        close FOOD;
        #MT params file
        my $file_name=$instance_name . "_MT_params.txt";
        #open file for writing and print the following
        open (FOOD, ">$file_name" );
        print FOOD << "EOF";
//
// params for MTs
//

//point (x y z) unit vector (x y z) R_MT
(0 0 .012) (1 0 0) .012
(0 0 -.012) (0 1 0) .012

EOF
        close FOOD;
        #done writing

        #increment inner loop values
        $val2 += $val2increment;
        $ctr2++;

    }
    #reset loop 2 values
    $val2=$val2Base;
    $ctr2=1;
    #increment loop 1 values
    $val1 += $val1increment;
    $ctr1++;
}