#!/usr/bin/perl

#use strict;
use warnings;

print "Launching (launch.pl)!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";

#clean out old files
system("'$code_dir'/launching_scripts/clean_files.sh '$code_dir' '$working_dir' $keep_old")==0 or die();

#make parameter files
do "$code_dir/launching_scripts/makeparams.pl" or die "$@ from call";

if ($launch_mode eq 'local') { #launch simulations
    system("'$code_dir'/launching_scripts/make_and_get_executable.sh '$code_dir' '$working_dir' $compile_keyword $compile") == 0
        or die "compilation failed";
    system("'$code_dir'/launching_scripts/launch_over_paramfiles.sh '$run_name' '$code_dir' '$working_dir' $repeats $groups $verbose $keep_seed $keep_old $dont_wait") == 0
        or die "launching failed";
    exec("'$code_dir'/launching_scripts/hpc/cat_files.sh");
} elsif ($launch_mode eq 'hpc') { #make parameter files only
    system("'$code_dir'/launching_scripts/hpc/prepHPC.sh '$code_dir' '$working_dir'") == 0 or die "prep_hpc failed";
    do "$code_dir/launching_scripts/hpc/make_pubs_array.pl" or die "$@ from call";
} else {
    die "Invalid launch mode: should be 'local' or 'hpc'";
}
return 1;
