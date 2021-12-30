//
// Assignment 4, Question 2
// PROG71985 - F20
// Karl Stencell - Nov 2020
//
//
// REVISION HISTORY
// 2.0		2020-Nov-30		refactor
//
// Header file for flightnode.c

#pragma once

#include "flight.h"

typedef struct flightnode
{
	FLIGHT nodeData;
	struct flightnode* next;
}FLIGHT_NODE, *P_FLIGHT_NODE;

// PROTOTYPES

P_FLIGHT_NODE createFlightNode(FLIGHT);
void setFlightNodeNextFlightNode(P_FLIGHT_NODE, P_FLIGHT_NODE);
P_FLIGHT_NODE getFlightNodeNextFlightNode(P_FLIGHT_NODE);
void disposeFlightNode(P_FLIGHT_NODE);