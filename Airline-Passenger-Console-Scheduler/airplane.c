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
// This file contains all the functionality pertaining to the AIRPLANE structs, namely initializing and return passenger data.

#include "airplane.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

AIRPLANE createAirplane(int airplaneNum)
{
	AIRPLANE airplane;
	airplane.airplaneNum = airplaneNum;
	airplane.capacity = MAX_SEATS;
	return airplane;
}

AIRPLANE copyAirplane(AIRPLANE airplane)
{
	AIRPLANE copy;
	copy.airplaneNum = airplane.airplaneNum;
	copy.capacity = airplane.capacity;
	return copy;
}

int getAirplaneCapacity(P_AIRPLANE thisAirplane)
{
	return thisAirplane->capacity;
}

int getAirplaneNumber(P_AIRPLANE thisAirplane)
{
	return thisAirplane->airplaneNum;
}

