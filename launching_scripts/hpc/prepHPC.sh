#!/bin/bash

##################################################################
#This script copies all files from the code directory to the working
#directory which are necessary for compiling and running on the HPC.
#(except for the parameter files and the ISEED)
##################################################################

code_dir="$1"
working_dir="$2"

#copy code to current folder
cp -r $code_dir/simulation_code "$working_dir"
#copy the file concatinator
cp -p $code_dir/launching_scripts/hpc/cat_files.sh "$working_dir"

#warn if missing necessary ISEED file
cp -n $code_dir/archetypes/ISEED "$working_dir"

#make the folders to hold the pubs and logs
cd "$working_dir"
if [ -f motors.x ]; then
    rm motors.x
fi
mkdir pubs
mkdir logs

#get commit hash
cd "$code_dir"
git log -1 --pretty=format:%H > "CommitHash.txt"
mv "CommitHash.txt" "$working_dir"
cd "$working_dir"
