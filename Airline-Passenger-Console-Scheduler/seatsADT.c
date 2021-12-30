//
// Assignment 4, Question 2
// PROG71985 - F20
// Karl Stencell - Nov 2020
//
//
// REVISION HISTORY
// 2.0		2020-Nov 30		refactor
//
// This file contains the ADT interface with the linked list of seats contained within the FLIGHT struct
// This file is extremely similar to the flightsADT.c file. The implementation of the linked list here is almost an exact copy, the nodes just now hold SEATS

#include "airplane.h"
#include "seatsADT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


SEATS createSeatList() // initialize the pointer
{
	SEATS seatList = { 0 };
	return seatList;
}

bool addSeatAssignmentToSeatList(P_SEATS p_seatList, SEAT thisSeat) // adds a SEAT to the end of the seat list
{
	P_SEAT_NODE newNode = createSeatNode(thisSeat);

	if (p_seatList->seats == NULL) // Flight List is empty
	{
		setSeatNodeNextSeatNode(newNode, p_seatList->seats);
		p_seatList->seats = newNode;
	}
	else
	{
		P_SEAT_NODE current = p_seatList->seats;

		while (getSeatNodeNextSeatNode(current) != NULL) // find the end of the list
		{
			current = getSeatNodeNextSeatNode(current);
		}

		setSeatNodeNextSeatNode(current, newNode); // append the new node to the end
	}
	return true;
}

int getSeatCount(P_SEATS p_seatList) // get the current seat count in a seat list
{
	if (p_seatList->seats == NULL)
	{
		return 0;
	}
	else
	{
		P_SEAT_NODE current = p_seatList->seats;
		int numOfSeatsFilled = 0;
		while (current != NULL) // until it reaches the end of the list
		{
			numOfSeatsFilled++;
			current = getSeatNodeNextSeatNode(current);
		}
		return numOfSeatsFilled;
	}
}

void listEmptySeatsInSeatList(P_SEATS p_seatList, int maxSeats) // list all empty seats in the list (sort of) this function detects when a valid and potential seat num is NOT present in the list 
{
	bool seatNumIsAvailable;
	int seatNum = 0;
	
	for (int i = 1; i <= maxSeats; i++) // Loop over all possible seat numbers
	{
		seatNumIsAvailable = true;
		P_SEAT_NODE current = p_seatList->seats;
		while (current != NULL)
		{
			if ((current->nodeData.seatID == i) && (current->nodeData.seatStatus == Occupied))
			{
				seatNumIsAvailable = false;
			}
			current = getSeatNodeNextSeatNode(current);
		}
		if (seatNumIsAvailable)
			printf("Seat %d is still available.\n", i);
	}
	printf("\n");
}

bool isSeatAvailableInSeatList(P_SEATS p_seatList, int seatNum) // iterate through the list and if a seat has the seat number we are looking for then it must already be occupied
{
	if (p_seatList->seats == NULL)
	{
		return true;
	}
	else
	{
		P_SEAT_NODE current = p_seatList->seats;
		while (current != NULL)
		{
			if (current->nodeData.seatID == seatNum)
				return false;
			current = getSeatNodeNextSeatNode(current);
		}
		return true;
	}
}

SEAT getSeatFromSeatList(P_SEATS p_seatList, int seatNum) // given a seat number this function returns the SEAT object 
{
	P_SEAT_NODE current = p_seatList->seats;
	while (current != NULL)
	{
		if (current->nodeData.seatID == seatNum)
			return current->nodeData;
		current = getSeatNodeNextSeatNode(current);
	}
}

bool removeSeatFromSeatList(P_SEATS p_seatList, SEAT seatToDelete) // removes a seat from the seat list
{
	P_SEAT_NODE current = p_seatList->seats;

	if (compareSeats(current->nodeData, seatToDelete)) 
	{
		if (getSeatNodeNextSeatNode(current) != NULL)
			p_seatList->seats = getSeatNodeNextSeatNode(current);
		else
			p_seatList->seats = NULL;

		disposeSeatNode(current);
		return true;
	}

	P_SEAT_NODE prev = NULL;
	while (current != NULL && !compareSeats(current->nodeData, seatToDelete)) // iterate through the list and look for the seat we are trying to delete
	{
		prev = current;
		current = getSeatNodeNextSeatNode(current);
	}

	if (current == NULL)
		return false; // wasn't found

	setSeatNodeNextSeatNode(prev, getSeatNodeNextSeatNode(current)); //unlink the seat we no longer want

	disposeSeatNode(current); // free it
	return true;
}

void printSeatsInAlphabeticalOrderFromSeatList(P_SEATS p_seatList) 
{
	int seatNums[MAX_SEATS];
	int i, j, temp;
	int seatCount = getSeatCount(p_seatList);

	P_SEAT_NODE current = p_seatList->seats;

	for (i = 0; i <seatCount; i++) // gather all the seat number into an array
	{
		seatNums[i] = getSeatNum(current->nodeData);
		current = getSeatNodeNextSeatNode(current);
	}

	for (i = 0; i < seatCount; i++) // sort the array into alphabetical order by looking up the names attached to the seat numbers
	{
		for (j = i + 1; j < seatCount; j++)
		{
			if (strcmp(getLastNameFromSeatID(p_seatList, seatNums[i]), getLastNameFromSeatID(p_seatList, seatNums[j])) > 0)
			{
				temp = seatNums[i];
				seatNums[i] = seatNums[j];
				seatNums[j] = temp;
			}
		}
	}

	fputs("List of passengers in alphabetical order:\n\n", stdout);
	for (i = 0; i < seatCount; i++) // now that the seat numbers correspond to their passengers in alphabetical order, just print them
	{
		printSeatAssignmentFromSeatList(p_seatList, seatNums[i]);
	}
}

char* getLastNameFromSeatID(P_SEATS p_seatList, int seatNum) // used for sorting alphabetically.
{
	P_SEAT_NODE current = p_seatList->seats;

	while (current != NULL)
	{
		if (current->nodeData.seatID == seatNum)
		{
			return getLastNameFromPassenger(current->nodeData.passenger); // contact the passenger interface for passenger info
		}
		else
			current = getSeatNodeNextSeatNode(current);
	}
}

void printSeatAssignmentFromSeatList(P_SEATS p_seatList, int seatNum) // find a specific seat and print it all
{
	P_SEAT_NODE current = p_seatList->seats;

	while (current != NULL)
	{
		if (current->nodeData.seatID == seatNum)
		{
			printSeatAssignmentFromSeat(current->nodeData); // contact seat interface for seat data
			return;
		}
		else
			current = getSeatNodeNextSeatNode(current);
	}
}

void streamPrintSeatList(FILE* fp, P_SEATS p_seatList) // iterate through a seat list and contact the seat interface to print all the info
{
	P_SEAT_NODE current = p_seatList->seats;

	fprintf(fp, "%d\n", getSeatCount(p_seatList));

	while (current != NULL)
	{
		streamPrintSeat(fp, current->nodeData);
		P_SEAT_NODE temp = getSeatNodeNextSeatNode(current);// have to use a temp pointer to hold the next address in the linked list while the nodes already printed get properly disposed
		disposeSeatNode(current);
		current = temp;
	}
}
