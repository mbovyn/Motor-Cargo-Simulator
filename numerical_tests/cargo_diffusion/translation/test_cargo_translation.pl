#!/usr/bin/perl
use strict;
use warnings;

# creates parameter files for sweeps, then launches either locally or on the hpc

###############################################################################
#Run mode
#set to 'local' or 'hpc'.
#If local, this will launch simulations for all param files in the folder
#If hpc, will make and submit pubs
our $launch_mode='local';
#option to not update the random seed
our $keep_seed=0;

#if local, set compilation options
#set compile to yes to compile and copy executable to local folder
our $compile=1;
#set compile keyword to correct one for number of motors
our $compile_keyword='bead0';

#if hpc, also set a short hpc run name
our $hpc_name='motors';
our $folder_name='motors_sweep';

###############################################################################
#define run name to label files
our $run_name = "test_cargo_translation";

###############################################################################
#set code and working directories
our $code_dir = glob("~/project_code/Motor_Freedom");
our $working_dir=$ENV{'PWD'};

###############################################################################
#define variables to loop over and the values to use in Perl arrays
#Ex:
#our @sweepvars = ("D_m1","N1");
#our @sweepvals = (
#    [.05, .5],
#    [1, 2, 3],
#    );

our @sweepvars = ("R");
our @sweepvals = (
   [.05,.25,1,1.5],
   #[.05],
   );
#print "\n@{$sweepvals[0]}\n";
#print "\n@{$sweepvals[1]}\n";

###############################################################################
#set parameter values

our $N1=0;      our $N2=0;         our $cc1="//number of motors";
our $F_s1=5;    our $F_s2=5;       our $cc2="//stall force (pN)";
our $F_d1=3.65; our $F_d2=4;       our $cc3="//detachment force (pN)";
our $eps_01=.8; our $eps_02=.7;    our $cc4="//base unbinding rate (1/s)";
our $pi_01=5;   our $pi_02=10;     our $cc5="//base binding rate (1/s)";
our $v_f1=.8;   our $v_f2=3;       our $cc6="//max velocity (microns/s)";

our $a1=1.56;   our $a2=1.07;      our $cc7="//superstall parameter 1";
our $b1=7.58;   our $b2=.186;      our $cc8="//superstall parameter 2";
our $w1=2;      our $w2=2;         our $cc9="//force velocity curve exponent";
our $L1=.08;    our $L2=.08;       our $cc10="//motor length (microns)";
our $k_m1=320;  our $k_m2=320;     our $cc11="//motor spring stiffness (pN/micron)";
our $s1=.008;   our $s2= -.008;    our $cc12="//step size (microns)";

our $D_m1=0;    our $D_m2=3;       our $cc13="//motor diffusion coefficiant (micron^2/s)";

our $cx=0; our $cy=0; our $cz=0; our $cc14="//cargo center (microns)";
our $R=.25;                        our $cc15="//cargo radius (microns)";
our $eta=.00089;                   our $cc16="//surrounding fluid viscosity (Pa s), water=8.9E-4";

our $n_MTs=1;    our $cc17="//number of MTs";
our $kcMT=40000; our $cc18="//MT-cargo steric spring stiffness (pN/micron)";

#Keyword Arguments-------------

#Motor Location

our $InitialLocations=3; our $IL2=0; our $IL3=0;
our $cc19="/*
1:
2:  Uniform Random on the surface of the sphere
3:  All at Top
4:  All at Bottom
5:  Uniform random, rotate so type0motor0 is on top
6:  Uniform random, rotate so motor with most close neighbors is on top
7:  Start at a defined elevation (specify in 3rd input in degrees)
8:  Uniform random, rotate so type0motor0 is on bottom
9:  All motors at same random spot
10:
second parameter: 1 - kin at bottom, 2 - dyn at bottom, 3 - kin on top, 4 - dyn on top
third parameter used to pass in angle (degrees, from -180 to 180)
north pole=90, +x equator=0, south pole=-90, -x equator=180/-180
*/";

our $MotorDiffusion=10;
our $cc20="/*
1:  no drag - Diffuse all motors by legacy function
2:  no drag - Only diffuse non-attached motors by legacy function
3:  free motors - deterministic (cargo trans and rot, motor diffusion set to 0)
4:  free motors
5:  free motors - cargo diffusion (rot and trans) set to 0
6:  free motors - cargo rot and anchor diffusion set to 0
7:  free motors - cargo trans and anchor diffusion set to 0
8:  free motors - debugging case
9:  free motors - cargo translational diffusion to 0
10: bead motors
11: bead motors - deterministic (cargo trans and rot, motor diffusion set to 0)
12: bead motors - only rotation
13:
14:
15:
*/";

#Interaction of motors with MT

our $InitialBinding=3; our $IB2=0;
our $cc21="/*
1: Bind all in range
2: Bind only 1 Kin
3: Don’t bind
4: Bind 1 dyn
5: Force all motors to bind (debugging)
6:
7:
8:
9:
Set second input to move x position of head of type0motor0 or type1motor0
 */";

