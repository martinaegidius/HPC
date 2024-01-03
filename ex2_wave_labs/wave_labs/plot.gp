#!/usr/bin/gnuplot -persist 
set terminal png
set output 'plot.png'
plot "cleaned_wave.dat" using 1:2 with lines
