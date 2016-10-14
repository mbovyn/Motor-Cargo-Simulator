#!/bin/bash

fname=forwardequations.c

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