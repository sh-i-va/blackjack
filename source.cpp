#include <iostream>
#include <array>
#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()
#include <cctype> // for toupper()
#include <cassert> // for assert()

// Class to hold a single card, with suit and rank
class Card
{
    public:
        // Enumerations for suits and ranks
        enum CardSuit
        {
            SUIT_CLUBS,
            SUIT_DIAMONDS,
            SUIT_HEARTS,
            SUIT_SPADES,
            MAX_SUITS
        };

        enum CardRank
        {
            RANK_2,
            RANK_3,
            RANK_4,
            RANK_5,
            RANK_6,
            RANK_7,
            RANK_8,
            RANK_9,
            RANK_10,
            RANK_JACK,
            RANK_QUEEN,
            RANK_KING,
            RANK_ACE,
            MAX_RANKS
        };

    private:
        CardSuit m_suit;
        CardRank m_rank;

    public:
        Card(CardRank rank = RANK_ACE, CardSuit suit = SUIT_SPADES): m_rank(rank), m_suit(suit) {}

        void printCard() const; // print the card
        int getCardValue(int) const; // get the card's value
};

// Print the card as a rank-suit 2-letter code
// e.g. Jack of Spades => JS
void Card::printCard() const
{
    using namespace std;

    // Print the letter of the card's rank
    switch (m_rank)
    {
        case RANK_2:    cout << '2'; break;
        case RANK_3:    cout << '3'; break;
        case RANK_4:    cout << '4'; break;
        case RANK_5:    cout << '5'; break;
        case RANK_6:    cout << '6'; break;
        case RANK_7:    cout << '7'; break;
        case RANK_8:    cout << '8'; break;
        case RANK_9:    cout << '9'; break;
        case RANK_10:   cout << 'T'; break;
        case RANK_JACK: cout << 'J'; break;
        case RANK_QUEEN:cout << 'Q'; break;
        case RANK_KING: cout << 'K'; break;
        case RANK_ACE:  cout << 'A'; break;
        case MAX_RANKS: cout << '?'; // Invalid case
    }

    // Print the letter of the card's suit
    switch (m_suit)
    {
        case SUIT_CLUBS:     cout << 'C'; break;
        case SUIT_DIAMONDS:  cout << 'D'; break;
        case SUIT_HEARTS:    cout << 'H'; break;
        case SUIT_SPADES:    cout << 'S'; break;
        case MAX_SUITS:      cout << '?'; // Invalid case
    }
}

// Calculate and return the value of the card
// currentScore is required to calculate the value of Ace
int Card::getCardValue(int currentScore) const
{
    // Only rank is relevant here
    switch (m_rank)
    {
        case RANK_2     : return 2;
        case RANK_3     : return 3;
        case RANK_4     : return 4;
        case RANK_5     : return 5;
        case RANK_6     : return 6;
        case RANK_7     : return 7;
        case RANK_8     : return 8;
        case RANK_9     : return 9;
        
        case RANK_10:
        case RANK_JACK:
        case RANK_QUEEN:
        case RANK_KING:
            return 10;

        case RANK_ACE:
            // If taking 11 for Ace busts the player, take 1; else take 11
            if (currentScore > 10)
                return 1;
            else
                return 11;
        
        case MAX_RANKS  :return 0; // Invalid case
    }
}

// Class to hold a deck of cards
class Deck
{
    private:
        std::array<Card, 52> m_deck;
        int m_cardIndex; // stores the index of the current topmost card in the deck

    public:
        Deck()
        {
            initDeck();
        }

        void initDeck(); // initialise the deck
        void printDeck(); // print all the cards in the deck
        void shuffleDeck(); // shuffle the current deck randomly
        const Card& dealCard(); // deal the topmost card from the deck

    private:
        // helper functions, don't need acces to *this
        static int getRandomNumber(int, int);
        static void swapCards(Card &, Card &);
};

// Initialise the deck into the unshuffled state (2C -> AS)
void Deck::initDeck()
{
    // Index for the card to be initialised
    int card = 0;

    // Step through the suits
    for (int suit = 0; suit < Card::MAX_SUITS; ++suit)
    {
        // Step through the ranks
        for (int rank = 0; rank < Card::MAX_RANKS; ++rank)
        {
            // Use static_cast to convert int's to enum's
            m_deck[card] = Card(static_cast<Card::CardRank>(rank), static_cast<Card::CardSuit>(suit));
            
            // Move to the next card for the next iteration
            ++card;
        }
    }
    
    // Start dealing from the top
    m_cardIndex = 0;
}

// Print the complete deck
void Deck::printDeck()
{
    // card is a reference object to the elements of the member array m_deck
    for (const auto &card : m_deck)
    {
        card.printCard();
        std::cout << ' ';
    }

    // Terminate with a newline
    std::cout << '\n';
    return;
}

// Swap two cards, passed as references to change the original values
void Deck::swapCards(Card &a, Card &b)
{
    // Create a temporary card to store a;
    Card temp(a);
    
    a = b;
    b = temp;
    
    return;
}

// Generate a random number between given limits (included)
int Deck::getRandomNumber(int min, int max)
{
    // Assumes srand() has already been called
    // Multiplier to reduce the random number to < 1
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);

    // Calculate the random number, normalize, truncate and return it
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

