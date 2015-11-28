#include "pch.h"
#include "CPP Files\Header Files\Dealer.h"

Dealer::Dealer(std::shared_ptr<Deck> deck) : m_bIsDealing(true),
m_iHandSize(5),
m_iNumOfPlayers(2),
m_bIsHighCardGame(false),
m_bIsTie(false)
{
    m_Deck = deck;
    m_DealtCards = std::make_shared<std::vector<Card>>();
    m_DealtCards->resize(m_iHandSize);
    m_winningPlayers = std::vector<std::shared_ptr<Player>>();
}

Dealer::~Dealer()
{
}

// SET METHODS //

void Dealer::SetIsDealing(bool isDealing)
{
    m_bIsDealing = isDealing;
}

void Dealer::SetCategory(std::shared_ptr<Player> p, Hand::CATEGORY eCategory)
{
    p->SetCategory(eCategory);
}

void Dealer::SetNumOfPlayers(int num)
{
    m_iNumOfPlayers = num;
}

void Dealer::SetHandSize(int size)
{
    m_iHandSize = size;
}

// GET METHODS //
bool Dealer::GetIsDealing()
{
    return m_bIsDealing;
}

int Dealer::GetHandSize()
{
    return m_iHandSize;
}

int Dealer::GetNumOfPlayres()
{
    return m_iNumOfPlayers;
}

// ADD PLAYERS //
void Dealer::AddPlayers(std::shared_ptr<Player> player)
{
    // If empty, resize and add players
    if (m_vPlayers.empty())
    {
        m_vPlayers.resize(1, player);
        m_iNumOfPlayers = 1;
        return;
    }
    // Otherwise just add in to our container
    m_vPlayers.push_back(player);
    m_iNumOfPlayers = m_vPlayers.size();
}

// DRAW CARDS // 
void Dealer::DrawCard(int amount)
{
    // Check if size > 0, if not we want to clean this hand and use a new one, so we 
    // don't give players the same hand
    if (m_DealtCards->empty())
    {
        m_DealtCards->resize(amount);
    }

    // Draw cards based on amount passed
    for (unsigned int i = 0; i < amount; ++i)
    {
        m_DealtCards->at(i) = m_Deck->DrawCard();
    }
    return;
}

// Functions with calls to Player

// GAME FUNCTIONS //
void Dealer::DealCards()
{
    // Draw cards based on handSize; pass to player's Hand; repeat for all players
    for (unsigned int i = 0; i < m_vPlayers.size(); ++i)
    {

        DrawCard(m_iHandSize);

        // Sort the Player's Hand
        m_vPlayers.at(i)->SortHandHighLow(m_DealtCards);

        // Pass the cards to the player Objects
        m_vPlayers.at(i)->AddToHand(m_DealtCards);

    }
}

// COMPARE HANDS //
void Dealer::CompareHands()
{
    // Compare Categories First
    CompareCategories();
}

void Dealer::FindSameCategory()
{
    // Players should be sorted in order of Highest CATEGORY to LOWEST, so take player 0's CATEGORY
    switch (m_vPlayers.at(0)->GetCategory())
    {
    case SFLUSH:
        CompareSFlush();
        break;
    case FOAK:
        CompareFoak();
        break;
    case FULLHOUSE:
        CompareFullHouse();
        break;
    case STRAIGHT:
        CompareStraight();
        break;
    case TOAK:
        CompareToak();
        break;
    case TWOPAIR:
        CompareTwoPair();
        break;
    case ONEPAIR:
        CompareOnePair();
        break;
    case HIGHCARD:
        CompareHighCard();
        break;
    }

}

void Dealer::CompareCategories()
{
    // Take first player's Category and find the highest from the players
    SortPlayersByCategory();

    // If Highest Player Category == HIGHCARD
    if (m_vPlayers.at(0)->GetCategory() == CATEGORY::HIGHCARD)
    {
        m_bIsHighCardGame = true;
        // Add all players to list
        for (unsigned int i = 0; i < m_vPlayers.size(); ++i)
        {
            m_highCardList.push_back(m_vPlayers.at(i));
        }
    }
    else if (m_vPlayers.at(0)->GetCategory() != m_vPlayers.at(1)->GetCategory())
    {
        // player one has highest value, they win
        m_vPlayers.at(0)->SetHasWinningHand(true);
        for (unsigned int i = 1; i < m_vPlayers.size(); ++i)
        {
            m_vPlayers.at(i)->SetHasWinningHand(false);
        }
        m_bIsHighCardGame = false;
    }
    else if (m_vPlayers.at(0)->GetCategory() == m_vPlayers.at(1)->GetCategory())
    {
        m_highCardList.push_back(m_vPlayers.at(0));
        m_highCardList.push_back(m_vPlayers.at(1));
        m_bIsHighCardGame = true;
    }
    else if (m_vPlayers.size() != 2) // We have players with same Category and more than 2 players
    {
        // Add players to our list that have the same category, 
        // Since we know players 1 and 2 match, check 2 against 3, and so on...
        // If we do not encounter the same category, jump out
        m_bIsHighCardGame = true;
        // Should already be organized by Category
        for (unsigned int i = 1; i < m_vPlayers.size() - 1; ++i)
        {
            if (m_vPlayers.at(i)->GetCategory() == m_vPlayers.at(i + 1)->GetCategory())
            {
                m_highCardList.push_back(m_vPlayers.at(i + 1));
            }
            else
            {
                // no more matches, jump out
                break;
            }
        }
    }

}

