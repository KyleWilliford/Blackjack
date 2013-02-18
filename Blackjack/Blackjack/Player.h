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
	explicit Player() : wallet(), handTotal(0){ };		//Constructor for "player" instance with default wallet size (500)

	explicit Player(const int, const bool);	//Constructor for "player" instance with parameterized wallet size

	//explicit Player(std::vector<FACE> hand_dud, std::vector<std::string> names_dud){this->hand = hand_dud; this->names = names_dud;};	//UnitTestCardDisplay

	virtual ~Player(){};	//dtor

	//TEST
	void hit();

	const void hit(Deck&);

	const int checkForAces();

	const void changeAce(const FACE, const int);

	//Public interface function prototypes defined with inline implementations
	const int handSize() const { return hand.size(); };	//Return the size of this Player's hand (size of the hand vector)

	const FACE displayCardVal(const int index) const { return hand.at(index); };	//Return the value of the card at the indexed location in the hand vector

	const std::string displayCard(const int index) const { return names.at(index); };	//Return the name of the card at the indexed location in the names vector

	const void placeBet(){wallet.bettingMenu();};	//Calls Wallet.bettingMenu method

	const void updatePurse(const int bet){ wallet.updatePurse(bet); };	//Updates the Wallet.purse value with the result of a win/loss/push

	const int getBet() const { return wallet.getBet(); };	//Return a copy of the bet amount stored in Wallet

	const int getPurse() const { return wallet.getPurse(); };	//Return a copy of the purse amount stored in Wallet

	const int getHandSize() const { return hand.size(); };	//Return the size of the hand vector from this instance

	const int getHandTotal()const { int rtr = handTotal; return rtr; };	//Return a copy of the hand total value from this instance

	const void resetHand(){ hand.resize(0); names.resize(0); handTotal = 0; };	//Reset the hand, names, and handTotal vectors, and variable, respectively

private:
	//Variables
	Wallet wallet;
	std::vector<FACE> hand;
	std::vector<std::string> names;
	int handTotal;
};

#endif 