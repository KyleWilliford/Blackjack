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
	explicit Player();		//Constructor for "player" instance with default wallet size (500)
	explicit Player(int);	//Constructor for "player" instance with parameterized waller size
	explicit Player(char);	//Constructor for "dealer" instance (no wallet instantiation)
	//explicit Player(std::vector<FACE> hand_dud, std::vector<std::string> names_dud){this->hand = hand_dud; this->names = names_dud;};	//UnitTestCardDisplay
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