void Dealer::SortPlayersByCategory()
{
    bool swapped;
    do
    {
        swapped = false;
        for (unsigned int i = 0; i < m_vPlayers.size() - 1; ++i)
        {
            if (m_vPlayers.at(i)->GetCategory() > m_vPlayers.at(i + 1)->GetCategory())
            {
                // Best hand is lower int
                SwapPlayers(i, i + 1); // Didn't jump in
            }
            else
            {
                // Do nothing here
            }
        }
    } while (swapped);

}

void Dealer::SwapPlayers(int pos1, int pos2)
{
    // Create temp
    std::vector<std::shared_ptr<Player>> temp;

    // Store value of pos2 in temp vec: temp[POS2], HAND[POS1, POS2]
    temp.push_back(m_vPlayers.at(pos2));

    // Now take value of pos1 and place into pos2 of vector: temp[POS2], HAND[POS1, POS1]
    m_vPlayers.at(pos2) = m_vPlayers.at(pos1);

    // Transfer back temp into position 1: temp[POS2], HAND[POS2, POS1]
    m_vPlayers.at(pos1) = temp.at(0);
}

void Dealer::PlayGame()
{
    // Dealer will first DealCards()
    DealCards();

    // Find Category and Sequence
    for (unsigned int i = 0; i < m_vPlayers.size(); ++i)
    {
        m_vPlayers.at(i)->EvaluateSequence();
        m_vPlayers.at(i)->EvaluateCategory();
    }
#ifdef _WIN32
    PrintTable(); //TODO: Make it so we display this to our game view
#elif WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
    // TODO: Windows 8.1 and up SDK
#endif

    // After Cards are Dealt, Dealer will then compare hands of each player, start at 0
    CompareCategories();
    // Based on evaluation Do we have multiple hands with the same CATEGORY?
    if (m_bIsHighCardGame)
    {
        // Evaluate the hand's m_iValues first before finding the winner based on Category
        for (auto it = m_highCardList.begin(); it != m_highCardList.end(); ++it)
        {
            (*it)->EvaluateValue();
        }
        FindSameCategory();
    }
    // if tie, add Ties and Losses to players who do not have "Winning" hand
    if (m_bIsTie)
    {
        std::cout << "It's a TIE: ";
        for (unsigned int i = 0; i < m_vPlayers.size(); ++i)
        {
            if (m_vPlayers.at(i)->GetHasWinningHand())
            {
                m_vPlayers.at(i)->AddTie();
                PrintTie(m_vPlayers.at(i));
            }
            else
            {
                m_vPlayers.at(i)->AddLoss();
            }
        }
        std::cout << std::endl;
    }
    else // Add win for the winner and loss for losing hands
    {
        for (unsigned int i = 0; i < m_vPlayers.size(); ++i)
        {
            if (m_vPlayers.at(i)->GetHasWinningHand())
            {
                m_vPlayers.at(i)->AddWin();
                PrintWinner(m_vPlayers.at(i));
                m_winningPlayers.push_back(m_vPlayers.at(i));
            }
            else
            {
                m_vPlayers.at(i)->AddLoss();
            }
        }

    }
    // Confirm if Player[0] would like to play again? (Main player)

}

// NEW GAME: Reset all values to default except for LOSS, WINS, and TIES
void Dealer::NewGame()
{
    for (auto it = m_vPlayers.begin(); it != m_vPlayers.end(); ++it)
    {
        (*it)->Reset();
    }
    m_highCardList.clear();
    m_winningPlayers.clear();
}

// PRINT CALLS TO DISPLAY GAME INFORMATION //

void Dealer::PrintWinner(std::shared_ptr<Player> p)
{
    std::cout << "Congratulations! [" << p->GetName();
    std::cout << "] You won!" << std::endl;
}

