//
// Assignment 4, Question 2
// PROG71985 - F20
// Karl Stencell - Nov 2020
//
//
// REVISION HISTORY
// 1.0		2020-Nov-07		initial
// 2.0		2020-Nov 30		refactor
//
// INITIAL NOTES:
// This program managers a list of passengers scheduled to board a 12 seat plane.
// Through the menu options a user will be able to view the current list of passengers, add new passengers, and remove passengers.
// The program saves its data to the computer storage when completed and will retrieve it upon execution.
// The data is set up with a nested struct technique. The plane itself is a struct that within it contains an array of seat structs pointers pointing to passenger info.
//
// REFACTOR NOTES:
// Assignment feedback for version 1.0:
// "Your utility functions must be in separate files (with their own .h file)"
// "I don't understand the separation of functions in source, seat, and airplane..."
//
// Version 1.0 had this pesky issue of not being able to iterate through the array of seats if some were not initialized, however with the power and knowledge of linked lists I have overcome this issue.
// Implementing linked lists was quite the task and involved considerable refactoring. The general structure now is that an AIRLINE struct contains a linked list of FLIGHT structs and each FLIGHT struct
// contains a linked list of SEAT structs and inside of each is a PASSENGER struct.
// A picture outlining my object organization can be found in the solution directory under q2 called "organization.jpg".
// This program still has all the functionality of the initial version except now it has functionality for handling multiple flights, multiple planes, and confirming seat assignments.
// To address the assignment feedback, the menu functionality has been moved to its own file.


//#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "airline.h"
#include "airplane.h"
#include "seat.h"
#include "menu.h"
#include "source.h"


int main(void)
{
	// Create the airline and the airplanes
	AIRLINE colossusAirlines = createAirline("Colossus Airlines");
	P_AIRLINE p_colossusAirlines = &colossusAirlines;

	AIRPLANE airplane1 = createAirplane(p_colossusAirlines->airplaneNums[0]);
	P_AIRPLANE p_airplane1 = &airplane1;
	AIRPLANE airplane2 = createAirplane(p_colossusAirlines->airplaneNums[1]);
	P_AIRPLANE p_airplane2 = &airplane2;

	if (!loadAirlineFromDisk(p_colossusAirlines, p_airplane1, p_airplane2, "datafile.txt")) // If there's saved data then pull from it.
	{
		fprintf(stderr, "No previous flight data found.\n"); // If no saved data, provide just enough initialization to get started.
	
		int flightNums[NUM_OF_FLIGHTS] = { 102,311,444,519 };
		int numberOfFlights = sizeof(flightNums) / sizeof(flightNums[0]);

		for (int i = 0; i < numberOfFlights; i++)
		{
			FLIGHT newFlight = createFlight(flightNums[i]);
			addFlightToAirline(&colossusAirlines, newFlight);
		}

		// There's no explicit reason to assign one plane over another for a flight since they don't have routes to consider
		// So I just randomly assigned them to show that the program does at least consider multiple planes.
		assignAirplane(p_colossusAirlines, p_airplane1, flightNums[0]);
		assignAirplane(p_colossusAirlines, p_airplane1, flightNums[1]);
		assignAirplane(p_colossusAirlines, p_airplane2, flightNums[2]);
		assignAirplane(p_colossusAirlines, p_airplane2, flightNums[3]);
	}

	while (true) // The main engine of the code which keeps spinning the menus round and round until the user wants to exit.
	{
		int flightNum;
		flightNum = flightChoiceMenuOptions(p_colossusAirlines); //Top level menu for chosing a flight.
		bool continueMainMenu = true;

		while (continueMainMenu)
		{
			printMainMenuOptions(flightNum); // "Main" menu for manipulating data within a flight.
			continueMainMenu = executeUserOptionChoice(p_colossusAirlines, flightNum);
		}
	}
}