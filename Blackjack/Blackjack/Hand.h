/*
	Kyle Williford
	2/26/13
	Blackjack [WIP]
*/

#pragma once
#ifndef HAND_H
#define HAND_H

#include "Deck.h"
#include <vector>
#include <string>

class Hand{

public:
	explicit Hand() : hand(), names(), handTotal(0) { };

	explicit Hand(const FACE card, const std::string namedCard, const int total) : hand(1, card), names(1, namedCard), handTotal(total){ };	//For split hand construction

	virtual ~Hand(){ };	//dtor

	const void hit(Deck&);

	const int checkForAces() const;

	const void changeAce(const FACE, const int);

	const FACE displayCardVal(const int index) const { return hand.at(index); };	//Return the value of the card at the indexed location in the hand vector

	const std::string displayCard(const int index) const { return names.at(index); };	//Return the name of the card at the indexed location in the names vector

	const int getHandSize() const { return hand.size(); };	//Return the size of the hand vector from this instance

	const int getHandTotal()const { return handTotal; };	//Return a copy of the hand total value from this instance

	const void resetHand(){ hand.resize(0); names.resize(0); handTotal = 0; };	//Reset the hand, names, and handTotal vectors, and variable, respectively

private:
	//Private variables and containers
	std::vector<FACE> hand;
	std::vector<std::string> names;
	int handTotal;
};

#endif 