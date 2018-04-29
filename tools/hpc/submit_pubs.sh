#!/bin/bash

if [ ! -f ISEED ] ; then
    echo "Missing ISEED!"
    exit 1
fi

cp code/motors.x .

for filename in pubs/*.pub; do
    qsub $filename
done
