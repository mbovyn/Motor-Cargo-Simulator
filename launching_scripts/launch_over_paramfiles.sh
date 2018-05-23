#!/bin/bash

echo "****Launching locally (launch_over_paramfiles.sh)****"

#take in variables passed from perl script where parameter values are set
run_name="$1"
#echo "run_name is $run_name"
code_dir="$2"
#echo "code_dir is $code_dir"
working_dir="$3"
#echo "working_dir is $working_dir"
repeats=$4
verbose=$5
keep_seed=$6
#whether or not to keep old files
keep_old=$7
dont_wait=$8

#number of processes we want to run at once
numCores=4

. $code_dir/launching_scripts/get_param_file_list.sh

echo "****Running ${#param_files[@]} instances, $(date +"started at %r on %F")"

ctr=1

for instance in ${param_files[*]};
do
    #echo "${instance%*_MT_params.txt}"
    instance_name="${instance%*_MT_params.txt}"

    if [ "$dont_wait" -ne "1" ]
    then
        #find the number of simulations currently running
        numInstances=$( pgrep motors | wc -l )
        #wait to run the next instance until there are less than the max
        while [ "$numInstances" -ge "$numCores" ]
        do
        	sleep 5s
            numInstances=$( pgrep motors | wc -l )
        done
    fi

    echo "****Starting $ctr of ${#param_files[@]}, $instance_name at $(date +"%r on %F")"

    #run executable
    #motors.x   run_name            repeats       verbose
    ./motors.x  "${instance_name}"  ${repeats:-1} ${verbose:-2} ${keep_seed:-0} &

    let ctr++

    #sleep so as not to go before the ISEED is updated
    if [ "$repeats" -gt "1" ]
    then
        sleep .1s
    fi

done

echo "****finished launching"

if [ "$dont_wait" -ne "1" ]
then
    let talk=1
    numInstances=$( jobs -r | wc -l )
    while [ "$numInstances" -gt "0" ]
    do

        numInstancesnew=$( jobs -r | wc -l )

        if [ "$numInstancesnew" -lt "$numInstances" ]
        then
            numInstances=$numInstancesnew
            let talk=1
        fi

        if [ "$talk" -eq "1" ]
        then
            echo ****waiting for last $numInstances to finish at $(date +"%r on %F")
            let talk=0
        fi

        #sleep so as not to go before the ISEED is updated
        if [ "$repeats" -gt "1" ]
        then
            sleep 1s
        fi
    done

    date +"****done at: %r on %F"
    #create a notification
    osascript -e 'display notification "Simulation Complete" with title "Done!"'
fi
