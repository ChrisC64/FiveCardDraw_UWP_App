#ifndef DEALER_H
#define DEALER_H

#include "Player.h"
#include "Deck.h"
#include "pch.h"
class Dealer : public Player, public Deck
{
private:
    // Pointers to player objects
    std::vector<std::shared_ptr<Player>> m_vPlayers;
    std::shared_ptr<Deck> m_Deck;
    std::shared_ptr<std::vector<Card>> m_DealtCards;
    std::shared_ptr<std::vector<Card>> m_vUniqueCards; 
    std::list<std::shared_ptr<Player>> m_highCardList;
    std::vector<std::shared_ptr<Player>> m_winningPlayers;
    CATEGORY    highestCategory;

    //std::map<CATEGORY, Player*> m_mPairMap; 
    
    // Continue playing?
    bool m_bIsHighCardGame;
    bool m_bIsDealing;
    bool m_bIsTie;

    int m_iNumOfPlayers;
    int m_iHandSize;

public:

    // Constructor
    Dealer(std::shared_ptr<Deck> deck);
    ~Dealer();
    
    // SET METHODS //

    /*  Name: SetIsDealing(bool)
        Param: bool
        Return: void
        Info: Set m_bIsDealing variable
    */
    void SetIsDealing(bool isDealing);

    /*  Name: SetNumOfPlayers(int)
        Param: int
        Return: void
        Info: Set m_iNumOfPlayers variable
    */
    void SetNumOfPlayers(int num);

    /*  Name: SetHandSize(int)
        Param: Int
        Return: void
        Info: Set Hand size of the game
    */
    void SetHandSize(int size);

    /*  Name: SetCategory(Player, Hand::Category)
        Param: Player*, Hand::CATEGORY
        Return: Set the Player's HAND Category (SFLUSH, STRAIGHT, TOAK, etc)
    */
    void SetCategory(std::shared_ptr<Player> player, Hand::CATEGORY eCategory);
    
    /*  Name: DetermineCategory(Player *p)
        Param: Player*
        Return: void
        Info: Set the player's HAND category
    */
    void SetCategory(std::shared_ptr<Player> player);

    /*  Name: AddPlayers(Players* p);
        Param: Players*
        Return: void
        Info: Add players into our container
    */
    void AddPlayers(std::shared_ptr<Player> player);

    // GET METHODS //

    /*  Name: GetIsDealing()
        Param: void
        Return: bool
        Info: Return m_bIsDealing value
    */
    bool GetIsDealing();

    /*  Name: GetHandSize()
        Param: void
        Return: int
        Info: Return m_iHandSize value
    */
    int GetHandSize();

    /*  Name: GetNumOfPlayers()
        Param: void
        Return: int
        Info: Get m_iNumOfPlayers value
    */
    int GetNumOfPlayres();

    /*  Name: GetWinningPlayers()
        Param: void
        Return: std::shared_ptr<std::vector<std::shared_ptr<Player>>>
        Info: Get a shared pointer to the vector of winning players
    */
    std::vector<std::shared_ptr<Player>> GetWinningPlayers();


    // CHECKS on Cards

    /*  Name: IsSequential()
        Parm: void
        Return: bool
        Info: Returns a boolean if the hand of the player is Sequential
        (Cards N, N[2] = N + 1 OR N - 1, ... N[x] = N -/+ (x - 1)
    */
    //bool IsSequential(Player *p);

    /*  Name: IsMatchingSuit()
        Parm: void
        Return: bool
        Info: Checks if all SUITS of the PLAYER's HAND are matching
    */
    //bool IsMatchingSuit(Player *p);

    /*  Name: CompareHands(Player *p)
        Parm: Player*
        Return: void
        Info: Determine which player holds the winning hand
    */
    void CompareHands();

    // HELPER FUNCTIONS

    /*  Name: FindPairs(Player *P)
        Param: Player*
        Return: void
        Info: Set up our PairMap and find the number of pairs for this hand;
    */
    //bool FindPairs(Player *p);

    /*  Name: CompareHighCards(vector<Player> *p)
        Param: Player*
        Return: void
        Info: Determine which player has the highest card and wins
    */
    void FindSameCategory();

    /*  Name: CompareCategory()
        Param: void
        Return: void
        Info: Compare the category of the player's hand with the other. We look for the highest
        Category, and then compare it only with similar or higher ranking categories.
        If we find a higher category, that becomes our new "Winner"
    */
    void CompareCategories();

