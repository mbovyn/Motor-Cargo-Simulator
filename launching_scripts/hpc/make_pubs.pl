#!/usr/bin/perl
use warnings;

# create pub files to submit jobs to pbs

# make pubs ###########################################################

#check ISEED exists
if (! -f "ISEED"){
    print "No ISEED\n";
}

#loop over instance names, generated in makeparams2.pl
foreach $instance_name (@namelist) {

    #pub file name
    my $file_name=$instance_name . ".pub";

    #hpc run name
    #get suffix numbers from regex on instance name
    $s = $instance_name;
    $s =~ /$run_name([0-9.]+)/;
    my $hpc_instance_name = $hpc_name . $1;
    #print "$hpc_instance_name\n";

    #check the parameter files exist
    if (! -f $instance_name . "_params.txt"){
        die "Error: Params file $instance_name _params.txt missing"
    };
    if (! -f $instance_name . "_MT_params.txt"){
        die "Error: MT params file $instance_name _MT_params.txt missing"
    };

    #
    my $entry="$instance_name";

    #open file for writing and print the following
    open(FOOD, ">pubs/$file_name" ) or die "Can't open pubs/$file_name";
    print FOOD << "EOF";
#!/bin/bash
#\$ -N $hpc_instance_name
#\$ -q bio,abio,free64,pub64
#\$ -ckpt blcr
#\$ -e logs/$instance_name.err
#\$ -o logs/$instance_name.log

cd /pub/mbovyn/$folder_name

echo Running on host `hostname`
echo Time is `date`
echo Directory is `pwd`

# Run executable
#motors.x instance_name repeat verbose keep_seed
./motors.x $instance_name $repeats 2 0

echo Finished at `date`

EOF
    close FOOD;
    #done writing
}
return 1;