void Dealer::PrintTie(std::shared_ptr<Player> p)
{
    std::cout << p->GetName();
    std::cout << " ";
}

void Dealer::PrintEndGameStats()
{
    for (auto it = m_vPlayers.begin(); it != m_vPlayers.end(); ++it)
    {
        std::cout << "\nStats for: " << (*it)->GetName() << std::endl;
        std::cout << "Wins: " << (*it)->GetWins() << std::endl;
        std::cout << "Loss: " << (*it)->GetLoss() << std::endl;
        std::cout << "Ties: " << (*it)->GetTies() << std::endl;
    }
}

void Dealer::PrintTable()
{
    // Print the hands of the Players
    for (auto p = m_vPlayers.begin(); p != m_vPlayers.end(); ++p)
    {
        std::cout << "-------------------------------" << std::endl;
        std::cout << (*p)->GetName() << " hand is a ";
        (*p)->PrintCategory();
        std::cout << std::endl;
        (*p)->PrintHand();
        std::cout << "\n-------------------------------" << std::endl;
    }
}

/**********************/
// COMPARE CALLS HERE //
/*********************/
// { sequential }
void Dealer::CompareSFlush()
{
    FindHighValue();
}
// { x, x, x, x, y }
void Dealer::CompareFoak()
{
    FindHighInPair(4);
}
// {x, x, x, y, y }
void Dealer::CompareFullHouse()
{
    FindHighInPair(3);
}
// { sequential }
void Dealer::CompareStraight()
{
    FindHighValue();
}
// { x, x, y, z, a }
void Dealer::CompareToak()
{
    FindHighInPair(3);
}
// { x, x, y, y, z }
void Dealer::CompareTwoPair()
{
    // Local Variables 
    std::list<std::shared_ptr<Player>> winningPlayers;
    Card::RANK highRank;
    bool isFirstPass = true;
    int firstPair = 0; // Counter: if > 1; we go into next pair
    int secondPair = 0;// Counter: if > 1; we go into kicker
    std::map<Card::RANK, int> *rankMap;

    // Iterate through highCardList
    for (auto it = m_highCardList.begin(); it != m_highCardList.end(); ++it)
    {
        rankMap = (*it)->GetRankMap();
        for (auto rm = rankMap->begin(); rm != rankMap->end(); ++rm)
        {
            if ((*rm).second == 2)
            {
                if (isFirstPass)
                {
                    highRank = (*rm).first;
                    winningPlayers.push_back(*it);
                }
                else if ((rm->first > highRank) && (highRank != Card::RANK::ACE))
                {
                    highRank = (*rm).first;
                    winningPlayers.push_back(*it);
                    winningPlayers.pop_front();
                }
                else if ((rm->first == Card::RANK::ACE) && (highRank != Card::RANK::ACE))
                {
                    highRank = (*rm).first;
                    winningPlayers.push_back(*it);
                    winningPlayers.pop_front();
                }
                else if ((rm->first == Card::RANK::ACE) && (highRank == Card::RANK::ACE))
                {
                    winningPlayers.push_back(*it);
                    firstPair++;
                }
            }
        }
    }

    // if WinningPlayers.size() > 2, we have a tie, let's check the values of the TwoPairs
    if (firstPair == 0)
    {
        winningPlayers.front()->SetHasWinningHand(true);
        m_bIsTie = false;
        m_highCardList.clear();
        return;
    }

    // First Pair is > 0, we need to find the low value of the card for hands with only the highRank
    Card::RANK nextPair;
    isFirstPass = true;
    std::list<std::shared_ptr<Player>> tieBreaker;
    for (auto p = winningPlayers.begin(); p != winningPlayers.end(); ++p)
    {
        rankMap = (*p)->GetRankMap();
        for (auto rm = rankMap->begin(); rm != rankMap->end(); ++rm)
        {
            if (rm->first != highRank)
            {
                if (isFirstPass)
                {
                    nextPair = rm->first;
                    tieBreaker.push_back(*p);
                    isFirstPass = false;
                    break;
                }
                else if ((rm->first > highRank) && (highRank != Card::RANK::ACE))
                {
                    nextPair = (*rm).first;
                    tieBreaker.push_back(*p);
                    tieBreaker.pop_front();
                    break;
                }
                else if ((rm->first == Card::RANK::ACE) && (highRank != Card::RANK::ACE))
                {
                    nextPair = (*rm).first;
                    tieBreaker.push_back(*p);
                    tieBreaker.pop_front();
                    break;
                }
                else if ((rm->first == Card::RANK::ACE) && (highRank == Card::RANK::ACE))
                {
                    tieBreaker.push_back(*p);
                    secondPair++;
                }
            }
        }
    }

    if (secondPair == 0)
    {
        tieBreaker.front()->SetHasWinningHand(true);
        m_bIsTie = false;
        m_highCardList.clear();
        return;
    }

    int highNumber = 0;
    int tieCounter = 0;
    // compare the kicker
    for (auto it = tieBreaker.begin(); it != tieBreaker.end(); ++it)
    {
        if (isFirstPass)
        {
            highNumber = (*it)->GetCardValue();
        }
        else if ((*it)->GetCardValue() > highNumber)
        {
            highNumber = (*it)->GetCardValue();
        }
        else if ((*it)->GetCardValue() == highNumber)
        {
            tieCounter++;
        }
    }

    // If counter > 0; we have a tie
    if (tieCounter == 0)
    {
        tieBreaker.front()->SetHasWinningHand(true);
        m_bIsTie = false;
        return;
    }
    else
    {
        m_bIsTie = true;
        for (auto p = tieBreaker.begin(); p != tieBreaker.end(); ++p)
        {
            if ((*p)->GetCardValue() == highNumber)
            {
                (*p)->SetHasWinningHand(true);
            }
            else
            {
                (*p)->SetHasWinningHand(false);
            }
        }
    }
    m_highCardList.clear();
}

