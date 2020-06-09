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

## Getting started

This simulation uses scripts in bash and perl, and the c code is compiled with gcc by default.
These tools are included with macOS by default as far as I can gather.
They are part of the build-essential package in Debian/Ubuntu.
I don't know much about the Windows command line, but I know this works:

Windows 10:
* Turn Windows features on or off -> check Windows Subsystem for Linux
* Windows store -> get and install ubuntu
* in Ubuntu
  * sudo apt update
  * sudo apt install build-essential
  
Good to go! Can clone in the code and launch. If you want to edit code in Windows, clone to mnt/c/some_folder
