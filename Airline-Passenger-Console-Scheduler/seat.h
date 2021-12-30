//
// Assignment 4, Question 2
// PROG71985 - F20
// Karl Stencell - Nov 2020
//
//
// REVISION HISTORY
// 2.0		2020-Nov-30		refactor
//
// Header file for seat.c

#pragma once

#include <stdbool.h>
#include <stdio.h>
#include "passenger.h"

typedef enum OccupyStatus { Occupied, Unoccupied } STATUS;

typedef struct seat
{
	PASSENGER passenger;
	int seatID;
	STATUS seatStatus;
}SEAT, *P_SEAT;

// PROTOTYPES

SEAT createSeat(PASSENGER, int);
SEAT copySeat(SEAT);
bool compareSeats(SEAT, SEAT);
int getSeatNum(SEAT);
char* getLastNameFromSeat(SEAT);
void printSeatAssignmentFromSeat(SEAT);
void streamPrintSeat(FILE*, SEAT);
SEAT streamReadSeat(FILE*);