void Dealer::CompareOnePair()
{
    FindHighInPair(2);
}

void Dealer::CompareHighCard()
{
    // Look for hand with ACE in it, if only one hand has an ACE
    // that hand wins, if not, we compe the hands
    std::cout << "\nFinding the highest card between the HIGHCARDS\n\n";

    std::shared_ptr<std::list<std::shared_ptr<Player>>> aceList;
    int highNumber = 0;
    bool isFirstPass = true;
    for (auto it = m_highCardList.begin(); it != m_highCardList.end(); ++it)
    {
        if ((*it)->GetAceCounter() == 1)
        {
            aceList->push_back(*it);
        }
    }

    if (aceList != NULL && aceList->size() == 1)//TODO: Access violation, read while empty. 
    {
        // Find the high value
        m_bIsTie = false;
        aceList->front()->SetHasWinningHand(true);
    }
    else if (aceList->size() > 1)
    {
        FindHighValue(aceList);
    }
    else
    {
        FindHighValue();
    }

}

void Dealer::FindHighInPair(int pairValue)
{
    if (m_highCardList.empty())
    {
        printf_s("Cannot FindHighInPair(): HigcardList is empty!");
        return;
    }

    // Map with RANK count
    std::map<Card::RANK, int> *rankMap;
    std::list<std::shared_ptr<Player>> winningPlayers;
    Card::RANK highRank;
    bool isFirstPass = true;
    int highNumber = 0;
    // Perform search for the card's Pair, find RANK of that card
    for (auto it = m_highCardList.begin(); it != m_highCardList.end(); ++it)
    {
        rankMap = (*it)->GetRankMap();
        for (auto rm = rankMap->begin(); rm != rankMap->end(); ++rm)
        {
            if (rm->second == pairValue) // Found the pair
            {
                if (isFirstPass)
                {
                    highRank = rm->first;
                    winningPlayers.push_back(*it);
                    isFirstPass = false;
                    break;
                }
                else if (rm->first > highRank && highRank != Card::RANK::ACE)
                {
                    highRank = rm->first;
                    winningPlayers.push_back(*it);
                    winningPlayers.pop_front();
                    break;
                }
                else if ((rm->first == Card::RANK::ACE) && (highRank != Card::RANK::ACE))
                {
                    highRank = rm->first;
                    highNumber = (*it)->GetCardValue(); // Store the Hand's CardValue for alter
                    winningPlayers.push_back(*it);
                    winningPlayers.pop_front();
                    break;
                }
                else if ((rm->first == Card::RANK::ACE) && (highRank == Card::RANK::ACE))
                {
                    // compare the values of each hand, highest value wins
                    if ((*it)->GetCardValue() > highNumber)
                    {
                        highNumber = (*it)->GetCardValue();
                        winningPlayers.push_back(*it);
                        winningPlayers.pop_front();
                    }
                    else if ((*it)->GetCardValue() == highNumber)
                    {
                        // We have a tie
                        winningPlayers.push_back(*it);
                    }
                }
            }
        }
    }

    // check if tie
    if (winningPlayers.size() == 1)
    {
        winningPlayers.front()->SetHasWinningHand(true);
        m_bIsTie = false;
        m_highCardList.clear();
        return;
    }
    else
    {
        for (auto wp = winningPlayers.begin(); wp != winningPlayers.end(); ++wp)
        {
            (*wp)->SetHasWinningHand(true);
            m_bIsTie = true;
        }
        m_highCardList.clear();
        return;
    }
}

