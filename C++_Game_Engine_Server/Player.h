/*
 * Project: C++_Game_Engine_Server
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 9 December 2012
 * Purpose: To provide a Player for a Server for a 2D C++ Game Engine
 * File: C++_Game_Engine_Server\Player.h
 */

#pragma once
#include "SFML\Network.hpp"
#include "SFML\Graphics.hpp"
#include "FileStream.h"

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
		int GetDirection();
		void SetDirection(int direction);
		int GetSprite();
		void SetSprite(int sprite);
		void LoadFromFile(FileStream& fileStream);
		void SaveToFile(FileStream& fileStream);
		void SetName(std::string name);
		void SetPassword(std::string password);
		void SetEmail(std::string email);
		std::string GetName();
		std::string GetPassword();
	private:
		// Network Variables
		sf::SocketTCP mClient;
		sf::IPAddress mClientAddress;
		bool mConnected;

		// Player-Instance Variables
		sf::Vector2f mPosition;
		int mSprite;
		int mDirection;
		std::string mName;
		std::string mPassword;
		std::string mEmail;
};