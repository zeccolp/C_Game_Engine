/*
 * Project: C++_Game_Engine_Client
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 16 December 2012
 * Purpose: To provide a Main-Menu for a Client for a 2D C++ Game Engine
 * File: C++_Game_Engine_Client\MainMenu.cpp
 */

#include "MainMenu.h"

MainMenu::MainMenu()
{

}

MainMenu::MainMenu(sf::Font font)
{
	// Copy the local parameter to our Class Member for our Font.
	this->mFont = font;

	// Update our Buttons, create the text, reference the font of our Member.
	this->mLoginButton = sf::String("Login", this->mFont, 18.0f);
	this->mRegisterButton = sf::String("Register", this->mFont, 18.0f);

	// Get the location of the login button.
	sf::FloatRect rect = this->mLoginButton.GetRect();

	// Center it to the Screen.
	this->mLoginButton.SetPosition(400 - (rect.Right / 2), 300 - (rect.Bottom));
	
	// Get the location of the register button.
	rect = this->mRegisterButton.GetRect();

	// Center it to the Screen.
	this->mRegisterButton.SetPosition(400 - (rect.Right / 2), 300 + (rect.Bottom));
}

void MainMenu::SetFont(sf::Font font)
{
	// Set our Class Member font to the parameter font.
	this->mFont = font;
}

void MainMenu::RunIteration(sf::RenderWindow &App, ClientNetwork &network)
{
	// Draw our Buttons.
	App.Draw(this->mLoginButton);
	App.Draw(this->mRegisterButton);
}