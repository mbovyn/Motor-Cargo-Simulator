#!/bin/bash

#This script generates a file with the commit hash of the current code and makes
#an executable, then copies both to the working folder

#take in inputs
code_dir="$1"
working_dir="$2"
compile_keyword="$3"

# generate and save a file that tells the hash of the git commit used to generate the data
cd $code_dir
git log -1 --pretty=format:%H > "${run_name}_CommitUsedHash.txt"
mv "${run_name}_CommitUsedHash.txt" "$working_dir"

#compile and copy code to working directory
cd simulation_code
make $compile_keyword
mv "$code_dir/simulation_code/motors.x" "$working_dir"

#also copy the archetypes ISEED in if one doesn't exist here
if [ ! -f ISEED ] ; then
    cp "$code_dir/archetypes/ISEED" "$working_dir"
fi
