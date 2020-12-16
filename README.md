# 3D computational model of intracellular cargo transport by molecular motors [![DOI](https://zenodo.org/badge/68874025.svg)](https://zenodo.org/badge/latestdoi/68874025)

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

## Documentation

Each of the folders listed above has a readme which gives more information.

The [numerical tests](/numerical_tests) folder includes tests of many aspects of the simulation which show they recapitulate expected results.

## Getting started

#### Running a simulation
This repo contains the C source code for the simulation. Compiliation of this code is one of the steps included in the launching scripts, so don't worry about compiling before you get started.

To run a simulaton, start with [setandlaunch.pl](archetypes/setandlaunch.pl). This Perl code sets up everything for a simulation and starts it. For it to run, you need

* Perl
* Bash
* GCC
* make

Everything you need should come with the build-essential package in Debian/Ubuntu, or xcode / xcode command line tools in macOS.
The code is not Windows friendly, but can be run through the Windows Subsystem for Linux.

It has been tested on modern MacOS up to Catalina, Ubuntu 18.04 and 20.04, and those distributions of Ubuntu installed through Windows Subsystem for Linux on Windows 10.

#### Analyzing a simulation

Code for reading in simulation results and making movies of them is included, written in Matlab. Start with [analysis.m](archetypes/analysis.m) and [movie.m](archetypes/movie.m).

## Other tools

Also included are some scripts which generate C code (Mathematica + command line tools). These tools were used to go from the mathematical model to the simulation implementation, and could be helpful if changes to the model are desired.
