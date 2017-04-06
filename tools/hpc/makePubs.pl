#!/usr/bin/perl
# creates a number of job execution lines for submission to pbs

my $run_name = "run_length"; # command line

my $i1Max = 16;
my $i2Max = 16;

my $repeats=200;

for (my $i1 = 1; $i1 <= $i1Max; $i1++)
{

    my $N0 = 2+3*$i1;

    for (my $i2 = 1; $i2 <= $i2Max; $i2++)
    {

        my $pi_0 = 2+3*$i2;

        my $instance_name=$run_name . "." . $i1 . "." . $i2;
        my $file_name=$instance_name . ".pub";

        open (FOOD, ">pubs/$file_name" );
        print FOOD << "EOF";

#!/bin/bash
#\$ -N $instance_name
#\$ -q bio,abio,free64,pub64
#\$ -ckpt blcr
#\$ -e logs/$instance_name.err
#\$ -o logs/$instance_name.log

cd /pub/mbovyn/test

echo Running on host `hostname`
echo Time is `date`
echo Directory is `pwd`

# Run your executable and then stuff
./motors.x  $run_name  $instance_name  $repeats 1 NAN NAN $pi_0 NAN NAN $N0

echo Finished at `date`

EOF
            close FOOD;
    }
}