void Dealer::FindHighValue()
{
    if (m_highCardList.empty())
    {
        printf_s("Cannot findValue(): HigcardList is empty!");
        return;
    }

    // Look at first player in list
    int highNumber = 0;
    int tieCounter = 0;
    std::list<Player*> winningPlayers;
    bool isFirstPass = true;
    // Iterate through the list, store the highest nuber from theplayers
    for (auto it = m_highCardList.begin(); it != m_highCardList.end(); ++it)
    {
        // Get their hand
        if (isFirstPass)
        {
            highNumber = (*it)->GetValue();
        }
        else if ((*it)->GetValue() > highNumber)
        {
            highNumber = (*it)->GetValue();
        }
        else if ((*it)->GetValue() == highNumber)
        {
            tieCounter++;
        }
    }

    // If counter > 0; we have a tie
    if (tieCounter == 0)
    {
        m_bIsTie = false;
    }
    else
    {
        m_bIsTie = true;
    }

    // Set winning and losing players
    for (auto p = m_highCardList.begin(); p != m_highCardList.end(); ++p)
    {
        if ((*p)->GetValue() == highNumber)
        {
            (*p)->SetHasWinningHand(true);
        }
        else
        {
            (*p)->SetHasWinningHand(false);
        }
    }

    m_highCardList.clear();
}

void Dealer::FindHighValue(std::shared_ptr<std::list<std::shared_ptr<Player>>> playerList)
{
    if (playerList->empty())
    {
        printf_s("Cannot findValue(): HigcardList is empty!");
        return;
    }

    // Look at first player in list
    int highNumber = 0;
    int tieCounter = 0;
    std::list<Player*> winningPlayers;
    bool isFirstPass = true;
    // Iterate through the list, store the highest nuber from theplayers
    for (auto it = playerList->begin(); it != playerList->end(); ++it)
    {
        // Get their hand
        if (isFirstPass)
        {
            highNumber = (*it)->GetValue();
        }
        else if ((*it)->GetValue() > highNumber)
        {
            highNumber = (*it)->GetValue();
        }
        else if ((*it)->GetValue() == highNumber)
        {
            tieCounter++;
        }
    }

    // If counter > 0; we have a tie
    if (tieCounter == 0)
    {
        m_bIsTie = false;
    }
    else
    {
        m_bIsTie = true;
    }

    // Set winning and losing players
    for (auto p = playerList->begin(); p != playerList->end(); ++p)
    {
        if ((*p)->GetValue() == highNumber)
        {
            (*p)->SetHasWinningHand(true);
        }
        else
        {
            (*p)->SetHasWinningHand(false);
        }
    }
}

void Dealer::Compare(std::shared_ptr<std::list<std::shared_ptr<Player>>> playerList)
{
    std::shared_ptr<std::vector<Card>> currHand;
    std::shared_ptr<std::vector<Card>> secondHand;
    bool winnerFound = false;
    int highNum = 0;
    std::list<std::shared_ptr<Player>> winningPlayer;
    for (auto p = playerList->begin(); p != playerList->end(); ++p)
    {
        // Obtain the players hand
        currHand = p->get()->GetHand();
        int i = 0;
        for (auto it = ++playerList->begin(); it != --playerList->end(); ++it)
        {
            secondHand = (*it)->GetHand();
            // Compare the first cards of each hand
            // If the value of currHand.at(x)->GetValue() secondHand.at(x)->GetValue()
            if (currHand->at(i).GetCardValue() > secondHand->at(i).GetCardValue())
            {
                highNum = currHand->at(i).GetCardValue();
                winningPlayer.push_back(*p);
                if (winningPlayer.size() > 1)
                {
                    winningPlayer.pop_front();
                }
                winnerFound = true;
            }
            else
            {
                // set this player as winning and exit return
                highNum = secondHand->at(i).GetCardValue();
                winningPlayer.push_back(*it);
                if (winningPlayer.size() > 1)
                {
                    winningPlayer.pop_front();
                }
                winnerFound = true;
            }

            // else if they are the same, iterate to the next hand
        }
        if (highNum == 0)
        {
            i++;
        }
        else if (winnerFound)
        {
            winningPlayer.front()->SetHasWinningHand(true);
        }
    }
}

std::vector<std::shared_ptr<Player>> Dealer::GetWinningPlayers()
{
    return m_winningPlayers;
}