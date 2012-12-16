/*
 * Project: C++_Game_Engine_Client
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 16 December 2012
 * Purpose: To provide a Main-Menu for a Client for a 2D C++ Game Engine
 * File: C++_Game_Engine_Client\MainMenu.h
 */

#pragma once
#include "Menu.h"

class MainMenu : public Menu
{
	public:
		MainMenu();
		MainMenu(sf::Font font);
		void SetFont(sf::Font font);
		void RunIteration(sf::RenderWindow &App, ClientNetwork &network);
	private:
		sf::String mLoginButton;
		sf::String mRegisterButton;
		sf::Font mFont;
};