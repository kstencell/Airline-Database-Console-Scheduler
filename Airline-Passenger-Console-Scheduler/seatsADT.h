//
// Assignment 4, Question 2
// PROG71985 - F20
// Karl Stencell - Nov 2020
//
//
// REVISION HISTORY
// 2.0		2020-Nov-30		refactor
//
// Header file for seatsADT.c

#pragma once

#define NAME_LEN 20

#include <stdio.h>
#include "seatnode.h"
#include "seat.h"

typedef struct seatsADT
{
	P_SEAT_NODE seats;
}SEATS, *P_SEATS;

// PROTOTYPES

SEATS createSeatList();
bool addSeatAssignmentToSeatList(P_SEATS, SEAT);
int getSeatCount(P_SEATS);
void listEmptySeatsInSeatList(P_SEATS, int);
bool addSeatAssignmentToSeatList(P_SEATS, SEAT);
bool isSeatAvailableInSeatList(P_SEATS, int);
SEAT getSeatFromSeatList(P_SEATS, int);
bool removeSeatFromSeatList(P_SEATS, SEAT);
void printSeatsInAlphabeticalOrderFromSeatList(P_SEATS);
char* getLastNameFromSeatID(P_SEATS, int);
void printSeatAssignmentFromSeatList(P_SEATS, int);
void streamPrintSeatList(FILE*, P_SEATS);

