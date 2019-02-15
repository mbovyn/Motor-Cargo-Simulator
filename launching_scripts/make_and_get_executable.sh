#!/bin/bash
set -e
#shopt -s failglob

#This script generates a file with the commit hash of the current code and makes
#an executable, then copies both to the working folder

echo "Checking executable (make_and_get_executable.sh)"

#take in inputs
code_dir="$1"
working_dir="$2"
compile_keyword="$3"
force_recompile="$4"

#copy the archetypes ISEED in if one doesn't exist here
if [ ! -f ISEED ] ; then
    cp "$code_dir/archetypes/ISEED" "$working_dir"
fi

#deal with the executable
cd "$working_dir"
#if it doesn't exist or we want to recompile
if [ ! -f motors*.x ] || [ $force_recompile -gt 0 ] ; then

    # generate and save a file that tells the hash of the git commit used to generate the data
    cd $code_dir
    git log -1 --pretty=format:%H > "CommitUsedHash.txt"
    mv "CommitUsedHash.txt" "$working_dir"

    #compile and copy code to working directory
    cd simulation_code
    echo -n "--->"
    make $compile_keyword
    mv "$code_dir/simulation_code/motors.x" "$working_dir"

else
    echo "--->Using current executable"
    if [ -f motors.x ]; then
        echo "--->Using current motors.x"
    else
        for file in motors_*.x; do
            if [ -f $file ]; then
                echo "--->renaming $file to motors.x"
                mv "$file" "motors.x"
            fi
        done
    fi
fi

exit 0
