#!/bin/bash

#need to set these two things:
#name of current run (corresponds to param files)
run_name=demo
#git repository of the code
code_dir=~/project_code/Motor_Freedom

#saves the current directory
working_dir=$("pwd")

#set the parameters to pass in, leave others unset
repeats=1
verbose=2
#D=0
#eps_0=0
#pi_0=0
#z_MT_offset=0
#R=0
#N0=0
#F_trap=-.216
#theta_c=0
#MT_angle=90
#F_d=4
#eta=.0001
#k_m=320

#source the script that calls the function. See here:
#http://stackoverflow.com/questions/9772036/pass-all-variables-from-one-shellscript-to-another
. $code_dir/singlerun.sh
