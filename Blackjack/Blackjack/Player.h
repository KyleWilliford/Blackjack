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
#include "Hand.h"
#include <vector>
#include <string>

class Player{

public:
	explicit Player() : wallet(), hand(1, Hand()) { };		//Constructor for "player" instance with default wallet size (500)

	explicit Player(const int walletSize) : wallet(walletSize), hand(1, Hand()) { };	//Constructor with parameterized wallet size (player)

	explicit Player(const bool) : hand(1, Hand()) { };		//Constructor dealer - skip wallet initialization

	virtual ~Player(){ };	//dtor

	//Wallet methods
	const void placeBet(){wallet.bettingMenu();};	//Calls Wallet.bettingMenu method

	const void updatePurse(const int bet){ wallet.updatePurse(bet); };	//Updates the Wallet.purse value with the result of a win/loss/push

	const int getBet() const { return wallet.getBet(); };	//Return a copy of the bet amount stored in Wallet

	const void doubleBet() { wallet.doubleBet(); };	//Call the Wallet double bet method (double down)

	const int getPurse() const { return wallet.getPurse(); };	//Return a copy of the purse amount stored in Wallet

	//Hand manipulation methods
	const void hit(Deck& deck) { hand[0].hit(deck); };	//Hit on the initial hand of cards
	const void hit(const int handIndex, Deck& deck) { hand[handIndex].hit(deck); };	//Overloaded for hitting on a specific hand of cards

	const int checkForAces() const { return hand[0].checkForAces(); };	//Call an instance of hand to check for Aces
	const int checkForAces(const int handIndex) const { return hand[handIndex].checkForAces(); };	//Overloaded

	const void changeAce(const FACE aceVal, const int aceIndex) { return hand[0].changeAce(aceVal, aceIndex); };	//Call an instance of hand to change an Ace's value
	const void changeAce(const int handIndex, const FACE aceVal, const int aceIndex) { return hand[handIndex].changeAce(aceVal, aceIndex); };	//Overloaded

	const FACE displayCardVal(const int cardIndex) const { return hand[0].displayCardVal(cardIndex); };	//Return the value of the card at the indexed location in the hand vector
	const FACE displayCardVal(const int handIndex, const int cardIndex) const { return hand[handIndex].displayCardVal(cardIndex); };	//Overloaded

	const std::string displayCard(const int cardIndex) const { return hand[0].displayCard(cardIndex); };	//Return the name of the card at the indexed location in the names vector
	const std::string displayCard(const int handIndex, const int cardIndex) const { return hand[handIndex].displayCard(cardIndex); };	//Overloaded

	const int getHandSize() const { return hand[0].getHandSize(); };	//Return the size of the hand vector from this instance
	const int getHandSize(const int handIndex) const { return hand[handIndex].getHandSize(); };	//Overloaded

	const int getHandTotal() const { return hand[0].getHandTotal(); };		//Return a copy of the hand total value from this instance
	const int getHandTotal(const int handIndex) const { return hand[handIndex].getHandTotal(); };	//Overloaded

	const void resetHand(){ hand[0].resetHand(); };	//Reset the hand, names, and handTotal vectors, and variable, respectively
	const void resetHand(const int handIndex){ hand[handIndex].resetHand(); };	//Overloaded

private:
	//Private variables and containers
	Wallet wallet;
	std::vector<Hand> hand;

	//Prevent copying
	Player(const Player &);	//Copy constructor
	Player& operator=(const Player &);	//Copy assignment operator
};

#endif 