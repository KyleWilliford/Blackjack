/*
	Kyle Williford
	Blackjack [WIP]
*/

#pragma once
#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Deck.h"

class Game{

public:
	//Ctors and Dtor
	explicit Game() : dealerStands(false), dealerBusted(false), doubledDown(false), splitHand(false), player(), dealer(true), deck(), round_counter(1), current_hand(0) { };	//default ctor
	explicit Game(const int deckCount, const int walletSize) : dealerStands(false), dealerBusted(false), doubledDown(false), splitHand(false), player(walletSize), dealer(true), deck(deckCount), round_counter(1), current_hand(0) { };	//ctor
	virtual ~Game(){ };	//dtor

	//Public interface function prototypes
	const void execRound();
	const bool purseNotEmpty() const;

	//Public static variables
	static bool playAgain;

private:
	//Game private function prototypes
	const void displayChips() const;
	const bool initRound();
	const void placeBet();
	const void displayCards(const bool) const;
	const void flipAces();
	const void flipAllAces(Player&);
	const void revertAces();
	const int checkNumAces() const;
	const void gameChoice();
	const void dealerAI();
	const void displayEndOfRound();
	const bool checkWinConditions(const bool, const bool);
	const bool gameOver();
	const void cleanupRound();
	const void setPlayerStands(const bool);
	const bool getPlayerStands() const;
	
	//Variables
	bool dealerStands, dealerBusted, doubledDown, splitHand;
	Player player, dealer;
	Deck deck;
	int round_counter, current_hand;

	//Prevent copying
	Game(const Game &);	//Copy constructor
	Game& operator= (const Game &);	//Copy assignment constructor
};

#endif 