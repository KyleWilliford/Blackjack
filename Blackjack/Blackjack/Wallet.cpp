/*
	Kyle Williford
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

/*
	@getBet
	Return this Wallet's current bet amount
*/
const int Wallet::getBet() const 
{ 
	return bet; 
}

/*
	@doubleBet
	Double the bet (double down)
*/
const void Wallet::doubleBet() { 
	updatePurse(-bet); bet *= 2; 
}

/*
	@getPurse
	Return the value of this Wallet's purse
*/
const int Wallet::getPurse() const { 
	return purse; 
}

/*
	@updatePurse
	Update the purse with the bet amount (addition only - subtraction with a negative integer obviously)
*/
const void Wallet::updatePurse(int bet) { 
	purse += bet; 
}