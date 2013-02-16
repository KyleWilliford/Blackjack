/*
	Kyle Williford
	2/6/13
	Blackjack [WIP]
*/

#include <iostream>
#include <string>
#include "Wallet.h"

/*
	@bettingMenu
	Present a menu for the player to ante up.
*/
const void Wallet::bettingMenu(){
	bool valid = true;
	do{
		std::cout << "\nBet how much? (positive integers only): ";
		std::string input;
		std::cin >> input;
		bet = atoi(input.c_str());
		if (bet <= 0 || bet > purse){
			std::cout << "\nInvalid input.\n";
			valid = false;
		}
		else{
			valid = true;
			purse -= bet;
		}
	}while(!valid);
}