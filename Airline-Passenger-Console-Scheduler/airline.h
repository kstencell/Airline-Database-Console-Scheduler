// Assignment 4, Question 2
// PROG71985 - F20
// Karl Stencell - Nov 2020
//
//
// REVISION HISTORY
// 2.0		2020-Nov-30		refactor
//
// Header file for airline.c

#pragma once

#include <stdbool.h>
#include "flightsADT.h"

#define NUM_OF_AIRPLANES		2
#define MAX_BUFFER				25

typedef struct airline
{
	char* name;
	int airplaneNums[NUM_OF_AIRPLANES];
	P_FLIGHTS flightList;
}AIRLINE, *P_AIRLINE;


// PROTOTYPES

AIRLINE createAirline(char[]);
bool addFlightToAirline(P_AIRLINE, FLIGHT);
bool assignAirplane(P_AIRLINE, P_AIRPLANE, int);
int getEmptySeatCount(P_AIRLINE, int);
int getOccupiedSeatCount(P_AIRLINE, int);
int getFlightCapacityFromAirline(P_AIRLINE);
void listEmptySeats(P_AIRLINE, int);
bool addSeatAssignment(P_AIRLINE, int, SEAT);
bool isSeatAvailable(P_AIRLINE, int, int);
SEAT getSeat(P_AIRLINE, int, int);
bool removeSeat(P_AIRLINE, int, SEAT);
void printSeatsInAlphabeticalOrder(P_AIRLINE, int);
void printSeatAssignment(P_AIRLINE, int, int);
void disposeAirline(P_AIRLINE);

bool saveAirlineToDisk(P_AIRLINE airline, char []);
bool loadAirlineFromDisk(P_AIRLINE, P_AIRPLANE, P_AIRPLANE, char[]);