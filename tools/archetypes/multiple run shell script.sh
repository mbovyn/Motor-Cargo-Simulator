#!/bin/bash

#define run name here
code_dir=~/project_code/Motor_Freedom
run_name=demo

#number of processes we want to run at once
numCores=4

#some counters
ctr2=0

#theta_cs=`seq -1.375 .0625 1.375`
theta_cs=($(seq -1.375 .25 1.375))
Rs=( .15 .25 .35 )
#Rs=( .1 )

echo "Running ${#Rs[@]} R's and ${#theta_cs[@]} theta_c's"

#for each set of paramters
for R in ${Rs[*]};
do

    let ctr1=0

    for theta_c in ${theta_cs[*]};
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

        instance_name="${run_name}.${ctr2}.${ctr1}"

        fname="${instance_name}_Summary.txt"
        if [ -e $fname ] ; then
        rm $fname
        echo "    deleted old summary file $fname"
        fi

        #launch a simulation in the background by adding & after call
        #motors.x          param_file.txt           runName            repeats verbose D eps_0 pi_0 z_MT_offset R theta_c
        $code_dir/motors.x "${run_name}_params.txt" "${instance_name}" 500      0      0 0     0    0           $R $theta_c &
        #sleep so as not to go before the ISEED is updated
        sleep .000001s

        #track where we are
        let ctr1++
    	echo "    ran $ctr1 of ${#theta_cs[@]}, theta_c=$theta_c"

    	sleep .01

    done #first loop

    let ctr2++
    echo "done with R=$R, number $ctr2 of ${#Rs[@]}"
done #second loop

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

echo "done"
#create a notification
osascript -e 'display notification "Simulation Complete" with title "Done!"'

# generate and save a file that tells the hash of the git commit used to generate the data
working_dir=$("pwd")
cd $code_dir
git log -1 --pretty=format:%H > "${run_name}_CommitUsedHash.txt"
mv "${run_name}_CommitUsedHash.txt" "$working_dir"
cd "$working_dir"
