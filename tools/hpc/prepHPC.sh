#!/bin/bash

code_dir=~/project_code/Motor_Freedom
working_dir=$("pwd")

#copy code to current folder
cp $code_dir/*.c .
cp $code_dir/*.h .
cp -n $code_dir/tools/hpc/make_and_submit_Pubs.pl .

#get commit hash
cd $code_dir
git log -1 --pretty=format:%H > "CommitHash.txt"
mv "CommitHash.txt" "$working_dir"
cd "$working_dir"
