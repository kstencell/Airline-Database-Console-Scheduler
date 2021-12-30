//
// Assignment 4, Question 2
// PROG71985 - F20
// Karl Stencell - Nov 2020
//
//
// REVISION HISTORY
// 2.0		2020-Nov 30		refactor
//
// This .c file contains the meat and potatoes of how both menus function.
// It involves printing options, getting user input, and executing user options.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "airline.h"
#include "airplane.h"
#include "menu.h"

int flightChoiceMenuOptions(P_AIRLINE p_airline) //Top level menu for flight choice.
{
	char userInput[MAX_USER_INPUT_LEN];
	int flightNum;
	bool validOptionChoice = false;

	fputs("~~~~~~~~~~~~~~~ FLIGHT MENU ~~~~~~~~~~~~~~~~~\n", stdout);
	fputs("Which flight would you like to query?\n", stdout);
	fputs("a) 102\n", stdout);
	fputs("b) 311\n", stdout);
	fputs("c) 444\n", stdout);
	fputs("d) 519\n", stdout);
	fputs("e) Quit\n", stdout);
	fputs("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n", stdout);
	fputs("Option: ", stdout);

	while (!validOptionChoice)
	{
		fgets(userInput, MAX_USER_INPUT_LEN, stdin);
		userInput[strcspn(userInput, "\n")] = 0;

		if (!strcmp("a", userInput)) 
		{
			flightNum = 102;
			validOptionChoice = true;
		}
		else if (!strcmp("b", userInput)) 
		{
			flightNum = 311;
			validOptionChoice = true;
		}
		else if (!strcmp("c", userInput)) 
		{
			flightNum = 444;
			validOptionChoice = true;
		}
		else if (!strcmp("d", userInput))
		{
			flightNum = 519;
			validOptionChoice = true;
		}
		else if (!strcmp("e", userInput))
		{
			if (!saveAirlineToDisk(p_airline, "datafile.txt")) // Save all data to disk before terminating.
				fprintf(stderr, "\nError saving to file.\n");
			exit(EXIT_SUCCESS);
		}
		else // Menus are great because you define valid input instead of excluding all invalid input (there is a difference!)
		{
			fputs("\nError reading menu option, please try again!\n\n", stdout);
		}
	}
	return flightNum;
}

void printMainMenuOptions(int flightNum) // Main menu options.
{
	fputs("~~~~~~~~~~~~~~~~~~~~ MENU ~~~~~~~~~~~~~~~~~~~\n", stdout);
	printf("\t\tFlight Number: %d\n\n", flightNum);
	fputs("To choose a function, enter its letter label:\n\n", stdout);
	fputs("a) Show number of empty seats\n", stdout);
	fputs("b) Show list of empty seats\n", stdout);
	fputs("c) Show alphabetical list of seats\n", stdout);
	fputs("d) Assign a customer to a seat assignment\n", stdout);
	fputs("e) Confirm a seat assignment.\n", stdout);
	fputs("f) Delete a seat assignment\n", stdout);
	fputs("g) Quit\n", stdout);
	fputs("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n", stdout);
	fputs("Option: ", stdout);
}

bool executeUserOptionChoice(P_AIRLINE p_airline, int flightNum) // This function reads the user's input and if it corresponds to one of the menu options it will execute the desired function.
{
	char user_input[MAX_USER_INPUT_LEN];

	while (true)
	{
		fgets(user_input, MAX_USER_INPUT_LEN, stdin);
		user_input[strcspn(user_input, "\n")] = 0;

		if (!strcmp("a", user_input)) // I wish switch cases worked more easily with strings...
		{
			int emptySeatCount = getEmptySeatCount(p_airline, flightNum);
			printf("There are %d seat(s) still available on flight %d\n\n", emptySeatCount, flightNum);
			return true;
		}
		else if (!strcmp("b", user_input)) // "Show list of empty seats"
		{
			listEmptySeats(p_airline, flightNum);
			return true;
		}
		else if (!strcmp("c", user_input)) // "Show alphabetical list of seats"
		{
			printf("\n");
			printSeatsInAlphabeticalOrder(p_airline, flightNum);
			printf("\n");
			return true;
		}
		else if (!strcmp("d", user_input)) // "Assign a customer to a seat assignment"
		{
			printf("\n");
			menuAddSeatAssignment(p_airline, flightNum);
			return true;
		}
		else if (!strcmp("e", user_input)) // "Confirm a seat assignment"
		{
			printf("\n");
			menuConfirmSeatAssignment(p_airline, flightNum);
			return true;
		}
		else if (!strcmp("f", user_input)) //"Delete a seat assignment"
		{
			printf("\n");
			if (getEmptySeatCount(p_airline, flightNum) != 12) // This statement prevents a user from being stuck in the deletion function with no available option.
				menuDeleteSeatAssignment(p_airline, flightNum);
			else
				fputs("\nThere are no current seat assignments\n\n", stdout);
			return true;
		}
		else if (!strcmp("g", user_input)) // Go back to top level menu.
		{
			return false;
		}
		else
		{
			fputs("\nError reading menu option, please try again!\n\n", stdout); 
		}
	}
}