// Shuffle the deck of cards randomly
void Deck::shuffleDeck()
{
    // First, we need to loop through the deck
    for (int card = 0; card < 52; ++card)
    {
        // Get a random card
        int randomCard = Deck::getRandomNumber(0, 51);
        
        // Swap the current card with the random card
        swapCards(m_deck[card], m_deck[randomCard]);
    }

    // After shuffling, we need to start dealing from the top again
    m_cardIndex = 0;

    return;
}

// Deal the topmost card from the deck
const Card& Deck::dealCard()
{
    assert (m_cardIndex < 52);
    
    // Print the dealt card to the console
    m_deck[m_cardIndex].printCard();

    // Then return a const reference to the dealt card in the m_deck array
    // and advance the index to the next card
    return m_deck[m_cardIndex++];
}

// Print the current scores of the dealer and the player
void printScores(int dealerScore, int playerScore)
{
    std::cout << "\n\nCurrent scores\n--------------\n";
    std::cout << "Dealer: " << dealerScore << "\tPlayer: " << playerScore << std::endl;
    return;
}

// Play a single game of Blackjack ('deck' is a shuffled deck)
// Return true if the player wins, false if they lose
bool playBlackjack(Deck &deck)
{
    // Variables to store the players' scores
    int playerScore {0};
    int dealerScore {0};

    // Let's begin the game!
    std::cout << "\nDealing...";

    // Deal one card to the dealer, print it and add it's value to their score
    std::cout << "\nDealer: ";
    dealerScore += deck.dealCard().getCardValue(dealerScore);
    
    // Deal two cards to the player, print them and update the  player's scores
    std::cout << "\tPlayer: ";
    playerScore += deck.dealCard().getCardValue(playerScore);
    std::cout << ' ';
    playerScore += deck.dealCard().getCardValue(playerScore); // #2
    
    // Print the current scores
    printScores(dealerScore, playerScore);

    // Store the player's choice
    char playerChoice;

    // Player's turn
    do
    {
        // Ask the player as long as they enter an invalid choice
        do
        {
            std::cout << "Enter your move: Hit(H) or Stand(S)? ";
            std::cin >> playerChoice;
            playerChoice = toupper(playerChoice);
        } while (playerChoice != 'H' && playerChoice != 'S');

        if (playerChoice == 'H')
        {
            // Player hits, draw another card from the deck and update score
            std::cout << "\nDrawn: ";
            playerScore += deck.dealCard().getCardValue(playerScore);
            
            // Print the current scores
            printScores(dealerScore, playerScore);
        }

        // If the player goes over 21, busted
        if (playerScore > 21)
        {
            std::cout << "You went over 21!\n";
            return false;
        }
 
        // Break out of the loop if the player stands
    } while (playerChoice != 'S');

    // Dealer's turn: draw repeatedly until the dealer reach 17 or more
    std::cout << "\nDealer drawing...";
    while (dealerScore < 17)
    {
        std::cout << "\nDrawn ";
        dealerScore += deck.dealCard().getCardValue(dealerScore);
   }

    // Print the scores after the dealer's turn
    printScores(dealerScore, playerScore);
    
    // If the dealer goes over 21, dealer busts
    if (dealerScore > 21)
    {
        std::cout << "Dealer went over 21!\n";
        return true;
    }

    // Control reaches here only if both player and dealer stand below 21
    // Then, return true if playerScore >= dealerScore, false otherwise
    return (playerScore >= dealerScore);
}

// Main function
int main()
{
    // Seed srand() with system time for calling rand()
    srand(static_cast<unsigned int>(time(0)));

    // Create an empty deck and populate it with unshuffled cards
    Deck deck;

    // Play the game as many time as the player wants
    char playAgain;

    do
    {
        // Init the console with some introduction
        std::cout << "\033[2J\033[1;1H"; //Clear the console
        std::cout << "\n\t\t\t\tBLACKJACK";
        std::cout << "\n\t\t\t\t=========";
        std::cout << "\n\n* Instructions\n  ------------";
        std::cout << "\n1. Use the keyboard to enter your moves.\
\n2. Each card is denoted using two letters: one for its rank and one for its\
\n   suit. e.g. JS denotes the Jack of Spades, 5H denotes the 5 of Spades, etc.\
\n3. You must know the basic rules of Blackjack.\
\n4. For simplicity, Player wins ties.\n\n\tSo, let's begin!\n";
        
        // Shuffle the deck and play a single game
        deck.shuffleDeck();
        bool playerWon = playBlackjack(deck); 

        // Print result
        if (playerWon)
            std::cout << "\n### You won! \\o/ ###\n";
        else
            std::cout << "\n### You lose! Better luck next time... ###\n";
        
        // Ask the player if he want's play again
        // Accept only a valid input
        do
        {
            std::cout << "\nHave time for another game? (Y/N) ";
            std::cin >> playAgain;
            playAgain = toupper(playAgain);
        } while (playAgain != 'Y' && playAgain != 'N');
    
        // Iterate if the player says yes (Y), break out otherwise
    } while (playAgain == 'Y');
    
    // Clear the console
    std::cout << "\033[2J\033[1;1H";

    // Return 0 to the OS and terminate the program
    return 0;
}

