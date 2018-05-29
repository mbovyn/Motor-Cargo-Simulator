#!/bin/bash

if [ ! -f ISEED ] ; then
    echo "Missing ISEED!"
    exit 1
fi

if [ ! -f simulation_code/motors.x ] ; then
    echo "Missing executable!"
    exit 2
fi

cp simulation_code/motors.x .

for filename in pubs/*.pub; do
    qsub $filename
done
