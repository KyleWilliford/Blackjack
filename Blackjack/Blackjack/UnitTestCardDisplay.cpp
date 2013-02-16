#include "Game.h"
#include <vector>
#include <string>

//Test the correct display of cards when the player stands, but the player has not 
//(player could see the dealer's hidden card while still being given the option to hit)
int main(){
	std::vector<FACE> hand;
	std::vector<std::string> names;
	hand.push_back(ACE);
	hand.push_back(ACE);
	names.push_back("ACE");
	names.push_back("ACE");
	Player p(hand, names), d(hand, names);
	Game game(p, d);
}

/*
	RESULTS: successfully fixed bug
	playerStands = true, dealerStands = true	display hidden card
	playerStands = true, dealerStands = false	hide card
	playerStands = false, dealerStands = false	hide card
	playerStands = false, dealerStands = true	hide card	(fixed bug here)
*/