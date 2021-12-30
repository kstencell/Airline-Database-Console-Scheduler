//
// Assignment 4, Question 2
// PROG71985 - F20
// Karl Stencell - Nov 2020
//
//
// REVISION HISTORY
// 2.0		2020-Nov-30		refactor
//
// Header file for seatnode.c

#pragma once
#include "seat.h"

typedef struct seatnode
{
	SEAT nodeData;
	struct seatnode* next;
}SEAT_NODE, *P_SEAT_NODE;

// PROTOTYPES

P_SEAT_NODE createSeatNode(SEAT);
void setSeatNodeNextSeatNode(P_SEAT_NODE, P_SEAT_NODE);
P_SEAT_NODE getSeatNodeNextSeatNode(P_SEAT_NODE);
void disposeSeatNode(P_SEAT_NODE);