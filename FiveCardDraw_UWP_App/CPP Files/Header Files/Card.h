#pragma once
/*  Christopher Carlos
    Date: 9/25/2014
    Info: This class is a playing Card class, used in our game. It will be created via the 
    Deck class. Hand inherits this class and create
*/
#include "pch.h"
class Card
{
protected:
    enum RANK
    {
        JOKER   = 0,
        ACE     = 1,
        TWO     = 2,
        THREE   = 3,
        FOUR    = 4,
        FIVE    = 5, 
        SIX     = 6,
        SEVEN   = 7,
        EIGHT   = 8,
        NINE    = 9,
        TEN     = 10,
        JACK    = 11,
        QUEEN   = 12,
        KING    = 13,
    };

    enum COLOR
    {
        RED = 0,
        BLACK
    };

    enum SUIT
    {
        HEART = 0,
        DIAMOND,
        CLUB,
        SPADE
    };
private: 
    RANK m_eRank;
    COLOR m_eColor;
    SUIT m_eSuit;
    // the Face Value of a card will range from 1-13. J - K = 11, 12, 13
    int  m_iFaceValue;  
public:

    // Constructor and Destructor
    Card();
    ~Card();

    /*  Name: Card() 
        Param: int, string
        Return: void - Constructs card
        Info: This is an override Constructor class. Set the face value according to the enum RANK value (A = 1, TWO = 2, .. QUEEN 12, KING 13).
        Color will be assigned based on SUIT. RED = { DIAMOND, HEARTS } and BLACK = {CLUBS , SPADE }
    */
    Card(int faceValue, std::string suit);

    // SET METHODS //

    /*  Name : SetRank(int rank)
        Param: Int
        Return: Void
        Info: Sets the card's m_eRank. RANK will be assigned based on int value passed. This class should only be called by Deck to set up the cards.
    */
    void SetRank(int rank);

    /*  Name: SetColor(bool isRed)
        Param: bool
        Return: Void
        Info: Sets cards color. Should be called within the class, when the card's SetSuit() is called. 
    */
    void SetColor(bool isRed);

    /*  Name: SetSuit(std::string suit)
        Param: std::string
        Return: Void
        Info: Sets the Card's Suit. Color will also be set after Suit is determined. Red = { Diamond, Hearts} Black = { Club, Spade }
    */
    void SetSuit(std::string suit);

    // GET METHODS //

    /*  Name: GetRank()
        Param: void
        Return: RANK
        Info: Returns RANK enum 
    */
    RANK GetRank();

    /*  Name: GetCardValue()
        Param: void
        Return: int
        Info: Returns int value of the RANK cards (Used for helping HAND class figure out total value of cards.
    */
    int GetCardValue();

    /*  Name: GetColor
        Param: void
        Return: COLOR
        Info: Returns color enum
    */
    COLOR GetColor();

    /*  Name: GetSuit()
        Param: void
        Return: SUIT
        Info: Returns SUIT of the card
    */
    SUIT GetSuit();

    /*  Name: PrintRank()
        Param: void
        Return: void
        Info: Print Card's Rank (Ex: Ace, 1, 2, 3, ... Jack, Queen, King) for display purposed on the Console
    */
    void PrintRank();

    /*  Name: PrintSuit()
        Param: void
        Return: void
        Info: Print the card's first letter of the suit (D, C, S, H)
    */
    void PrintSuit();

    /*  Name: PrintColor()
        Param: void
        Return: void
        Info: Print the card's color (R/B)
    */
    void PrintColor();

    /*  Name: PrintCard()
        Param: void
        Return: void
        Info: Print out the card's information
    */
    void PrintCard();


};
