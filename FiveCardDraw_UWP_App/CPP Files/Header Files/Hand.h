#pragma once

#include "Card.h"
#include "pch.h"

class Hand : public Card
{
protected:
    // The hand's category will be one of the steps in determining a winner. 
    // Organinized from High to low
    enum CATEGORY
    {
        SFLUSH = 0,
        FOAK   = 1, // Four of a kind
        FULLHOUSE = 2,
        FLUSH = 3,
        STRAIGHT = 4,
        TOAK = 5, // Two of a kind
        TWOPAIR = 6,
        ONEPAIR = 7,
        HIGHCARD = 8
    };
private:
    // Our vector container of cards. 
    std::vector<Card> m_vHand;

    // When comparing cards of same CATEGORY in event of a tie, store the
    // unique cards of the hand that do not repeat here, and perform comparison.
    // Ex: CATEGORY: TWOPAIR HandA: { 10, 10, 7, 7, 3 } HandB: { 10, 10, 7, 7, 2}
    // HandA.UniqueCards = {10, 7, 3} HandB.UniqueCards = { 10, 7, 2}
    std::vector<Card> m_vUniqueCards;
    std::map<int, int> m_mPairMap;  // key = CardValue (A, 1, 2, 3, etc...) value = # of key in hand
    std::map<RANK, int> m_mRankMap; // key = Card::RANK, value = # of Card::RANK in hand

    //std::map<Card, int> m_HandMap; // Card.Rank(), count in hand

    int m_iValue; // Value of the hand in total (sum of cards based on CATEGORY)
    int m_iSize;  // The size of our hand 
    int m_iAceCounter;

    // Used by Dealer
    bool m_bAllSuitsMatch;
    bool m_bIsSequential;
    bool m_bHasKing;
    CATEGORY m_eCategory;

public:
    // Constructor
    Hand();
    // Destructor
    ~Hand();
    // Reset hand for next game
    void Reset();

    /*  Name: Hand(int size)
        Param: int
        Return: void
        Info: Override constructor to set a hand with a new size
    */
    Hand(int size);

    // Class Functions //

    /*  Name: SortHand()
        Param: void
        Return: void
        Info: Sort our vector container from High to Low based upon the CARD's value
    */
    void SortHandHighLow();

    /*  Name: SortHand()
        Param: veector<Card> *c
        Return: void
        Info: Sort our vector container from High to Low based upon the CARD's value
    */
    void SortHandHighLow(std::shared_ptr<std::vector<Card>> c);

    /*  Name: SwapCards()
        Param: Void
        Return: void
        Info: Help function Swap cards, used in SortHandHighLow()
        This is a simple bubble/swap sort function, we can look to using merge sort if our hands
        do become larger
    */
    void SwapCards(int pos1, int pos2);

    /*  Name: SwapCards()
        Param: Void
        Return: void
        Info: Help function Swap cards, used in SortHandHighLow()
        This is a simple bubble/swap sort function, we can look to using merge sort if our hands
        do become larger
    */
    void SwapCards(std::shared_ptr<std::vector<Card>> c, int pos1, int pos2);

    /*  Name: AddToHand(Card *c)
        Param: Card
        Return: void
        Info: Add into the hand a SINGLE card, called by our Dealer when they get a card from the deck.
    */
    void AddToHand(std::shared_ptr<Card> c);
    
    /*  Name: AddToHand(vector<Card> *c)
        Param: std::vector<Card>
        Return: void
        Info: Add into the hand a VECTOR of cards, called by our Dealer when they get a card from the deck.
    */
    void AddToHand(std::shared_ptr<std::vector<Card>> c);
    
    // SET METHODS //

    /*  Name: SetSize(int)
        Param: int
        Return: void
        Info: Set the size of our hand; m_iSize value
    */
    void SetSize(int size);

    /*  Name: SetValue(int)
        Param: int
        Return: void
        Info: Set the hand's value of the sum of our cards
    */
    void SetValue(int value);