void menuAddSeatAssignment(P_AIRLINE p_airline, int flightNum)
{
	fputs("Enter seat number would you like the new passenger to be assigned to (0 to return to menu): ", stdout);
	int seatNum;
	bool seatNumIsAvailable;
	char firstName[MAX_NAME_LEN];
	char lastName[MAX_NAME_LEN];

	do // Do While loop to reprompt the user if they chose a seat already taken or otherwise unavailable.
	{
		seatNumIsAvailable = true;
		scanf("%d", &seatNum);
		int c;
		while ((c = getchar()) != EOF && c != '\n'); // clear input stream
		if (seatNum == 0) //exit condition
		{
			printf("\n");
			return;
		}
		if (isSeatAvailable(p_airline, flightNum, seatNum) && (seatNum > 0) && (seatNum < getFlightCapacityFromAirline(p_airline))) // validate seat number chosen
		{
			// Grab the first name
			fputs("Please enter the passenger's first name (0 to return to menu): ", stdout);
			fgets(firstName, MAX_NAME_LEN, stdin);
			if (!strcmp(firstName, "0\n")) //exit condition
			{
				printf("\n");
				return;
			}
			firstName[0] = toupper(firstName[0]); // fancy it up
			firstName[strcspn(firstName, "\n")] = 0; 

			// Grab the last name
			fputs("Please enter the passenger's last name (0 to return to menu): ", stdout);
			fgets(lastName, MAX_NAME_LEN, stdin);
			if (!strcmp(firstName, "0\n")) //exit condition
			{
				printf("\n");
				return;
			}
			lastName[0] = toupper(lastName[0]); // fancy it up
			lastName[strcspn(lastName, "\n")] = 0; 

			// Now create the assignment from the ground up
			PASSENGER newPassenger = createPassenger(firstName, lastName);
			SEAT newSeat = createSeat(newPassenger, seatNum);
			addSeatAssignment(p_airline, flightNum, newSeat);
			printf("\nConfirmation Status:\n");
			printf("The following seat booking as been added to flight %d\n", flightNum);
			printSeatAssignment(p_airline, flightNum, seatNum);
		}
		else
		{
			printf("Seat %d is currently occupied or otherwise unavailable. Please pick another seat number: ", seatNum);
			seatNumIsAvailable = false;
		}
	} while (!seatNumIsAvailable);
}

void menuDeleteSeatAssignment(P_AIRLINE p_airline, int flightNum)
{
	fputs("Enter the seat number of the seat assignment you would like to remove (0 to return to menu): ", stdout);
	int seatNum;
	bool seatNumIsNotAvailable;

	do // Do While loop to reprompt the user if they chose a seat already taken or otherwise unavailable.
	{
		seatNumIsNotAvailable = true;
		scanf("%d", &seatNum);
		int c;
		while ((c = getchar()) != EOF && c != '\n'); // clear input stream
		if (seatNum == 0) // exit condition
		{
			printf("\n");
			return;
		}
		if (!isSeatAvailable(p_airline, flightNum, seatNum) && (seatNum > 0) && (seatNum < getFlightCapacity(p_airline))) // validate seat number chosen)
		{
			SEAT seatToDelete = getSeat(p_airline, flightNum, seatNum);
			removeSeat(p_airline, flightNum, seatToDelete); // tracks down the seat within the seat linked list, unlinks it, then frees it.
		}
		else
		{
			printf("Seat %d is currently not occupied or otherwise unavailable. Please pick another seat number: ", seatNum);
			seatNumIsNotAvailable = false;
		}
	} while (!seatNumIsNotAvailable);
}

void menuConfirmSeatAssignment(P_AIRLINE p_airline, int flightNum)
{
	fputs("Enter the seat number you would like to confirm an assignment for (0 to return to menu): ", stdout);
	int seatNum;
	bool seatNumIsNotAvailable;
	do // Do While loop to reprompt the user if they chose a seat already taken or otherwise unavailable.
	{
		seatNumIsNotAvailable = true;
		scanf("%d", &seatNum);
		int c;
		while ((c = getchar()) != EOF && c != '\n'); //clear input stream
		if (seatNum == 0) //exit condtion
		{
			printf("\n");
			return;
		}
		if (!isSeatAvailable(p_airline, flightNum, seatNum) && (seatNum > 0) && (seatNum < getFlightCapacity(p_airline))) // validate seat number chosen
		{
			printf("\nConfirming seat assignment:\n");
			printSeatAssignment(p_airline, flightNum, seatNum);
		}
		else
		{
			printf("Seat %d is currently not occupied or otherwise unavailable. Please pick another seat number: ", seatNum);
			seatNumIsNotAvailable = false;
		}
	} while (!seatNumIsNotAvailable);
}