/*
 * Project: C++_Game_Engine_Client
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 16 December 2012
 * Purpose: To provide a Game-Menu for a Client for a 2D C++ Game Engine
 * File: C++_Game_Engine_Client\GameMenu.h
 */

#pragma once
#include "Menu.h"
#include "Player.h"

class GameMenu : public Menu
{
	public:
		GameMenu();
		GameMenu(sf::Font font);
		void SetFont(sf::Font font);
		Menu::NewMenu RunIteration(sf::RenderWindow &App, ClientNetwork &network);
	private:
		sf::Font mFont;
		Player mMainPlayer;
		sf::String mText;
};