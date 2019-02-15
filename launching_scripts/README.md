## Files which launch simulation

Call launch.pl from setandlaunch.pl edited to have desired parameters. launch.pl calls
* clean_files.sh:clear out stale files from the directory of setandlaunch.pl
* makeparams.pl: makes parameter files by calling makeparams1.pl and makeparams2.pl
Based on the settings in setandlaunch.pl, it then sets up simulations one of two ways:
#### Local
simulates on local machine. Calls
* make_and_get_executable.sh: makes executable and writes hash of current commit
* launch_over_paramfiles.sh: launches and monitors simulations
* cat_files.sh: concatenates outputs when simulations are split up into multiple groups
Simulation output should be ready to be read in once launch.pl completes.

#### HPC
creates files to simulate on UCI High Performance Computing Cluster. Calls
* prepHPC.sh: copies code and scripts to directory of setandlaunch.pl
* make_pubs_array: writes files which submit jobs to the HPC
After call, directory is ready to be copied over to the HPC. See instructions in launching_scripts/hpc/README.md for running on HPC.
