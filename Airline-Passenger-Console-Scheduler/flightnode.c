//
// Assignment 4, Question 2
// PROG71985 - F20
// Karl Stencell - Nov 2020
//
//
// REVISION HISTORY
// 2.0		2020-Nov 30		refactor
//
// This file contains all the functionality pertaining to the FLIGHT_NODE structs

#include <stdlib.h>
#include "flightnode.h"

P_FLIGHT_NODE createFlightNode(FLIGHT flight)
{
	P_FLIGHT_NODE newNode = (P_FLIGHT_NODE)malloc(sizeof(FLIGHT_NODE));
	if (!newNode)
	{
		fprintf(stderr, "Error allocating memory.\n");
		exit(1);
	}
	newNode->nodeData = copyFlight(flight);
	newNode->next = NULL;

	return newNode;
}

P_FLIGHT_NODE getFlightNodeNextFlightNode(P_FLIGHT_NODE flightNode)
{
	return flightNode->next;
}

void setFlightNodeNextFlightNode(P_FLIGHT_NODE sourceFlightNode, P_FLIGHT_NODE newNextFlightNode)
{
	sourceFlightNode->next = newNextFlightNode;
}

void disposeFlightNode(P_FLIGHT_NODE flightNode)
{
	disposeFlight(flightNode->nodeData);
}
