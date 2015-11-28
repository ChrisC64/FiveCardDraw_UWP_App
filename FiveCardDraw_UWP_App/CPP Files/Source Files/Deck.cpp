#pragma once
#include "pch.h"
#include "CPP Files\Header Files\Deck.h"

Deck::Deck() : m_iDeckSize(52),
m_iDeckPosition(0),
m_bSrandCalled(false)
{
    // ACE
    m_vListOfCards.push_back(CARD_A_H);
    m_vListOfCards.push_back(CARD_A_D);
    m_vListOfCards.push_back(CARD_A_C);
    m_vListOfCards.push_back(CARD_A_S);
    // TWO
    m_vListOfCards.push_back(CARD_TWO_H);
    m_vListOfCards.push_back(CARD_TWO_D);
    m_vListOfCards.push_back(CARD_TWO_C);
    m_vListOfCards.push_back(CARD_TWO_S);
    // THRE
    m_vListOfCards.push_back(CARD_THREE_H);
    m_vListOfCards.push_back(CARD_THREE_D);
    m_vListOfCards.push_back(CARD_THREE_C);
    m_vListOfCards.push_back(CARD_THREE_S);
    // FOUR
    m_vListOfCards.push_back(CARD_FOUR_H);
    m_vListOfCards.push_back(CARD_FOUR_D);
    m_vListOfCards.push_back(CARD_FOUR_C);
    m_vListOfCards.push_back(CARD_FOUR_S);
    // FIVE
    m_vListOfCards.push_back(CARD_FIVE_H);
    m_vListOfCards.push_back(CARD_FIVE_D);
    m_vListOfCards.push_back(CARD_FIVE_C);
    m_vListOfCards.push_back(CARD_FIVE_S);
    // SIX
    m_vListOfCards.push_back(CARD_SIX_H);
    m_vListOfCards.push_back(CARD_SIX_D);
    m_vListOfCards.push_back(CARD_SIX_C);
    m_vListOfCards.push_back(CARD_SIX_S);
    // SEVEN
    m_vListOfCards.push_back(CARD_SEVEN_H);
    m_vListOfCards.push_back(CARD_SEVEN_D);
    m_vListOfCards.push_back(CARD_SEVEN_C);
    m_vListOfCards.push_back(CARD_SEVEN_S);
    // EIGHT
    m_vListOfCards.push_back(CARD_EIGHT_H);
    m_vListOfCards.push_back(CARD_EIGHT_D);
    m_vListOfCards.push_back(CARD_EIGHT_C);
    m_vListOfCards.push_back(CARD_EIGHT_S);
    // NINE
    m_vListOfCards.push_back(CARD_NINE_H);
    m_vListOfCards.push_back(CARD_NINE_D);
    m_vListOfCards.push_back(CARD_NINE_C);
    m_vListOfCards.push_back(CARD_NINE_S);
    // TEN
    m_vListOfCards.push_back(CARD_TEN_H);
    m_vListOfCards.push_back(CARD_TEN_D);
    m_vListOfCards.push_back(CARD_TEN_C);
    m_vListOfCards.push_back(CARD_TEN_S);
    // JACK
    m_vListOfCards.push_back(CARD_JACK_H);
    m_vListOfCards.push_back(CARD_JACK_D);
    m_vListOfCards.push_back(CARD_JACK_C);
    m_vListOfCards.push_back(CARD_JACK_S);
    // QUEEN
    m_vListOfCards.push_back(CARD_QUEEN_H);
    m_vListOfCards.push_back(CARD_QUEEN_D);
    m_vListOfCards.push_back(CARD_QUEEN_C);
    m_vListOfCards.push_back(CARD_QUEEN_S);
    // KING
    m_vListOfCards.push_back(CARD_KING_H);
    m_vListOfCards.push_back(CARD_KING_D);
    m_vListOfCards.push_back(CARD_KING_C);
    m_vListOfCards.push_back(CARD_KING_S);

    m_vPlayDeck.resize(1);
}

Deck::~Deck()
{
}

Deck::Deck(int size)
{
    // Not yet implemented; Considering to make this "number of decks" instead of the actual decks size.
}

// SET METHODS //
void Deck::SetDeckSize(int size)
{
    m_iDeckSize = size;
}

// GET METHODS //
int Deck::GetDeckSize()
{
    return m_iDeckSize;
}

// CLASS FUNCTIONS

void Deck::ShuffleDeck()
{
    // PlayDeck is shuffled, so that all cards are randomly assigned again, when we DrawCard()


}

Card Deck::DrawCard()
{
    // Generate a random number
    int randNum = RandomNumber(0, m_vListOfCards.size() - 1);
    static int count = 0;
    // Check if our "usedCards" array contains this value
    if (!UsedCard(randNum))
    {
        // If it is not used, return the card from this position
        return m_vListOfCards.at(randNum);
    }
    else
    {
        // If it is being used, DrawCard()
        count++; 
        if (count < 5)
        {
            Card newCard = DrawCard();
            count = 0;
            return newCard;
        }
    }
    // If no card can be drawn that isn't the same in 5 attempts
    // Give the player the last created card
    return m_vListOfCards.at(RandomNumber(0, m_vListOfCards.size() - 1));
    
}

// When a card is drawn, increment counter, when we recharge the deck, reset counter
void Deck::UpdateDeckPosition(bool isDrawingCard)
{
    if (isDrawingCard && m_iDeckPosition < m_vPlayDeck.size())
    {
        m_iDeckPosition++;
    }
    else
    {
        m_iDeckPosition = 0;
    }
}

void Deck::SetPlayDeck()
{
}

int Deck::RandomNumber(int low, int high)
{
    if (!m_bSrandCalled)
    {
        srand(time(NULL));
        m_bSrandCalled = true;
    }

    return (int)rand() % (low - high) + 1;
}

bool Deck::UsedCard(int value)
{
    if (m_vPlayDeck.empty())
    {
        m_vPlayDeck.push_back(value);
        return false;
    }
    // Iterate through our vector and see if we have the value already stored in our array.
    if (std::find(m_vPlayDeck.begin(), m_vPlayDeck.end(), value) != m_vPlayDeck.end())
    {
        return true;
    }
    else
    {
        // Add to our list and move on
        //printf_s("Card not used!\n");
        m_vPlayDeck.push_back(value);
        return false;

    }
}

