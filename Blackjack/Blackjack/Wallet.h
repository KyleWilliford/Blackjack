/*
	Kyle Williford
	2/6/13
	Blackjack [WIP]
*/

#pragma once
#ifndef WALLET_H
#define WALLET_H

class Wallet{

public:
	explicit Wallet() : purse(500), bet(0){ };	//default ctor

	explicit Wallet(const int amount) : purse(amount), bet(0){ };	//ctor

	virtual ~Wallet(){ };	//dtor

	const void bettingMenu();

	//Function prototypes with inline implementations
	const int getBet(){ int rtr = bet; return rtr; };		//Return a copy of this Wallet's current bet

	const int getPurse(){ int rtr = purse; return rtr; };	//Return a copy of the value of this Wallet's purse

	const void updatePurse(int bet){ purse += bet; };	//Update the purse with the bet amount

private:
	//Variables
	int purse, bet;
};

#endif 