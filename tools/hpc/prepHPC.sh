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
#copy the pub submitter
cp $code_dir/tools/hpc/submit_pubs.sh .
#copy the param file generator if it don't already exist
cp -n $code_dir/tools/archetypes/makeandlaunch.pl .

#warn if missing necessary ISEED file
if [ ! -f ISEED ] ; then
    echo "Missing ISEED!"
fi

#make the folders to hold the pubs and logs
mkdir pubs
mkdir logs

#get commit hash
cd $code_dir
git log -1 --pretty=format:%H > "CommitHash.txt"
mv "CommitHash.txt" "$working_dir"
cd "$working_dir"
