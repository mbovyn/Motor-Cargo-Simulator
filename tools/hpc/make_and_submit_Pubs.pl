#!/usr/bin/perl
# creates a number of job execution lines for submission to pbs

#need to change values in here --------------------------------------------

#define run name (match parameter files)
my $run_name = "set this!";
#define directory name to find executable and write to
my $dir_name = "set this!";
#base name for HPC (needs to be short)
my $hpc_name = "set this!";

#define base, max and increment values
my $val1Base = "set this!";
my $val2Base = "set this!";
my $val1Max = "set this!";
my $val2Max = "set this!";
my $val1increment = "set this!";
my $val2increment = "set this!";
my $repeats = "set this!";

#variable business using symbolic reference
#http://www.perlmonks.org/?node_id=724856

#defaults (leave these)
my $D="NANpassthrough";
my $eps_0="NANpassthrough";
my $pi_0="NANpassthrough";
my $z_MT_offset="NANpassthrough";
my $R="NANpassthrough";
my $N0="neg1passthrough";
my $F_trap="NANpassthrough";
my $theta_c="NANpassthrough";
my $MT_angle="NANpassthrough";
#values to be passed through
our $neg1passthrough=-1;
our $NANpassthrough="NAN";

#set params to be swept to param1 and param2 here
my $set_this="param1";
my $set_this="param2";


#need to change values in here --------------------------------------------

# make pubs ###########################################################

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
        my $file_name=$instance_name . ".pub";
        #hpc run name
        my $hpc_instance_name = $hpc_name . "." . $ctr1 . "." . $ctr2;
        #open file for writing and print the following
        open (FOOD, ">pubs/$file_name" );
        print FOOD << "EOF";
#!/bin/bash
#\$ -N $hpc_instance_name
#\$ -q bio,abio,free64,pub64
#\$ -ckpt blcr
#\$ -e logs/$instance_name.err
#\$ -o logs/$instance_name.log

cd /pub/mbovyn/$dir_name

echo Running on host `hostname`
echo Time is `date`
echo Directory is `pwd`

# Run executable
#motors.x   run_name   instance_name  repeat   verbose D   eps_0   pi_0   z_MT_offset   R   N[0] F_trap   theta_c   MT_angle
./motors.x  $run_name  $instance_name $repeats 2       $$D $$eps_0 $$pi_0 $$z_MT_offset $$R $$N0 $$F_trap $$theta_c $$MT_angle

echo Finished at `date`

EOF
        close FOOD;
        #done writing

        #submit job
        system "qsub pubs/$file_name";

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
