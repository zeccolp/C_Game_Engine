/*
 * Project: C++_Game_Engine_Server
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 9 December 2012
 * Purpose: To provide a Player for a Server for a 2D C++ Game Engine
 * File: C++_Game_Engine_Server\Player.h
 */

#pragma once

class Player
{
	public:
		Player();
		~Player();
		void SetConnected(bool connected);
		void SetClient(sf::SocketTCP client);
		void SetAddress(sf::IPAddress clientAddress);
		bool GetConnected();
		sf::SocketTCP GetClient();
		sf::IPAddress GetAddress();
		sf::Vector2f GetPosition();
		void SetPosition(sf::Vector2f position);
	private:
		// Network Variables
		sf::SocketTCP mClient;
		sf::IPAddress mClientAddress;
		bool mConnected;

		// Player-Instance Variables
		sf::Vector2f mPosition;
};