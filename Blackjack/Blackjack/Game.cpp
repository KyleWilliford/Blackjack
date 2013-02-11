/*
	Kyle Williford
	2/6/13
	Blackjack [WIP]
*/

#include <iostream>
#include "Game.h"

Game::Game() : playerStands(false), dealerStands(false), playAgain(true), player(), dealer('y'), deck(), round_counter(1){
}

Game::Game(int deckCount) : playerStands(false), dealerStands(false), playAgain(true), player(), dealer('y'), deck(deckCount), round_counter(1){
}

Game::Game(int deckCount, int walletSize) : playerStands(false), dealerStands(false), playAgain(true), player(walletSize), dealer('y'), deck(deckCount), round_counter(1){
}

Game::~Game(){
}

/*
	@initRound
	Iinitialize a new round of cards using the current deck of cards.
*/
bool Game::initRound(){
	//Draw two cards for the player and dealer
	placeBet();
	for(int i = 0; i < 2; ++i){
		player.hit(deck);
		dealer.hit(deck);
	}

	//Display round #
	std::cout << "\n\n!---ROUND " << round_counter << " START---!\n";

	//Check if cards drawn form a blackjack (21 = Ace + face card or ten card)
	bool blackjack = false;
	int playerAceCount = player.checkAce();
	int dealerAceCount = dealer.checkAce();
	if(playerAceCount == 1 && dealerAceCount == 1 && player.getHandTotal() == 11 && dealer.getHandTotal() == 11){
		blackjack = checkWinConditions(true, true);
	}
	else if(playerAceCount == 1 && player.getHandTotal() == 11){
		blackjack = checkWinConditions(true, false);
	}
	else if(dealerAceCount == 1 && dealer.getHandTotal() == 11){
		blackjack = checkWinConditions(false, true);
	}

	if(blackjack){
		return gameOver();
	}
	return false;
}

/*
	@displayCards
	Display the cards in each player's hand.
	Dealer's second card is hidden until the dealer stands (or the end of the round).
*/
void Game::displayCards(){
	//Display card names
	std::cout << "\n\nYour hand:";
	for(int i = 0; i < player.handSize(); ++i){
		std::cout << "\nCard " << (i+1) << ": " << player.displayCard(i);
	}
	std::cout << "\n\nDealer's hand:";
	for(int i = 0; i < dealer.handSize(); ++i){
		if(i == 1 && !dealerStands && !playerStands){ //Hide second drawn card
			std::cout << "\nCard " << (i+1) << ": face down (hidden).";
		}
		else{
			std::cout << "\nCard " << (i+1) << ": " << dealer.displayCard(i);
		}
	}
	std::cout << "\n";
}

/*
	@flipAces
	[WIP]
*/
void Game::flipAces(){
	int num_aces = checkAces();
	if(num_aces != 0){
		displayCards();
		std::cout << "\nYou have one or more ace cards whose value can be modified (to 1 or 11).\nEnter the card number for an ace that you would like to flip (or 0 to cancel): ";
		int choice;
		std::cin >> choice;
		if(choice <= player.getHandSize() && choice >= 1){
			player.changeAce(player.displayCardVal(choice-1), 1);
		}
	}
}

/*
	@gameMenu
	Controls a round of blackjack, dealer AI calls, card display calls, and player menu display, and input parse calls
*/
void Game::gameMenu(){
	int turn_counter = 1;
	bool round_over = initRound();
	while(round_over == false){
		std::cout << "\n\n!---TURN " << turn_counter << " START---!\n\n";
		std::cout << "\nWallet: " << player.getPurse();
		std::cout << "\nBet amount: " << player.getBet();
		displayCards();

		//flipAces(); //Untested feature to switch ace card values between 1 and 11

		//Display menu
		if(playerStands == false){
			std::cout << "\n1. Hit" << std::endl;
			std::cout << "2. Stand\n" << std::endl;
			std::cout << "Make your choice: ";
			gameChoice();
		}

		round_over = checkWinConditions(false, false);
		if(round_over){
			gameOver();
		}
		else{
			dealerAI();	//Dealer's turn
			round_over = checkWinConditions(false, false);	//Check if dealer has busted or tied player at 21
			if(round_over){
				gameOver();
			}
		}
		++turn_counter;
	}
}

/*
	@placeBet
	Calls Player::placeBet, asking the user to ante up from their Wallet
*/
void Game::placeBet(){
	std::cout << "\nBetting wallet: " << player.getPurse();
	player.placeBet();
}

/*
	@hasMoneyLeft
	Returns true iff the player has money left to bet.
*/
bool Game::purseNotEmpty(){
	if(player.getPurse() == 0){
		return false;
	}
	return true;
}

/*
	@checkAces
	Check for the existence of aces within a player's hand.
*/
int Game::checkAces(){
	return player.checkAce();
}

/*
	@gameChoice
	Parse input from gameMenu for user game interactions.
*/
void Game::gameChoice(){
	bool valid = false;
	do{
		std::string input;
		std::cin >> input;
		int choice = atoi(input.c_str());
		std::cout << "\n";
		switch(choice){
			case 1:
				player.hit(deck);
				valid = true;
				break;
			case 2:
				playerStands = true;
				valid = true;
				break;
			default:
				valid = false;
				break;
		}
		if(!valid){
			std::cout << "\n\nInvalid Input.\nMake your choice: ";
		}
	}while(!valid);
}

/*
	@dealerAI
	Process the dealer's turn.
	The dealer will decide to hit or stand based on the value of its hand.
	Stand on 17.
*/
void Game::dealerAI(){
	if(!dealerStands){
		//Determine dealer's move
		int dealerTotal = dealer.getHandTotal();
		if(dealerTotal < 17){
			std::cout << "\nDealer draws a card." << std::endl;
			dealer.hit(deck);
		}
		else if(dealerTotal >= 17){
			std::cout << "\nDealer stands." << std::endl;
			dealerStands = true;
		}
	}
}

