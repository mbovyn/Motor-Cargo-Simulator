#!/usr/bin/perl
#use strict;
#use warnings;

#call first part of script
#sets names
do "$code_dir/makeparams1.pl";

#set params to be swept over to param1 and param2 by overwriting
#append name to variablename to enable symbolic reference

my $name1=$sweepvars[0] . "name";
my $name2=$sweepvars[1] . "name";

$$name1="param1";
$$name2="param2";

#call second half of script
do "$code_dir/makeparams2.pl";
