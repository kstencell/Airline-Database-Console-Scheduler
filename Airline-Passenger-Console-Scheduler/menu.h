// Assignment 4, Question 2
// PROG71985 - F20
// Karl Stencell - Nov 2020
//
//
// REVISION HISTORY
// 1.0		2020-Nov-30		refactor
//
// Header file for menu.c

#pragma once
#define MAX_USER_INPUT_LEN		20

//PROTOTYPES

int flightChoiceMenuOptions(P_AIRLINE);
void printMainMenuOptions(int);
bool executeUserOptionChoice(P_AIRLINE, int);
void menuShowEmptySeats(P_AIRLINE);
void menuAddSeatAssignment(P_AIRLINE, int);
void menuDeleteSeatAssignment(P_AIRLINE, int);
void menuConfirmSeatAssignment(P_AIRLINE, int);