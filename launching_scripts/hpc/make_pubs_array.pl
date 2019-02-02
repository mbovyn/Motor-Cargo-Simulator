#!/usr/bin/perl
use warnings;

# create pub files to submit jobs to pbs

#todo: add grouping number

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
    # #\$ -t 1-$repeats:10 would schedule in groups of 10
    #./motors.x $instance_name.\$SGE_TASK_ID 1 2 0
    open(FOOD, ">pubs/$file_name" ) or die "Can't open pubs/$file_name";
    print FOOD << "EOF";
#!/bin/bash
#\$ -N $hpc_instance_name
#\$ -t 1-$groups
#\$ -q bio,abio,abio128,free64,pub64
#\$ -ckpt restart
#\$ -e logs/
#\$ -o logs/

cd /pub/mbovyn/$folder_name

echo -----------------------------------------------------------
echo This is instance \$SGE_TASK_ID
echo

echo Running on host `hostname`
echo Time is `date`
echo Directory is `pwd`

# Run executable
#motors.x instance_name repeat verbose keep_seed
#sleep \$(printf %.10f "\$((\$SGE_TASK_ID))e-2")
./motors.x $instance_name $repeats 2 0 \$SGE_TASK_ID

echo Finished at `date`

EOF
    close FOOD;
    #done writing
}


# Make submit_pubs.sh

open(FOOD, ">submit_pubs_$hpc_name.sh" ) or die "couldn't make submit_pubs_$hpc_name.sh";
print FOOD << "EOF";
#!/bin/bash

if [ "\$PWD" != "dfs3/pub/mbovyn/$folder_name" ]; then
  echo "something is wrong with folder name"
  exit 3
fi

if [ ! -f ISEED ] ; then
    echo "Missing ISEED!"
    exit 1
fi

#Make executable
cd simulation_code
make $compile_keyword
cd ..
cp simulation_code/motors.x .

if [ ! -f motors.x ] ; then
    echo "Missing executable!"
    exit 2
fi

for filename in pubs/*.pub; do
    qsub \$filename
done

EOF
close FOOD;
#done writing

system("chmod +x submit_pubs_$hpc_name.sh");

return 1;
