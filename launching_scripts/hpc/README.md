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
* launch ```./submit_pubs.sh```

Monitoring

* see queues: ```q```
* see my jobs: ```qstat -u mbovyn```
* kill jobs: ```qdel 'runid'``` or ```qdel -u mbovyn```

Other useful things:

* change current directory to
    * any folder: ```cd /the/absolute/file/path``` or ```~/file/path``` where ```~``` means home folder
    * subfolder: ```cd foldername```
    * up one folder ```cd ..```
    * up two folders ```cd ../..```
    * to last folder ```cd -```
* see number of lines in file: ```wc -l filename```
* find and display lines: ```grep -E "find this" *.log```
* open with no wrapping: ```vi -c 'set nowrap' filename```
* delete folder ```rm -r foldername```
* work on a different screen which can be put in the background
    * to open: ```screen``` or ```screen submit_pubs.sh```
    * to terminate: ctrl+d (not command+d)
    * to detach and leave running: ctrl+a ctrl+d
    * to return: ```screen -r```
* hpc website: https://hpc.oit.uci.edu/
    * checkpoint and continue: https://hpc.oit.uci.edu/checkpoint
    * restart: https://hpc.oit.uci.edu/restart
    * location of checkpoint files: /checkpoint/mbovyn
