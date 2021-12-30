//
// Assignment 4, Question 2
// PROG71985 - F20
// Karl Stencell - Nov 2020
//
//
// REVISION HISTORY
// 2.0		2020-Nov 30		refactor
//
// This file contains all the functionality pertaining to the PASSENGER structs, namely initializing and return passenger data.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "passenger.h"

PASSENGER createPassenger(char firstName[], char lastName[])
{
	PASSENGER passenger;
	
	//Assign first name
	int stringLength = strlen(firstName) + 1;
	passenger.firstName = (char*)malloc(stringLength);
	if (!passenger.firstName)
	{
		fprintf(stderr, "error allocating memory\n");
		exit(1);
	}
	strncpy(passenger.firstName, firstName, stringLength);
	passenger.firstName[stringLength - 1] = '\0';

	//Assign last name
	stringLength = strlen(lastName) + 1;
	passenger.lastName = (char*)malloc(stringLength);
	if (!passenger.lastName)
	{
		fprintf(stderr, "error allocating memory\n");
		exit(1);
	}
	strncpy(passenger.lastName, lastName, stringLength);
	passenger.lastName[stringLength - 1] = '\0';

	return passenger;
}

char* getLastNameFromPassenger(PASSENGER p)
{
	return p.lastName;
}

void disposePassenger(PASSENGER p)
{
	free(p.firstName);
	free(p.lastName);
}

void printPassengerInfo(PASSENGER p)
{
	printf("Passenger Name: %s, %s\n\n", p.lastName, p.firstName);
}

void streamPrintPassenger(FILE* fp, PASSENGER passenger)
{
	fprintf(fp, "%s\n", passenger.firstName);
	fprintf(fp, "%s\n", passenger.lastName);
}