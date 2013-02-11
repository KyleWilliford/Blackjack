/*
	Kyle Williford
	2/6/13
	Blackjack [WIP]
*/

#pragma once
#ifndef DECK_H
#define DECK_H

#include "FACESUIT.h"
#include <vector>
#include <string>

class Deck{

public:
	Deck();
	Deck(int);
	virtual ~Deck();
	void shuffle();
	void build();
	FACE draw();
	std::string drawName();

private:
	int deckCount;
	int deckSize;
	std::vector<FACE> deck;			//A vector for holding card values
	std::vector<std::string> names;	//A vector for holding string face names for cards (matching indices to variable deck)
};

#endif