#!/bin/bash

#program chooses to append or open to write based on existance of files
#if there's an old one hanging around, we probably want to delete it
#if given keep_old=1, don't delete them

#all files code creates
file_endings=(_Summary.txt _Center_and_Anchors.txt _Heads.txt _Forces.txt _Omega.txt _ToW.txt)

#for each ending, check if the file exists and delete it
#unless keeping old files
for ending in ${file_endings[*]}
do
    fname="${instance_name}$ending"
    if [ -f $fname -a ${keep_old:-0} -eq 0 ] ; then
        rm $fname
        echo "    Script: deleted $fname"
    else
        if [ ${keep_old:-0} -eq 1 ] ; then
            echo "    Script: didn't delete $fname, keeping old"
        fi
    fi
done
