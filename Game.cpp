//
//  Game.cpp
//  HandHomework
//
//  Created by Howard Stahl on 12/6/15.
//  Copyright © 2015 Howard Stahl. All rights reserved.
//

#include "Game.h"
#include <iostream>

// CS 31 Students need to complete this class.
// Please read over the assignment and the TODO comments in the accompanying
// implementation file for further instructions.
namespace cs31
{

Game::Game()
{
	mPlayerStood = false; // this sets it so that the game is not over when it hasn't even started yet
	mOutcome = NOOUTCOME; // no outcome yet because the game hasn't started
}
 
Game::Game( Player player, Player dealer )
{
    mPlayer = player;
    mDealer = dealer;
	// TODO : set the outcome of the game initially //
    //        set the player's turn is not yet over //
	mPlayerStood = false; // basically repeat code from above
	mOutcome = NOOUTCOME;
}

// did the Player win?
bool Game::playerWon()
{
    return( mOutcome == PLAYERWON );
}
    
// did the Player lose?
bool Game::playerLost()
{
    return( mOutcome == PLAYERLOST );
}
    
// did the Player and the Dealer tie?
bool Game::playerTied( )
{
    return( mOutcome == TIED );
}
    
void Game::deal()
{
	mDeck.shuffleDeck(); //shuffles the mDeck that we are using for this game
	// Now need to deal two cards to the player first, and then to the dealer
	// Note that in blackjack, the player plays first, and then the dealer
	mPlayer.acceptCard(mDeck.dealCard());
	mPlayer.acceptCard(mDeck.dealCard());
	mDealer.acceptCard(mDeck.dealCard());
	mDealer.acceptCard(mDeck.dealCard());
}
    
void Game::playerHits( )
{
	mPlayer.acceptCard(mDeck.dealCard()); // same syntax as the function above
}
    
// let the Game know that the Player's turn is over
void Game::playerStands()
{
    mPlayerStood = true;
}
 
// has the Player's turn ended?
bool Game::playerStood() const
{
    return( mPlayerStood );
}

void Game::dealerHits( )
{
	mDealer.acceptCard(mDeck.dealCard());
}
    
void Game::dealerStands( )
{
	// just a standard if-else statement tree
	if (dealerBusted() == true) // if dealer busts, player wins
	{
		mOutcome = PLAYERWON;
	}
	else if (playerBusted() == true) // player busts, dealer wins autmomatically
	{
		mOutcome = PLAYERLOST;
	}
	else if (mPlayer.handcount() > mDealer.handcount()) // simple comparisons
	{
		mOutcome = PLAYERWON;
	}
	else if (mPlayer.handcount() < mDealer.handcount())
	{
		mOutcome = PLAYERLOST;
	}
	else if (mPlayer.handcount() == mDealer.handcount())
	{
		mOutcome = TIED;
	}
}
    
bool Game::dealerBusted( ) const
{
    bool result = false;
	if (mDealer.handcount() > 21) // hand count counts up the value of the hand
	{
		result = true;
	}
    return( result );
}
    
bool Game::playerBusted( ) const
{
    bool result = false;
	if (mPlayer.handcount() > 21) // same deal as dealerBusted
	{
		result = true;
	}
    return( result );
}
    
void Game::dealerPlays()
{
	if (playerBusted() == false) // player hasn't busted, or else the dealer would automatically win
	{
		while (mDealer.handcount() < mPlayer.handcount() && mDealer.handcount() < 17) // dealer plays until the hand hits 17
		{
			mDealer.acceptCard(mDeck.dealCard()); // same syntax to accept cards
		}
	}

    // let the Game know that play has ended
    dealerStands();
}
    
bool Game::playerHasBlackJack( ) const
{
    bool result = false;
	if (mPlayer.hasBlackJack() == true) // there's already a function written for the blackjack case
	{
		result = true;
	}
    return( result );
}
    
bool Game::dealerHasBlackJack( ) const
{
    bool result = false;
	if (mDealer.hasBlackJack() == true) // same deal as above
	{
		result = true;
	}
    return( result );
}
    
//
// ALL THE CODE BELOW THIS POINT SHOULD NOT BE CHANGED!
//
void Game::display( std::string s , bool allCards )
{
    // when allCards is true  --> show all dealer cards
    // otherwise just show the one turned up dealer card
    // and then display the passed message at the bottom of the screen, if supplied
    using namespace std;
    int dealerCount = mDealer.handcount();
    int playerCount = mPlayer.handcount();
    cout << "DEALER'S HAND:" << endl;
    if (allCards)
    {
        cout << mDealer << endl;
    }
    else
    {
        cout << mDealer.getCard(0) << endl;
    }
    if (dealerBusted())
    {
        cout << "          --->dealer busted!" << endl;
    }
    else if (allCards)
    {
        cout << "          --->" << dealerCount << endl;
    }
    cout << endl;
    cout << "PLAYER'S HAND:" << endl;
    cout << mPlayer << endl;
    if (playerBusted())
    {
        cout << "          --->player busted!" << endl;
    }
    else if (allCards)
    {
        cout << "          --->" << playerCount << endl;
    }

    if (s != "")
        cout << s << endl;
}
    


    
}