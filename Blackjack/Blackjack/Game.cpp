/*
	Kyle Williford
	2/6/13
	Blackjack [WIP]
*/

#include <iostream>
#include "Game.h"

bool Game::playAgain = false;

/*
	@gameMenu
	Controls a round of blackjack, dealer AI calls, card display calls, and player menu display, and input parse calls
*/
const void Game::gameMenu(){
	int turn_counter = 1;
	bool round_over = initRound();
	while(round_over == false){
		std::cout << "\n!---TURN " << turn_counter << " START---!\n";

		displayChips();

		gameChoice();

		if(player.getHandTotal() > 21){
			if(checkNumAces() != 0){
				for(int i = 0; i < player.getHandSize(); ++i){
					if(player.displayCardVal(i) == VERSA_ACE){
						player.changeAce(player.displayCardVal(i), i);
						if(!doubledDown){	//If doubled down, do not allow the user to draw more cards
							playerStands = false;
						}
						displayCards(false);
						std::cout << "\n\nWARNING: Your current hand is greater than 21, but at least one ace card with a value of 11 was detected.\nYour ace card with value of 11 has been reverted to 1.\nYou can also hit again even if you chose to stand with a hand greater than 21.";
						break;
					}
				}
			}
		}

		round_over = checkWinConditions(false, false);
		if(round_over){
			std::cout << "\n!---END OF TURN " << turn_counter << "---!\n";
			gameOver();
		}
		else{
			dealerAI();	//Dealer's turn
			std::cout << "\n!---END OF TURN " << turn_counter << "---!\n";
			round_over = checkWinConditions(false, false);	//Check if dealer has busted or tied player at 21
			if(round_over){
				std::cout << "\n!---END OF TURN " << turn_counter << "---!\n";
				gameOver();
			}
		}
		++turn_counter;
	}
}

/*
	@purseNotEmpty
	Returns true iff the player has money left to bet.
*/
const bool Game::purseNotEmpty() const {
	if(player.getPurse() == 0){
		return false;
	}
	return true;
}

