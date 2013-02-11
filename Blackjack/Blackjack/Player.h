/*
	Kyle Williford
	2/6/13
	Blackjack [WIP]
*/

#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Wallet.h"
#include "Deck.h"
#include <vector>
#include <string>

class Player{

public:
	Player();
	Player(int);
	Player(char);	//Constructor for dealer instance (no wallet instantiation)
	virtual ~Player();
	void hit(Deck&);
	int handSize();
	FACE displayCardVal(int);
	std::string displayCard(int);
	int getHandTotal();
	int checkAce();
	void changeAce(FACE, int);
	int getHandSize();
	void placeBet(){wallet.bettingMenu();};
	void updatePurse(int);
	int getBet(){return wallet.getBet();};
	int getPurse(){return wallet.getPurse();};
	void resetHand();

private:
	Wallet wallet;
	std::vector<FACE> hand;
	std::vector<std::string> names;
	int handTotal;
};

#endif 