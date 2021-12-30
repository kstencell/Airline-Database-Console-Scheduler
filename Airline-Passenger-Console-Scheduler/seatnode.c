//
// Assignment 4, Question 2
// PROG71985 - F20
// Karl Stencell - Nov 2020
//
//
// REVISION HISTORY
// 2.0		2020-Nov 30		refactor
//
// This file contains all the functionality pertaining to the SEAT_NODE structs

#include <stdio.h>
#include <stdlib.h>
#include "seatnode.h"

P_SEAT_NODE createSeatNode(SEAT seat)
{
	P_SEAT_NODE newNode = (P_SEAT_NODE)malloc(sizeof(SEAT_NODE));
	if (!newNode)
	{
		fprintf(stderr, "Error allocating memory.\n");
		exit(1);
	}
	newNode->nodeData = copySeat(seat);
	newNode->next = NULL;

	return newNode;
}

P_SEAT_NODE getSeatNodeNextSeatNode(P_SEAT_NODE seatNode)
{
	return seatNode->next;
}

void setSeatNodeNextSeatNode(P_SEAT_NODE sourceSeatNode, P_SEAT_NODE newNextSeatNode)
{
	sourceSeatNode->next = newNextSeatNode;
}

void disposeSeatNode(P_SEAT_NODE seatNode)
{
	disposePassenger(seatNode->nodeData.passenger);
	free(seatNode);
}