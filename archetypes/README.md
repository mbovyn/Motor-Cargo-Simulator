## Example files for starting simulation, analysis and visualization

Copy and modify these files to perform simulation and analysis

### Simulation

setandlaunch.pl: Sets simulation parameters and calls launch.pl, which launches simulation. To perform simulation, edit file and set desired parameters, then ```./setandlaunch.pl```

### Analysis

analysis.m: Gives correct formatting of inputs to import_params_and_results.m, which brings simulation output into Matlab. Set desired directories and run names then run in Matlab.

movie.m: Gives correct inputs to draw_movie.m, which draws visualization of simulation output. Set desired movie parameters and run in Matlab.
