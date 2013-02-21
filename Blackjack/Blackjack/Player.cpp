/*
	Kyle Williford
	2/6/13
	Blackjack [WIP]
*/

#include "Player.h"

/*
	@hit
	Draw a card from the deck and add it to this Player's hand. 
	Modifies Deck's deck vector in place.
*/
const void Player::hit(Deck &deck){
	FACE cardDrawn = deck.draw();
	hand.push_back(cardDrawn);
	names.push_back(deck.drawName());
	handTotal += cardDrawn;
}
/*
	@checkAce
	Looks for a number of aces in the player's hand.
*/
const int Player::checkForAces(){
	int numAces = 0;
	for(unsigned int i = 0; i < hand.size(); ++i){
		if(hand[i] == ACE || hand[i] == VERSA_ACE){
			++numAces;
		}
	}
	return numAces;
}

/*
	@changeAce
	Swap between ace with value of 1 and ace with value of 11.
*/
const void Player::changeAce(const FACE ace, const int index){
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