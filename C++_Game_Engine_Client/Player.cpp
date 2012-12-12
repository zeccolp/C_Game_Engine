/*
 * Project: C++_Game_Engine_Client
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 11 December 2012
 * Purpose: To provide a Player for a Client for a 2D C++ Game Engine
 * File: C++_Game_Engine_Client\Player.cpp
 */

#include "Player.hpp"
#include "GeneralPacket.hpp"
#include <iostream>

Player::Player()
{
	mDispPos = sf::Vector2f();
	mRealPos = sf::Vector2f();
	mSprite = 0;
	mDirection = 0x00;
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

sf::Vector2f Player::GetDisplayPosition()
{
	return mDispPos;
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

void Player::Update()
{
	if (mRealPos.x != mDispPos.x)
	{
		mDispPos.x += mRealPos.x > mDispPos.x ? 1 : -1;
	}
	if (mRealPos.y != mDispPos.y)
	{
		mDispPos.y += mRealPos.y > mDispPos.y ? 1 : -1;
	}
}

void Player::Move(int direction, ClientNetwork& network)
{
	// Check if we need to move.
	if (mRealPos == mDispPos)
	{
		// Yes, what direction? Move them when we find out.
		if ((direction & 0x01) != 0x00)
			mRealPos = sf::Vector2f(mRealPos.x, mRealPos.y - 32);
		if ((direction & 0x02) != 0x00)
			mRealPos = sf::Vector2f(mRealPos.x, mRealPos.y + 32);
		if ((direction & 0x04) != 0x00)
			mRealPos = sf::Vector2f(mRealPos.x - 32, mRealPos.y);
		if ((direction & 0x08) != 0x00)
			mRealPos = sf::Vector2f(mRealPos.x + 32, mRealPos.y);

		// Prepare to update the server with the new information.
		GeneralPacket packet;
		packet << sf::Int8(ClientNetwork::PacketType::C_BlankPacket);
		packet << *this;
		std::cout << packet;
		network.SendPacket(packet);
	}
}