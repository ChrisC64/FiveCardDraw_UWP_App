//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace FiveCardDraw_UWP_App;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409
// Globals //

void InitDeck();

Deck deck;
Dealer gameDealer(std::make_shared<Deck>(deck));
Player playerOne("Christopher");
Player playerTwo("Faith");

MainPage::MainPage()
{
    InitializeComponent();
    gameDealer.AddPlayers(std::make_shared<Player>(playerOne));
    gameDealer.AddPlayers(std::make_shared<Player>(playerTwo));
    auto converter = [](std::string s) 
    {
        std::wstring wstr = std::wstring(s.begin(), s.end());
        const wchar_t* tempChar = wstr.c_str();
        String^ uwpString = ref new String(tempChar);
        return uwpString;
    };

    opponent_box->Text = converter(playerTwo.GetName());
    player_box->Text = converter(playerOne.GetName());
}

void FiveCardDraw_UWP_App::MainPage::DrawButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
    gameDealer.PlayGame();
    std::vector<std::shared_ptr<Player>> winningPlayers = gameDealer.GetWinningPlayers();
    PrintHand();
    if (winningPlayers.size() > 1)
    {
        Winner_Text->Text = "We have " + winningPlayers.size() + " winners!";
    }
    else
    { // Convert the std::string to std::wstring to use with Windows 10
        std::string name = winningPlayers.at(0)->GetName();
        std::wstring winnerName = std::wstring(name.begin(), name.end());
        const wchar_t* winnerChar = winnerName.c_str();
        String^ winner = ref new String(winnerChar);
        Winner_Text->Text = winner + " Wins!!";
    }

    gameDealer.NewGame();
}

void InitDeck()
{
}

void FiveCardDraw_UWP_App::MainPage::PrintHand()
{
    User_Card1->Text = playerOne.GetHand()->at(0).GetCardValue().ToString();
    User_Card2->Text = playerOne.GetHand()->at(1).GetCardValue().ToString();
    User_Card3->Text = playerOne.GetHand()->at(2).GetCardValue().ToString();
    User_Card4->Text = playerOne.GetHand()->at(3).GetCardValue().ToString();
    User_Card5->Text = playerOne.GetHand()->at(4).GetCardValue().ToString();
    Opponent_Card1->Text = playerTwo.GetHand()->at(0).GetCardValue().ToString();
    Opponent_Card2->Text = playerTwo.GetHand()->at(1).GetCardValue().ToString();
    Opponent_Card3->Text = playerTwo.GetHand()->at(2).GetCardValue().ToString();
    Opponent_Card4->Text = playerTwo.GetHand()->at(3).GetCardValue().ToString();
    Opponent_Card5->Text = playerTwo.GetHand()->at(4).GetCardValue().ToString();
}

