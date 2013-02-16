/*
	Kyle Williford
	2/6/13
	Blackjack [WIP]
*/

#include <iostream>
#include <string>
#include "Game.h"

#define NUMBER_OF_DECKS 6
#define WALLET_SIZE 30000

Game *game;

/*
	@mainMenuChoice
	Parse input from mainMenu() and call Game methods
*/
void mainMenuChoice(){
	bool round_over = false;
	std::string input;
	std::cin >> input;
	int choice = atoi(input.c_str());
	switch (choice){
	case 1:
		delete game;
		game = NULL;
		game = new Game(NUMBER_OF_DECKS, WALLET_SIZE);
		do{
			game->gameMenu();
			if(!game->purseNotEmpty()){
				std::cout << "\n\nOut of money!\nStart a new game?\n";
			}
		}while(game->playAgain && game->purseNotEmpty());
		break;
	case 2:
		std::cout << "\nNow exiting.\n\n";
		delete game;
		game = NULL;
		exit(0);
	default:
		//Invalid input - exit;
		std::cout << "\nError - Invalid input. Now exiting.\n\n";
		delete game;
		game = NULL;
		exit(0);
	}
}

/*
	@mainMenu
	Presents a new game/exit menu to the user.
*/
void mainMenu(){
	std::cout << "\nBLACKJACK!\n" << std::endl;
	std::cout << "1. New Game" << std::endl;
	std::cout << "2. Exit" << std::endl;
	std::cout << "Enter your choice: ";
	mainMenuChoice();
}

int main(){
	do{
		mainMenu();
		std::cout << "\n";
	}while(game->playAgain);

	return 0;
}