our $Binding=2; our $B2=.5;
our $cc22="/*
1: set given binding rate if in range
2: motors don’t bind
3: always bind if in range
4: (not implemented) set binding rate if between L and inner limit (fraction*L)
5: Normal binding, but excluded in region for 0nm MT crossings
6:
7:
8:
9:
10:
*/";

our $Unbinding=3;
our $cc23="/*
1: Bergman 2018 (symmetrical, like Kunwar 2011)
2: unbind at constant rate eps_0
3: NoUnbinding
4: Bergman2018-like asymmetrical
5: Bovyn2018 piecewise exponential, asymmetrical
6:
7:
8:
9:
10:
*/";

our $Stepping=3; our $S2=999999999;
our $cc24="/*
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
*/";

our $InitialNucleotideBehavior=1;
our $cc25="/*
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
*/";

our $NucleotideBehavior=0; our $NB2=300; our $NB3=300;
our $cc26="/*
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
*/";

#Bound motor behavior

our $MotorLoading=1;
our $cc27="/*
1: Load by stretch of necks
2: Force always 0
*/";

#Cargo Behavior

our $CargoBehavior=1;
our $cc28="/*
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
*/";

our $ExternalForce=1; our $EFx=0; our $EFy=0; our $EFz=0;
our $cc29="/*
1: no external forces
2: external force given by next three values (x y z), pN
3: force given by optical trap, linear with stiffness next three values (pN/micron)
*/";

our $ExternalTorque=1; our $ET2=0; our $ET3=0; our $ET4=100;
our $cc30="/*
1: no external torque
2: external torque given by next three values (x y z)
#
*/";

our $UseSteric=0;
our $cc31="/*
1: Use steric force
0: Don’t use steric force
#
Note: steric force spring constant specified in kcMT
/*";

#Output

our $ReturnDetails=4; our $RD2=0; our $RD3=0; our $RD4=0; our $RD5=1;
our $cc32="/* create text files with records
0: Only return end state
1: Return details every step
2: Return details only when something important happens (step, attachment, etc.)
3: Return details every 100 steps
4: Return details every .001 seconds
set second value to 1 to return file with head locations, 0 for no
set third value to 1 to return file with forces, 0 for no
set fourth value to 1 to return file with rotation of cargo
set fifth value to 1 to return file with locations of cargo and anchors
*/";

our $ReturnFinalState=1;
our $cc33="/*
Not implemented
#
*/";

#Simulation end conditions (1=yes,0=no)
our $RequireAttached=0;             our $cc34="//Stop when all motors in unbound state";
our $StopOnMotor2Attach=0;          our $cc35="//Stop when second motor binds";
our $StopOnAllAttached=0;           our $cc36="//Stop when all motors bound";
our $StopOnStep=0;                  our $cc37="//0 for don’t stop, otherwise enter step";
our $StopOnTime=1;                 our $cc38="//0 for don’t stop, otherwise enter time (s)";
our $StopOnDistance=0;              our $cc39="//0 no stop, otherwise distance (microns)";
our $StopBelowThetaC=0; our $SB=-1; our $cc40="//2nd value elevation radians -pi/2 to pi/2";
our $multiMT_assay=0;               our $cc41="//1 for switch, 2 for ToW";
our $StopOnBeadDissociation=0;      our $cc42="//stop if bead is > 500nm from all MTs";
our $StopOnCargoBinding=0;          our $cc43="//stop when any motor binds";

#Success Conditions
our $Success=0; our $SS2=3;
our $cc44="/*success success_mode - if mode=0, success if result==success
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
*/";

# //debugging
our $dt_override=-1E-5; our $cc45="//Value in (s) to override. 0=no override. \"inf\" to ignore dt_default";

###############################################################################
#MT parameters
#Note: for no second MT, set n_MTs to 1 above! Can just leave MT2 values here
#//point (x y z) unit vector (x y z) R_MT
our $px1=0; our $py1=0; our $pz1=-.012;
our $vx1=1; our $vy1=0; our $vz1=0; our $R_MT1=.012;

our $px2=0; our $py2=0; our $pz2=-.012;
our $vx2=0; our $vy2=1; our $vz2=0; our $R_MT2=.012;

###############################################################################
#metaparameters

#number of times to repeat
our $repeats=500;
#verbosity (0-5)
our $verbose=1;
#set to 1 to append to old files
our $keep_old=0;
#set to 1 to override wait for open thread
our $dont_wait=0;
#set to anything>=0 to override z postion of cargo
our $setCargoMT_dist=-1;
#set these to start numbering at something other than 0
#our $ctr1start=0;
#our $ctr2start=0;

###############################################################################
#launch
do "$code_dir/launching_scripts/launch.pl" or die "$@ from call";
