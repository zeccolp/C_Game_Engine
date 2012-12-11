/*
 * Project: C++_Game_Engine_Client
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 11 December 2012
 * Purpose: To provide a Player for a Client for a 2D C++ Game Engine
 * File: C++_Game_Engine_Client\Player.cpp
 */

#include "Player.hpp"

Player::Player()
{
	mDispPos = sf::Vector2f();
	mRealPos = sf::Vector2f();
}

Player::~Player()
{
}

sf::Vector2f Player::GetRealPosition()
{
	return mRealPos;
}

void Player::SetRealPosition(sf::Vector2f realPos)
{
	mRealPos = realPos;
}