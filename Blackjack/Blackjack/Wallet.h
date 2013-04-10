/*
	Kyle Williford
	Blackjack [WIP]
*/

#pragma once
#ifndef WALLET_H
#define WALLET_H

class Wallet{

public:
	//Ctors and Dtor
	explicit Wallet() : purse(500), bet(0){ };	//default ctor
	explicit Wallet(const int amount) : purse(amount), bet(0){ };	//ctor
	virtual ~Wallet(){ };	//dtor

	const void bettingMenu();
	const int getBet() const;
	const void doubleBet();
	const int getPurse() const;
	const void updatePurse(int);

private:
	//Variables
	int purse, bet;

	//Prevent copying
	Wallet(const Wallet &);	//Copy constructor
	Wallet& operator=(const Wallet &);	//Copy assignment constructor
};

#endif 