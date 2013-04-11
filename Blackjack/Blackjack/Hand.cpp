/*
	Kyle Williford
	Blackjack [WIP]
*/

#include "Hand.h"

/*
	@getBet
	Return the value of this Hand's bet variable
*/
const int Hand::getBet() const
{ 
	return bet; 
}

/*
	@setBet
	Sets this Hand's bet variable to @param bet
*/
const void Hand::setBet(const int bet)
{ 
	this->bet = bet; 
}

/*
	@hit
	Draw a card from the deck and add it to this hand. 
	Modifies Deck's deck vector in place.
*/
const void Hand::hit(Deck &deck)
{
	FACE cardDrawn = deck.draw();
	hand.push_back(cardDrawn);
	names.push_back(deck.drawName());
	handTotal += cardDrawn;
}

/*
	@checkAce
	Looks for and returns the number of aces in this hand.
*/
const int Hand::checkForAces() const 
{
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
const void Hand::changeAce(const FACE ace, const int index)
{
	if(ace == ACE){
		handTotal += (-1 * ace) + VERSA_ACE;	//swap card values in handTotal
		hand[index] = VERSA_ACE;
		names[index] = "ACE (11)";
	}
	else if(ace == VERSA_ACE){
		handTotal += (-1 * ace) + ACE;
		hand[index] = ACE;
		names[index] = "ACE (1)";
	}
}

/*
	@displayCardVal
	Return the value of the card at the indexed location in the vector of names
*/
const FACE Hand::displayCardVal(const int index) const
{
	return hand.at(index); 
}

/*
	@displayCardName
	Return the name of the card at the indexed location in the vector of names
*/
const std::string Hand::displayCardName(const int index) const 
{ 
	return names.at(index); 
}

/*
	@getHandSize
	Return the size of the hand vector from this instance
*/
const int Hand::getHandSize() const
{ 
	return hand.size(); 
}

/*
	@getHandTotal	
	Return a copy of the hand total value from this instance
*/
const int Hand::getHandTotal() const 
{ 
	return handTotal; 
}

/*
	@resetHand
	Reset the hand, names, and handTotal vectors, and variable, respectively
*/
const void Hand::resetHand()
{ 
	hand.resize(0); 
	names.resize(0); 
	handTotal = 0, bet = 0, stand = false; 
}

/*
	@split
	Split the current hand - removes the last card from this Hand's vectors
	NOTE: Should only be called when a split is a valid user action
*/
const void Hand::split() 
{ 
	hand.pop_back();
	names.pop_back(); 
	handTotal /= 2; 
}

/*
	@setStand
	Set this Hand's stand var to @param stand
*/
const void Hand::setStand(const bool stand)
{ 
	this->stand = stand; 
}

/*
	@getStand
	Return the value of variable stand
*/
const bool Hand::getStand() const 
{
	return stand; 
}