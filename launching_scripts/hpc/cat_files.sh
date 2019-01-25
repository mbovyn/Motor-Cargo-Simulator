
#minimal example:
#cp sweepNR.0.0.1_Summary.txt sweepNR.0.0_Summary.txt
#rm sweepNR.0.0.1_Summary.txt
#find . -type f -name 'sweepNR.0.0.*_Summary.txt' -exec cat {} + >> sweepNR.0.0_Summary.txt
#rm sweepNR.0.0.*_Summary.txt

#we use:

#Parameter substitution
#https://www.cyberciti.biz/tips/bash-shell-parameter-substitution-2.html
#${var/blah*.txt/_} replaces e.g. blah1.txt with blah_.txt

#uses pattern matching
#https://www.gnu.org/software/bash/manual/html_node/Pattern-Matching.html
# ? is like * but only matches a single character

for file in *.*.*.1_Summary.txt; do
    #echo $file

    #want to find everything that has the same filename except with different repeat number
    #create pattern to find them, e.g. sweepNR.0.0.*_Summary.txt

    #first change the name of the first repeat file so the pattern won't find it again
    mv $file $file.bk
    #generate, e.g. sweepNR.0.0.*_Summary.txt with parameter substitution
    #save the list of files which match the pattern in an array
    lst=(${file/.?_/*})
    #sort the filenames so 10 comes after 9
    #https://stackoverflow.com/questions/7442417/how-to-sort-an-array-in-bash
    IFS=$'\n'
    lst=($(sort -V <<<"${lst[*]}"))
    unset IFS
    #copy first repeat (has header) to start concatinated file
    cp $file.bk ${file/.1_/_}
    #append the contents of the other files onto cat'd file
    #echo "${lst[@]}"
    cat "${lst[@]}" >> ${file/.1_/_}

done

# to undo:
# remove .bk: for file in *.bk; do mv $file ${file%.bk};  done;
# delete all two number summaries: rm sweepNR.?.?_Summary.txt

#rm *.bk
#rm *.*.*.*_Summary.txt
