#!/bin/bash

#fnames=(forwardequations.c stochasticequations.c)
#echo ${fnames[1]}

for fname in pointToMT_formulae.txt stochasticequations.c beadequations.c
do
    if [ -e $fname ] ; then

        #sed: -i '' -> write in place, don't save a backup copy (would specify filename in '')
        #'s/stuff/otherstuff/g' replace stuff with other stuff g -> globally
        #good resource: http://www.grymoire.com/Unix/Sed.html#uh-6

        #replace indicies in parentheses with same number in square brackets
        #matches (<any number>) and replaces with [<any number>]
        #[0-9] finds any number, then [0-9]* extends to 0 to however many other numbers
        #uses \( \) to save the substring of what's found (the number)
        sed -i '' 's/(\([0-9][0-9]*\))/[\1]/g' $fname

        #replace == with =
        #wrote == in Mathematica for ease
        sed -i '' 's/==/=/g' $fname

        #replace Mathematica's way of writing exponents (Power(x,y)) with the correct C
        #expression (pow(x,y))
        sed -i '' 's/Power/pow/g' $fname
        sed -i '' 's/Sin/sin/g' $fname
        sed -i '' 's/Cos/cos/g' $fname

        #replace miscapitalized Sqrt with correct sqrt
        sed -i '' 's/Sqrt/sqrt/g' $fname
        #first switch of () to [] catches sqrt[number], turn back
        #note need to escape [ and ] because it thinks its being used for a range,
        #a la [0-9]
        sed -i '' 's/sqrt\[\([0-9][0-9]*\)\]/sqrt(\1)/g' $fname

        #replace parens with brackets around variable in point to MT dist
        sed -i '' 's/(MTnum)/[MTnum]/g' $fname
        #replace RMT with R_MT
        sed -i '' 's/RMT/R_MT/g' $fname

        #the exit statement doesn't go with the rule
        sed -i '' 's/exit\[0\];/exit(0);/g' $fname

        #need actual == in the if statement
        sed -i '' 's/omega\[\([0-9]\)\]=0/omega[\1]==0/g' $fname

        echo processed $fname

    fi
done
