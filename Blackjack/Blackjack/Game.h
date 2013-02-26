/*
	Kyle Williford
	2/6/13
	Blackjack [WIP]
*/

#pragma once
#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Deck.h"

class Game{

public:
	explicit Game() : playerStands(false), dealerStands(false), doubledDown(false), player(), dealer(true), deck(), round_counter(1){ };	//default ctor

	explicit Game(const int deckCount, const int walletSize) : playerStands(false), dealerStands(false), doubledDown(false), player(walletSize), dealer(true), deck(deckCount), round_counter(1){ };	//ctor

	virtual ~Game(){ };	//dtor

	//Public interface function prototypes
	const void execRound();

	const bool purseNotEmpty() const;

	//Public static variable
	static bool playAgain;

private:
	const void displayChips() const { 
		std::cout << "\nWallet: " << player.getPurse(); 
		std::cout << "\nBet amount: " << player.getBet(); 
	};

	//Function prototypes
	const bool initRound();

	const void placeBet();

	const void displayCards(const bool) const;

	const void flipAces();

	const void flipAllAces(Player&);

	const void revertAces();

	const int checkNumAces();

	const void gameChoice();

	const void dealerAI();

	const void displayEndOfRound();
	
	const bool checkWinConditions(const bool, const bool);

	const bool gameOver();

	const void cleanupRound();
	
	//Variables
	bool playerStands, dealerStands, doubledDown;
	Player player, dealer;
	Deck deck;
	int round_counter;

	//Prevent copying
	Game(const Game &);	//Copy constructor
	Game& operator= (const Game &);	//Copy assignment constructor
};

#endif 