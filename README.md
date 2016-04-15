### Blackjack

Blackjack is a popular casino card game. This is a simplified version, with a   single-player against-the-computer gameplay. Coded as an exercise. :)

#### Notes

* The game has no GUI. Will run on any Unix shell.
* If you are building the source using gcc or clang, use the `-std=c++11` option  to enable the C++11 standard functionality.

#### Simplified rules

For those who are unfamiliar with Blackjack, here are the basic rules for our   version of Blackjack:

* The dealer gets one card to start (in real life, the dealer gets two).
* The player gets two cards to start.
* The player goes first.
* A player can repeatedly hit (draw) or stand (pass).
* If the player stands, their turn is over.
* If the player hits, they get another card from the deck and the value of that  card is added to their total score.
* An ace normally counts as a 1 or an 11 (whichever is better for the total score).  It is automatically calculated to the player's or dealer's benefit.
* If the player goes over a score of 21, they bust and lose immediately.
* The dealer goes after the player.
* The dealer repeatedly draws until they reach a score of 17 or more, at which  point they stand.
* If the dealer goes over a score of 21, they bust and the player wins immediately.
* Otherwise, if the player has a higher score than the dealer, the player wins.  Otherwise, the player loses.
* For simplicity, player wins ties.

For more info, read the [Wikipedia artice](https://en.wikipedia.org/wiki/Blackjack) about Blackjack.

__Developer__ : Shiva Prasad ~ [github.com/sh-i-va](https://github.com/sh-i-va)
__Credits__   : Thanks to Alex @[learncpp.com](https://learncpp.com) for the challenge.  Check out his site, it's awesome. :)
