# Tools for deriving equations and generating C code

## Contents:

* generateEquations.nb: algorithmically writes out model equations
    * generated beadequations*.c and stochasticequations*.c
* findDistanceSphere.nb: equation to find shortest distance along sphere surface and through empty space to the MT
    * generates spheredist.txt, which holds an equation used in the function findMTdist, [defined in motorHelpers_setup.c](https://github.com/mbovyn/Motor_Freedom/blob/b3c23df1b85995bf6ca94763a3e3098d953ae4c3/simulation_code/motorHelpers_setup.c#L368)
* pointToMT.nb: finds the shortest line from a point to the MT
    * generates pointToMT_formulae.txt, which holds 3 equations used in:
        * function vecToClosestPointOnMT, [defined in motorHelpers_setup.c](https://github.com/mbovyn/Motor_Freedom/blob/b3c23df1b85995bf6ca94763a3e3098d953ae4c3/simulation_code/motorHelpers_setup.c#L350)
        * function pointToMTdist, [defined in motorHelpers_setup.c](https://github.com/mbovyn/Motor_Freedom/blob/b3c23df1b85995bf6ca94763a3e3098d953ae4c3/simulation_code/motorHelpers_setup.c#L360)
        * function closestPointOnMT, [defined in motorHelpers_setup.c](https://github.com/mbovyn/Motor_Freedom/blob/b3c23df1b85995bf6ca94763a3e3098d953ae4c3/simulation_code/motorHelpers_setup.c#L645)
* anchorDiffusionTimestep.nb: finds timestep which limits error of motor movement
    * used to set max timestep [in getInputParams.c](https://github.com/mbovyn/Motor_Freedom/blob/b3c23df1b85995bf6ca94763a3e3098d953ae4c3/simulation_code/getInputParams.c#L560)
* quaternions.nb: equations to save rotation record as quaternions and convert to Euler vectors
    * generates quaternion_formulae.txt, used in:
        * function update_quaternion, [defined in aggregate_numbers.c](https://github.com/mbovyn/Motor_Freedom/blob/b3c23df1b85995bf6ca94763a3e3098d953ae4c3/simulation_code/aggregate_numbers.c#L53)
        * conversion in ReturnOmega of function write_all [in dataCollection.c](https://github.com/mbovyn/Motor_Freedom/blob/b3c23df1b85995bf6ca94763a3e3098d953ae4c3/simulation_code/dataCollection.c#L401)
* rotateToVec.nb: equation to rotate cargo to a certain vector
    * generates rotateToVecFormulae.txt, equations are used in:
        * function makeRotationMatrix, [defined in motorHelpers_setup.c](https://github.com/mbovyn/Motor_Freedom/blob/b3c23df1b85995bf6ca94763a3e3098d953ae4c3/simulation_code/motorHelpers_setup.c#L324)
        * function rotateCargo, [defined in motorHelpers_setup.c](https://github.com/mbovyn/Motor_Freedom/blob/b3c23df1b85995bf6ca94763a3e3098d953ae4c3/simulation_code/motorHelpers_setup.c#L336)

* CFormToC.sh: bash code that uses sed to convert from the CForm expressions that Mathematica writes to vanilla C code

## Generating code to simulate more/different numbers of motors

* Set nmax and nmaxbead in and run the notebook generateEquations.nb
    * Will take a long time (hours) for >10 free or >30 rigid motors
    * Quick for <=5, so if you're trying to make more free set bead to 5, or vice versa
    * generates
* Run the conversion script: ```./CFormToC.sh```
* Copy the file you wanted to ```../simulation_code```
* Add cases to Makefile and driveMotors.c
