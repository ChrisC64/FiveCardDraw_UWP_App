#include "pch.h"
#include "CPP Files\Header Files\Hand.h"

Hand::Hand() : m_iSize(5),
m_iValue(0),
m_iAceCounter(0),
m_eCategory(CATEGORY::HIGHCARD),
m_bAllSuitsMatch(false),
m_bIsSequential(false),
m_vUniqueCards(),
m_vHand()
{
    //m_vHand.resize(1);
}

Hand::~Hand()
{
}

Hand::Hand(int size) : m_iValue(0),
m_eCategory(CATEGORY::HIGHCARD),
m_bAllSuitsMatch(false),
m_bIsSequential(false)
{
    // Set variables
    SetSize(size);
}

void Hand::Reset()
{
    m_iSize = 5;
    m_iValue = 0;
    m_iAceCounter = 0;
    m_eCategory = CATEGORY::HIGHCARD;
    m_bAllSuitsMatch = false;
    m_bIsSequential = false;
    m_vUniqueCards.clear();
    m_vHand.clear();
    m_mPairMap.clear();
    m_mRankMap.clear();
}

// SET METHODS // 

void Hand::SetSize(int size)
{
    m_iSize = size;
    // Resize the vector
    m_vHand.resize(m_iSize, Card(5, "Club"));
}

void Hand::SetValue(int value)
{
    m_iValue = value;
}

void Hand::SetCategory(CATEGORY c)
{
    m_eCategory = c;
}

void Hand::SetAllSuitsMatch(bool isAllMatching)
{
    m_bAllSuitsMatch = isAllMatching;
}

void Hand::SetIsSequential(bool isSequential)
{
    m_bIsSequential = isSequential;
}

void Hand::SetHand(std::shared_ptr<std::vector<Card>> c)
{
    AddToHand(c);
}

// GET METHODS //

int Hand::GetSize()
{
    return m_vHand.size();
}

int Hand::GetValue()
{
    return m_iValue;
}

Hand::CATEGORY Hand::GetCategory()
{
    return m_eCategory;
}

bool Hand::GetIsSequential()
{
    return m_bIsSequential;
}

bool Hand::GetAllSuitsMatch()
{
    return m_bAllSuitsMatch;
}

std::shared_ptr<std::vector<Card>> Hand::GetHand()
{
    return std::make_shared<std::vector<Card>>(m_vHand);
}

std::map<int, int>* Hand::GetPairMap()
{
    return &m_mPairMap;
}

std::map<Card::RANK, int>* Hand::GetRankMap()
{
    return &m_mRankMap;
}

int Hand::GetAceCounter()
{
    return m_iAceCounter;
}
// CLASS FUNCTIONS

void Hand::PrintHand()
{
    for (auto it = m_vHand.begin(); it != m_vHand.end(); ++it)
    {
        std::cout << "[ "; (*it).PrintRank(); (*it).PrintSuit(); 
        std::cout << " "; (*it).PrintColor(); std::cout  << " ] ";
    }
}

void Hand::PrintCategory()
{
    switch (m_eCategory)
    {
        case SFLUSH:
            std::cout << "STRAIGHT FLUSH";
            break;
        case FOAK:
            std::cout << "FOUR OF A KIND";
            break;
        case FULLHOUSE:
            std::cout << "FULL HOUSE";
            break;
        case STRAIGHT:
            std::cout << "STRAIGHT";
            break;
        case TOAK:
            std::cout << "THREE OF A KIND";
            break;
        case TWOPAIR:
            std::cout << "TWO PAIR";
            break;
        case ONEPAIR:
            std::cout << "ONE PAIR";
            break;
        case HIGHCARD:
            std::cout << "HIGHCARD";
            break;
    }
}

