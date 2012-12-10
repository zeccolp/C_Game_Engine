/*
 * Project: C++_Game_Engine_Server
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 9 December 2012
 * Purpose: To provide a Player for a Server for a 2D C++ Game Engine
 * File: C++_Game_Engine_Server\Player.cpp
 */

#include "Player.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Config.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Network.hpp"
#include "SFML\System.hpp"
#include "SFML\Window.hpp"

Player::Player()
{
	SetClient(sf::SocketTCP());
	SetAddress(sf::IPAddress());
	SetConnected(false);
}

Player::~Player()
{
	mClient.Close();
	SetConnected(false);
}

void Player::SetClient(sf::SocketTCP client)
{
	mClient = client;
}

void Player::SetAddress(sf::IPAddress clientAddress)
{
	mClientAddress = clientAddress;
}

bool Player::GetConnected()
{
	return mConnected;
}

void Player::SetConnected(bool connected)
{
	mConnected = connected;
}

sf::SocketTCP Player::GetClient()
{
	return mClient;
}

sf::IPAddress Player::GetAddress()
{
	return mClientAddress;
}