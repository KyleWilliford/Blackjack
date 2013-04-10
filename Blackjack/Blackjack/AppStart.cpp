/*
	Kyle Williford
	Blackjack [WIP]
*/

#include <windows.h>
#include <iostream>
#include <string>
#include "Game.h"


const int x = 1024;	//window width
const int y = 768;	//window height

static const int NumberOfDecks = 6;
static const int WalletSize = 30000;

static Game *game;

void instructionsMenu() {
	std::cout << "\nInstructions Menu" << std::endl;
	std::cout << "1: View Game Rules" << std::endl;
	std::cout << "2: View Gameplay Choices" << std::endl;
	std::cout << "3: Return to Main Menu" << std::endl;
	std::cout << "Enter your choice: ";
}

/*
	@Instructions
	Print instructions to the user
*/
void displayInstructions() {
	bool valid = false;
	do{
		instructionsMenu();
		std::string input;
		std::cin >> input;
		int choice = atoi(input.c_str());
		switch (choice){
		case 1:
			std::cout << "\nRULES:\n";
			std::cout << "Draw cards to get as close to 21 without going over. Card values are equal to " <<
				"\ntheir face value, with Jack, Queen, and King cards worth 10 each." <<
				"\n\nAces are worth 1 or 11, and their values can be flipped back and forth if you "<<
				"\nhave one or more in your hand, except when having an 11 would make you " << 
				"\ngo over 21, but having a 1 would not.";
			valid = true;
			break;
		case 2:
			std::cout << "\nGAMEPLAY CHOICES:\n";
			std::cout << "Hit - Draw a card\n";
			std::cout << "Stand - Stop drawing cards and finalize your hand. You cannot draw " <<
				"\nmore cards for a hand after standing.\n";
			std::cout << "Double Down - Draw a card, and double your existing bet." <<
				"\nOnly available on your first turn. Not available after a split hand.\n";
			std::cout << "Split - Split your hand, creating an additional hand of cards " <<
				"\nthat you can play during the current round." << 
				"\n\nYou can only split your hand when you have exactly two cards in your " <<
				"\ncurrent hand, and they must be identical cards " <<
				"\n(i.e. two Kings, or two 2's, etc.)." <<
				"\n\nCards are automatically drawn from the deck to bring each hand " <<
				"\nup to two cards, after the split." <<
				"\n\nYour bet is doubled to cover each additional hand, and each hand is " <<
				"\njudged on its own during win/lose evaluation condition checks." <<
				"\n\nExample scenario: You have 1 hand of cards containing two Jacks." <<
				"\nYou choose to split the hand. You now have two hands, each with a Jack." <<
				"\nTwo cards are drawn automatically so you now have two hands of cards, " <<
				"\neach with a Jack, plus one additonal card from the deck in each hand for a total " <<
				"\nof four cards across both hands. " <<
				"\n\nIf in either of those hands, there is another Jack, such that you have another " << 
				"\ntwo Jacks in a single hand with no other cards in that hand, then you can " << 
				"\nsplit that hand, thus giving you three hands total." <<
				"\n\nYou can continue splitting hands so long as the previously described " <<
				"\nconditions for a split are met, and you have enough money in the purse to " <<
				"\ncover each additonal hand.";
			valid = true;
			break;
		case 3:
			std::cout << "\nReturning to main menu.\n\n";
			valid = true;
			break;
		default:
			//Invalid input - exit;
			valid = false;
			std::cout << "\nError - Invalid input. Try again.\n\n";
			break;
		}
	}while(!valid);
	std::cout << std::endl;
}

/*
	@mainMenu
	Presents a new game/exit menu to the user.
*/
void mainMenu() {
	std::cout << "\nBLACKJACK!\n" << std::endl;
	std::cout << "Main Menu" << std::endl;
	std::cout << "1: New Game" << std::endl;
	std::cout << "2: Instructions" << std::endl;
	std::cout << "3: Exit" << std::endl;
	std::cout << "Enter your choice: ";
}

/*
	@mainMenuChoice
	Parse input from mainMenu() and call Game methods
*/
void mainMenuChoice() {
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
			displayInstructions();
			valid = false;
			break;
		case 3:
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

/*
	@setWindow
	Resize the game window
*/
void setWindow(const int x, const int y) {
	_COORD coord;
    coord.X = x;
    coord.Y = y;

    _SMALL_RECT rect;
    rect.Top = 0;
    rect.Left = 0;
    rect.Bottom = y - 1;

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleScreenBufferSize(handle, coord);
    SetConsoleWindowInfo(handle, TRUE, &rect);
	MoveWindow(GetConsoleWindow(), 0, 0, x, y, TRUE);
}

int main() {
    setWindow(x, y);
	do{
		mainMenuChoice();
		std::cout << "\n";
	}while(game->playAgain);

	return 0;
}