#!/bin/bash

cd "$working_dir"

#copy the current version of the executable into the local folder
cp $code_dir/motors.x motors.x

#program chooses to append or open to write based on existance of summary file
#if there's an old one hanging around, delete it
fname="${run_name}_Summary.txt"
if [ -e $fname ] ; then
    rm $fname
    echo Script: deleted old summary file
else
    echo Script: no summary file
fi

#run the simulation from the local folder
#motors.x   run_name   instance_name  repeats  verbose  D  eps_0  pi_0  z_MT_offset  R  N[0] theta_c
./motors.x  $run_name  $run_name      $repeats $verbose $D $eps_0 $pi_0 $z_MT_offset $R $N0  $theta_c

# generate and save a file that tells the hash of the git commit used to generate the data
cd $code_dir
git log -1 --pretty=format:%H > "${run_name}_CommitUsedHash.txt"
mv "${run_name}_CommitUsedHash.txt" "$working_dir"
cd "$working_dir"
