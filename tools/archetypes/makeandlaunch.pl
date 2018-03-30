#!/usr/bin/perl

# creates parameter files for sweeps, then launches simulations for all
# param files in the folder

#use strict;
use warnings;

###############################################################################
#define run name to label files
our $run_name = "test";

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

our @sweepvars = ("D_m1","N1");
our @sweepvals = (
   [.05, .5],
   [1, 2, 3],
   );

###############################################################################
#set parameter values

our $N1=3;     our $N2=0;      #number of motors
our $F_s1=5;    our $F_s2=5;    #stall force
our $F_d1=4;    our $F_d2=4;    #detachment force
our $eps_01=.7; our $eps_02=.7; #base unbinding rate
our $pi_01=10;  our $pi_02=10;  #base binding rate
our $v_f1=1;    our $v_f2=3;    #max velocity

our $a1=1.07;   our $a2=1.07;   #superstall parameter 1
our $b1=.186;   our $b2=.186;   #superstall parameter 2
our $w1=2;      our $w2=2;      #force velocity curve exponent
our $L1=.08;    our $L2=.08;    #motor length
our $k_m1=320;  our $k_m2=320;  #motor spring stiffness
our $s1=.008;   our $s2= -.008; #step size

our $D_m1=0;    our $D_m2=3;    #motor diffusion constant

our $cx=-1; our $cy=0; our $cz=-.5; #cargo center (microns)
our $R=.5;                          #cargo radius
our $eta=.00089;                    #surrounding fluid viscosity

our $n_MTs=1;
our $kcMT=40000;

#//Keyword Arguments-------------

#//Motor Location

our $InitialLocations=5; our $IL2=0; our $IL3=0;
# /*
# 1:
# 2: Uniform Random on the surface of the sphere
# 3: Top
# 4: Bottom
# 5: Uniform random, rotate so type0motor0 is on top
# 6: Uniform random, rotate so motor with most close neighbors is on top
# 7: Start at a defined elevation (specify in 3rd input in degrees)
# 8: Uniform random, rotate so type0motor0 is on bottom
# 9: All motors set to same random spot
# 10:
#
# second parameter: 1  - kin at bottom, 2 for dyn, 3 - kin on top, 4 for dyn
# third parameter used to pass in angle (degrees)
#  */

our $MotorDiffusion=10;
# /*
# 1: no drag - Diffuse all motors by legacy function
# 2: no drag - Only diffuse non-attached motors by legacy function
# 3: free motors - deterministic (cargo trans and rot, motor diffusion set to 0)
# 4: free motors
# 5: free motors - cargo diffusion (rot and trans) set to 0
# 6: free motors - cargo rot and anchor diffusion set to 0
# 7: free motors - cargo trans and anchor diffusion set to 0
# 8: free motors - debugging case
# 9: free motors - cargo translational diffusion to 0
# 10: bead motors
# 11: bead motors - deterministic (cargo trans and rot, motor diffusion set to 0)
# 12: bead motors - only rotation
# 13:
# 14:
# 15:
#  */

# //Interaction of motors with MT

our $InitialBinding=2; our $IB2=0;
# /*
# 1: Bind all in range
# 2: Bind only 1 Kin
# 3: Don’t bind
# 4: Bind 1 dyn
# 5: Force all motors to bind (debugging)
# 6:
# 7:
# 8:
# 9:
# 10:
#  */

our $Binding=5; our $B2=.5;
# /*
# 1: set given binding rate if in range
# 2: motors don’t bind
# 3: always bind if in range
# 4: (not implemented) set binding rate if between L and inner limit (fraction*L)
# 5: Normal binding, but excluded in region for 0nm MT crossings
# 6:
# 7:
# 8:
# 9:
# 10:
#  */

our $Unbinding=1;
# /*
# 1: Ambarish Unbinding
# 2: unbind at constant rate eps_0
# 3: NoUnbinding
# 4: different between assisting and hindering
# 5:
# 6:
# 7:
# 8:
# 9:
# 10:
#  */

our $Stepping=5; our $S2=999999999;
# /*
# 1: Step at rate determined by unloaded velocity
# 2: Stepping rate depends on force (Ambarish)
# 3: no stepping
# 4: override stepping rate with second input (999999999 for always step)
# 5: Don’t step into excluded in region for 0nm MT crossings
# 6:
# 7:
# 8:
# 9:
# 10:
#  */

