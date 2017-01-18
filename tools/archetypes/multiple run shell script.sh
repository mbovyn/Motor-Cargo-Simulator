#!/bin/bash

#define run name here
code_dir=~/project_code/Motor_Freedom
run_name=demo_mult

#number of processes we want to run at once
numCores=4

#some counters
ctr1=0

sweep=($(seq 5 5 25))

echo "Running ${#sweep[@]} params"

echo "started at:"
date

#for each set of paramters
for param in ${sweep[*]};
do

    #find the number of simulations currently running
    #need to subtract 1 because grep finds itself
    numInstances=$(( $( ps | grep motors | wc -l ) - 1 ))
	#echo "    starting, have $numInstances running"

    talk=1
    #if we are at the max, wait and check every 5 seconds
	while [ "$numInstances" -ge "$numCores" ] # number of cores to use
	do

		numInstances=$(( $( ps | grep motors | wc -l ) - 1))

        if [ "$talk" -eq "1" ]
        then
            #echo "    waiting, have $numInstances running"
            let talk=0
        fi

		sleep 1s
	done
    #when this exits, we are at less than the max number of sims
    #so launch a new one and check again

    #program chooses to append or open to write based on existance of summary file
    #if there's an old one hanging around, delete it

    instance_name="${run_name}.${ctr1}"

    fname="${instance_name}_Summary.txt"
    if [ -e $fname ] ; then
    rm $fname
    echo "    deleted old summary file $fname"
    fi

    #launch a simulation in the background by adding & after call
    #motors.x          run_name       instance_Name     repeats  verbose D     eps_0  pi_0   z_MT_offset R N F_trap theta_c
    $code_dir/motors.x "${run_name}" "${instance_name}" 10      1       0     0      $param 0           0         &
    #sleep so as not to go before the ISEED is updated
    sleep .000001s

    #track where we are
    let ctr1++
	echo "    ran $ctr1 of ${#sweep[@]}, param=$param at"
    date

	sleep .01

done #first loop

echo finished launching

let talk=1
while [ "$numInstances" -gt "0" ] # number of cores to use
do

    numInstances=$(($( ps | grep motors | wc -l ) - 1))

    if [ "$talk" -eq "1" ]
    then
        echo waiting for last $numInstances to finish
        let talk=0
    fi

    sleep 1s
done

echo "done at:"
date
#create a notification
osascript -e 'display notification "Simulation Complete" with title "Done!"'

# generate and save a file that tells the hash of the git commit used to generate the data
working_dir=$("pwd")
cd $code_dir
git log -1 --pretty=format:%H > "${run_name}_CommitUsedHash.txt"
mv "${run_name}_CommitUsedHash.txt" "$working_dir"
cd "$working_dir"
