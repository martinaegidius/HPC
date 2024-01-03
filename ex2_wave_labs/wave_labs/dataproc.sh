#!/bin/sh

awk '{ if ($2!=0) print $1,$2; else print $1, $3;}' wave.dat > cleaned_wave.dat

