/*
 * Project: C++_Game_Engine_Server
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 9 December 2012
 * Purpose: To provide a Player for a Server for a 2D C++ Game Engine
 * File: C++_Game_Engine_Server\Player.hpp
 */

#pragma once
#include "SFML\Network.hpp"

class Player
{
	public:
		Player();
		~Player();
		void SetClient(sf::SocketTCP client);
		void SetAddress(sf::IPAddress clientAddress);
		void SetConnected(bool connected);
		bool GetConnected();
		sf::SocketTCP GetClient();
		sf::IPAddress GetAddress();
	private:
		sf::SocketTCP mClient;
		sf::IPAddress mClientAddress;
		bool mConnected;
};