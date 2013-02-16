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
	explicit Game();
	explicit Game(int);
	explicit Game(int, int);
	//explicit Game(Player p, Player d){this->player = p; this->dealer = d; playerStands = false; dealerStands = true; displayCards();};	//UnitTestCardDisplay
	virtual ~Game();
	void gameMenu();
	bool gameOver();
	void placeBet();
	bool purseNotEmpty();

	bool playerStands, dealerStands, playAgain;

private:
	bool initRound();
	void displayCards();
	void flipAces();
	int checkAces();
	void gameChoice();
	void dealerAI();
	void displayEndOfRound(const bool *, const bool *, const int *, const int *);
	bool checkWinConditions(bool, bool);
	void cleanupRound();
	
	int round_counter;
	Player player, dealer;
	Deck deck;
};

#endif 