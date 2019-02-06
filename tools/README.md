# Tools for deriving equations and generating C code

## Contents:

* generateEquations.nb: algorithmically writes out model equations
    * generates
* findDistanceSphere.nb: equation to find shortest distance along sphere surface and through empty space to the MT
    * generates spheredist.txt, which holds an equation used in the function findMTdist, defined in motorHelpers_setup.c
* pointToMT.nb: finds the shortest line from a point to the MT
    * generates pointToMT_formulae.txt, which holds 3 equations used in:
        * function vecToClosestPointOnMT, defined in motorHelpers_setup.c
        * function pointToMTdist, defined in motorHelpers_setup.c
        * function closestPointOnMT, defined in motorHelpers_setup.c
* anchorDiffusionTimestep: finds timestep which limits error of motor movement
    * used when looking at timesteps in getInputParams.c
* quaternions.nb: equations to save rotation record as quaternions and convert to Euler vectors
    * generates quaternion_formulae.txt, used in:
        * function update_quaternion, defined in aggregate_numbers.c
        * conversion in ReturnOmega of function write_all in dataCollection.c
* rotateToVec.nb: equation to rotate cargo to a certain vector
    * generates rotateToVecFormulae.txt, equations are used in:
        * function makeRotationMatrix, defined in motorHelpers_setup.c
        * function rotateCargo, defined in motorHelpers_setup.c

* CFormToC.sh: bash code that uses sed to convert from the CForm expressions that Mathematica writes to vanilla C code

## Generating code to simulate more/different numbers of motors

* Set nmax and nmaxbead in and run the notebook generateEquations.nb
    * Will take a long time (hours) for >10 free or >30 rigid motors
    * Quick for <=5, so if you're trying to make more free set bead to 5, or vice versa
    * generates
* Run the conversion script: ```./CFormToC.sh```
* Copy the file you wanted to ```../simulation_code```
* Add cases to Makefile and driveMotors.c
