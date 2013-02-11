/*
	Kyle Williford
	2/6/13
	Blackjack [WIP]
*/

#include "Player.h"

Player::Player() : wallet(), handTotal(0){
}

Player::Player(int walletSize) : wallet(walletSize), handTotal(0){
}

Player::Player(char dealer) : handTotal(0){
}

Player::~Player(){
}

/*
	@hit
	Draw a card from the deck and add it to this Player's hand. 
	Modifies Deck's deck vector in place.
*/
void Player::hit(Deck &deck){
	FACE cardDrawn = deck.draw();
	hand.push_back(cardDrawn);
	names.push_back(deck.drawName());
	handTotal += cardDrawn;
}

int Player::handSize(){
	return hand.size();
}

FACE Player::displayCardVal(int index){
	return hand.at(index);
}

std::string Player::displayCard(int index){
	return names.at(index);
}

int Player::getHandTotal(){
	return handTotal;
}

/*
	@checkAce
	Looks for a number of aces in the player's hand.
*/
int Player::checkAce(){
	int numAces = 0;
	for(unsigned int i = 0; i < hand.size(); ++i){
		if(hand[i] == ACE || hand[i] == VERSA_ACE){
			++numAces;
		}
	}
	return numAces;
}

/*
	[WIP]
	@changeAce
	Swap between ace with value of 1 and ace with value of 11.
*/
void Player::changeAce(FACE ace, int index){
	if(ace == 1){
		handTotal += (-1 * ace) + VERSA_ACE;	//swap card values in handTotal
		hand[index] = VERSA_ACE;
		names[index] = "ACE (11)";
	}
	else if(ace == 11){
		handTotal += (-1 * ace) + ACE;
		hand[index] = ACE;
		names[index] = "ACE (1)";
	}
}

int Player::getHandSize(){
	return hand.size();
}

void Player::updatePurse(int bet){
	wallet.updatePurse(bet);
}

void Player::resetHand(){
	hand.clear();
	names.clear();
	handTotal = 0;
}