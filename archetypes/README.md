## Example files for starting simulation, analysis and visualization

Copy and modify these files to perform simulation and analysis

### Simulation

setandlaunch.pl: Sets simulation parameters and calls launch.pl, which launches simulation. To perform simulation, edit file and set desired parameters, then ```./setandlaunch.pl```

### Analysis

analysis.m: Gives correct formatting of inputs to import_params_and_results.m, which brings simulation output into Matlab. Set desired directories and run names then run in Matlab.

movie.m: Gives correct inputs to draw_movie.m, which draws visualization of simulation output. Set desired movie parameters and run in Matlab.

### Adding parameters

To add a parameter, you need to edit several files:

1. Add as variable to perl script setandlaunch.pl in archetypes
1. Add to perl script that writes parameter file: makeparams2.pl
    * If you want to be able to sweep over the parameter, you need to add it to makeparams1.pl as well, and give it a passthrough name which goes into makeparams2.pl (check the other variables for examples).
1. Edit getInputParams to read the new lines
1. Add the variable(s) to the header, motors.h
