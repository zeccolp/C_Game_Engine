/*
 * Project: C++_Game_Engine_Client
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 16 December 2012
 * Purpose: To provide a Game-Menu for a Client for a 2D C++ Game Engine
 * File: C++_Game_Engine_Client\GameMenu.cpp
 */

#include "GameMenu.h"

GameMenu::GameMenu()
{
}

GameMenu::GameMenu(sf::Font font)
{
	// Set our member font to the parameter font.
	mFont = font;

	// Setup the Text object
	mText = sf::String("Hello", mFont, 18);
}

void GameMenu::SetFont(sf::Font font)
{
	// Set our member font to the parameter font.
	mFont = font;
}

Menu::NewMenu GameMenu::RunIteration(sf::RenderWindow &App, ClientNetwork &network)
{
	// Try to connect to the network.
	if (!network.Connect())
		App.Close();

	// Get a reference to the input manager associated to our window, and store it for later use
	const sf::Input& Input = App.GetInput();

	// This will return false only if our Keepalives failed.
	if (!network.RunIteration(mMainPlayer))
		App.Close();

	// Check for movement.
	if (Input.IsKeyDown(sf::Key::W))
		mMainPlayer.Move(0x01, network);
	if (Input.IsKeyDown(sf::Key::S))
		mMainPlayer.Move(0x02, network);
	if (Input.IsKeyDown(sf::Key::A))
		mMainPlayer.Move(0x04, network);
	if (Input.IsKeyDown(sf::Key::D))
		mMainPlayer.Move(0x08, network);

	// Update the player. (Internal synchronization logic and whatnot.)
	mMainPlayer.Update();

	// Update the Text Position and draw it.
	mText.SetPosition(mMainPlayer.GetDisplayPosition(true));
	App.Draw(mText);

	// Tell them that we want to keep this menu.
	return Menu::NewMenu::M_GameMenu;
}