// Sort the Hand's cards from Highest Value to Lowest Value based on the Card.GetCardValue()
void Hand::SortHandHighLow()
{
    if (m_vHand.empty())
    {
        printf_s("m_vHand is empty! Cannot sort the hand high to low");
        return;
    }

    // Iterate throught the card's hand
    bool swapped;
    do
    {
        swapped = false;
        for (unsigned int i = 0; i < m_vHand.size() - 1; ++i)
        {
            if (m_vHand.at(i).GetCardValue() < m_vHand.at(i + 1).GetCardValue())
            {
                SwapCards( i, i + 1);
                swapped = true;
            }
            else
            {
                // Do nothing here
            }
        }
    } while (swapped);

}

// OVERRIDE 
void Hand::SortHandHighLow(std::shared_ptr<std::vector<Card>> c)
{
    if (c->empty())
    {
        printf_s("Passing a null/void vector! Cannot sort the hand high to low");
        return;
    }
    // Iterate throught the card's hand
    bool swapped;
    do
    {
        swapped = false;
        for (unsigned int i = 0; i < c->size() - 1; ++i)
        {
            if (c->at(i).GetCardValue() < c->at(i + 1).GetCardValue())
            {
                SwapCards(c, i, i + 1);
                swapped = true;
            }
            else
            {
                // Do nothing here
            }
        }
    } while (swapped);

}

void Hand::SwapCards(int pos1, int pos2)
{
    // Create temp
    std::vector<Card> temp;

    // Store value of pos2 in temp vec: temp[POS2], HAND[POS1, POS2]
    temp.push_back(m_vHand.at(pos2));

    // Now take value of pos1 and place into pos2 of vector: temp[POS2], HAND[POS1, POS1]
    m_vHand.at(pos2) = m_vHand.at(pos1);

    // Transfer back temp into position 1: temp[POS2], HAND[POS2, POS1]
    m_vHand.at(pos1) = temp.at(0);
}

// OVERRIDE
void Hand::SwapCards(std::shared_ptr<std::vector<Card>> c, int pos1, int pos2)
{
    // Create temp
    std::vector<Card> temp;

    // Store value of pos2 in temp vec: temp[POS2], HAND[POS1, POS2]
    temp.push_back(c->at(pos2));

    // Now take value of pos1 and place into pos2 of vector: temp[POS2], HAND[POS1, POS1]
    c->at(pos2) = c->at(pos1);

    // Transfer back temp into position 1: temp[POS2], HAND[POS2, POS1]
    c->at(pos1) = temp.at(0);
}

// ADDTOHAND() and OVERRIDES 

void Hand::AddToHand(std::shared_ptr<Card> c)
{
    m_vHand.push_back(*c);
}

void Hand::AddToHand(std::shared_ptr<std::vector<Card>> c)
{
    // Resize hand to size of C
    SetSize(c->size());
    // Check needs to make sure we aren't going over hand size of the game
    for (unsigned int i = 0; i < c->size(); ++i)
    {
        m_vHand.at(i) = c->at(i);
    }
}