/*
	@displayEndOfRound
	Displays relevant UI data for the end of the round.
	Round #
	Cards (with hidden card revealed)
	Player hand total
	Dealer hand total
*/
void Game::displayEndOfRound(const bool *p_blackjack, const bool *d_blackjack, const int *playerHand, const int *dealerHand){
	std::cout << "\n!---END OF ROUND " << round_counter << "---!\n";
	playerStands, dealerStands = true;
	displayCards();
	std::cout << "\nYour hand total: " << *playerHand << std::endl;
	std::cout << "Dealer hand total: " << *dealerHand << std::endl;
}

/*
	@checkWinConditions
	Checks the player's and dealer's hands against all win, lose, and tie conditions.
	p_blackjack and d_blackjack are values representing whether or not a blackjack was achieve on the first two card draws of the round.
*/
bool Game::checkWinConditions(const bool p_blackjack, const bool d_blackjack){
	int playerHand = player.getHandTotal();
	int dealerHand = dealer.getHandTotal();
	if(p_blackjack){
		playerHand += 10;	//+10 is temporary until I finish the flip aces feature
	}
	else if(d_blackjack){
		dealerHand += 10;
	}
	else if(p_blackjack && d_blackjack){
		playerHand, dealerHand += 10;
	}

	//Check for blackjack on first two card draws
	if(p_blackjack && d_blackjack){		//Player and dealer both have blackjack.
		displayEndOfRound(&p_blackjack, &d_blackjack, &playerHand, &dealerHand);
		std::cout << "You and the dealer both drew blackjack. Push." << std::endl;
		player.updatePurse(player.getBet());
		return true;
	}
	else if(!p_blackjack && d_blackjack){	//Dealer has blackjack
		displayEndOfRound(&p_blackjack, &d_blackjack, &playerHand, &dealerHand);
		std::cout << "Dealer got a Blackjack! You lost." << std::endl;
		player.updatePurse(0);
		return true;
	}
	else if(p_blackjack && !d_blackjack){	//Player has blackjack
		displayEndOfRound(&p_blackjack, &d_blackjack, &playerHand, &dealerHand);
		std::cout << "You got a Blackjack! Payout = 3:2" << std::endl;
		player.updatePurse(player.getBet() + (player.getBet() * 3 / 2));
		return true;
	}

	//Other win and lose conditions
	if(playerHand > 21 && dealerHand > 21){	//Player and dealer hands > 21
		displayEndOfRound(&p_blackjack, &d_blackjack, &playerHand, &dealerHand);
		std::cout << "You and the dealer both bust. Push." << std::endl;
		player.updatePurse(player.getBet());
		return true;
	}
	else if(playerHand > 21){				//Player hand > 21
		displayEndOfRound(&p_blackjack, &d_blackjack, &playerHand, &dealerHand);
		std::cout << "You Bust." << std::endl;
		player.updatePurse(0);
		return true;
	}
	else if(dealerHand > 21){				//Dealer hand > 21
		displayEndOfRound(&p_blackjack, &d_blackjack, &playerHand, &dealerHand);
		std::cout << "Dealer Bust. You won!" << std::endl;
		player.updatePurse(player.getBet() * 2);
		return true;
	}
	else if(playerHand == 21 && dealerHand == 21){	//Player and dealer hands = 21
		displayEndOfRound(&p_blackjack, &d_blackjack, &playerHand, &dealerHand);
		std::cout << "You and the dealer both have 21. Push." << std::endl;
		player.updatePurse(player.getBet());
		return true;
	}
	else if(playerStands && dealerStands){	//Final check for win, lose, tie after player and dealer have finished moving (both player "stand")
		if(playerHand == dealerHand){	//Tie
			displayEndOfRound(&p_blackjack, &d_blackjack, &playerHand, &dealerHand);
			std::cout << "You and the dealer have the same card values. Push." << std::endl;
			player.updatePurse(player.getBet());
			return true;
		}
		else if(playerHand < dealerHand){	//Player loses
			displayEndOfRound(&p_blackjack, &d_blackjack, &playerHand, &dealerHand);
			std::cout << "You lost!" << std::endl;
			player.updatePurse(0);
			return true;
		}
		else if(playerHand > dealerHand){	//Player wins
			displayEndOfRound(&p_blackjack, &d_blackjack, &playerHand, &dealerHand);
			std::cout << "You won!" << std::endl;
			player.updatePurse(player.getBet() * 2);
			return true;
		}
	}
	return false;
}

/*
	@gameOver
	Prompt for a user response to continue playing. 
	Reset a round of blackjack, or exit.
*/
bool Game::gameOver(){
	bool valid = false;
	do{
		std::cout << "\nPlay Again? (Y/N): ";
		char choice;
		std::cin >> choice;
		switch(choice){
		case 'y':
			valid = true;
			playAgain = true;
			cleanupRound();
			return true;
		case 'Y':
			valid = true;
			playAgain = true;
			cleanupRound();
			return true;
		case 'n':
			std::cout << "\nNow exiting.\n\n";
			exit(0);
		case 'N':
			std::cout << "\nNow exiting.\n\n";
			exit(0);
		default:
			valid = false;
			std::cout << "\nInvalid Input.\n";
			break;
		}
	}while(!valid);
}

/*
	@cleanupRound
	Clean the player & dealer hands in anticipation of a new round.
	Calls initRound to initialize a new round of play.
*/
void Game::cleanupRound(){
	playerStands = false;
	dealerStands = false;
	player.resetHand();
	dealer.resetHand();
	++round_counter;
}