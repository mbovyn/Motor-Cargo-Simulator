#!/bin/bash
set -e

#program chooses to append or open to write based on existance of files
#if there's an old one hanging around, we probably want to delete it
#if given keep_old=1, don't delete them

code_dir="$1"
working_dir="$2"
keep_old="$3"

echo "Cleaning old files (clean_files.sh)"

#all files code creates
param_endings=( _params.txt _MT_params.txt )
file_endings=( _Summary.txt _Center_and_Anchors.txt _Heads.txt _Forces.txt _Omega.txt _ToW.txt)

cd "$working_dir"
. "$code_dir/launching_scripts/get_param_file_list.sh"

#for each ending, check if the file exists and delete it
#unless keeping old files

for instance in ${param_files[*]};
do
    #echo "${instance%*_MT_params.txt}"
    instance_name="${instance%*_MT_params.txt}"

    for ending in ${param_endings[*]}
    do
        fname="${instance_name}$ending"
        if [ -f $fname ] ; then

            rm $fname
            echo "--->deleted $fname"

        fi
    done

    for ending in ${file_endings[*]}
    do
        fname="${instance_name}$ending"
        if [ -f $fname ] ; then

            if [ ${keep_old:-0} -eq 1 ] ; then
                echo "--->didn't delete $fname, keeping old"
            else
                rm $fname
                echo "--->deleted $fname"
            fi

        fi

        if [ $(find . -maxdepth 1 -name "*.*.*.*$ending" | wc -l) -gt 0 ] ; then
            echo "--->deleting $(ls -l *.*.*.*$ending | wc -l) of individual $ending"
            rm *.*.*.*$ending
        fi
    done
done

folders=( logs pubs simulation_code )
for folder_name in ${folders[*]}; do

    if [ -d $folder_name ]; then
        rm -r $folder_name
        echo "--->deleted $folder_name"
    fi

done

others=( submit_pubs*.sh cat_files.sh CommitHash.txt )
for other_name in ${others[*]}; do

    if [ -f $other_name ]; then
        rm -r $other_name
        echo "--->deleted $other_name"
    fi

done

# if [$(find . -name "motors*.*.*.*.x" | wc -l) -gt 0 ] ; then
#     for stale_executable in motors*.*.*.*.x; do
#         rm $stale_executable
#         echo "--->delted old executable $stale_executable"
#     done
# fi

# if [$(find . -name "motors*.*.*.x" | wc -l) -gt 0 ] ; then
#     for stale_executable in motors*.*.*.x; do
#         rm $stale_executable
#         echo "--->delted old executable $stale_executable"
#     done
# fi

exit 0
