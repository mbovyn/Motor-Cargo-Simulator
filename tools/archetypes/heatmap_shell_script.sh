#!/bin/bash

#need to set these two things:
#name of current run (corresponds to param files)
run_name=demo_mult
#git repository of the code
code_dir=~/project_code/Motor_Freedom

#saves the current directory
working_dir=$("pwd")

#values to sweep over
sweep1=($(seq 5 5 30))
sweep2=($(seq 1.2 -.2 .4))

#set the parameters to pass in, leave others unset
#set the param to be swept over to param
repeats=25
verbose=0
#D=0
eps_0=param2
pi_0=param1
#z_MT_offset=0
#R=0
#N0=0
#F_trap=0
#theta_c=0
#MT_angle=90

. $code_dir/TwoParamSweep.sh
