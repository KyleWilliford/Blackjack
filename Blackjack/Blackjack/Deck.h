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
	explicit Deck() : deckCount(1), deckSize(52), deck(), names() { build(); shuffle(); };	//Build a Deck of 52 cards, and shuffle it

	explicit Deck(const int deckCount) : deckCount(deckCount), deckSize(deckCount * 52), deck(), names() { build(); shuffle(); };	//Build a deck of 52 * deckCount cards, and shuffle it

	virtual ~Deck(){ };	//dtor

	const void shuffle();

	const void build();

	const FACE draw();

	const std::string drawName();

private:
	int deckCount;
	int deckSize;
	std::vector<FACE> deck;			//A vector for holding card values
	std::vector<std::string> names;	//A vector for holding string face names for cards (matching indices to vector "deck")
	static const double ShuffleTime;

	//Prevent copying
	Deck(const Deck &);	//Copy constructor

	Deck & operator=(const Deck &);	//Copy assignment constructor
};

#endif