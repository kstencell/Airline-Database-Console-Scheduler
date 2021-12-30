//
// Assignment 4, Question 2
// PROG71985 - F20
// Karl Stencell - Oct 2020
//
//
// REVISION HISTORY
// 1.0		2020-Nov-07		initial
// 2.0		2020-Nov-30		refactor
//
// Header file for airplane.c

#pragma once

#include "seat.h"
#include <stdbool.h>

#define MAX_SEATS		12

typedef struct airplane
{
	int airplaneNum;
	int capacity;
} AIRPLANE, *P_AIRPLANE;

// PROTOTYPES
AIRPLANE createAirplane(int);
int getAirplaneCapacity(P_AIRPLANE);
int getAirplaneNumber(P_AIRPLANE);