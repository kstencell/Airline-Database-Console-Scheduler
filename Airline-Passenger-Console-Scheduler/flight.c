//
// Assignment 4, Question 2
// PROG71985 - F20
// Karl Stencell - Nov 2020
//
//
// REVISION HISTORY
// 2.0		2020-Nov 30		refactor
//
// This file contains all the functionality pertaining to the FLIGHT structs, namely initializing and return flight data.

#include <stdlib.h>
#include "flight.h"

FLIGHT createFlight(int flightNum)
{
	FLIGHT flight;
	flight.flightNum = flightNum;
	flight.airplane = NULL;
	flight.seatList = (P_SEATS)malloc(sizeof(P_SEATS));
	flight.seatList->seats = NULL;

	return flight;
}

FLIGHT copyFlight(FLIGHT flight)
{
	FLIGHT copy;
	copy.flightNum = flight.flightNum;
	copy.airplane = flight.airplane;
	copy.seatList = flight.seatList;

	return copy;
}

void addAirplaneToFlight(P_FLIGHT p_flight, P_AIRPLANE p_airplane)
{
	p_flight->airplane = p_airplane;
}

void disposeFlight(FLIGHT flight)
{
	free(flight.seatList);
}