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
#copy the pub submitter
cp -p $code_dir/launching_scripts/hpc/submit_pubs.sh "$working_dir"
#copy the param file generator if it don't already exist
#cp -n $code_dir/archetypes/setandlaunch.pl .

#warn if missing necessary ISEED file
cp -n $code_dir/archetypes/ISEED "$working_dir"

#make the folders to hold the pubs and logs
cd "$working_dir"
mkdir pubs
mkdir logs

#get commit hash
cd "$code_dir"
git log -1 --pretty=format:%H > "CommitHash.txt"
mv "CommitHash.txt" "$working_dir"
cd "$working_dir"
