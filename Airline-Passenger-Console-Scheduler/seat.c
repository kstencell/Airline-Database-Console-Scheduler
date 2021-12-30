//
// Assignment 4, Question 2
// PROG71985 - F20
// Karl Stencell - Nov 2020
//
//
// REVISION HISTORY
// 2.0		2020-Nov 30		refactor
//
// This file contains all the functionality pertaining to the SEAT structs, namely initializing and return seat data.

#include <string.h>
#include <stdio.h>
#include "seat.h"

SEAT createSeat(PASSENGER passenger, int seat_id)
{
	SEAT seat;
	seat.passenger = passenger;
	seat.seatID = seat_id;
	seat.seatStatus = Occupied;

	return seat;
}


SEAT copySeat(SEAT seat)
{
	SEAT copy;
	copy.passenger = seat.passenger;
	copy.seatID = seat.seatID;
	copy.seatStatus = seat.seatStatus;

	return copy;
}

bool compareSeats(SEAT a, SEAT b)
{
	if (a.seatID != b.seatID)
		return false;

	if (strcmp(a.passenger.firstName, b.passenger.firstName) && strcmp(a.passenger.lastName, b.passenger.lastName))
		return false;

	if (a.seatStatus != b.seatStatus)
		return false;

	return true;
}

int getSeatNum(SEAT seat)
{
	return seat.seatID;
}

char* getLastNameFromSeat(SEAT seat)
{
	return getLastNameFromPassenger(seat.passenger); // contact passenger interface for this info
}

void printSeatAssignmentFromSeat(SEAT seat)
{
	printf("\n");
	printf("Seat ID: %d\n", seat.seatID);
	printPassengerInfo(seat.passenger); // contact passenger interface for this info
}

void streamPrintSeat(FILE* fp, SEAT seat)
{
	streamPrintPassenger(fp, seat.passenger); // contact passenger interface for this info
	fprintf(fp, "%d\n", seat.seatID);
	fprintf(fp, "%d\n", seat.seatStatus);
}

SEAT streamReadSeat(FILE* fp) // reads an entire seats data from a file and recreates the struct
{
	char firstName[MAX_NAME_LEN];
	char lastName[MAX_NAME_LEN];
	int seatNum;
	int seatStatus;

	fgets(firstName, MAX_NAME_LEN, fp);
	for (size_t i = 0; i < strlen(firstName); i++)
		if (firstName[i] == '\n')
			firstName[i] = '\0';

	fgets(lastName, MAX_NAME_LEN, fp);
	for (size_t i = 0; i < strlen(lastName); i++)
		if (lastName[i] == '\n')
			lastName[i] = '\0';

	PASSENGER passenger = createPassenger(firstName, lastName);

	fscanf(fp, "%d\n", &seatNum);
	fscanf(fp, "%d\n", &seatStatus);

	SEAT s = createSeat(passenger, seatNum);
	return s;
}