    /*  Name: SwapPlayers(int pos1, int pos2)
        Param: int, int
        Return: void
        Info: Perform a swap on the m_vPlayers container
    */
    void SwapPlayers(int pos1, int pos2);

    // GAME FUNCTION //

    /*  Name: DealCards(std::<Player*> p)
        Param: vector<Player*>
        Return: void
        Info: Deal cards to all players
    */
    void DealCards();

    /*  Name: DrawCards(int amount)
        Param: int
        Return: void
        Info: Here we fill up our m_DealtCards container before passing off thsi new
        hand to the player. We perform the Deck::DrawCards() x amount
    */
    void DrawCard(int amount);

    /*  Name: SortPlayersByCategory();
        Param: void
        Return: void
        Info: Our m_vPlayers will be organized by player's Hand Category, Best hands to worst hands
    */
    void SortPlayersByCategory();

    /*  Name: PlayGame()
        Param: void
        Return: void
        Info: Our main function to call, when we start the game.
    */
    void PlayGame();

    /*  Name: PrintWinner();
        Param: Player*
        Return: void
        Info: Print the Winner of the match
    */
    void PrintWinner(std::shared_ptr<Player> player);

    /*  Name: PrintTie()
        Param: Player*
        Return: void
        Info: Print the players who tied
    */
    void PrintTie(std::shared_ptr<Player> player);

    /*  Name: PrintEndGameStats();
        Param: void
        Return: void
        Info: Print the end game stats (Wins, losses, and Ties of each player)
    */
    void PrintEndGameStats();

    /*  Name: PrintTable()
        Param: void
        Return: void
        Info: Print the cards of each player, with name and Category as well
    */
    void PrintTable();

    /*  Name: NewGame()
        Param: void
        Return: void
        Info: Start a new game, call each player's "Reset()" to wipe their hands.
        This does not erase any player's wins, loss, and ties scores. Just sets up for 
        a new game.
    */
    void NewGame();

    // RULES FOR HAND CATEGORY //

    /*  Name: CompareSFlush();
        Info: Rules on comparing same hands with SFLUSH
    */
    void CompareSFlush();

    /*  Name: CompareFoak();
        Info: Rules on comparing same hands with FOAK
    */
    void CompareFoak();

    /*  Name: CompareFullHouse();
        Info: Rules on comparing same hands with Fullhouse
    */
    void CompareFullHouse();

    /*  Name: CompareStraight();
        Info: Rules on comparing same hands with STRAIGHT
    */
    void CompareStraight();

    /*  Name: CompareToak();
        Info: Rules on comparing same hands with TOAK
    */
    void CompareToak();   

    /*  Name: CompareTwoPair();
        Info: Rules on comparing same hands with TwoPair
    */
    void CompareTwoPair();

    /*  Name: CompareOnePair();
        Info: Rules on comparing same hands with OnePair
    */
    void CompareOnePair();

    /*  Name: CompareHighCards();
        Info: Rules for finding a HIGHCARD hand
    */
    void CompareHighCard();

    // FINDING THE PAIRS/VALUES OF CARDS //

    /*  Name: FindHighRankCard( );
        Param: int valueToLookfor
        Return: void
        Info: Look for a specific pair value 
        (EX: TOAK: pairValue = 3, FOAK: pairValue = 4, TwoPair pairValue = 2, etc)
        ** NOTE: Use FindHighInTWoPair for CATEGORY::TWOPAIR
    */
    void FindHighInPair(int pairValue);

    /*  Name: FindTwoPair;
        Param: void
        Return: voi 
        Info: Slight modified rules for finding a TwoPair cards.
        If we have two pairs, we will check both pairs first, then check the value of the
        final card only if there has been no winner yet.
    */
    void  FindHighInTwoPair();

    /*  Name: FindHighValue()
        Param: void
        Return: void
        Info: Find the highest value of the card (used in STRAIGHT, SFLUSH, FLUSH, and HIGHCARD)
    */
    void FindHighValue();

    // Override
    void FindHighValue(std::shared_ptr<std::list<std::shared_ptr<Player>>> playerList);
    /*  Name: Compare(list<Player*>)
        Param: void
        Return: void
        Info: Compare the cards of each player individually
    */
    void Compare(std::shared_ptr<std::list<std::shared_ptr<Player>>> playerList);
};

#endif DEALER_H