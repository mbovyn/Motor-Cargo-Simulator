#!/usr/bin/perl
# creates a number of job execution lines for submission to pbs

my $run_name = "run_length"; # command line

my $i1Max = 16;
my $i2Max = 16;

for (my $i1 = 1; $i1 <= $i1Max; $i1++)
{
    for (my $i2 = 1; $i2 <= $i2Max; $i2++)
    {

        my $file_name=$run_name . "." . $i1 . "." . $i2 . ".pub";

        system "qsub pubs/$file_name";

    }
}
