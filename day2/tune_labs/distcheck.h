#ifndef __DISTCHECK_H
#define __DISTCHECK_H

#include "data.h"

#ifdef ARRAY_OF_STRUCTS
double distcheck(particle_t *, int);
#else
double distcheck(particle_t, int);
#endif

#define CHECK_FLOP 1	// we simply add two numbers for every particle, ie. 1 op
#endif
