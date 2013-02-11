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
	Wallet();
	Wallet(int);
	virtual ~Wallet();
	void bettingMenu();
	void ante();
	int getBet(){int rtr = bet; return rtr;};
	int getPurse(){int rtr = purse; return rtr;};
	void updatePurse(int bet){purse += bet;};

private:
	int purse, bet;

};

#endif 