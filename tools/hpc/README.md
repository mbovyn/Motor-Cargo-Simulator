# Steps for running on the HPC

From scratch. Locally:

* create a folder (remember name)
* copy prepHPC.sh into the folder and run it
* edit makeandlaunch.pl to reflect the parameters you want to use, hpc and folder name
* run makeandlaunch.pl - this will create parameter files and pub files
* Add an ISEED
* copy that folder onto the hpc via filezilla or whatever

To the HPC

* SSH in: ```ssh mbovyn@hpc.oit.uci.edu```
* navigate to correct folder: ```cd /pub/mbovyn```
* cd into code folder and compile correct version
* copy executable up one level ```cp motors.x ..```
* return to folder ```cd ..```
* launch ```qsub pubs/*```

Monitoring

* see queues: ```q```
* see my jobs: ```qstat -u mbovyn```
* kill jobs: ```qdel 'runid'``` or ```qdel -u mbovyn```
