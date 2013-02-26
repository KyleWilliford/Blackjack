/*
	Kyle Williford
	2/6/13
	Blackjack [WIP]
*/

#include <iostream>
#include <string>
#include "Game.h"

static const int NumberOfDecks = 6;
static const int WalletSize = 30000;

static Game *game;

/*
	@mainMenu
	Presents a new game/exit menu to the user.
*/
void mainMenu(){
	std::cout << "\nBLACKJACK!\n" << std::endl;
	std::cout << "1: New Game" << std::endl;
	std::cout << "2: Exit" << std::endl;
	std::cout << "Enter your choice: ";
}

/*
	@mainMenuChoice
	Parse input from mainMenu() and call Game methods
*/
void mainMenuChoice(){
	bool valid = false;
	do{
		mainMenu();
		std::string input;
		std::cin >> input;
		int choice = atoi(input.c_str());
		switch (choice){
		case 1:
			delete game;
			game = NULL;
			game = new Game(NumberOfDecks, WalletSize);
			do{
				game->execRound();	//Execute one round of blackjack
				if(!game->purseNotEmpty()){
					std::cout << "\n\nOut of money!\nStart a new game?\n";
				}
			}while(game->playAgain && game->purseNotEmpty());
			valid = true;
			break;
		case 2:
			std::cout << "\nNow exiting.\n\n";
			delete game;
			game = NULL;
			exit(0);
		default:
			//Invalid input - exit;
			valid = false;
			std::cout << "\nError - Invalid input. Try again.\n\n";
			break;
		}
	}while(!valid);
}

int main(){
	do{
		mainMenuChoice();
		std::cout << "\n";
	}while(game->playAgain);

	return 0;
}