#!/bin/sh
#BSUB -q hpcintro
#BSUB -J SLEEPER
#BSUB -R "rusage[mem=200MB]"
#BSUB -R "select[model == XeonE5_2650v4]"
#BSUB -n 4 #4 cores please
#BSUB -R "span[hosts=1]" #on a single host 
#BSUB -W 00:02

#BSUB -u gygridd@gmail.com
#BSUB -o multicore.out

#commands to exec
/bin/sleep 30 
echo "Finished sleeping..." 
echo $CPUTYPEV
