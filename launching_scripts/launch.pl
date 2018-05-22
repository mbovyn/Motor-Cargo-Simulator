#!/usr/bin/perl

#use strict;
use warnings;

#clean out old files
system("$code_dir/launching_scripts/clean_files.sh $code_dir $working_dir $keep_old");

#make parameter files
do "$code_dir/launching_scripts/makeparams.pl";

if ($launch_mode eq 'local') { #launch simulations
    if ($compile eq 'yes') {
        system("$code_dir/launching_scripts/make_and_get_executable.sh $code_dir $working_dir $compile_keyword");
    }
    exec("$code_dir/launching_scripts/launch_over_paramfiles.sh '$run_name' '$code_dir' '$working_dir' $repeats $verbose $keep_old $dont_wait");
} elsif ($launch_mode eq 'hpc') { #make parameter files only
    do "$code_dir/launching_scripts/hpc/make_pubs.pl";
} else {
    die "Invalid launch mode: should be 'local' or 'hpc'\n";
}