// This function will be used for determining a winner based on 2 or more hands
// with the same winning Category. (Straight Flush, Flush, etc)
void Hand::EvaluateValue()
{
    
    if (m_iValue == 0)
    {
        printf_s("Warning: m_iValue == 0, and we are trying to evaluateValue()");
    }

    //// Evaluate card based on category of the hand
    switch (m_eCategory)
    {
        case SFLUSH: // {A, K, Q, J, 10 }
            if (m_bHasKing && m_iAceCounter == 1)
            {
                m_iValue += 13;  // ACE = 1 by default, add 13 to make it 14, highest card value
            }
            break;
        case FOAK: // {A, A, A, A, 2} OR {2, 2, 2, 2, A}
            // if Four of a kind AND aceCounter == 1, m_iValue = 14
            if (m_iAceCounter == 1)
            {
                m_iValue = 14;
            }
            else
            {
                m_iValue = 0;
                for (auto pm = m_mPairMap.begin(); pm != m_mPairMap.end(); ++pm)
                {
                    if (pm->second == 1)
                    {
                        m_iValue = (*pm).first;
                    }
                }
            }
            break;
        case FULLHOUSE: // {A, A, A, 2, 2} OR {2, 2, 2, A, A}
            if (m_iAceCounter == 2)
            {
                m_iValue = 14 * 2;
            }
            else
            {
                m_iValue = 0;
                for (auto pm = m_mPairMap.begin(); pm != m_mPairMap.end(); ++pm)
                {
                    if (pm->second == 2)
                    {
                        m_iValue = (*pm).first;
                    }
                }
            }
            break;
        case STRAIGHT:
            if (m_bHasKing && m_iAceCounter == 1)
            {
                m_iValue += 13;
            }
            break;
        case TOAK: // {A, A, A, 10, 2} OR {2, 2, 2, A, 10 } 
            // If have an ACE, add up value then add 14
            m_iValue = 0;
            for (auto pm = m_mPairMap.begin(); pm != m_mPairMap.end(); ++pm)
            {
                if ((*pm).second == 1)
                {
                    m_iValue += (*pm).first;
                }
            }
            if (m_iAceCounter == 1)
            {
                m_iValue += 13;
            }
            break;
        case TWOPAIR: // {A, A, 4, 4, 10} or { 3, 3, 8, 8, A}
            m_iValue = 0;
            if (m_iAceCounter == 1)
            {
                m_iValue = 14;
            }
            else
            {
                for (auto pm = m_mPairMap.begin(); pm != m_mPairMap.end(); ++pm)
                {
                    if (pm->second == 1)
                    {
                        m_iValue = pm->first;
                    }
                }
            }
            break;
        case ONEPAIR:
            m_iValue = 0;
            for (auto pm = m_mPairMap.begin(); pm != m_mPairMap.end(); ++pm)
            {
                if ((*pm).second == 1)
                {
                    m_iValue += (*pm).first;
                }
            }
            if (m_iAceCounter == 1)
            {
                m_iValue += 13;
            }
            break;
        case HIGHCARD:
            // m_iValue should already be added, just ad 13 to make ace the high card
            if (m_iAceCounter == 1)
            {
                m_iValue -= 1;
            }
            break;
    }
}

bool Hand::EvaluateSequence()
{
    // Iterate throught he container of cards, determine if the actual cards are
    bool bIsRisingOrder; // If N[x+1] == N[x] + 1 we are rising order
    if (m_vHand.empty())
    {
        printf_s("Cannot evaluate sequence on an empty hand!");
        return false;
    }

    if (m_vHand.at(1).GetCardValue() == m_vHand.at(0).GetCardValue() + 1)
    {
        bIsRisingOrder = true;
    }
    else
    {
        bIsRisingOrder = false;
    }
    // in Sequence where N[x] and N[x+1] == N[x] + 1 / N[x] - 1 
    for (unsigned int i = 1; i < m_vHand.size() - 1; i++)
    {
        if (bIsRisingOrder)
        {
            if (m_vHand.at(i + 1).GetCardValue() == m_vHand.at(i).GetCardValue() + 1)
            {
                // Keep going
            }
            else if ((i + 1 == m_vHand.size() - 1) && m_vHand.at(i + 1).GetRank() == Card::RANK::ACE) // Check if we're at the last position, ACE is lowest value
            {
                // Check if King is the first card
                if (m_vHand.at(0).GetRank() == Card::RANK::KING)
                {
                    // Ace hand is ok, we have sequence
                    m_bIsSequential = true;
                    return m_bIsSequential;
                }
            }
            else
            {
                m_bIsSequential = false;
                return m_bIsSequential; // Order is none sequential
            }
        }
        else // Not rising, descending order
        {
            if (m_vHand.at(i + 1).GetCardValue() == m_vHand.at(i).GetCardValue() - 1)
            {
                // Keep going
            }
            else if ((i + 1 == m_vHand.size() - 1) && m_vHand.at(i + 1).GetRank() == Card::RANK::ACE)
            {
                if (m_vHand.at(0).GetRank() == Card::RANK::KING)
                {
                    m_bIsSequential = true;
                    return m_bIsSequential;
                }
            }
            else
            {
                m_bIsSequential = false;
                return m_bIsSequential;
            }

        }
    }
    //return true;
}

