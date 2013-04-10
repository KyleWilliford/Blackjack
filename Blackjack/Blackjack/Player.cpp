/*
	Kyle Williford
	Blackjack [WIP]
*/

#include "Player.h"

/*
	@Player
	Default constructor
*/
Player::Player() : wallet(), hand(1, Hand()) { 
};

/*
	@Player(int)
	Constructor for the human player instance
	@param wallet size
*/
Player::Player(const int walletSize) : wallet(walletSize), hand(1, Hand()) {
}

/*
	@Player(bool)		
	Constructor for the dealer (AI player instance) - skips wallet initialization
*/
Player::Player(const bool) : hand(1, Hand()) {
}

/*
	@~Player 
	Player obj destructor
*/
Player::~Player(){
}

/*
	@placeBet
	Interface for calling WalletbettingMenu
*/
const void Player::placeBet() {
	wallet.bettingMenu(); 
	hand[0].setBet(wallet.getBet()); 
}

/*
	@updatePurse
	Updates Wallet.purse with the result of a win/loss/push
*/
const void Player::updatePurse(const int handIndex, const int scale_amount) { 
	wallet.updatePurse(hand[handIndex].getBet() + scale_amount); 
}

/*
	@getBet
	Return a copy of the bet amount stored in Wallet
*/
const int Player::getBet() const { 
	return wallet.getBet(); 
}

/*
	@doubleBet	
	Interface methof for doubling down on a bet
*/
const void Player::doubleBet() {
	wallet.doubleBet(); 
}

/*
	@getPurse
	Interface method for getting a copy of the purse amount stored in Wallet
*/
const int Player::getPurse() const { 
	return wallet.getPurse(); 
}

/*
	@hit
	Interface method for drawing a card on a specified hand of cards
*/
const void Player::hit(const int handIndex, Deck& deck) {
	hand[handIndex].hit(deck); 
}

/*
	@checkForAces
	Interface method for Call an instance of hand to check for Aces
*/
const int Player::checkForAces(const int handIndex) const { 
	return hand[handIndex].checkForAces();
}
	
/*
	@changeAce	
	Call an instance of hand to change an Ace's value
*/
const void Player::changeAce(const int handIndex, const FACE aceVal, const int aceIndex) { 
	return hand[handIndex].changeAce(aceVal, aceIndex); 
}

/*
	@displayCardVal
	Interface method for getting the enum value of a card at the indexed location in the vector of cards
*/
const FACE Player::displayCardVal(const int handIndex, const int cardIndex) const { 
	return hand[handIndex].displayCardVal(cardIndex); 
}

/*
	@displayCardName
	Interface method for getting the string name of a card at the indexed location in the vector of names
*/
const std::string Player::displayCardName(const int handIndex, const int cardIndex) const { 
	return hand[handIndex].displayCardName(cardIndex); 
}

/*
	@getHandSize	
	Return the vector size of the specified hand of cards (i.e. the number of cards in the hand)
*/
const int Player::getHandSize(const int handIndex) const { 
	return hand[handIndex].getHandSize(); 
}

/*
	@getHandTotal	
	Return total value of the specified hand of cards (as integer)
*/
const int Player::getHandTotal(const int handIndex) const { 
	return hand[handIndex].getHandTotal(); 
}

/*
	@resetHand	
	Interface method for resetting the flag variables of the specified hand
*/
const void Player::resetHand(const int handIndex){
	hand[handIndex].resetHand(); 
}

/*
	@resetAllHands
	Reset all hands by removing all but one of the Hand objects in the Player::hand vector, and then resetting the remaining Hand object's variables
*/
const void Player::resetAllHands(){
	hand.resize(1);
	hand[0].resetHand();
}

/*
	@addSplitHand
	Split a specified hand of cards, and create an additional hand of cards
*/
const void Player::addSplitHand(const int handIndex, Deck & deck){
	hand.push_back(Hand(hand[handIndex].displayCardVal(0), 
		hand[handIndex].displayCardName(0), 
		hand[handIndex].getHandTotal() / 2, 
		hand[handIndex].getBet())
		);
	hand[handIndex].split();

	//Draw a new card for each split hand
	hand[handIndex].hit(deck);
	hand[handIndex + 1].hit(deck);
}

/*
	@getNumberOfHands
	Return the size of vector hand (the size equals the number of card hands the player has in play)
*/
const int Player::getNumberOfHands() const { 
	return hand.size(); 
}

/*
	@setHandStandStatus
	Interface method for setting the specified hand of card's stand variable to @param stand
*/
const void Player::setHandStandStatus(const int handIndex, const bool stand) { 
	hand[handIndex].setStand(stand); 
}

/*
	@getHandStandStatus
	Interface method for getting the stand status of a specified hand of cards
*/
const bool Player::getHandStandStatus(const int handIndex) const { 
	return hand[handIndex].getStand(); 
}