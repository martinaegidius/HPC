#!/bin/sh
#BSUB -q hpcintro
#BSUB -J SOAvsAOS
#BSUB -R "rusage[mem=4GB]"
#BSUB -R "select[model == XeonE5_2650v4]"
#BSUB -W 01:00
#BSUB -u gygridd@gmail.com
#BSUB -o /zhome/ba/f/147212/hpc/day2/tune_labs/logs/SOAvsAOS.out


for nparticles in {2000..3000000..4000}
do 
	/zhome/ba/f/147212/hpc/day2/tune_labs/soa.gcc 1000 $nparticles
	/zhome/ba/f/147212/hpc/day2/tune_labs/aos.gcc 1000 $nparticles
done



