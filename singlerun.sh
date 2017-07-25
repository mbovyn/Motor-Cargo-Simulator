#!/bin/bash

#copy the current version of the executable into the local folder
cd "$working_dir"
cp $code_dir/motors.x .

#clean up existing files
. $code_dir/clean_files.sh

date +"    Script: started at %r on %F"

#run the simulation from the local folder

#if a parameter is set in calling script, pass it to the program
#otherwise, pass the program NAN for each unset parameter

#do this using the parameter expansion
#http://stackoverflow.com/questions/3601515/how-to-check-if-a-variable-is-set-in-bash
#answer by Jens
#ex) ${eps_0:-NAN} returns NAN if variable eps_0 isn't set, whatever it's set to otherwise
#motors.x   run_name   instance_name  repeats       verbose       D         eps_0         pi_0         z_MT_offset         R         N[0]       F_trap         theta_c         MT_angle         F_d         eta         k_m
./motors.x  $run_name  $run_name      ${repeats:-1} ${verbose:-0} ${D:-NAN} ${eps_0:-NAN} ${pi_0:-NAN} ${z_MT_offset:-NAN} ${R:-NAN} ${N0:--1}  ${F_trap:-NAN} ${theta_c:-NAN} ${MT_angle:-NAN} ${F_d:-NAN} ${eta:-NAN} ${k_m:-NAN}

#notify
date +"    Script: done at %r on %F"
osascript -e 'display notification "Simulation Complete" with title "Done!"'

# generate and save a file that tells the hash of the git commit used to generate the data
cd $code_dir
git log -1 --pretty=format:%H > "${run_name}_CommitUsedHash.txt"
mv "${run_name}_CommitUsedHash.txt" "$working_dir"
cd "$working_dir"
