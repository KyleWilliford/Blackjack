/*
	Kyle Williford
	Blackjack [WIP]
*/

#include <iostream>
#include "Game.h"
#include "math.h"

bool Game::playAgain = false;

/*
	@execRound
	Controls a round of blackjack, dealer AI calls, card display calls, and player menu display, and input parse calls
*/
const void Game::execRound(){
	bool round_over = initRound();
	int turn_counter = 1;
	while(round_over == false){
		std::cout << "\n!---TURN " << turn_counter << " START---!\n";

		do{
			//Present and process user menu choices
			gameChoice();

			//Check that changing an Ace's values has not put the player over 21; auto-correct if necessary
			revertAces();
			
			round_over = checkWinConditions(false, false);
			if(round_over && !splitHand){
				std::cout << "\n!---END OF TURN " << turn_counter << "---!\n";
				gameOver();
			}

			++current_hand;
		}while(current_hand < player.getNumberOfHands());
		current_hand = 0;

		if(!round_over){
			dealerAI();	//Dealer's turn
		}
		
		//Check that all conditions (i.e. all hands are set to stand) are right to end the game
		bool all_hands_stand = true;
		for(int i = 0; i < player.getNumberOfHands(); ++i){
			if(player.getHandStandStatus(i) == false){
				all_hands_stand = false;
				break;
			}
		}
		if(!dealerStands){
			all_hands_stand = false;
		}

		if(round_over && all_hands_stand){
			std::cout << "\n!---END OF TURN " << turn_counter << "---!\n";
			gameOver();
		}
		else{
			std::cout << "\n!---END OF TURN " << turn_counter << "---!\n";
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
	@displayChips
	Display the bet amount for each of the player's hands of cards
*/
const void Game::displayChips() const { 
	std::cout << "\nRemaining wallet: " << player.getPurse();
	if(player.getNumberOfHands() == 1){
		std::cout << "\nBet amount: " << player.getBet(); 
	}
	else{
		for(int i = current_hand; i < player.getNumberOfHands(); ++i){
			std::cout << "\nBet amount for hand # " << (i + 1) << ": " << player.getBet(); 
		}
	}
}

/*
	@initRound
	Iinitialize a new round of cards using the current deck of cards.
*/
const bool Game::initRound() {
	//Draw two cards for the player and dealer
	placeBet();
	for(int i = 0; i < 2; ++i){
		player.hit(current_hand, deck);
		dealer.hit(0, deck);
	}

	//Display round #
	std::cout << "\n\n!---ROUND " << round_counter << " START---!\n";

	//Check if cards drawn form a blackjack (21 = Ace + face card or ten card)
	bool blackjack = false;
	int playerAceCount = player.checkForAces(current_hand);
	int dealerAceCount = dealer.checkForAces(0);
	if(playerAceCount == 1 && dealerAceCount == 1 && player.getHandTotal(current_hand) == 11 && dealer.getHandTotal(0) == 11){
		blackjack = checkWinConditions(true, true);
	}
	else if(playerAceCount == 1 && player.getHandTotal(current_hand) == 11){
		blackjack = checkWinConditions(true, false);
	}
	else if(dealerAceCount == 1 && dealer.getHandTotal(0) == 11){
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
	//Display wallet
	displayChips();

	//Display card names
	std::cout << "\n\nYOUR CARDS\n";
	int local_hand_counter = 0;
	do{
		if(player.getNumberOfHands() != 1){
			std::cout << "Hand #" << local_hand_counter + 1 << ":\n";
		}
		for(int i = 0; i < player.getHandSize(local_hand_counter); ++i){
			std::cout << "Card " << (i+1) << ": " << player.displayCardName(local_hand_counter, i) << std::endl;
		}
		++local_hand_counter;
	}while(local_hand_counter < player.getNumberOfHands());
	if(displayDealerHand){
		bool player_stands_all = true;
		for(int i = 0; i < player.getNumberOfHands(); ++i){
			if(player.getHandStandStatus(i) == false){
				player_stands_all = false;
				break;
			}
		}
		std::cout << "\n\nDEALER'S CARDS";
		for(int i = 0; i < dealer.getHandSize(0); ++i){
			if(i == 1 && ((!player_stands_all) || (!dealerStands))){ //Hide second drawn card
				std::cout << "\nCard " << (i+1) << ": face down (hidden).";
			}
			else{
				std::cout << "\nCard " << (i+1) << ": " << dealer.displayCardName(0, i);
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
		std::cout << "\nYou have one or more ace cards whose value can be modified (to 1 or 11).\n" <<
			"Enter the card number for an ace that you would like to flip (or -1 to cancel): ";
		std::string input;
		std::cin >> input;
		int choice = atoi(input.c_str());
		if(choice == -1){
			break;
		}
		else if(choice <= 0 || choice > player.getHandSize(current_hand)){
			std::cout << "\nInvalid input.\n";
			continue;
		}
		else if(choice >= 1 && choice <= player.getHandSize(current_hand)){
			int index = choice - 1;
			player.changeAce(current_hand, player.displayCardVal(current_hand, index), index);
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
	for(int i = 0; i < player.getHandSize(current_hand); ++i){
		player.changeAce(current_hand, player.displayCardVal(current_hand, i), i);
	}
}

/*
	@revertAces
	Revert ACE (11) cards to ACE (1) if the player's current hand is over 21. You wouldn't want to stand on two ACE (11) cards, now would you?
*/
const void Game::revertAces(){
	if(player.getHandTotal(current_hand) > 21 && checkNumAces() != 0){
		for(int i = 0; i < player.getHandSize(current_hand); ++i){
			if(player.displayCardVal(current_hand, i) == VERSA_ACE){
				player.changeAce(current_hand, player.displayCardVal(current_hand, i), i);
				if(!doubledDown){	//If doubled down, do not allow the user to draw more cards
					setPlayerStands(false);
				}
				displayCards(false);
				std::cout << "\n\nWARNING: Your current hand is greater than 21, but at least one ace card with a value of 11 was detected.\n" <<
					"Your ace card with value of 11 has been reverted to 1.\n" <<
					"You can also hit again even if you chose to stand with a hand greater than 21.";
				if(player.getHandTotal(current_hand) < 21){
					break;	//Break only if the player's hand has been reduced under 21
				}
			}
		}
	}
}

/*
	@checkForAcess
	Check for the existence of aces within a player's hand.
*/
const int Game::checkNumAces() const {
	return player.checkForAces(current_hand);
}

/*
	@gameChoice
	Parse input from execRound for user game interactions.
*/
const void Game::gameChoice(){
	if(!getPlayerStands()){
		bool valid = false;
		do{
			displayCards(true);
			bool double_valid = false, split_valid = false, ace_valid = false;

			//Display menu
			std::cout << "\nMake a choice for hand #" << current_hand + 1 << ".\n";
			std::cout << "1. Hit\n";
			std::cout << "2. Stand\n";
			if(player.getHandSize(current_hand) == 2 && player.getNumberOfHands() == 1 && (player.getBet() * 2 <= player.getPurse())){	//Check that the player can afford to double down, and is eligible to do so this round
				std::cout << "3. Double Down\n";
				double_valid = true;
			}
			if(player.getHandSize(current_hand) == 2 && ((player.displayCardName(current_hand, 0) == player.displayCardName(current_hand, 1)) || ((player.displayCardVal(current_hand, 0) == 1 || player.displayCardVal(current_hand, 0) == 11) && (player.displayCardVal(current_hand, 1) == 1 || player.displayCardVal(current_hand, 1) == 11)))){
				if(player.getBet() <= player.getPurse()){
					std::cout << "4. Split Hand\n";
					split_valid = true;
				}
			}
			if(checkNumAces() != 0){
				std::cout << "5. Change Ace Values\n";
				ace_valid = true;
			}

			//Parse user input
			std::cout << "\nMake your choice: ";
			std::string input;
			std::cin >> input;
			int choice = atoi(input.c_str());

			if((choice == 3 && !double_valid)
				|| (choice == 4 && !split_valid)
				|| (choice == 5 && !ace_valid)){	//Prevent access to unlisted choices in specific conditions
				std::cout << "\nInvalid Input.";
				valid = false;
				continue;
			}

			switch(choice){
				case 1:	//HIT
					player.hit(current_hand, deck);
					std::cout << "\nYou drew a " << player.displayCardName(current_hand, player.getHandSize(current_hand) - 1) << ".\n";
					if(player.getHandTotal(current_hand) == 21){	//Force player to stand on 21
						setPlayerStands(true);
					}
					valid = true;
					break;
				case 2:	//STAND
					setPlayerStands(true);
					valid = true;
					break;
				case 3:	//DOUBLE DOWN
					doubledDown = true;
					player.doubleBet();	//Double the bet
					player.hit(current_hand, deck);	//Draw a single card
					std::cout << "\nYou drew a " << player.displayCardName(current_hand, player.getHandSize(current_hand) - 1) << ".\n";
					setPlayerStands(true);	//Prevent drawing more cards
					valid = true;
					break;
				case 4:	//SPLIT HAND
					splitHand = true;
					std::cout << "\nYou split your hand!\n" <<
						"You draw a new card for each hand.\n" <<
						"You will now play on each hand until you stand, win, lose, or push on all of your hands of cards." <<
						"\nYour bet is also increased to cover each hand.\n";
					player.addSplitHand(current_hand, deck);
					valid = false;	//Allow the user to hit/stand on hand 1 before proceeding
					break;
				case 5:	//FLIP ACES
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
		int dealerTotal = dealer.getHandTotal(0);
		if(dealerTotal >= 21){
			dealerStands = true;
		}
		else if(dealerTotal < 17){
			dealer.hit(0, deck);
			std::cout << "\nDealer draws a(n) " << dealer.displayCardName(0, dealer.getHandSize(0) - 1) << ".\n";
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
	int playerHand = player.getHandTotal(current_hand);
	int dealerHand = dealer.getHandTotal(0);
	setPlayerStands(true);
	dealerStands = true;
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
		return true;
	}
	else if(p_blackjack && !d_blackjack){	//Player has blackjack
		displayEndOfRound();
		std::cout << "You got a Blackjack! Payout = 3:2" << std::endl;
		int scale = (int) ceil(player.getBet() + (1.5 * player.getBet()));
		player.updatePurse(scale);
		return true;
	}
	
	/*
		Other win and lose conditions
	*/
	if(player.getHandTotal(current_hand) > 21 && dealer.getHandTotal(0) > 21){	//Player and dealer hands > 21
		displayEndOfRound();
		std::cout << "You and the dealer both bust for hand #" << current_hand + 1 << ". Push." << std::endl;
		player.updatePurse(player.getBet());
		return true;
	}
	else if(player.getHandTotal(current_hand) > 21){				//Player hand > 21
		displayEndOfRound();
		std::cout << "You bust hand #" << current_hand + 1 << "." << std::endl;
		return true;
	}
	else if(dealer.getHandTotal(0) > 21){				//Dealer hand > 21
		displayEndOfRound();
		std::cout << "Dealer bust. You won hand #" << current_hand + 1 << "!" << std::endl;
		player.updatePurse(player.getBet() * 2);
		dealerBusted = true;
		return true;
	}
	else if(player.getHandTotal(current_hand) == 21 && dealer.getHandTotal(0) == 21){	//Player and dealer hands = 21
		displayEndOfRound();
		std::cout << "You and the dealer both have 21 for hand #" << current_hand + 1 << ". Push." << std::endl;
		player.updatePurse(player.getBet());
		return true;
	}
	else if(getPlayerStands() && dealerStands){	//Final check for win, lose, tie after player and dealer have finished moving (both players "stand")
		if(player.getHandTotal(current_hand) == dealer.getHandTotal(0)){	//Tie
			displayEndOfRound();
			std::cout << "You and the dealer have the same card values for hand #" << current_hand + 1 << ". Push." << std::endl;
			player.updatePurse(player.getBet());
			return true;
		}
		else if(player.getHandTotal(current_hand) < dealer.getHandTotal(0)){	//Player loses
			displayEndOfRound();
			std::cout << "You lost hand #" << current_hand + 1 << "!" << std::endl;
			return true;
		}
		else if(player.getHandTotal(current_hand) > dealer.getHandTotal(0)){	//Player wins
			displayEndOfRound();
			std::cout << "You won hand #" << current_hand + 1 <<"!" << std::endl;
			player.updatePurse(player.getBet() * 2);
			return true;
		}
	}
	return false;	//The round is not over - no condition satisfied
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
	player.resetAllHands();
	dealerStands = false, dealerBusted = false, doubledDown = false;
	player.resetHand(current_hand);
	dealer.resetHand(0);
	++round_counter;
}

/*
	@setPlayerStands
	Set the player's currently in use hand of cards to the value of @param stand (i.e. the hand is finalized)
*/
const void Game::setPlayerStands(const bool stand) { 
	player.setHandStandStatus(current_hand, stand); 
}

/*
	@getPlayerStands
	Get the "Stand" status of the player's currently in use hand of cards
*/
const bool Game::getPlayerStands() const { 
	return player.getHandStandStatus(current_hand); 
}