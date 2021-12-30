//
// Assignment 4, Question 2
// PROG71985 - F20
// Karl Stencell - Nov 2020
//
//
// REVISION HISTORY
// 2.0		2020-Nov-30		refactor
//
// Header file for flight.c

#pragma once
#include "airplane.h"
#include "seatsADT.h"

typedef struct flight
{
	int flightNum;
	P_AIRPLANE airplane;
	P_SEATS seatList;
}FLIGHT, *P_FLIGHT;

// PROTOTYPES

FLIGHT createFlight(int);
FLIGHT copyFlight(FLIGHT);
void addAirplaneToFlight(P_FLIGHT, P_AIRPLANE);
void disposeFlight(FLIGHT);