#!/bin/bash

##################################################################
#This script copies all files from the code directory to the working
#directory which are necessary for compiling and running on the HPC.
#(except for the parameter files and the ISEED)
##################################################################

#local location to copy the code from
code_dir=~/project_code/Motor_Freedom
working_dir=$("pwd")

#copy code to current folder
mkdir code
cp $code_dir/*.c ./code
cp $code_dir/*.h ./code
cp $code_dir/Makefile ./code
#copy the scripts if they don't already exist
#first the file which genearates the parameter files
cp -n $code_dir/tools/archetypes/makeandlaunch.pl .
#then the script which makes the pub files
cp -n $code_dir/tools/hpc/make_and_submit_Pubs.pl .

#warn if missing necessary files
if [ ! -f "$run_name"_params.txt ] ; then
    echo "Missing parameter file!"
fi
if [ ! -f "$run_name"_MT_params.txt ] ; then
    echo "Missing MT parameter file!"
fi
if [ ! -f ISEED ] ; then
    echo "Missing ISEED!"
fi

#make the folders
mkdir pubs
mkdir logs

#get commit hash
cd $code_dir
git log -1 --pretty=format:%H > "CommitHash.txt"
mv "CommitHash.txt" "$working_dir"
cd "$working_dir"
