#!/bin/bash

#take in variables passed from perl script where parameter values are set
run_name="$1"
#echo "run_name is $run_name"
code_dir="$2"
#echo "code_dir is $code_dir"
working_dir="$3"
#echo "working_dir is $working_dir"
repeats=$4
verbose=$5

# generate and save a file that tells the hash of the git commit used to generate the data
cd $code_dir
git log -1 --pretty=format:%H > "${run_name}_CommitUsedHash.txt"
mv "${run_name}_CommitUsedHash.txt" "$working_dir"

cd "$working_dir"

#copy the current version of the executable into the local folder
cp $code_dir/motors.x .
#also copy the archetypes ISEED in if one doesn't exist here
if [ ! -f ISEED ] ; then
    cp "$code_dir/tools/archetypes/ISEED" .
fi

#number of processes we want to run at once
numCores=4

#make an array of all the parameter files
param_files=( $run_name*_MT_params.txt )
#echo "${param_files[@]}"

echo "Running ${#param_files[@]} instances"
date +"    started at: %r on %F"

ctr=1

for instance in ${param_files[*]};
do
    #echo "${instance%*_MT_params.txt}"
    instance_name="${instance%*_MT_params.txt}"

    #find the number of simulations currently running
    numInstances=$( pgrep motors | wc -l )
    #wait to run the next instance until there are less than the max
    while [ "$numInstances" -ge "$numCores" ]
    do
    	sleep 5s
        numInstances=$( pgrep motors | wc -l )
    done

    #delete old files
    . $code_dir/clean_files.sh

    #run executable
    ./motors.x  "${instance_name}"  "${instance_name}"  ${repeats:-1} ${verbose:-2} &

    echo "ran $ctr of ${#param_files[@]}, $instance_name at"
    date +"    %r on %F"

    let ctr++

    #sleep so as not to go before the ISEED is updated
	sleep .1s

done

echo finished launching

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
        echo waiting for last $numInstances to finish at
        date +"    %r on %F"
        let talk=0
    fi

    sleep 1s
done

date +"done at: %r on %F"
#create a notification
osascript -e 'display notification "Simulation Complete" with title "Done!"'
