#ifndef PLAYER_H
#define PLAYER_H

#include "Hand.h"
#include "pch.h"

class Player : public Hand // TODO: Why am I inheriting hand? I shouldn't need this... 
{
private:
    int m_iWins;
    int m_iLoss;
    int m_iTies;

    bool m_bHasWinningHand;
    bool m_bAllSuitsMatch;
    bool m_bHandIsSequential;
    // Name
    std::string m_sName;

    // Player's hand
    std::shared_ptr<Hand> m_pHand;

    // Player's unique cards in hand
    std::shared_ptr<std::vector<Card>> m_vUniqueCards;

public:
    Player();
    ~Player();

    Player(std::string name);
    // Reset after each round
    void Reset();

    // SET METHODS //

    void SetWins(int w);
    void SetLoss(int l);
    void SetTies(int t);
    void SetName(std::string name);
    void SetHasWinningHand(bool isWinning);
    void SetUniqueCards(std::shared_ptr<std::vector<Card>> c);
    void SetUniqueCardSize(int size);
    void SetCategory(Hand::CATEGORY eCat);
    void SetHandIsSequential(bool isSequence);
    void SetHand(std::shared_ptr<std::vector<Card>> c);
    // GET METHODS //

    int GetWins();
    int GetLoss();
    int GetTies();
    int GetUniuqeCardSize();
    int GetAceCounter();
    int GetValue();

    std::string GetName();
    
    bool GetHasWinningHand();
    bool GetHandIsSequential();

    CATEGORY GetCategory();
    Card GetUniqueCard(int pos);
    
    std::shared_ptr<std::vector<Card>> GetUniqueCard();
    std::shared_ptr<std::vector<Card>> GetHand();

    std::map<int, int>* GetPairMap();
    std::map<RANK, int>* GetRankMap();
    
    // CLASS FUNCTIONS

    /*  Name: AddWin()
        Param: Void
        Return: Void
        Info: Increment win by 1
    */
    void AddWin();

    /*  Name: AddLoss()
        Param: Void
        Return: Void
        Info: Increment loss by 1
    */
    void AddLoss();

    /*  Name: AddTie()
        Param: Void
        Return: Void
        Info: Increment tie by 1
    */
    void AddTie();

    /*  Name: Input(char input)
        Param: char
        Return: void
        Info: Handler to input; should lead to the World/Input class
    */
    void Input(char *input);

    /*  Name: EvaluateHand();
        Param: void
        Return: void
        Info: Sets the hand's Category, by evaluating based on the cards.
    */
    void EvaluateHand(std::shared_ptr<std::vector<Card>> c); // Pass class object here in param

    /*  Name: AddCardToHand(Card *c)
        Param: Card object
        Return Void
        Info: Add a card to your hand
    */
    void AddCardTohand(std::shared_ptr<Card> c);

    /*  Name: AddHand(std::vector<Card*> *c)
        Param: vector<Card*>
        Return: void
        Info: An override method to add a hand by instead passing over a
        vector by reference.
    */
    void AddToHand(std::shared_ptr<std::vector<Card>> c);

    /*  Name: FindUniqueCards()
        Param: std::vector<Card> *c
        Return: std::vector<Card>*
        Info: Returns the unique cards to your hand
    */
    void FindUniqueCards();

    /*  Name: IsMatchingSuit(std::vector<Card> *c)
        Param: vector<Card>*
        Return: bool
        Info: Stub for checking if all card's in Player's hand is matching SUIT
    */
    bool IsMatchingSuit();

    /*  Name: EvaluateCategory(std::vector<Card> *c)
        Param: vector<Card>*
        Return: CATEGORY
        Info: Find the Category of the given hand 
    */
    void EvaluateCategory();

    /*  Name: EvaluateSequence()
        Param: void
        Return: bool
        Info: Evaluate the hand's sequence, determine if it is in order
    */
    bool EvaluateSequence();

    /*  Name: EvaluateValue()
        Param: void
        Return: void
        Info: Evaluate hand's value
    */
    void EvaluateValue();

    void PrintHand();

    void PrintCategory();

};


#endif PLAYER_H