#pragma once
#include <map>
#include <cmath>
#include <random>
#include <stdio.h>
#include <cstring>
#include <complex>
#include <fstream>
#include <iomanip>
#include <iostream>

// HEADER FILE FOR GLOBAL VARIABLES
#include "vars.h"

//Random number generator
extern std::ranlux48 rgen;

// DECLARATIONS FOR GLOBAL VARIABLE STRUCTS
extern struct subsystem_variables subsystem;
extern struct trajectory_variables traj;
extern struct input_variables input;
extern struct bath_variables bath;
extern struct observables obs;
extern struct potential pot;
