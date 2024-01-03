#!/bin/sh
#BSUB -q hpcintro
#BSUB -J SLEEPER
#BSUB -R "rusage[mem=200MB]"
#BSUB -R "select[model == XeonE5_2650v4]"
#BSUB -W 00:02
#BSUB -u gygridd@gmail.com
#BSUB -o Output%J.out

#commands to exec
/bin/sleep 30 
echo "Finished sleeping..." 
echo $CPUTYPEV
