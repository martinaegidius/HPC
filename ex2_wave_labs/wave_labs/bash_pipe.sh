#!/bin/bash

awk '{ if ($2!=0) print $1, $2; else print $1, $3; }' wave.dat > processed.dat
gnuplot -persist <<-EOFMarker 
  set terminal png 
  set output 'plot_bash.png'
  set title "waves"
  plot 'processed.dat' using 1:2 with lines
EOFMarker

