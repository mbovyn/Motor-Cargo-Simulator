# Steps for running on the HPC

From scratch. Locally:

* create a folder (remember name)
* copy makeandlaunch.pl and ISEED into folder
* edit makeandlaunch.pl to reflect the parameters you want to use, hpc and folder name
* run makeandlaunch.pl - this will create parameter files and pub files
* copy that folder onto the hpc via filezilla or whatever
    * sftp://mbovyn@hpc.oit.uci.edu
    * want /pub/mbovyn instead of default home of /data/users/mbovyn

To the HPC

* SSH in: ```ssh mbovyn@hpc.oit.uci.edu```
* navigate to correct folder: ```cd /pub/mbovyn/folder_you_transferred```
* ```cd code``` and ```make free5``` or whatever the correct version version to compile is
* return to folder ```cd ..```
* launch ```./submit_pubs.sh```

Monitoring

* see queues: ```q```
* see my jobs: ```qstat -u mbovyn```
* kill jobs: ```qdel 'runid'``` or ```qdel -u mbovyn```

Other useful things:

* see number of lines in file: ```wc -l filename```
* find and display lines: ```grep -E "find this" *.log```
* open with no wrapping: ```vi -c 'set nowrap' filename```
