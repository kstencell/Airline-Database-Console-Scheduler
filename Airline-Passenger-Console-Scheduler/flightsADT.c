//
// Assignment 4, Question 2
// PROG71985 - F20
// Karl Stencell - Nov 2020
//
//
// REVISION HISTORY
// 2.0		2020-Nov 30		refactor
//
// This file contains the ADT interface with the linked list of flights contained within the AIRLINE struct
// 

#include <stdlib.h>
#include "flightsADT.h"

FLIGHTS createFlightList() //initialize the list
{
	FLIGHTS flightList = { 0 };
	return flightList;
}

bool addFlightToFlightList(P_FLIGHTS p_flightList, FLIGHT thisFlight) // takes a flight, wraps it in a node, and adds it to the linked list
{
	P_FLIGHT_NODE newNode = createFlightNode(thisFlight);

	if (p_flightList->flights == NULL) // Flight List is empty
	{
		setFlightNodeNextFlightNode(newNode, p_flightList->flights);
		p_flightList->flights = newNode;
	}
	else
	{
		P_FLIGHT_NODE current = p_flightList->flights;

		while (getFlightNodeNextFlightNode(current) != NULL)
		{
			current = getFlightNodeNextFlightNode(current);
		}

		setFlightNodeNextFlightNode(current, newNode); // found the end of the chain so attach the new node.
	}
	return true;
}

int getNumberOfFlights(P_FLIGHTS p_flightList) // iterates through the list and keeps track of how many nodes it passes before it reaches the end
{

	if (p_flightList->flights == NULL) // Flight List is empty
	{
		return 0;
	}
	else
	{
		P_FLIGHT_NODE current = p_flightList->flights;
		int flightCount = 0;

		while (current != NULL)
		{
			flightCount++;
			current = getFlightNodeNextFlightNode(current);
		}
		return flightCount;
	}
}

int getFlightCapacity(P_FLIGHT_NODE thisFlight) // simply passing through this interface to get to the plane interface.
{
	return getAirplaneCapacity(thisFlight->nodeData.airplane);
}

bool assignAirplaneToFlight(P_FLIGHTS p_flightList, P_AIRPLANE thisAirplane, int flightNum) // takes a specific plane and assigns it to be the plane for a flight
{
	if (p_flightList->flights == NULL) // flight list is empty
	{
		fprintf(stderr, "No flights to assign an airplane to.\n");
		exit(1);
	}
	else
	{
		P_FLIGHT_NODE current = p_flightList->flights;

		while (current != NULL) // iterate through the list until we find the flight with the correct flight number we are looking for
		{
			if (current->nodeData.flightNum == flightNum) // found it
			{
				current->nodeData.airplane = thisAirplane; // assign the plane to the flight
				return true;
			}
			else
				current = getFlightNodeNextFlightNode(current);
		}
		return false;
	}
}

int getEmptySeatCountOnFlight(P_FLIGHTS p_flightList, int flightNum) // returns how many empty seats are still left on a flight
{
	if (p_flightList->flights == NULL) // flight list is empty
	{
		fprintf(stderr, "No flights to check seat list.\n");
		exit(1);
	}
	else
	{
		P_FLIGHT_NODE current = p_flightList->flights;

		while (current != NULL) // iterate through the list until we find the flight with the correct flight number we are looking for
		{
			if (current->nodeData.flightNum == flightNum) // found it
			{
				int emptySeatCount = current->nodeData.airplane->capacity - getSeatCount(current->nodeData.seatList); // contact the seatsADT for a seat count
				return emptySeatCount;
			}
			else
				current = getFlightNodeNextFlightNode(current);
		}
	}
}

int getOccupiedSeatCountOnFlight(P_FLIGHTS p_flightList, int flightNum) // get the number of seats currently taken on a flight
{
	if (p_flightList->flights == NULL) // flight list is empty
	{
		fprintf(stderr, "No flights to check seat list.\n");
		exit(1);
	}
	else
	{
		P_FLIGHT_NODE current = p_flightList->flights;

		while (getFlightNodeNextFlightNode(current) != NULL) // iterate through the list until we find the flight with the correct flight number we are looking for
		{
			if (current->nodeData.flightNum == flightNum)
			{
				int seatCount = getSeatCount(current->nodeData.seatList); // contact the seatsADT for a seat count.
				return seatCount;
			}
			else
				current = getFlightNodeNextFlightNode(current);
		}
	}
}

void listEmptySeatsOnFlight(P_FLIGHTS p_flightList, int flightNum) // list all the empty seats on a flight
{
	if (p_flightList->flights == NULL) // flight list is empty
	{
		fprintf(stderr, "No flights to check seat list.\n");
		exit(1);
	}
	else
	{
		P_FLIGHT_NODE current = p_flightList->flights;

		while (current != NULL) // iterate through the list until we find the flight with the correct flight number we are looking for
		{
			if (current->nodeData.flightNum == flightNum) // found it
			{
				int maxSeats = getFlightCapacity(current);
				listEmptySeatsInSeatList(current->nodeData.seatList, maxSeats); //contact seatsADT for a seat count
				return;
			}
			else
				current = getFlightNodeNextFlightNode(current);
		}
	}
}

