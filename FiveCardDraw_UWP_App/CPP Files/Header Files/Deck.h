#pragma once

#include "Card.h"
#include "CardList.h"
#include "pch.h"

class Deck : public Card
{
private:
    int m_iDeckSize;
    int m_iDeckPosition;

    bool m_bSrandCalled;
    // Vector container of cards used
    std::vector<int> m_vPlayDeck;

    // Vector container of available cards to use
    std::vector<Card> m_vListOfCards;

public:

    // Constructor and Destructor
    Deck();
    ~Deck();

    // Overloaded Constructor
    Deck(int size);

    // SET METHODS //
    void SetDeckSize(int size);

    // GET METHODS //
    int GetDeckSize();

    // CLASS FUNCTIONS // 

    /*  Name: ShuffleDeck()
        Param: Void
        Return: Void
        Info: Here we shuffle our deck.
    */
    void ShuffleDeck();

    /*  Name: DrawCard();
        Param: Void
        Return: Card
        Info: Returns a card from our container. 
    */
    Card DrawCard();

    /*  Name: UpdateDeckPosition(bool drawCard)
        Param: bool
        Return: Void
        Info: When we draw a card, we update position by incrementing. When we Recharge the Deck, we reset
        the counter back to 0.
    */
    void UpdateDeckPosition(bool isDrawingCard);

    /*  Name: SetPlayDeck()
        Param: void
        Return: void
        Info: Set up our playing deck. A random array (randArr) with integer values will be created, this integer
        will contain numbers 0 - m_iDeckSize - 1. When we crreate the array, we then go and 
        iterate through our m_vCardList to assign m_vPlayDeck the cards randArr[pos]
    */
    void SetPlayDeck();

    /*  Name: RandomNumer
        Param: int, int
        Return: int
        Info: Generate a random number between low and max
    */
    int RandomNumber(int low, int max);

    /*  Name: PlayDeckDuplicateCheck()
        Param: void
        Return: bool
        Info: Check if there are duplicate cards in the deck
    */
    bool UsedCard(int value);
};