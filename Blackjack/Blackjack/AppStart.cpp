/*
	Kyle Williford
	Blackjack [WIP]
*/

#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "Game.h"

static const int x = 1024;	//window width
static const int y = 768;	//window height

static const int NumberOfDecks = 6;
static const int WalletSize = 30000;

static Game *game;

/*
	@optionsMenu
	Display a list of choices for the options menu.
*/
void optionsMenu()
{
	std::cout << "\n\nBLACKJACK!\n\nOptions Menu" << std::endl;
	std::cout << "1: View Credits" << std::endl;
	std::cout << "2: View Game Version Information" << std::endl;
	std::cout << "3: Return to Main Menu" << std::endl;
	std::cout << "Enter your choice: ";
}

/*
	@displayOptionss
	Parse the user's choice from the options menu.
*/
void displayOptions()
{
	bool valid = false;
	do{
		optionsMenu();
		std::string s;
		std::cin >> s;
		int choice = atoi(s.c_str());
		switch (choice){
		case 1:
			system("cls");
			std::cout << "\nThanks for playing!\nBlackjack\nby Kyle Williford";
			valid = false;
			break;
		case 2:
			system("cls");
			std::cout << "\nVersion: build 16 (alpha)";
			valid = false;
			break;
		case 3:
			system("cls");
			valid = true;
			break;
		default:
			//Invalid input - exit;
			valid = false;
			std::cout << "\nError - Invalid input. Try again.\n\n";
			break;
		}
	}while(!valid);
}

/*
	@instructionsMenu
	Display a list of choices for the instructions menu.
*/
void instructionsMenu()
{
	std::cout << "\n\nBLACKJACK!\n\nInstructions Menu" << std::endl;
	std::cout << "1: View Game Rules" << std::endl;
	std::cout << "2: View Gameplay Choices" << std::endl;
	std::cout << "3: Return to Main Menu" << std::endl;
	std::cout << "Enter your choice: ";
}

