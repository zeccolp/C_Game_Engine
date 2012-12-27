/*
 * Project: C++_Game_Engine_Client
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 16 December 2012
 * Purpose: To provide a Main-Menu for a Client for a 2D C++ Game Engine
 * File: C++_Game_Engine_Client\MainMenu.h
 */

#pragma once
#include "Menu.h"
#include "InputHandler.h"

class MainMenu : public Menu
{
	public:
		enum MenuAction { M_MainMenu, M_Login, M_Register };

		MainMenu();
		MainMenu(sf::Font font);
		void SetFont(sf::Font font);
		Menu::NewMenu RunIteration(sf::RenderWindow &App, ClientNetwork &network, Player& player);
	private:
		sf::String mLoginButton;
		sf::String mRegisterButton;
		sf::String mActionTitle;
		sf::String mActionButton;
		sf::String mCancelButton;
		sf::String mUsername;
		sf::String mPassword;
		sf::String mEmail;
		sf::String mResponse;
		sf::Font mFont;
		MenuAction mMenuAction;
		std::string mUsernameAct;
		std::string mPasswordAct;
		std::string mEmailAct;
		int mActiveInput;
		bool mWaitingOnNetwork;
		bool mDisplayResponse;
		InputHandler mInputHandle;
};