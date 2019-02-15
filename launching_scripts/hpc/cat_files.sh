#!/bin/bash
set -e
#shopt -s failglob

#This script takes the files written out by each repeat during an hpc job array
#run and concatinates them into one file per parameter set

#on way to do it would be to, for each parameter set
#find . -type f -name 'sweepNR.0.0.*_Summary.txt' -exec cat {} + >> sweepNR.0.0_Summary.txt

#so we are general to any number of parameter sets, we use:

#Bash parameter substitution
#https://www.cyberciti.biz/tips/bash-shell-parameter-substitution-2.html
#${var/blah*.txt/_} replaces e.g. blah1.txt with blah_.txt

#uses pattern matching
#https://www.gnu.org/software/bash/manual/html_node/Pattern-Matching.html
# ? is like * but only matches a single character

#https://www.tldp.org/LDP/abs/html/parameter-substitution.html
# % matches ending with pattern, ex. ${var/%.o*/.log} replaces a.b.o123456.1 with a.b.log

# for the summary files
#echo running
file_endings=( _Summary.txt _Center_and_Anchors.txt _Heads.txt _Forces.txt _Omega.txt _ToW.txt)
for ending in ${file_endings[*]}; do
    #echo $ending
    for file in *.*.*.1$ending; do
        if [ ! -f $file ]; then
            #echo "$file does not exist"
            break
        fi

        echo "cat'ing ${file/.1_/_}"
        #want to find everything that has the same filename except with different repeat number
        #create pattern to find them, e.g. sweepNR.0.0.*_Summary.txt

        #first change the name of the first repeat file so the pattern won't find it again
        mv $file $file.bk
        #generate, e.g. sweepNR.0.0.*_Summary.txt with parameter substitution
        #save the list of files which match the pattern in an array
        lst=(${file/.?_/*})
        #echo "${lst[@]}"
        #sort the filenames so 10 comes after 9
        #https://stackoverflow.com/questions/7442417/how-to-sort-an-array-in-bash
        IFS=$'\n'
        lst=($(sort -V <<<"${lst[*]}"))
        unset IFS
        #copy first repeat (has header) to start concatinated file
        cp $file.bk ${file/.1_/_}
        #append the contents of the other files onto cat'd file
        cat "${lst[@]}" >> ${file/.1_/_}
    done

    for file in *.bk; do
        #echo $file
        if [ ! -f $file ]; then
            #echo "$file does not exist"
            break
        else
            #echo "removing $file"
            rm *.bk
            break
        fi
    done

    for file in *.*.*.*$ending; do
        if [ ! -f $file ]; then
            #echo "$file does not exist"
            break
        else
            #echo "removing $file"
            rm *.*.*.*$ending
            break
        fi
    done

done

# to undo:
# remove .bk: for file in *.bk; do mv $file ${file%.bk};  done;
# delete all two number summaries: rm sweepNR.?.?_Summary.txt



# for the log files
if [ -d "logs" ]; then
    cd logs
    for file in *.*.o*.1; do
        echo "working on ${file/%.o*/.log}"

        mv $file ${file/%.1/bk}
        lst=(${file/%.1/.*})
        #echo "${lst[@]}"

        IFS=$'\n'
        lst=($(sort -V <<<"${lst[*]}"))
        unset IFS
        #copy first repeat (has header) to start concatinated file
        cp ${file/%.1/bk} ${file/%.o*/.log}
        #append the contents of the other files onto cat'd file
        #echo "${lst[@]}"
        cat "${lst[@]}" >> ${file/%.o*/.log}

        rm "${lst[@]}"
        rm ${file/%.1/bk}

    done
    cd ..
fi

# to undo:
# remove .bk: for file in *bk; do mv $file ${file/%bk/.1};  done;
# to remove cat'd files: rm *.log
