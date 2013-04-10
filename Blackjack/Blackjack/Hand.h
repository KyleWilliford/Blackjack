/*
	Kyle Williford
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
	//Ctors and Dtor
	explicit Hand() : hand(), names(), handTotal(0), bet(0), stand(false) { };
	explicit Hand(const FACE card, const std::string namedCard, const int total, const int bet) : hand(1, card), names(1, namedCard), handTotal(total), bet(bet), stand(false) { };	//For split hand construction
	virtual ~Hand() { };	//dtor

	//Hand public interface function prototypes
	const int getBet() const;
	const void setBet(const int bet);
	const void hit(Deck&);
	const int checkForAces() const;
	const void changeAce(const FACE, const int);
	const FACE displayCardVal(const int index) const;
	const std::string displayCardName(const int index) const;
	const int getHandSize() const;
	const int getHandTotal() const;
	const void resetHand();
	const void split();
	const void setStand(const bool stand);
	const bool getStand() const;

private:
	//Private variables and containers
	std::vector<FACE> hand;
	std::vector<std::string> names;
	int handTotal, bet;
	bool stand;
};

#endif 