/*
	@initRound
	Iinitialize a new round of cards using the current deck of cards.
*/
const bool Game::initRound(){
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
	int playerAceCount = player.checkForAces();
	int dealerAceCount = dealer.checkForAces();
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
	@placeBet
	Calls Player::placeBet, asking the user to ante up from their Wallet
*/
const void Game::placeBet(){
	std::cout << "\nBetting wallet: " << player.getPurse();
	player.placeBet();
}

/*
	@displayCards
	Display the cards in each player's hand.
	Dealer's second card is hidden until the dealer stands (or the end of the round).
*/
const void Game::displayCards(const bool displayDealerHand) const {
	//Display card names
	std::cout << "\n\nYour hand:";
	for(int i = 0; i < player.handSize(); ++i){
		std::cout << "\nCard " << (i+1) << ": " << player.displayCard(i);
	}
	if(displayDealerHand){
		std::cout << "\n\nDealer's hand:";
		for(int i = 0; i < dealer.handSize(); ++i){
			if(i == 1 && !dealerStands && !playerStands){ //Hide second drawn card
				std::cout << "\nCard " << (i+1) << ": face down (hidden).";
			}
			else if(i == 1 && !playerStands){ //Hide second drawn card
				std::cout << "\nCard " << (i+1) << ": face down (hidden).";
			}
			else if(i == 1 && !dealerStands){ //Hide second drawn card
				std::cout << "\nCard " << (i+1) << ": face down (hidden).";
			}
			else{
				std::cout << "\nCard " << (i+1) << ": " << dealer.displayCard(i);
			}
		}
	}
	std::cout << "\n";
}

/*
	@flipAces
	Allow the player to change the value of ace cards.
*/
const void Game::flipAces(){
	do{
		displayCards(false);	//Don't display the dealer's hand
		std::cout << "\nYou have one or more ace cards whose value can be modified (to 1 or 11). \n\nEnter the card number for an ace that you would like to flip (or -1 to cancel): ";
		std::string input;
		std::cin >> input;
		int choice = atoi(input.c_str());
		if(choice == -1){
			break;
		}
		else if(choice <= 0 || choice > player.getHandSize()){
			std::cout << "\nInvalid input.\n";
			continue;
		}
		else if(choice >= 1 && choice <= player.getHandSize()){
			int index = choice - 1;
			player.changeAce(player.displayCardVal(index), index);
		}
	}while(true);
}

/*
	@flipAllAces
	Flip the value of all of the parameter player's ace cards.
	Can be used for the dealer or player.
	Used when a player has a blackjack (Ace + 10 value card on first two card draws).
*/
const void Game::flipAllAces(Player &player){
	for(int i = 0; i < player.getHandSize(); ++i){
		player.changeAce(player.displayCardVal(i), i);
	}
}

/*
	@checkForAcess
	Check for the existence of aces within a player's hand.
*/
const int Game::checkNumAces(){
	return player.checkForAces();
}

/*
	@gameChoice
	Parse input from gameMenu for user game interactions.
*/
const void Game::gameChoice(){
	if(!playerStands){
		bool valid = false;
		int num_choices = 2;
		do{
			displayCards(true);

			//Display menu
			std::cout << "\n1. Hit\n";
			std::cout << "2. Stand\n";
			if(player.getHandSize() == 2 && (player.getBet() * 2 <= player.getPurse())){	//Check that the player can afford to double down, and is eligible to do so this round
				num_choices += 1;
				std::cout << "3. Double Down\n";
			}
			if(checkNumAces() != 0){
				num_choices += 1;
				std::cout << "4. Change Ace Values\n";
			}

			//Parse user input
			std::cout << "\nMake your choice: ";
			std::string input;
			std::cin >> input;
			int choice = atoi(input.c_str());

			if(choice > num_choices || (choice == 3 && player.getHandSize() != 2)){	//Prevent access to unlisted choices in specific conditions
				std::cout << "\nInvalid Input.";
				valid = false;
				continue;
			}

			switch(choice){
				case 1:	//HIT
					player.hit(deck);
					if(player.getHandTotal() == 21){	//Force player to stand on 21
						playerStands = true;
					}
					valid = true;
					break;
				case 2:	//STAND
					playerStands = true;
					valid = true;
					break;
				case 3:	//DOUBLE DOWN
					doubledDown = true;
					player.doubleBet();	//Double the bet
					player.hit(deck);	//Draw a single card
					playerStands = true;	//Prevent drawing more cards
					valid = true;
					break;
				case 4:	//FLIP ACES
					flipAces();
					valid = false;	//Don't immediately proceed to checkWinConditions with the new ace values
					break;
				default:
					std::cout << "\nInvalid Input.\n\n";
					valid = false;
					break;
			}
		}while(!valid);
	}
}

/*
	@dealerAI
	Process the dealer's turn.
	The dealer will decide to hit or stand based on the value of its hand.
	Stand on 17.
*/
const void Game::dealerAI(){
	if(!dealerStands){
		//Determine dealer's move
		int dealerTotal = dealer.getHandTotal();
		if(dealerTotal < 17){
			std::cout << "\nDealer draws a card.\n";
			dealer.hit(deck);
		}
		else if(dealerTotal >= 17){
			std::cout << "\nDealer stands.\n";
			dealerStands = true;
		}
	}
}

/*
	@displayEndOfRound
	Displays relevant game data for the end of the round.
	Round #
	Cards (with hidden card revealed)
	Player hand total
	Dealer hand total
*/
const void Game::displayEndOfRound(){
	int playerHand = player.getHandTotal();
	int dealerHand = dealer.getHandTotal();
	playerStands = true, dealerStands = true;
	displayChips();
	displayCards(true);
	std::cout << "\nYour hand total: " << playerHand << std::endl;
	std::cout << "Dealer hand total: " << dealerHand << std::endl;
}

/*
	@checkWinConditions
	Checks the player's and dealer's hands against all win, lose, and tie conditions.
	p_blackjack and d_blackjack are values representing whether or not a blackjack was achieved on the first two card draws of the round.
*/
const bool Game::checkWinConditions(const bool p_blackjack, const bool d_blackjack){
	if(p_blackjack && d_blackjack){
		flipAllAces(player);
		flipAllAces(dealer);
	}
	else if(p_blackjack && !d_blackjack){
		flipAllAces(player);
	}
	else if(!p_blackjack && d_blackjack){
		flipAllAces(dealer);
	}

	//Check for blackjack on first two card draws
	if(p_blackjack && d_blackjack){		//Player and dealer both have blackjack.
		displayEndOfRound();
		std::cout << "You and the dealer both drew blackjack. Push." << std::endl;
		player.updatePurse(player.getBet());
		return true;
	}
	else if(!p_blackjack && d_blackjack){	//Dealer has blackjack
		displayEndOfRound();
		std::cout << "Dealer got a Blackjack! You lost." << std::endl;
		player.updatePurse(0);
		return true;
	}
	else if(p_blackjack && !d_blackjack){	//Player has blackjack
		displayEndOfRound();
		std::cout << "You got a Blackjack! Payout = 3:2" << std::endl;
		player.updatePurse(player.getBet() + (player.getBet() * 3 / 2));
		return true;
	}

	//Other win and lose conditions
	if(player.getHandTotal() > 21 && dealer.getHandTotal() > 21){	//Player and dealer hands > 21
		displayEndOfRound();
		std::cout << "You and the dealer both bust. Push." << std::endl;
		player.updatePurse(player.getBet());
		return true;
	}
	else if(player.getHandTotal() > 21){				//Player hand > 21
		displayEndOfRound();
		std::cout << "You Bust." << std::endl;
		player.updatePurse(0);
		return true;
	}
	else if(dealer.getHandTotal() > 21){				//Dealer hand > 21
		displayEndOfRound();
		std::cout << "Dealer Bust. You won!" << std::endl;
		player.updatePurse(player.getBet() * 2);
		return true;
	}
	else if(player.getHandTotal() == 21 && dealer.getHandTotal() == 21){	//Player and dealer hands = 21
		displayEndOfRound();
		std::cout << "You and the dealer both have 21. Push." << std::endl;
		player.updatePurse(player.getBet());
		return true;
	}
	else if(playerStands && dealerStands){	//Final check for win, lose, tie after player and dealer have finished moving (both players "stand")
		if(player.getHandTotal() == dealer.getHandTotal()){	//Tie
			displayEndOfRound();
			std::cout << "You and the dealer have the same card values. Push." << std::endl;
			player.updatePurse(player.getBet());
			return true;
		}
		else if(player.getHandTotal() < dealer.getHandTotal()){	//Player loses
			displayEndOfRound();
			std::cout << "You lost!" << std::endl;
			player.updatePurse(0);
			return true;
		}
		else if(player.getHandTotal() > dealer.getHandTotal()){	//Player wins
			displayEndOfRound();
			std::cout << "You won!" << std::endl;
			player.updatePurse(player.getBet() * 2);
			return true;
		}
	}
	return false;	//The round is not over
}

/*
	@gameOver
	Prompt for a user response to continue playing. 
	Reset a round of blackjack, or exit.
*/
const bool Game::gameOver(){
	std::cout << "\n!---END OF ROUND " << round_counter << "---!\n";
	bool valid = false;
	do{
		std::cout << "\nPlay Again? (Y/N): ";
		std::string input;
		std::cin >> input;
		if(input.size() > 1){
			valid = false;
			std::cout << "\nInvalid Input.\n";
			continue;
		}
		switch(input[0]){
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
	return valid;
}

/*
	@cleanupRound
	Clean the player & dealer hands in anticipation of a new round.
*/
const void Game::cleanupRound(){
	playerStands = false, dealerStands = false, doubledDown = false;
	player.resetHand();
	dealer.resetHand();
	++round_counter;
}