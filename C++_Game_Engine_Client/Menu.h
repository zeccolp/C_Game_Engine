/*
 * Project: C++_Game_Engine_Client
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 16 December 2012
 * Purpose: To provide a Menu for a Client for a 2D C++ Game Engine
 * File: C++_Game_Engine_Client\Menu.h
 */

#pragma once
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "ClientNetwork.h"

class Menu
{
	public:
		Menu();
		Menu(sf::Font font);

		// Putting = 0; makes it a pure virtual call. This means that all base classes MUST INCLUDE THESE FUNCTIONS or they get a error
		// But this actual class does not have these functions so it cannot be Called.
		virtual void SetFont(sf::Font font) = 0;
		virtual void RunIteration(sf::RenderWindow &App, ClientNetwork &network) = 0;
	private:
};