/*
	Kyle Williford
	Blackjack [WIP]
*/

#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Wallet.h"
#include "Deck.h"
#include "Hand.h"
#include <vector>
#include <string>

class Player{

public:
	//Ctors and Dtor
	explicit Player();
	explicit Player(const int);
	explicit Player(const bool);
	virtual ~Player();	//dtor

	//Wallet methods
	const void placeBet();	
	const void updatePurse(const int scale_amount);
	const int getBet() const;
	const void doubleBet();
	const int getPurse() const;

	//Hand manipulation methods
	const void hit(const int handIndex, Deck& deck);
	const int checkForAces(const int handIndex) const;
	const void changeAce(const int handIndex, const FACE aceVal, const int aceIndex);
	const FACE displayCardVal(const int handIndex, const int cardIndex) const;
	const std::string displayCardName(const int handIndex, const int cardIndex) const;
	const int getHandSize(const int handIndex) const;
	const int getHandTotal(const int handIndex) const;
	const void resetHand(const int handIndex);
	const void resetAllHands();
	const void addSplitHand(const int, Deck &);
	const int getNumberOfHands() const;
	const void setHandStandStatus(const int handIndex, const bool stand);
	const bool getHandStandStatus(const int handIndex) const;

private:
	//Private variables and containers
	Wallet wallet;
	std::vector<Hand> set_of_hands;

	//Prevent copying
	Player(const Player &);	//Copy constructor
	Player& operator=(const Player &);	//Copy assignment operator
};

#endif 