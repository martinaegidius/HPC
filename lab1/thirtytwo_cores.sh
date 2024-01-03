#!/bin/sh
#BSUB -q hpcintro
#BSUB -J SLEEPER
#BSUB -R "rusage[mem=200MB]"
#BSUB -R "select[model == XeonE5_2650v4]"
#BSUB -n 32 #32 cores please
#BSUB -R "span[block=8]" #this *should* give us 4 hosts  
#BSUB -W 00:02

#BSUB -u gygridd@gmail.com
#BSUB -o thirtytwo_Cores.out

#commands to exec
/bin/sleep 30 
echo "Finished sleeping..." 
echo $CPUTYPEV
