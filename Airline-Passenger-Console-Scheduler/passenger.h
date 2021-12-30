//
// Assignment 4, Question 2
// PROG71985 - F20
// Karl Stencell - Nov 2020
//
//
// REVISION HISTORY
// 2.0		2020-Nov-30		refactor
//
// Header file for passenger.c

#pragma once

#include <stdio.h>
#define MAX_NAME_LEN		20

typedef struct passenger
{
	char* firstName;
	char* lastName;
}PASSENGER, *P_PASSENGER;

// PROTOTYPES

PASSENGER createPassenger(char[], char[]);
char* getLastNameFromPassenger(PASSENGER);
void disposePassenger(PASSENGER);
void printPassengerInfo(PASSENGER);
void streamPrintPassenger(FILE*, PASSENGER);