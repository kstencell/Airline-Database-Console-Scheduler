//
// Assignment 4, Question 2
// PROG71985 - F20
// Karl Stencell - Nov 2020
//
//
// REVISION HISTORY
// 2.0		2020-Nov 30		refactor
//
// 
// This .c file contains the functionality provided for the AIRLINE struct
// A lot of these functions are trivial however it still speaks to the organization of objects and data within this program.
// It just so happens that for this assignment so far the AIRLINE struct is mostly a mask for the flightsADT because once the planes
// are initialized and the airline name is set there isn't much else in terms of functionality. It is expansible though.

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "flightsADT.h"
#include "airline.h"

AIRLINE createAirline(char name[])
{
	AIRLINE airline;

	// give the Airline a name
	int stringLength = strlen(name) + 1;
	airline.name = (char*)malloc(stringLength);
	if (!airline.name)
	{
		fprintf(stderr, "error allocating memory\n");
		exit(1);
	}
	strncpy(airline.name, name, stringLength);
	airline.name[stringLength - 1] = '\0';

	// give the Airline some planes.
	for (int i = 0; i < NUM_OF_AIRPLANES; i++)
	{
		airline.airplaneNums[i] = i+1;
	}

	// initialize the pointer to the linked list flightsADT
	airline.flightList = (P_FLIGHTS)malloc(sizeof(P_FLIGHTS));
	airline.flightList->flights = NULL;

	return airline;
}


bool addFlightToAirline(P_AIRLINE thisAirline, FLIGHT thisFlight) // Adds a flight to the list of flights
{
	if (addFlightToFlightList(thisAirline->flightList, thisFlight))
		return true;
	else
		return false;
}

bool assignAirplane(P_AIRLINE thisAirline, P_AIRPLANE thisAirplane, int flightNum) // assigns an airplane to a specific flight
{
	if (assignAirplaneToFlight(thisAirline->flightList, thisAirplane, flightNum))
		return true;
	else
		return false;
}

int getEmptySeatCount(P_AIRLINE thisAirline, int flightNum) // gets the empty seat count of a specific flight.
{
	return getEmptySeatCountOnFlight(thisAirline->flightList, flightNum);
}

int getOccupiedSeatCount(P_AIRLINE thisAirline, int flightNum) // gets the occupied seat count of a specific flight.
{
	return getOccupiedSeatCountOnFlight(thisAirline->flightList, flightNum);
}

int getFlightCapacityFromAirline(P_AIRLINE thisAirline) // gets the capacity of a flight from the flight's assigned airplane.
{
	return getFlightCapacity(thisAirline->flightList->flights);
}

void listEmptySeats(P_AIRLINE thisAirline, int flightNum) // list the empty seats on a flight.
{
	listEmptySeatsOnFlight(thisAirline->flightList, flightNum);
}

bool addSeatAssignment(P_AIRLINE thisAirline, int flightNum, SEAT newSeat) // add a seat to the seat list in a flight
{
	if (addSeatAssignmentOnFlight(thisAirline->flightList, flightNum, newSeat))
		return true;
	else
		return false;
}

bool isSeatAvailable(P_AIRLINE thisAirline, int flightNum, int seatNum) // check seat availability from a seat list in a flight
{
	if (isSeatAvailableOnFlight(thisAirline->flightList, flightNum, seatNum))
		return true;
	else
		return false;
}

SEAT getSeat(P_AIRLINE thisAirline, int flightNum, int seatNum) // returns a single seat from a seat list in a flight
{
	return getSeatFromFlight(thisAirline->flightList, flightNum, seatNum);
}

bool removeSeat(P_AIRLINE thisAirline, int flightNum, SEAT seatToDelete) // removes a single seat from a seat list in a flight.
{
	if (removeSeatFromFlight(thisAirline->flightList, flightNum, seatToDelete))
		return true;
	else
		return false;
}

void printSeatsInAlphabeticalOrder(P_AIRLINE thisAirline, int flightNum) // prints a flights seat list in alphabetical order
{
	printSeatsInAlphabeticalOrderForFlight(thisAirline->flightList, flightNum);
}

void printSeatAssignment(P_AIRLINE thisAirline, int flightNum, int seatNum) // prints an individual seat assignment from a seat list in a flight
{
	printSeatAssignmentFromFlight(thisAirline->flightList, flightNum, seatNum);
}

void disposeAirline(P_AIRLINE thisAirline)
{
	free(thisAirline->name);
}

bool saveAirlineToDisk(P_AIRLINE thisAirline, char filename[FILENAME_MAX]) // Save the whole airline to a text file
{
	FILE* fp;
	if ((fp = fopen(filename, "w+")) == NULL)
		return false;

	fprintf(fp, "%s\n", thisAirline->name);

	streamPrintFlightData(fp, thisAirline->flightList); // print all the data in all the flights to a file.
	disposeAirline(thisAirline);

	return true;
}

bool loadAirlineFromDisk(P_AIRLINE thisAirline, P_AIRPLANE p_airplane1, P_AIRPLANE p_airplane2, char filename[FILENAME_MAX]) // retrieve airline data from a text file
{
	FILE* fp;
	if ((fp = fopen(filename, "r")) == NULL)
		return false;

	char buffer[MAX_BUFFER];
	fscanf(fp, "%[^\n]s\n", buffer); // grabs the airline name from the file to bypass it

	int i;
	for (i = 0; i < NUM_OF_FLIGHTS; i++) // the flights are stored sequentially in the data file so this loop will call the "stream read flights" function for as many flights as there are.
	{
		int flightNum;
		fscanf(fp, "%d\n", &flightNum);
		FLIGHT newFlight = createFlight(flightNum);
		addFlightToAirline(thisAirline, newFlight); // actually make the flight node and fill it with a flight struct

		int planeNum;
		fscanf(fp, "%d\n", &planeNum);
		if (planeNum == 1) // again the plane numbers are a bit arbitrary in this assignment but the functionality is here to handle them
			assignAirplane(thisAirline, p_airplane1, flightNum);
		else if (planeNum == 2)
			assignAirplane(thisAirline, p_airplane2, flightNum);

		int numOfPassengersOnFlight;
		fscanf(fp, "%d\n", &numOfPassengersOnFlight);
		// linked lists don't inherently contain how long they are so I made sure to save how many passengers were onboard each flight in the text file when the program terminates
		// This is what informs the program when to stop reading the data file and move on to the next flight.
		for (int j = 0; j < numOfPassengersOnFlight; j++)
		{
			SEAT s = streamReadSeat(fp); // reads all the info about a seat in one go, then adds the seat to the appropriate flight's seat list.
			addSeatAssignment(thisAirline, flightNum, s);
		}
	}

	return true;
	
}