#!/bin/bash

#program chooses to append or open to write based on existance of files
#if there's an old one hanging around, we probably want to delete it
#if given keep_old=1, don't delete them

code_dir="$1"
working_dir="$2"
keep_old="$3"

echo "Cleaning old files (clean_files.sh)"

#all files code creates
file_endings=(_params.txt _MT_params.txt _Summary.txt _Center_and_Anchors.txt _Heads.txt _Forces.txt _Omega.txt _ToW.txt)

cd $working_dir
. $code_dir/launching_scripts/get_param_file_list.sh

#for each ending, check if the file exists and delete it
#unless keeping old files

for instance in ${param_files[*]};
do
    #echo "${instance%*_MT_params.txt}"
    instance_name="${instance%*_MT_params.txt}"

    for ending in ${file_endings[*]}
    do
        fname="${instance_name}$ending"
        if [ -f $fname -a ${keep_old:-0} -eq 0 ] ; then
            rm $fname
            echo "--->deleted $fname"
        else
            if [ ${keep_old:-0} -eq 1 ] ; then
                echo "--->didn't delete $fname, keeping old"
            fi
        fi
    done
done
