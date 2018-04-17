#!/usr/bin/perl
#use strict;
use warnings;

print "Making parameter files\n";

#call first part of script
#sets names
do "$code_dir/makeparams1.pl";

#set params to be swept over to param1 and param2 by overwriting
#append name to variablename to enable symbolic reference

my $name1=$sweepvars[0] . "name";
if(scalar(@sweepvars)<2){
    push @sweepvals, [0];
} else {
    my $name2=$sweepvars[1] . "name";
}
#print "$name1, $name2\n";
#print "$$name1, $$name2\n";

$$name1="param1";
$$name2="param2";
#print "$$name1, $$name2\n";

#call second half of script
do "$code_dir/makeparams2.pl";