bool addSeatAssignmentOnFlight(P_FLIGHTS p_flightList, int flightNum, SEAT newSeat) // add a seat to the flights seat list
{
	if (p_flightList->flights == NULL)
	{
		fprintf(stderr, "No flights to assign passengers.\n");
		exit(1);
	}
	else
	{
		P_FLIGHT_NODE current = p_flightList->flights;

		while (current != NULL) // iterate through the list until we find the flight with the correct flight number we are looking for
		{
			if (current->nodeData.flightNum == flightNum) // found it
			{

				addSeatAssignmentToSeatList(current->nodeData.seatList, newSeat); // contact seatsADT to add the new seat to the seat list
				return true;
			}
			else
				current = getFlightNodeNextFlightNode(current);
		}
		return false;
	}
}

bool isSeatAvailableOnFlight(P_FLIGHTS p_flightList, int flightNum, int seatNum) // check if a seat is available from the flights seat list
{
	if (p_flightList->flights == NULL)
	{
		fprintf(stderr, "No flights to assign passengers.\n");
		exit(1);
	}
	else
	{
		P_FLIGHT_NODE current = p_flightList->flights;

		while (current != NULL) // iterate through the list until we find the flight with the correct flight number we are looking for
		{
			if (current->nodeData.flightNum == flightNum) // found it
			{

				if (isSeatAvailableInSeatList(current->nodeData.seatList, seatNum)) // contact seatsADT for seat availability info
					return true;
				else
					return false;
			}
			else
				current = getFlightNodeNextFlightNode(current);
		}
		return false;
	}
}

SEAT getSeatFromFlight(P_FLIGHTS p_flightList, int flightNum, int seatNum)
{
	if (p_flightList->flights == NULL)
	{
		fprintf(stderr, "No flights to assign passengers.\n");
		exit(1);
	}
	else
	{
		P_FLIGHT_NODE current = p_flightList->flights;

		while (current != NULL) // iterate through the list until we find the flight with the correct flight number we are looking for
		{
			if (current->nodeData.flightNum == flightNum)
			{
				return getSeatFromSeatList(current->nodeData.seatList, seatNum); // contact seatsADT for a specific seat
			}
			else
				current = getFlightNodeNextFlightNode(current);
		}
	}
}

bool removeSeatFromFlight(P_FLIGHTS p_flightList, int flightNum, SEAT seatToDelete) // remove a specific seat from the seat list of a flight
{
	if (p_flightList->flights == NULL)
	{
		fprintf(stderr, "No flights to assign passengers.\n");
		exit(1);
	}
	else
	{
		P_FLIGHT_NODE current = p_flightList->flights;

		while (current != NULL) // iterate through the list until we find the flight with the correct flight number we are looking for
		{
			if (current->nodeData.flightNum == flightNum)
			{
				if (removeSeatFromSeatList(current->nodeData.seatList, seatToDelete)) // contact seatsADT to remove the seat from its linked list
					return true;
				else
					return false;
			}
			else
				current = getFlightNodeNextFlightNode(current);
		}
	}
}

void printSeatsInAlphabeticalOrderForFlight(P_FLIGHTS p_flightList, int flightNum) // prints the seats currently occupied on a flight in alphabetical order
{
	if (p_flightList->flights == NULL)
	{
		fprintf(stderr, "No flights to check seat list.\n");
		exit(1);
	}
	else
	{
		P_FLIGHT_NODE current = p_flightList->flights;

		while (current != NULL) // iterate through the list until we find the flight with the correct flight number we are looking for
		{
			if (current->nodeData.flightNum == flightNum)
			{
				if (getAirplaneCapacity(current->nodeData.airplane) == getEmptySeatCountOnFlight(p_flightList, flightNum)) // Nothing to list if the empty seat count is also the max seat count
					printf("There are no seat assignments on flight %d\n", flightNum);
				else
					printSeatsInAlphabeticalOrderFromSeatList(current->nodeData.seatList); // contact the seatsADT to print its seats in alphabetical order
				return;
			}
			else
				current = getFlightNodeNextFlightNode(current);
		}
	}
}

void printSeatAssignmentFromFlight(P_FLIGHTS p_flightList, int flightNum, int seatNum) // outputs the data from a seat on a flight
{
	if (p_flightList->flights == NULL)
	{
		fprintf(stderr, "No flights to check seat list.\n");
		exit(1);
	}
	else
	{
		P_FLIGHT_NODE current = p_flightList->flights;

		while (current != NULL) // iterate through the list until we find the flight with the correct flight number we are looking for
		{
			if (current->nodeData.flightNum == flightNum)
			{
				printSeatAssignmentFromSeatList(current->nodeData.seatList, seatNum); // contact seatsADT to inquire about the given seats info
				return;
			}
			else
				current = getFlightNodeNextFlightNode(current);
		}
	}
}

void streamPrintFlightData(FILE* fp, P_FLIGHTS p_flightList) // prints a whole flights data to a data file
{
	if (p_flightList->flights == NULL)
	{
		fprintf(stderr, "No flights to check seat list.\n");
		exit(1);
	}
	else
	{
		P_FLIGHT_NODE current = p_flightList->flights;

		while (current != NULL)
		{
			fprintf(fp, "%d\n", current->nodeData.flightNum);
			fprintf(fp, "%d\n", getAirplaneNumber(current->nodeData.airplane));
			streamPrintSeatList(fp, current->nodeData.seatList); // contact seatsADT to print the seat list inside the file
			P_FLIGHT_NODE temp = getFlightNodeNextFlightNode(current); // have to use a temp pointer to hold the next address in the linked list while the nodes already printed get properly disposed
			disposeFlightNode(current);
			current = temp;
		}
	}
}
