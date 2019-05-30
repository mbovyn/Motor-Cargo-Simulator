#!/bin/bash
set -e
#shopt -s failglob
shopt -s nullglob

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
    #echo "---- $ending ----"
    for file in *.*.*.1$ending; do
        #if [ ! -f $file ]; then
        #    #echo "$file does not exist"
        #    break
        #fi

        echo "cat'ing ${file/.1_/_}"
        #want to find everything that has the same filename except with different repeat number
        #create pattern to find them, e.g. sweepNR.0.0.*_Summary.txt

        #first change the name of the first repeat file so the pattern won't find it again
        # if test -n "$(find . -maxdepth 1 -name '${file/.?_/*}' -print -quit)"
        # then
        #     echo "found glob of ${file/.?_/*}"
        # else
        #     echo "didn't find glob of ${file/.?_/*}"
        #     exit 2
        # fi
        #echo "moving"
        mv $file $file.bk

        #generate, e.g. sweepNR.0.0.*_Summary.txt with parameter substitution
        #save the list of files which match the pattern in an array
        #echo "making list from glob of ${file/.?_/*}"
        lst=(${file/.?_/*})
        #echo "list is"
        #echo "${lst[@]}"
        if [ ${#lst[@]} -eq 0 ]; then
            echo "Oops, ${#lst[@]} entries in lst from glob of ${file/.?_/*}"
            echo "probably a Google Drive Stream issue. Run cat_files again."
            mv $file.bk $file
            exit 1
        #else
            #echo "${#lst[@]} entries in lst, ok"
        fi

        for item in ${lst[*]}; do
            if [ "$item" =  ${file/.1_/_} ]; then
                echo "found $item in lst. Would make infinite loop."
                exit 2
            fi
        done

        #sort the filenames so 10 comes after 9
        #https://stackoverflow.com/questions/7442417/how-to-sort-an-array-in-bash
        #echo "sorting"
        IFS=$'\n'
        lst=($(sort -V <<<"${lst[*]}"))
        unset IFS
        #echo "sorted list is"
        #echo "${lst[@]}"
        #copy first repeat (has header) to start concatinated file
        #echo "starting file"
        cp $file.bk ${file/.1_/_}
        #append the contents of the other files onto cat'd file
        #echo "cat'ing to ${file/.1_/_} this list:"
        #echo "${lst[@]}"
        #echo
        cat "${lst[@]}" >> ${file/.1_/_}
        #return file
        mv $file.bk $file
    done

    for file in *.*.*.*$ending; do
        #if [ ! -f $file ]; then
        #    #echo "$file does not exist"
        #    break
        #else
            echo "rm'ing *.*.*.*$ending"
            rm *.*.*.*$ending
            break
        #fi
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

        for item in ${lst[*]}; do
            if [ "$item" =  ${file/%.o*/.log} ]; then
                echo "found $item in lst. Would make infinite loop."
                exit 2
            fi
        done

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

    # for the error files
    for file in *.*.e*; do
        if [ ! -f ${file/%.e*/.err} ]; then
            echo "working on ${file/%.e*/.err}"
        fi

        echo "$file" >> ${file/%.e*/.err}
        cat "$file" >> ${file/%.e*/.err}
        echo >> ${file/%.e*/.err}
        echo "---------------------------------------" >> ${file/%.e*/.err}
        echo >> ${file/%.e*/.err}
        rm $file

    done
    cd ..
fi

# to undo:
# remove .bk: for file in *bk; do mv $file ${file/%bk/.1};  done;
# to remove cat'd files: rm *.log

echo "Done cat'ing"