/*
	@displayInstructions
	Parse the user's choice from the instruction menu.
*/
void displayInstructions()
{
	bool valid = false;
	do{
		instructionsMenu();
		std::string s;
		std::cin >> s;
		int choice = atoi(s.c_str());
		switch (choice){
		case 1:
			system("cls");
			std::cout << "\nRULES:\n";
			std::cout << "General Concept - Draw cards to get as close as possible to 21 without going over. Card values are equal to " <<
				"\ntheir face value, with Jack, Queen, and King cards worth 10 each." <<
				"\n\nAce cards - Aces are worth 1 or 11, and their values can be flipped back and forth if you "<<
				"\nhave one or more in your hand, except when having an 11 would make you " << 
				"\ngo over 21, but having a 1 would not." <<
				"\n\nWhat is a blackjack? - A blackjack occurs when you or the dealer draw an ace plus any card valued at 10 within" << 
				"\nthe first two cards drawn. A blackjack pays 3:2." <<
				"\n\nDealer rules - The dealer will stand on any 17 (hard, or soft)." <<
				"\n\nWhat is a turn? - A turn is a complete cycle consisting of the player moving, followed by the dealer moving." <<
				"\nThe dealer's turn is after the player's." <<
				"\n\nWhat is a round? - A round consists of an entire game of blackjack from betting to" << 
				"\nfinal evaluation and payouts, and can consist of many turns." <<
				"\n\nHow big are your shoes? - The shoe of cards (called deck in places) consists of 6 full" <<
				"\ndecks of cards (52 x 6 = 312 cards). Cards are drawn from the end of the deck, after it is" <<
				"\nshuffled. The deck is rebuilt and reshuffled when the deck has 12 or fewer cards remaining.";
			valid = false;
			break;
		case 2:
			system("cls");
			std::cout << "\nGAMEPLAY CHOICES:\n";
			std::cout << "\nHit - Draw a card\n";
			std::cout << "\nStand - Stop drawing cards and finalize your hand. You cannot draw " <<
				"\nmore cards for a hand after standing.\n";

			std::cout << "\nDouble Down - Draw a card, and double your existing bet." <<
				"\nOnly available on your first turn. Not available after a split hand.\n";

			std::cout << "\nSplit - Split your hand, creating an additional hand of cards " <<
				"\nthat you can play during the current round." << 
				"\nYou can only split your hand when you have exactly two cards in your " <<
				"\ncurrent hand, and they must be identical cards " <<
				"\n(i.e. two Kings, or two 2's, etc.)." <<
				"\nCards are automatically drawn from the deck to bring each hand " <<
				"\nup to two cards, after the split." <<
				"\nYour bet is doubled to cover each additional hand, and each hand is " <<
				"\njudged on its own during win/lose evaluation condition checks." <<
				"\n\nExample split hand scenario: You have 1 hand of cards containing two Jacks." <<
				"\nYou choose to split the hand. You now have two hands, each with a Jack." <<
				"\nTwo cards are drawn automatically so you now have two hands of cards, " <<
				"\neach with a Jack, plus one additonal card from the deck in each hand for a total " <<
				"\nof four cards across both hands. " <<
				"\nIf in either of those hands, there is another Jack, such that you have another " << 
				"\ntwo Jacks in a single hand with no other cards in that hand, then you can " << 
				"\nsplit that hand, thus giving you three hands total." <<
				"\nYou can continue splitting hands so long as the previously described " <<
				"\nconditions for a split are met, and you have enough money in the purse to " <<
				"\ncover each additonal hand." <<
				"\nEach hand won pays 2:1\n";

			std::cout << "\nInsurance - You can buy insurance up to half of your bet for a round if" <<
				"\nthe dealer has an Ace upcard (shown card), OR you have a blackjack." <<
				"\nThis bet is separate from your primary wager, and can be won or lost independently." <<
				"\nInsurance pays 2:1 of the insured amount.";
			valid = false;
			break;
		case 3:
			system("cls");
			valid = true;
			break;
		default:
			//Invalid input - exit;
			valid = false;
			std::cout << "\nError - Invalid input. Try again.\n\n";
			break;
		}
	}while(!valid);
}

/*
	@mainMenu
	Presents a new game/instructions/exit choice menu to the user.
*/
void mainMenu() 
{
	std::cout << "\n\nBLACKJACK!\n" << std::endl;
	std::cout << "Main Menu" << std::endl;
	std::cout << "1: New Game" << std::endl;
	std::cout << "2: Instructions" << std::endl;
	std::cout << "3: Options" << std::endl;
	std::cout << "4: Exit" << std::endl;
	std::cout << "Enter your choice: ";
}

/*
	@mainMenuChoice
	Parse input from mainMenu() and call Game methods.
*/
void mainMenuChoice() 
{
	bool valid = false;
	do{
		mainMenu();
		std::string s;
		std::cin >> s;
		int choice = atoi(s.c_str());
		switch (choice){
		case 1:
			system("cls");
			delete game;
			game = NULL;
			game = new Game(NumberOfDecks, WalletSize);
			do{	//Loop until the user decides not to play again, or the user runs out of currency
				game->execRound();	//Execute one round of blackjack
				if(game->isPurseEmpty()){
					std::cout << "Out of money!\nStart a new game?";
				}
			}while(game->playAgain && !game->isPurseEmpty());
			valid = true;
			break;
		case 2:
			system("cls");
			displayInstructions();
			valid = false;
			break;
		case 3:
			system("cls");
			displayOptions();
			valid = false;
			break;
		case 4:
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
	Resize the game window, and allow it to be resized manually by the user (by edge dragging).
*/
void setWindow(const int x, const int y) 
{
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

/*
	@main
	Main execution thread/ program start.
*/
int main()
{
    setWindow(x, y);
	system("cls");
	do{
		mainMenuChoice();
		std::cout << "\n";
	}while(game->playAgain);

	return 0;
}