//
// Assignment 4, Question 2
// PROG71985 - F20
// Karl Stencell - Nov 2020
//
//
// REVISION HISTORY
// 2.0		2020-Nov-30		refactor
//
// Header file for flightADT.c

#pragma once
#include "flightnode.h"
#include "flight.h"

#define NUM_OF_FLIGHTS		4

typedef struct flightsADT
{
	P_FLIGHT_NODE flights;
}FLIGHTS, *P_FLIGHTS;

// PROTOTYPES

FLIGHTS createFlightList();
bool addFlightToFlightList(P_FLIGHTS, FLIGHT);
int getNumberOfFlights(P_FLIGHTS);
int getFlightCapacity(P_FLIGHTS);
bool assignAirplaneToFlight(P_FLIGHTS, P_AIRPLANE, int);
int getEmptySeatCountOnFlight(P_FLIGHTS, int);
int getOccupiedSeatCountOnFlight(P_FLIGHTS, int);
void listEmptySeatsOnFlight(P_FLIGHTS, int);
bool addSeatAssignmentOnFlight(P_FLIGHTS, int, SEAT);
bool isSeatAvailableOnFlight(P_FLIGHTS, int, int);
SEAT getSeatFromFlight(P_FLIGHTS, int, int);
bool removeSeatFromFlight(P_FLIGHTS, int, SEAT);
void printSeatsInAlphabeticalOrderForFlight(P_FLIGHTS, int);
void printSeatAssignmentFromFlight(P_FLIGHTS, int, int);

void streamPrintFlightData(FILE*, P_FLIGHTS);