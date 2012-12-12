/*
 * Project: C++_Game_Engine_Client
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 11 December 2012
 * Purpose: To provide a Player for a Client for a 2D C++ Game Engine
 * File: C++_Game_Engine_Client\Player.hpp
 */

#pragma once
#include "SFML\Graphics.hpp"
#include "SFML\Network.hpp"
#include "ClientNetwork.hpp"

class Player
{
	public:
		Player();
		~Player();
		sf::Vector2f GetRealPosition();
		void SetRealPosition(sf::Vector2f realPos);
		sf::Vector2f GetDisplayPosition();
		void SetDisplayPosition(sf::Vector2f dispPos);
		int GetSprite();
		void SetSprite(int sprite);
		void Update();
		void Move(int direction, ClientNetwork& network);
	private:
		sf::Vector2f mRealPos;
		sf::Vector2f mDispPos;
		int mSprite;
		unsigned char mDirection;
};