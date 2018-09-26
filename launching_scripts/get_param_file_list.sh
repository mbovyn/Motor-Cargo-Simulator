#!/bin/bash
set -e

#make an array of all the parameter files
param_files_unsorted=( $run_name*_MT_params.txt )
IFS=$'\n' param_files=($(sort -t. -k2,2 -k3,3 -n <<<"${param_files_unsorted[*]}"))
unset IFS
#echo -e "param files are:\n${param_files[@]}"
