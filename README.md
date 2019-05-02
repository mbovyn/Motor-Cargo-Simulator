# 3D mathematical model of intracellular cargo transport by molecular motors

This code performs simulation of a mathematical model of the motion of
intracellular cargos driven by molecular motors.

Contained herein:
* simulation_code: Code which performs the simulation, written in C.
* tools: Mathematica code and Bash scripts which generate C code used in the
simulation
* launching_scripts: Bash and Perl scripts which are useful for feeding the
code parameters and running sweeps, etc.
* archetypes: Example scripts in which parameter values are entered
* analysis and visualization: Matlab code which reads in simulation output and
makes movies

Getting started on Windows 10:

* Turn Windows features on or off -> check Windows Subsystem for Linux
* Windows store -> get and install ubuntu
* in Ubuntu
  * sudo apt-get update
  * sudo apt-get install build-essential
  
Good to go! Can clone in the code and launch. If you want to edit code in Windows, clone to mnt/c/some_folder
