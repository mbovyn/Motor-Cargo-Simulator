#!/bin/bash

#copy the current version of the executable into the local folder
cd "$working_dir"
cp $code_dir/motors.x motors.x

#number of processes we want to run at once
numCores=4

#counter
ctr1=0

echo "Running ${#sweep[@]} params"

date +"    started at: %r on %F"

#for each set of paramters
for param in ${sweep[*]};
do

    #find the number of simulations currently running
    numInstances=$( pgrep motors | wc -l )

    #if we are at the max, wait and check every 5 seconds
	while [ "$numInstances" -ge "$numCores" ] # number of cores to use
	do
		sleep 5s
        numInstances=$( pgrep motors | wc -l )
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

    #need to select what variable we're sweeping over
    #do this by setting that variable to param in calling script
    #then use indirect referance to make calles to that variable into calls of
    #param (which we're looping over)
    #(explained a bit here http://tldp.org/LDP/abs/html/bashver2.html#EX78
    # and here http://tldp.org/LDP/abs/html/ivr.html)

    #ex) sweep set to array of 10,20,30
    #want to sweep over pi_0
    #in calling script set pi_0=param
    #then the call ${pi_0} returns the string param
    #the call ${!pi_0} translates to $param, so you get 10 for the first loop

    #motors.x   run_name       instance_Name       repeats       verbose       D          eps_0          pi_0          z_MT_offset          R          N           F_trap          theta_c          MT_angle &
    ./motors.x  "${run_name}"  "${instance_name}"  ${repeats:-1} ${verbose:-0} ${!D:-NAN} ${!eps_0:-NAN} ${!pi_0:-NAN} ${!z_MT_offset:-NAN} ${!R:-NAN} ${!N0:--1}  ${!F_trap:-NAN} ${!theta_c:-NAN} ${!MT_angle:-NAN} &

    #track where we are
    let ctr1++
	echo "ran $ctr1 of ${#sweep[@]}, param=$param at"
    date +"    %r on %F"

    #sleep so as not to go before the ISEED is updated
	sleep 1s

done

echo finished launching

let talk=1
numInstances=$( pgrep motors | wc -l )
while [ "$numInstances" -gt "0" ]
do

    numInstancesnew=$( pgrep motors | wc -l )

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

# generate and save a file that tells the hash of the git commit used to generate the data
cd $code_dir
git log -1 --pretty=format:%H > "${run_name}_CommitUsedHash.txt"
mv "${run_name}_CommitUsedHash.txt" "$working_dir"
cd "$working_dir"
