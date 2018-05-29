#!/usr/bin/perl
#use strict;
use warnings;

print "Making parameter files (makeparams.pl)\n";

#call first part of script
#sets names
do "$code_dir/launching_scripts/makeparams1.pl" or die "$@ from call";

#set params to be swept over to param1 and param2 by overwriting
#append name to variablename to enable symbolic reference

#print "the sweepvars are originally @sweepvars\n";
#my $a = scalar(@sweepvars);
#print "scalar is $a\n";

#print "the sweepvals are originally:";
#https://perldoc.perl.org/perldsc.html#Access-and-Printing-of-an-ARRAY-OF-ARRAYS
#for $aref ( @sweepvals ) {
#    print "\t [ @$aref ],\n";
#}

if(scalar(@sweepvars)<1){
    push @sweepvals, [0];
    our $name1="none1name";
} else {
    our $name1=$sweepvars[0] . "name";
    #print "$name1\n";
}

if(scalar(@sweepvars)<2){
    push @sweepvals, [0];
    our $name2="none2name";
} else {
    our $name2=$sweepvars[1] . "name";
}
#print "names are $name1, $name2\n";
#print "referenced var values are $$name1, $$name2\n";
#print "now sweepvals are:\n";
#for $aref ( @sweepvals ) {
#    print "\t [ @$aref ],\n";
#}

$$name1="param1";
$$name2="param2";
#print "$$name1, $$name2\n";

#call second half of script
do "$code_dir/launching_scripts/makeparams2.pl" or die "$@ from call";
return 1;