our $InitialNucleotideBehavior=1;
# /*
# 1: All start ready
# 2: All start not ready
# 3:
# 4:
# 5:
# 6:
# 7:
# 8:
# 9:
# 10:
#  */

our $NucleotideBehavior=0; our $NB2=300; our $NB3=300;
# /*
# 1: No nucleotide exchange (explicit)
# 2: set constant nucleotide exchange rate (give in arguments 2 and 3)
# 3:
# 4:
# 5:
# 6:
# 7:
# 8:
# 9:
# 10:
# second and third arguments are nucleotide exchange rates
# if first argument is set to 0, nucleotide exchange is ignored
#  */

# //Bound motor behavior

our $MotorLoading=1;
# /*
# 1: Load by stretch of necks
# 2: Force always 0
# */

# //Cargo Behavior

our $CargoBehavior=1;
# /*
# 1: Cargo moves normally
# 2: On rail - cargo moves only in x
# 3: stuck - cargo can’t move at all
# 4:
# 5:
# 6:
# 7:
# 8:
# 9:
# 10:
#  */

our $ExternalForce=2; our $EF2=0; our $EF3=0; our $EF4=-.005;
# /*
# 1: no external forces
# 2: external force given by next three values (x y z)
# 3: force given by optical trap (not implemented yet)
# */

our $ExternalTorque=1; our $ET2=0; our $ET3=0; our $ET4=100;
# /*
# 1: no external torque
# 2: external torque given by next three values (x y z)
#
# */

our $UseSteric=1;
# /*
# 1: Use steric force
# 0: Don’t use steric force
#
# Note: steric force spring constant specified in kcMT
# /*

# //Output

our $ReturnDetails=0; our $RD2=1; our $RD3=0; our $RD4=1;
# /* create text files with records of anchor and head locations
# 0: Don’t return any details during simulation
# 1: Return details every step
# 2: Return details only when something important happens (step, attachment, etc.)
# 3: Return details every 100 steps
# 4: Return details every .001 seconds
# 5:
# set second value to 1 to return file with head locations, 0 for no
# set third value to 1 to return file with forces, 0 for no
# set fourth value to 1 to return file with rotation of cargo
# */

our $ReturnFinalState=1;
# /*
# Not implemented
#
# */

# //Simulation end conditions (1=yes,0=no)
our $RequireAttached=0;
our $StopOnMotor2Attach=0;
our $StopOnAllAttached=0;
our $StopOnStep=0;                  #//0 for don’t stop, otherwise enter step
our $StopOnTime=.1;                  #//0 for don’t stop, otherwise enter time
our $StopOnDistance=0;              #//0 no stop, otherwise distance in microns
our $StopBelowThetaC=0; our $SB=-1; #//2nd value elevation radians -pi/2 to pi/2
our $multiMT_assay=0;               #//1 for switch, 2 for ToW
our $StopOnBeadDissociation=0;      #//stop if bead is > 500nm from all MTs
our $StopOnCargoBinding=1;        #//stop when any motor binds

# //Success Conditions
our $Success=0; our $SS2=3;
# /*success success_mode - if mode=0, success if result==success
# 0: Nothing counts as success
# 1: type0motor0 is bound
# 2: went > 10 microns
# 3: underwent a tug of war
# 4:
# 5:
# 6:
# 7:
# 8:
# 9:
# */

# //debugging
our $dt_override=0; #//set to positive value to override default dt.  Negative to ignore dt_default

###############################################################################
#MT parameters
#Note: for no second MT, set n_MTs to 1 above! Can just leave MT2 values here
#//point (x y z) unit vector (x y z) R_MT
our $px1=0; our $py1=0; our $pz1=.012;
our $vx1=1; our $vy1=0; our $vz1=0; our $R_MT1=.012;

our $px2=0; our $py2=0; our $pz2=-.012;
our $vx2=0; our $vy2=1; our $vz2=0; our $R_MT2=.012;

###############################################################################
#metaparameters

#number of times to repeat
my $repeats=1;
#verbosity (0-5)
my $verbose=0;
#set to 1 to append to old files
my $keep_old=0;
#set to 1 to override wait for open thread
my $dont_wait=0;

###############################################################################
#make parameter files
do "$code_dir/makeparams.pl";
#launch simulations for each parameter file
exec("$code_dir/launch_over_paramfiles.sh '$run_name' '$code_dir' '$working_dir' $repeats $verbose $keep_old $dont_wait")
