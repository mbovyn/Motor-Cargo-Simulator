#!/bin/bash

#need to set these two things:
#name of current run (corresponds to param files)
run_name=demo_mult
#git repository of the code
code_dir=~/project_code/Motor_Freedom

#saves the current directory
working_dir=$("pwd")

#values to sweep over
sweep=($(seq 5 5 25))

#set the parameters to pass in, leave others unset
#set the param to be swept over to param
repeats=10
verbose=0
#D=0
#eps_0=0
pi_0=param
#z_MT_offset=0
#R=0
#N0=0
#F_trap=0
#theta_c=0

. $code_dir/OneParamSweep.sh
