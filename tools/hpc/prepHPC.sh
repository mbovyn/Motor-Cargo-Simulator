#!/bin/bash

##################################################################
#change this stuff!

#set run name here
run_name=angle


##################################################################
#self sufficient below here

code_dir=~/project_code/Motor_Freedom
working_dir=$("pwd")

#copy code to current folder
cp $code_dir/*.c .
cp $code_dir/*.h .
cp $code_dir/Makefile .
#copy the script if it doesn't already exist
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
