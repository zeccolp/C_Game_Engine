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

class Player
{
	public:
		Player();
		~Player();
		sf::Vector2f GetRealPosition();
		void SetRealPosition(sf::Vector2f realPos);
	private:
		sf::Vector2f mRealPos;
		sf::Vector2f mDispPos;
};