//
//  Hand.cpp
//  HandHomework
//
//  Created by Howard Stahl on 4/30/15.
//  Copyright (c) 2015 Howard Stahl. All rights reserved.
//

#include "Player.h"

// CS 31 Students need to complete this class.
// Please read over the assignment and the TODO comments in the accompanying
// implementation file for further instructions.
namespace cs31
{

Player::Player( )
{
    // The Player has no Cards in his hand
    myNumberOfCards = 0;
}
    
std::ostream& operator <<( std::ostream& outs, const Player & p )
{
	int cardcounter = 0;
	while (cardcounter < p.cardCount())
	{
		outs << p.myCards[cardcounter]; // myCards is an array that we can utilize
		outs << std::endl; // note that we don't have using namespace std here so we need to add this. This will print cards on separate lines or else it gets messy
		cardcounter++;
	}

    return( outs );
}
    
void Player::acceptCard(Card c)
{

	if (myNumberOfCards < 12)
	{
		// note that myNumberOfCards
		myCards[myNumberOfCards] = c; // add the card to the array at the myNumberOfCards spot
										// you can treat myNumberOfCards as the index because 0 cards would be the 0 index, starting the first one, and then increment
		myNumberOfCards++; // increment the number because now you have another card
	}
	else if (myNumberOfCards >= 12)
	{
		throw std::logic_error("Too Many Cards \n"); // this is the logic error exception. Just throws out the logic error from std namespace with the text.
	}
}
    
Card Player::getCard( int index ) const
{
	if (myNumberOfCards >= 12)
	{
		throw std::logic_error("Index is Bad \n"); // this is the logic error exception, same as the one above.
	}
	
	Card c;
	c = myCards[index]; // this is a getter, so just get the card specified by the index
    return( c );
}

int  Player::cardCount( ) const
{
	// Forgot to include this in the cpp file so we need to add this
	// This function basically just counts how many cards that the person is holding in their hand

	int totalcards = 0;
	totalcards = myNumberOfCards;
	return (totalcards);
}


int  Player::handcount( ) const
{

    int total = 0;
	int number = 0; // I added an extra number variable because my Visual Studio was being weird and didn't want to accept total.
					// It's fixed itself since then, but I decided to leave the number variable stated because I had already changed everything.

	int acecounter = 0; // setting up an acecounter so that we can tell how many aces there are

	for (int k = 0; k < myNumberOfCards; k++)
	{
		number = number + myCards[k].count();
		if (myCards[k].getFace() == ACE) // if the current card that we are looking at is an ace, then increment the ace counter
		{
			acecounter++;
		}
	}

	if ((number + 10) <= 21 && acecounter == 1) // Testing each case to determine if the aces should be worth 1 or 11.
	{
		number = number + 10; // we add 10 because the ace is already worth 1, and if we are changing it to 11, then that is a difference of 10.
	}

	if ((number + 10) <= 21 && acecounter == 2) // Assuming there are two aces, then we can choose one of them to make into 1 or 11
	{
		number = number + 10;
	}
	if ((number + 10) <= 21 && acecounter == 3) // these might be repetitive, but just going through all of the possible cases
	{
		number = number + 10;
	}
	if ((number + 10) <= 21 && acecounter == 4)
	{
		number = number + 10;
	}
	if ((number + 20) <= 21 && acecounter == 2) // I don't think this is actually a possibility, but just in case
	{
		number = number + 20;
	}

	total = number;
    return( total );
}
    
    
bool Player::hasBlackJack( ) const
{
    bool result = false;
    if (myNumberOfCards == 2 && handcount() == 21)
    {
        result = true;
    }
    return( result );
}
    
}