// Evaluate the Hand's Category

void Hand::EvaluateCategory()
{
    // Find Unique Pairs
    FillPairMap();
 
    // Check if High Pair First
    switch (m_mPairMap.size())
    {
        case 5:
            // If Sequential
            if (m_bIsSequential)
            {
                // Do all suits Match?
                if (m_bAllSuitsMatch)
                {
                    // SFLUSH
                    m_eCategory = SFLUSH;
                }
                else
                {
                    // STRAIGHT
                    m_eCategory = STRAIGHT;
                }
            }
            else if (m_bAllSuitsMatch)
            {
                // FLUSH
                m_eCategory = FLUSH;
            }
            else
            {
                m_eCategory = HIGHCARD;
            }
            break;
        case 4:
            // {2, 1, 1, 1}
            m_eCategory = CATEGORY::ONEPAIR;
            break;
        case 3: // Either a TWOPAIR {x, x, a, b, c } or TOAK {x, x, x, a, b}
            // Look for 2, if we find a 2 value, we have a TWOPAIR
            for (auto it = m_mPairMap.begin(); it != m_mPairMap.end(); ++it)
            {
                if ((*it).second == 2)
                {
                    m_eCategory = TWOPAIR;
                    break;
                }
                else if ((*it).second == 3)
                {
                    m_eCategory = TOAK;
                    break;
                }
            }
            break;
        case 2: // FOAK = {4, 1} and FULLHOUSE { 3, 2} 
            // look for 3 || 2 or 4 || 1 in hand
            for (auto it = m_mPairMap.begin(); it != m_mPairMap.end(); ++it)
            {
                if ((*it).second == 4 || (*it).second == 1)
                {
                    m_eCategory = FOAK;
                    break;
                }
                else if ((*it).second == 3 || (*it).second == 2)
                {
                    m_eCategory = FULLHOUSE;
                    break;
                }
            }
            break;
    }
    
}

void Hand::ReplaceHand(std::vector<Card> *newHand)
{
    // Resize hand to new hand size
    m_vHand.resize(newHand->size());
    // Add contents into our resized hand from new hand
    for (unsigned int i = 0; i < m_vHand.size(); ++i)
    {
        m_vHand.at(i) = newHand->at(i);
    }
}

void Hand::FindUniqueCards()
{
}

bool Hand::IsMatchingSuit()
{
    // iterate through hand and determine if all suits match, if not, return false
    for (int i = 0; i < m_vHand.size() - 1; i++)
    {
        if (m_vHand.at(i).GetSuit() == m_vHand.at(i + 1).GetSuit())
        {

        }
        else
        {
            m_bAllSuitsMatch = false;
            return m_bAllSuitsMatch;
        }
    }
    m_bAllSuitsMatch = true;
    return m_bAllSuitsMatch;
}

void Hand::FillPairMap()
{
    std::map<SUIT, int> suitMap;
    // Count aces in the hand
    m_iAceCounter = 0;
    // Check if Hand has a KING
    m_bHasKing;
    // Find if card hand has KING, ACE, and how Value of our cards
    for (unsigned int i = 0; i < m_vHand.size(); i++)
    {
        if (m_vHand.at(i).GetRank() == RANK::KING)
        {
            m_bHasKing = true;
        }
        else if (m_vHand.at(i).GetRank() == RANK::ACE)
        {
            m_iAceCounter++;
        }
        m_mPairMap[m_vHand.at(i).GetCardValue()] += 1;
        m_mRankMap[m_vHand.at(i).GetRank()] += 1;
        suitMap[m_vHand.at(i).GetSuit()] += 1;
        // Add the values of the card as we iterate over them
        m_iValue += m_vHand.at(i).GetCardValue();
    }
    if (suitMap.size() == 1)
    {
        m_bAllSuitsMatch = true;
    }

}