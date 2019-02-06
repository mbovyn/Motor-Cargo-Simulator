#!/bin/bash
set -e

echo "****Launching locally (launch_over_paramfiles.sh)****"

#take in variables passed from perl script where parameter values are set
run_name="$1"
#echo "run_name is $run_name"
code_dir="$2"
#echo "code_dir is $code_dir"
working_dir="$3"
#echo "working_dir is $working_dir"
repeats=$4
groups=$5
verbose=$6
keep_seed=$7
#whether or not to keep old files
keep_old=$8
dont_wait=$9

#echo $run_name
#echo $code_dir
#echo $working_dir
#echo $repeats
#echo $verbose
#echo $keep_seed
#echo $keep_old
#echo $dont_wait

#number of processes we want to run at once
ncoresfound=$(getconf _NPROCESSORS_ONLN)
numCores=${ncoresfound:-4}
oldname=motors.x

. "$code_dir/launching_scripts/get_param_file_list.sh"

echo "****Running ${#param_files[@]} instances, $(date +"started at %r on %F")"

ctr=1

for instance in ${param_files[*]}; do

    echo "****Starting $ctr of ${#param_files[@]}, $instance at $(date +"%r on %F")"

    for r in $(eval echo {1..$groups}); do

        #echo "${instance%*_MT_params.txt}"
        param_name="${instance%*_MT_params.txt}"
        instance_name="${instance%*_MT_params.txt}.$r"

        if [ "$dont_wait" -ne "1" ]
        then
            #find the number of simulations currently running
            #numInstances=$( jobs -r | wc -l )
            numInstances=$( pgrep motors | wc -l )
            #wait to run the next instance until there are less than the max
            while [ "$numInstances" -ge "$numCores" ]
            do
                #echo sleeping
            	sleep .1s
                #numInstances=$( jobs -r | wc -l )
                numInstances=$( pgrep motors | wc -l )
            done
        fi

        #run executable
        newname="motors_$instance_name.x"
        mv "$working_dir"/"$oldname" "$working_dir"/"$newname"
        #motors.x   run_name            repeats       verbose
        #./$newname  "${instance_name}"  ${repeats:-1} ${verbose:-2} ${keep_seed:-0} &
        if [ "$groups" -eq "1" ]; then
            ./$newname  "${param_name}"  ${repeats:-1} ${verbose:-2} ${keep_seed:-0} 0 &
        else
            ./$newname  "${param_name}"  ${repeats:-1} ${verbose:-2} ${keep_seed:-0} $r &
        fi
        oldname=$newname

        #sleep so as not to go before the ISEED is updated
        #if [ "$repeats" -gt "1" ]
        #then
        #    sleep .001s
        #fi

    done

    echo "****finished $ctr of ${#param_files[@]}, $instance at $(date +"%r on %F")"
    let ctr++

done

mv "$working_dir"/"$newname" "$working_dir"/motors.x

echo "****finished launching"

if [ "$dont_wait" -ne "1" ]
then
    talk=1
    numInstances=$( jobs -r | wc -l )
    #numInstances=$( pgrep motors | wc -l )
    #echo $numInstances
    while [ "$numInstances" -gt "0" ]
    do

        #jobs
        numInstancesnew=$( jobs -r | wc -l )
        #numInstancesnew=$( pgrep motors | wc -l )
        #echo $numInstancesnew

        if [ "$numInstancesnew" -lt "$numInstances" ]
        then
            #echo "numInstances updating from $numInstances to $numInstancesnew"
            numInstances=$numInstancesnew
            talk=1
        #else
        #    echo "not updating numInstances"
        fi

        if [ "$talk" -eq "1" ]
        then
            echo ****waiting for last $numInstances to finish at $(date +"%r on %F")
            #apparently "let talk=0" returns a 0, which sets off the error
            #checking from set -e. regular assignment doens't though.
            talk=0
        #else
        #    echo "Not talking"
        fi

        #sleep so as not to go before the ISEED is updated
        if [ "$repeats" -gt "1" ]
        then
            #echo "sleeping"
            sleep .1s
        #else
        #    echo "not sleeping"
        fi
    done

    date +"****done at: %r on %F"
    #create a notification
    osascript -e 'display notification "Simulation Complete" with title "Done!"'
fi