    /*  Name: SetCategory(CATEGORY c)
        Param: CATEGORY
        Return: void
        Info: Set the current hand's CATEGORY enum
    */
    void SetCategory(CATEGORY c);

    /*  Name: SetIsSequential(bool)
        Param: Bool
        Return: void
        Info: Set if the Hand is in Sequential order
    */
    void SetIsSequential(bool isInSequence);
    
    /*  Name: SetAllSuitsMatch(bool)
        Param: bool
        Return: void
        Info: Set if the hand has all Matching suits
    */
    void SetAllSuitsMatch(bool isAllMatch);

    /*  Name: SetHand(vector<Card> *c)
        Param: vector<Card>*
        Return: void
        Info: Set the hand to the vector being passed
    */
    void SetHand(std::shared_ptr<std::vector<Card>> c);

    // GET METHODS //

    /*  Name: GetSize()
        Param: void
        Return: int
        Info: Return the size of our hand
    */
    int GetSize();

    /*  Name: GetValue()
        Param: void
        Return: int
        Info: Return the hand's total value 
    */
    int GetValue();

    /*  Name: GetHand()
        Param: void
        Return: std::Vector<Card> *c
        Info: Returns a pointer to the m_vHand member
    */
    std::shared_ptr<std::vector<Card>> GetHand();

    /*  Name: GetCategory()
        Param: void
        Return: CATEGORY
        Info: Return our currrent CATEGORY
    */
    CATEGORY GetCategory();

    /*  Name: GetIsSequential()
        Param: void
        Return: Bool
        Info: Return value of m_bIsSequential
    */
    bool GetIsSequential();

    /*  Name: GeetAllSuitsMatch()
        Param: void
        Return: bool
        Info: Return m_bAllSuitsMatch variable
    */
    bool GetAllSuitsMatch();

    /*  Name: GetPairMap()
        Param: void
        Return: pointer to map<int,int>
        Info; Retrive our map, and give to the dealer
    */
    std::map<int, int>* GetPairMap();

    /*  Name: GetPairMap()
        Param: void
        Return: pointer to map<int,int>
        Info; Retrive our map, and give to the dealer
    */
    std::map<RANK, int>* GetRankMap();

    /*  Name: GetAceCounter;
        Param: void
        Return: void
        Info: Return the aceCounter (ace count in hand)
    */
    int GetAceCounter();

    // CLASS FUNCTIONS //

    /*  Name: EvaluateValue();
        Param: void
        Return: void
        Info: Evaluate the card's Value 
    */
    void EvaluateValue();

    /*  Name: ReplaceHand()
        Param: void
        Return: void
        Info: Replaces hand entirely with new random cards
    */
    void ReplaceHand(std::vector<Card> *newHand);

    /*  Name: EvaluateSequence()
        Param: void
        Return: bool
        Info: Evaluate if our hand is sequential
    */
    bool EvaluateSequence();

    /*  Name: EvaluateCategory(vector<Card> *c)
        Param: std::vector<Card> *c
        Return: CATEGORY
        Info: Evaluate this container of cards and determine
        which CATEGORY the cards rank as. 
    */
    void EvaluateCategory();

    /*  Name: FindUniqueCards(std::vector<Card> *c)
        Param: vector<Card>*
        Return: vector<Card>*
        Info: Find the unique cards of a Hand, return values to the Dealer,
        where we decide which player wins in event of a tie.
    */
    void FindUniqueCards();

    /*  Name: EvaluateSuit(std::vector<Card> *c)
        Param: vector<Card>*
        Return: bool
        Info: Determine if the hand has a matching Suit
    */
    bool IsMatchingSuit();

    /*  Name: FillPairMap()
        Param: void
        Return: void
        Info: Use m_mPairMap and find the count of cards and card values in our hand
    */
    void FillPairMap();

    void PrintHand();

    void PrintCategory();
};