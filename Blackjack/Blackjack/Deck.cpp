/*
	Kyle Williford
	2/6/13
	Blackjack [WIP]
*/

#include <vector>
#include <iostream>
#include <time.h>
#include "Deck.h"

const double Deck::ShuffleTime = 1.0;

/*
	@shuffle
	Shuffle the card pack.
*/
const void Deck::shuffle(){
	int shuffle_counter = 0;
	std::cout << "\nShuffling the Deck, Please Wait... " << std::endl;

	time_t start, check;
	time(&start);
	double elapsed = 0;

	//Shuffles by choosing random cards in the pack to swap places with
	//Shuffles continuously for a number of seconds determined by ShuffleTime constant value
	//Tests indicate approximately 1 to 5 million swaps / sec with a 3.0 GHz processor. Faster CPU and RAM = fewer swap actions.
	while(elapsed < ShuffleTime){
		int shuffleCardpos1 = rand() % deckSize;	//Find random place in the vector to swap with
		int shuffleCardpos2 = rand() % deckSize;	//Find random place in the vector to swap with

		if(shuffleCardpos1 != shuffleCardpos2){
			//Swap cards in value deck
			FACE temp = deck[shuffleCardpos2];
			deck[shuffleCardpos2] = deck[shuffleCardpos1];
			deck[shuffleCardpos1] = temp;

			//Swap cards in name deck
			std::string tempStr = names[shuffleCardpos2];
			names[shuffleCardpos2] = names[shuffleCardpos1];
			names[shuffleCardpos1] = tempStr;
		}
		
		time(&check);
		elapsed = difftime(check, start);
		++shuffle_counter;
	}
	std::cout << "\nShuffled cards " << shuffle_counter << " times in " << ShuffleTime << " second(s)!\n";
}

/*
	@build
	Build a new deck of cards based on the deckCount.
*/
const void Deck::build(){
	deck.clear();
	names.clear();
	for(int i = 0; i < deckCount; ++i){
		for(int j = 0; j < 52; ++j){
			if(j % 13 == 0){
				deck.push_back(ACE);
				names.push_back("ACE (1)");
			}
			else if(j % 13 == 1){
				deck.push_back(TWO);
				names.push_back("TWO");
			}
			else if(j % 13 == 2){
				deck.push_back(THREE);
				names.push_back("THREE");
			}
			else if(j % 13 == 3){
				deck.push_back(FOUR);
				names.push_back("FOUR");
			}
			else if(j % 13 == 4){
				deck.push_back(FIVE);
				names.push_back("FIVE");
			}
			else if(j % 13 == 5){
				deck.push_back(SIX);
				names.push_back("SIX");
			}
			else if(j % 13 == 6){
				deck.push_back(SEVEN);
				names.push_back("SEVEN");
			}
			else if(j % 13 == 7){
				deck.push_back(EIGHT);
				names.push_back("EIGHT");
			}
			else if(j % 13 == 8){
				deck.push_back(NINE);
				names.push_back("NINE");
			}
			else if(j % 13 == 9){
				deck.push_back(TEN);
				names.push_back("TEN");
			}
			else if(j % 13 == 10){
				deck.push_back(JACK);
				names.push_back("JACK");
			}
			else if(j % 13 == 11){
				deck.push_back(QUEEN);
				names.push_back("QUEEN");
			}
			else if(j % 13 == 12){
				deck.push_back(KING);
				names.push_back("KING");
			}
		}
	}
}

/*
	@draw
	Draws a card from the back of the deck vector.
*/
const FACE Deck::draw(){
	if(deck.size() <= 12){
		std::cout << "\n\nDeck low on cards. Rebuilding.\n";
		build();
		shuffle();
	}
	FACE cardDrawn = deck.back();
	deck.pop_back();
	return cardDrawn;
}

/*
	@drawName
	Takes the name of a card from the names string vector 
	(name matches the value in the deck vector that is also drawn when this is called)
*/
const std::string Deck::drawName(){
	std::string cardDrawn = names.back();
	names.pop_back();
	return cardDrawn;
}