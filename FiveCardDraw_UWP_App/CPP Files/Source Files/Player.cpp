#include "pch.h"
#include "CPP Files\Header Files\Player.h"

Player::Player() : m_iWins(0),
m_iLoss(0),
m_iTies(0),
m_sName("Player"),
m_bHasWinningHand(false),
m_bAllSuitsMatch(false)
{
    m_pHand = std::make_shared<Hand>(Hand());
}

Player::~Player()
{
}

Player::Player(std::string name) : m_iWins(0),
m_iLoss(0),
m_iTies(0),
m_bHasWinningHand(false),
m_bAllSuitsMatch(false)
{
    m_sName = name;
    m_pHand = std::make_shared<Hand>(Hand());
}

void Player::Reset()
{
    // Do not reset score!
    m_bHasWinningHand = false;
    m_bAllSuitsMatch = false;
    m_pHand->Reset();
}

// SET METHODS //

void Player::SetWins(int w)
{
    m_iWins = w;
}

void Player::SetLoss(int l)
{
    m_iLoss = l;
}

void Player::SetTies(int t)
{
    m_iTies = t;
}

void Player::SetName(std::string name)
{
    m_sName = name;
}

void Player::SetHasWinningHand(bool isWinning)
{
    m_bHasWinningHand = isWinning;
}

void Player::SetUniqueCards(std::shared_ptr<std::vector<Card>> c)
{
    if (m_vUniqueCards->empty())
    {
        printf_s("Unique Vector is NULL");
        return;
    }
    // Resize Vector
    m_vUniqueCards->resize(c->size());
    for (unsigned int i = 0; i < c->size(); ++i)
    {
        m_vUniqueCards->at(i) = c->at(i);
    }
}

void Player::SetUniqueCardSize(int size)
{
    if (m_vUniqueCards->empty())
    {
        printf_s("Unique Vector SIZE cannot be set. NULL");
        return;
    }
    m_vUniqueCards->resize(size);
}

void Player::SetHandIsSequential(bool isSequential)
{
    m_bHandIsSequential = isSequential;
}

// GET METHODS //

int Player::GetWins()
{
    return m_iWins;
}

int Player::GetLoss()
{
    return m_iLoss;
}

int Player::GetTies()
{
    return m_iTies;
}

int Player::GetUniuqeCardSize()
{
    return m_vUniqueCards->size();
}

std::string Player::GetName()
{
    return m_sName;
}

bool Player::GetHasWinningHand()
{
    return m_bHasWinningHand;
}

Card Player::GetUniqueCard(int pos)
{
    return m_vUniqueCards->at(pos);
}

std::shared_ptr<std::vector<Card>> Player::GetUniqueCard()
{
    return m_vUniqueCards;
}

bool Player::GetHandIsSequential()
{
    return m_bHandIsSequential;
}

std::shared_ptr<std::vector<Card>> Player::GetHand()
{
    return m_pHand->GetHand();
}

std::map<int, int>* Player::GetPairMap()
{
    return m_pHand->GetPairMap();
}

std::map<Card::RANK, int>* Player::GetRankMap()
{
    return m_pHand->GetRankMap();
}

Hand::CATEGORY Player::GetCategory()
{
    return m_pHand->GetCategory();
}

int Player::GetAceCounter()
{
    return m_pHand->GetAceCounter();
}

int Player::GetValue()
{
    return m_pHand->GetValue();
}
// CLASS FUNCTIONS //

void Player::AddWin()
{
    m_iWins++;
}

void Player::AddLoss()
{
    m_iLoss++;
}

void Player::AddTie()
{
    m_iTies++;
}

void Player::AddCardTohand(std::shared_ptr<Card> c)
{
    m_pHand->AddToHand(c);
}

void Player::Input(char *input)
{
    return;
}

void Player::EvaluateCategory()
{
    m_pHand->EvaluateCategory();
}

void Player::AddToHand(std::shared_ptr<std::vector<Card>> c)
{
    m_pHand->AddToHand(c);
}

void Player::SetCategory(Hand::CATEGORY eCategory)
{
    m_pHand->SetCategory(eCategory);
}

void Player::FindUniqueCards()
{
   m_pHand->FindUniqueCards();
}

bool Player::IsMatchingSuit()
{
   return m_bAllSuitsMatch = m_pHand->IsMatchingSuit();
}

bool Player::EvaluateSequence()
{
    return m_pHand->EvaluateSequence();
}

void Player::EvaluateValue()
{
    m_pHand->EvaluateValue();
}

void Player::PrintHand()
{
    m_pHand->PrintHand();
}

void Player::PrintCategory()
{
    m_pHand->PrintCategory();
}