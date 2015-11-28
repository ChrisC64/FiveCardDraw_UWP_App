#include "pch.h"
#include "CPP Files\Header Files\Card.h"

Card::Card() : m_eRank(RANK::ACE),
m_eSuit(SUIT::CLUB),
m_eColor(COLOR::BLACK),
m_iFaceValue(1)
{ 
}

Card::~Card()
{
}

Card::Card(int faceValue, std::string suit)
{
    SetRank(faceValue);
    SetSuit(suit);
}

// SET METHODS //
void Card::SetRank(int rank)
{
    // Set m_iFaceValue based upon "rank", and RANK as well. (A == 1 ... K == 13)
    switch (rank)
    {
        case 1:
            m_iFaceValue = rank;
            m_eRank = RANK::ACE;
            break;
        case 2:
            m_iFaceValue = rank;
            m_eRank = RANK::TWO;
            break;
        case 3:
            m_iFaceValue = rank;
            m_eRank = RANK::THREE;
            break;
        case 4:
            m_iFaceValue = rank;
            m_eRank = RANK::FOUR;
            break;
        case 5:
            m_iFaceValue = rank;
            m_eRank = RANK::FIVE;
            break;
        case 6:
            m_iFaceValue = rank;
            m_eRank = RANK::SIX;
            break;
        case 7:
            m_iFaceValue = rank;
            m_eRank = RANK::SEVEN;
            break;
        case 8:
            m_iFaceValue = rank;
            m_eRank = RANK::EIGHT;
            break;
        case 9:
            m_iFaceValue = rank;
            m_eRank = RANK::NINE;
            break;
        case 10:
            m_iFaceValue = rank;
            m_eRank = RANK::TEN;
            break;
        case 11:
            m_iFaceValue = rank;
            m_eRank = RANK::JACK;
            break;
        case 12:
            m_iFaceValue = rank;
            m_eRank = RANK::QUEEN;
            break;
        case 13:
            m_iFaceValue = rank;
            m_eRank = RANK::KING;
            break;
        default:
            m_iFaceValue = 1;
            m_eRank = RANK::ACE;
            // Throw a message here stating we did not get the appropriate card set up correctly
            printf_s("Card's RANK was not set correctly, rank VALUE: %d", rank);
            break;
    };
}

void Card::SetColor(bool isRed)
{
    if (isRed)
    {
        m_eColor = COLOR::RED;
    }
    else
    {
        m_eColor = COLOR::BLACK;
    }
}

void Card::SetSuit(std::string suit)
{
    // Set suit, the set the color. Red {Diamond, Hearts} and Black {Club, Spade}
    // Convert string into UPPERCASE
    for (unsigned int i = 0; i < suit.length(); i++)
    {
        suit[i] = toupper(suit[i]);
    }
    // Check string and assign suit
    if (suit == "HEART")
    {
        m_eSuit = SUIT::HEART;
        SetColor(true);
    }
    else if (suit == "DIAMOND")
    {
        m_eSuit = SUIT::DIAMOND;
        SetColor(true);
    }
    else if (suit == "CLUB")
    {
        m_eSuit = SUIT::CLUB;
        SetColor(false);
    }
    else if (suit == "SPADE")
    {
        m_eSuit = SUIT::SPADE;
        SetColor(false);
    }
    else
    {
        printf_s("Card SUIT could not be set");
    }
}

// GET METHODS //

Card::RANK Card::GetRank()
{
    return m_eRank;
}

Card::COLOR Card::GetColor()
{
    return m_eColor;
}

Card::SUIT Card::GetSuit()
{
    return m_eSuit;
}

int Card::GetCardValue()
{
    return m_iFaceValue;
}

// PRINT METHODS

void Card::PrintRank()
{
    switch (m_eRank)
    {
        case RANK::ACE:
            std::cout << "A";
            break;
        case RANK::TWO:
            std::cout << "2";
            break;
        case RANK::THREE:
            std::cout << "3";
            break;
        case RANK::FOUR:
            std::cout << "4";
            break;
        case RANK::FIVE:
            std::cout << "5";
            break;
        case RANK::SIX:
            std::cout << "6";
            break;
        case RANK::SEVEN:
            std::cout << "7";
            break;
        case RANK::EIGHT:
            std::cout << "8";
            break;
        case RANK::NINE:
            std::cout << "9";
            break;
        case RANK::TEN:
            std::cout << "10";
            break;
        case RANK::JACK:
            std::cout << "J";
            break;
        case RANK::QUEEN:
            std::cout << "Q";
            break;
        case RANK::KING:
            std::cout << "K";
            break;
        default:
            std::cout << "INV";
            break;
    };
}

void Card::PrintSuit()
{
    switch (m_eSuit)
    {
        case SUIT::CLUB:
            std::cout << "C";
            break;
        case SUIT::DIAMOND:
            std::cout << "D";
            break;
        case SUIT::HEART:
            std::cout << "H";
            break;
        case SUIT::SPADE:
            std::cout << "S";
            break;
        default:
            std::cout << "INV";
            break;
    };
}

void Card::PrintColor()
{
    switch (m_eColor)
    {
        case COLOR::BLACK:
            std::cout << "B";
            break;
        case COLOR::RED:
            std::cout << "R";
            break;
        default:
            std::cout << "INV";
            break;
    };
}

void Card::PrintCard()
{
    // Print out the card: Text Print Sample V = value, C = color, S = suit
    /* -------- (8) spaces
       |-VS---| (5) spaces, (2) |, (1) Char
       |------|
       |----C-|
       -------- (8) spaces
    */
    std::cout << "--------" << std::endl;
    std::cout << "| "; PrintRank(); PrintSuit();  std::cout << "   |" << std::endl;
    std::cout << "|   "; std::cout << "   |" << std::endl;
    std::cout << "|   "; PrintColor(); std::cout << "  |" << std::endl;
    std::cout << "--------" << std::endl;

}