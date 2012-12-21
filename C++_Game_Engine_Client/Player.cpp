/*
 * Project: C++_Game_Engine_Client
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 11 December 2012
 * Purpose: To provide a Player for a Client for a 2D C++ Game Engine
 * File: C++_Game_Engine_Client\Player.cpp
 */

#include <iostream>
#include "SFML\Graphics.hpp"
#include "SFML\Network.hpp"
#include "ClientNetwork.h"
#include "GeneralPacket.h"
#include "Player.h"

Player::Player()
{
	mDispPos = sf::Vector2f();
	mRealPos = sf::Vector2f();
	mSprite = 0;
	mDirection = 0x00;
	mLastSignal = 0;
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

sf::Vector2f Player::GetDisplayPosition(bool inPixels)
{
	if (!inPixels)
		return mDispPos;
	else
		return sf::Vector2f(mDispPos.x * 32, mDispPos.y * 32);
}

void Player::SetDisplayPosition(sf::Vector2f dispPos)
{
	mDispPos = dispPos;
}

int Player::GetSprite()
{
	return mSprite;
}

void Player::SetSprite(int sprite)
{
	mSprite = sprite;
}

int Player::GetDirection()
{
	return mDirection;
}

void Player::SetDirection(int direction)
{
	mDirection = direction;
}

void Player::Update()
{
	if (mLastSignal > 0)
		mLastSignal--;

	if (mRealPos.x != mDispPos.x)
	{
		mDispPos.x += (float)((mRealPos.x > mDispPos.x ? 1 : -1) / 32.);
	}
	if (mRealPos.y != mDispPos.y)
	{
		mDispPos.y += (float)((mRealPos.y > mDispPos.y ? 1 : -1) / 32.);
	}
}

void Player::Move(int direction, ClientNetwork& network)
{
	// Check if we need to move.
	if (mRealPos == mDispPos && mLastSignal == 0)
	{
		// Set our direction.
		mDirection = direction;

		// Prepare to update the server with the new information.
		GeneralPacket packet;
		packet << sf::Int8(ClientNetwork::C_LocationUpdate);
		packet << mDirection;
		std::cout << packet;
		network.SendPacket(packet);

		// Update the LastSignal so we don't spam movement packets.
		mLastSignal = 30;
	}
}

void Player::SetName(std::string name)
{
	this->mName = name;
}

std::string Player::GetName()
{
	return this->mName;
}