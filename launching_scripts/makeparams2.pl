#!/usr/bin/perl
#use strict;
#use warnings;

# makes parameter files ######################################################

print "--->Writing parameter files (makeparams2.pl)\n";

our @namelist = ();

#for values in array for first parameter
for my $ctr1 ( 0 .. $#{ $sweepvals[0] } ) {
    our $param1=$sweepvals[0][$ctr1];
    #print "param1 is $param1\n";
    our $follow1=$followvals[0][$ctr1];
    #our $follow2=$followvals[1][$ctr1];

    #for values in array for second parameter
    for my $ctr2 ( 0 .. $#{ $sweepvals[1] } ) {
        our $param2=$sweepvals[1][$ctr2];
        #print "param2 is $param2\n";
        our $follow2=$followvals[1][$ctr2];

        #specific name for each instance that will run]
        my $id1=$ctr1+$ctr1start;
        my $id2=$ctr2+$ctr2start;
        my $instance_name=$run_name . "." . $id1 . "." . $id2;
        #print "$instance_name\n";
        push @namelist, $instance_name;

        #pub file name
        my $file_name=$instance_name . "_params.txt";

        #if change the cargo center location if the cargo-MT distance is
        #supposed to stay set for changing R
        if($setCargoMT_dist>=0) {
            # if($Rname eq "param1") {
            #     print "triggered, cz=$cz";
            #     $cz = $pz1 + $R_MT1 + $setCargoMT_dist + $param1;
            #     print " after, cz=$cz\n";
            # } elsif($Rname eq "param2") {
            #     #print "triggered, cz=$cz";
            #     $cz = $pz1 + $R_MT1 + $setCargoMT_dist + $param2;
            #     #print " after, cz=$cz\n";
            # } else {
                print "!!!!moving center from cz=$cz";
                $cz = $pz1 + $R_MT1 + $setCargoMT_dist + $$Rname;
                print " to cz=$cz\n";
            # }
        }
        if($setTrapMT_dist_to_R) {
                print "!!!!moving trap from TCz=$TCz";
                $TCz = $pz1 + $R_MT1 + $$Rname;
                print " to TCz=$TCz\n";
        }

        #open file for writing and print the following
        open (FOOD, ">$file_name" ) or die "can't open $file_name";
        print FOOD << "EOF";
//
// Parameters for
// $instance_name
//
// Generated by makeparams.pl
//
//

//Input parameters------------------------------------------------------------

//Motor Parameters
//entry 1 for kinesins, entry 2 for dynein

N      $$N1name $$N2name $cc1

//Muller Sim
F_s    $$F_s1name $$F_s2name        $cc2
F_d    $$F_d1name $$F_d2name        $cc3
eps_0  $$eps_01name $$eps_02name    $cc4
pi_0   $$pi_01name $$pi_02name      $cc5
v_f    $$v_f1name $$v_f2name        $cc6
v_b    -.006 .006 //max backward velocity (microns/s)

//Kunwar Sim
a         $$a1name $$a2name    $cc7
b         $$b1name $$b2name  $cc8
w         $$w1name $$w2name          $cc9
L         $$L1name $$L2name    $cc10
k_m       $$k_m1name $$k_m2name      $cc11
step_size $$s1name $$s2name $cc12

//Bovyn Sim
D_m       $$D_m1name $$D_m2name  $cc13

//Cargo Parameters

center  $$cxname $$cyname $$czname $cc14
R       $$Rname     $cc15
eta     $$etaname  $cc16

//Microtubule Parameters

n_MTs   $n_MTs     $cc17
kcMT    $$kcMTname $cc18

//Keyword Arguments------------------------------------------------------------

//Motor Location

InitialLocations $InitialLocations $IL2 $IL3
$cc19

MotorDiffusion $MotorDiffusion
$cc20

//Interaction of motors with MT

InitialBinding $InitialBinding $$IB2name
$cc21

Binding $Binding $B2
$cc22

Unbinding $Unbinding
$cc23

Stepping $Stepping $S2
$cc24

InitialNucleotideBehavior $InitialNucleotideBehavior
$cc25

NucleotideBehavior $NucleotideBehavior $NB2 $NB3
$cc26

//Bound motor behavior

MotorLoading $MotorLoading
$cc27

//Cargo Behavior

CargoBehavior $CargoBehavior $PerfectSterics
$cc28

ExternalForce $ExternalForce $$EFxname $$EFyname $$EFzname $$TCxname $$TCyname $$TCzname
$cc29

ExternalTorque $ExternalTorque $$ETxname $$ETyname $$ETzname
$cc30

UseStericSpring $UseStericSpring $Surface
$cc31

//Output

ReturnDetails $ReturnDetails $RD2 $RD3 $RD4 $RD5 $RD6
$cc32

ReturnFinalState $ReturnFinalState
$cc33

//Simulation end conditions (1=yes,0=no)
RequireAttached $RequireAttached        $cc34
StopOnMotor2Attach $StopOnMotor2Attach     $cc35
StopOnAllAttached $StopOnAllAttached      $cc36
StopOnStep $StopOnStep             $cc37
StopOnTime $StopOnTime           $cc38
StopOnDistance $StopOnDistance         $cc39
StopBelowThetaC $StopBelowThetaC $$SBname     $cc40
multiMT_assay $multiMT_assay $$MT_anglename         $cc41
StopOnBeadDissociation $StopOnBeadDissociation $cc42
StopOnCargoBinding $StopOnCargoBinding     $cc43

//Success Conditions
Success $Success $SS2
$cc44

//debugging
dt_override $dt_override $cc45

//check for correct read in
checkbit 732
checkbit2 576

EOF
        close FOOD;

        #MT params file
        my $MT_file_name=$instance_name . "_MT_params.txt";
        open (FOOD, ">$MT_file_name" ) or die "can't open $MT_file_name";
        print FOOD << "EOF";
//
// params for MTs
//

//point (x y z) unit vector (x y z) R_MT
($px1 $py1 $pz1) ($vx1 $vy1 $vz1) $R_MT1
($px2 $py2 $pz2) ($vx2 $vy2 $vz2) $R_MT2

EOF
        close FOOD;
        #done writing

    }
}
#print "@namelist\n";
#print "--->Done writing parameter files (makeparams2.pl)\n";
return 1;
