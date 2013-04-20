PROGRAM DESCRIPTION
Currently, this game consists of a simple implementation of the card game "Blackjack," a.k.a. "21".
Upon executing the program, the user will be presented with a game menu. Current choices are: New Game, Instructions, Options or Exit. Explore these choices at your leisure in game, as they are self-explanatory.
After selecting New Game, the game deck is built as a stack of 312 cards (6 decks of cards, 52 x 6 = 312). 
The deck is then immediately shuffled.
The player (you!) is then allowed to ante up for the current round. The starting wallet amount is 30,000 (of some unmarked currency/poker chips).
After placing a bet, the player and dealer each draw two cards. The dealer's second card is hidden until the end of the round.
The player can then choose to either hit, stand, double down (on the first turn only), split a hand (if possible), or change the value of ACE cards in their hand*, if one or more exist.
To draw a card, choose hit. When you do not want to draw any more cards, select stand. Selecting stand will prevent you from any further action this round, except under special circumstances*.
The dealer will stand on a hard OR soft 17, but not on a hand of a lower total value.
At the end of every turn, the hands of both parties are compared against all win/lose/tie conditions. Some conditions will not be checked until both the player and dealer make a stand on all hands.
If a round is over (one or both parties have won/lost/tied), then the option is given to play again (with an updated wallet based on the outcome of this round), or to exit the program now (by selecting not to play again, you are selecting to exit, since there is no other functionality to this program).
If you run out of currency, you will be presented with the starting game menu again, so you may choose to start a new game with a refreshed wallet, and a new deck of cards.

*NOTE: if you change an ACE to value 11, then draw a card that would put you over 21 (Ex. ACE (11) + 5 + King), your ACE will be devalued to 1 automatically, and you will be able to draw more cards, even if you stood with > 21 and an ACE (11) card. If you did this while doubling down, you will have a devalued ACE, but will not be able to hit again.


DEFINITIONS
WALLET - How much money you brought to bet with (currently fixed amount at 30,000).
ROUND - Consists of a complete game round, from betting to win/lose/tie. A round encompasses a hand of blackjack, and can contain zero or more turns.
TURN - An intra-ROUND circuit of player's and dealer's moves. Ex. TURN 1 goes from the player's first move (hit/stand/etc.) to the end of the dealer's move. Then TURN 2 starts if necessary. There can be zero or more turns per round.
HIT - Draw a card.
STAND - Do not draw a card. Also eliminates further opportunities to hit in the current round.
DOUBLE DOWN - Doubles your current bet, draws a single card, and immediately makes you stand. This can only be performed in the first turn of any round, and only by the player.
FLIP ACES - Change ACE cards from values of 1 to 11, and vice versa, at the player's discretion. 

TECHNICAL (CODING) DETAILS
ON CLASSES:
This program consists of several classes and instances of those classes. 
There is a heap allocated Game instance. Other objects are not heap memory objects. 
There are exactly this amount of instances:
GAME: 0..1
PLAYER: 0 OR 2
WALLET: 0 OR 2
DECK: 0 OR 1
STL vectors: 0 OR 6
SL string: 0..*
(0 in the case when the program is run and the user immediately decides to exit, or after a game is played until the user runs out of money, in which case the Game object, and composite instances are destroyed)
This program utilizes composition rather than class inheritance. 
Two Players are part of a Game: "player" and "dealer" are both Player objects. Each Wallet is part of a Player. A Deck is part of a Game.
The "dealer" Player instance does not explicitly initialize a Wallet. I felt that distinguishing a dealer from a player through inheritance was unnecessarily complex.

ON THE STRUCTURE OF THE CARD DECK:
The game's deck is built as a STL vector of 312 enum "FACE" values (6 decks of cards, 52 x 6 = 312). A second STL vector of 312 strings holds the associated string representations of each card (i.e. "ACE (1)", "KING", "TWO", etc.). These vectors are used as imitative stack structures; "cards" are drawn from the back of the vectors. I am considering using STL stack objects in a future revision.
The shuffling algorithm simply chooses two random index locations to swap, and swaps the elements if they are not the same index. This process runs continuously for 1 second (constant variable). Swap action counts vary from ~90k to ~4m swaps within the allotted time frame, but will vary by CPU and memory timings. This is not a perfect shuffle...by design. It is entirely possible for some cards to not be swapped at all (though extremely unlikely), or for some cards to end up in their starting position (also unlikely).

ON INPUT VALIDATION
Since this program is reliant on user input in program flow, incorrect input could cause erratic behavior. 
To address this, pains were taken to validate input, and test that validation as much as possible. 
Technically speaking, this is mainly performed by sticking the user inside of a loop until valid input is recognized. 
Input validation is performed by taking user input as a string, and then either looking for a single-character length string (which is the only case in which a character input is valid in this program's menus), or by using the atoi function to parse integers from the string for menus that use integer selection for options.
This, of course, relies on the user providing the correct input choice for what they actually want to do. You can't change your mind if you wanted to stand, but accidentally chose to hit!

SYSTEM REQUIREMENTS
Windows XP/Vista/7/8

"Release" EXECUTABLE RUNTIME REQUIREMENTS:
Microsoft Visual C++ 2010 SP1 Redistributable 
(For 64 bit OS - http://www.microsoft.com/en-us/download/details.aspx?id=13523)
(For 32 bit OS - http://www.microsoft.com/en-us/download/details.aspx?id=8328)

"Debug" EXECUTABLE RUNTIME REQUIREMENTS:
An installed version of Visual Studio (2010; maybe 2012, but not tested)

INSTALLATION INSTRUCTIONS
To play the game, simply:
1. Download and run setup.exe, or the msi installer located in the Installer/Release directory, AND the VC++ 2010 Redistributable prereqs, and then skip to step 5, OR Install the prerequisites (see above) and proceed to Step 2.
2. navigate to https://github.com/KyleWilliford/Blackjack/blob/master/Blackjack/Release/Blackjack.exe
3. Click "View Raw" in the center of the page.
4. Choose a directory to store the executable.
5. Run the executable/installer (may require a firewall / AV exception)
6. ???
7. Profit.

You could also compile the project in VS 2010 or another IDE. 
There may be compatibility errors if you try to compile using GCC or another C compiler (not tested). I used Visual Studio 2010 to compile and test this program, on Windows 7 Ultimate, 64-bit.



NOTICE:
This is a work in progress. This is not intended for (any) commercial release.
Please do not use this code in any of your projects. Ask me for permission if you wish to contribute (I prefer ideas rather than code contributions, if any).

You can contact me at willifordkyle@hotmail.com or via my account on Github (not checked regularly though).