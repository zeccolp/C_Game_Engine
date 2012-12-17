/*
 * Project: C++_Game_Engine_Client
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 16 December 2012
 * Purpose: To provide an Input Handler for a Client for a 2D C++ Game Engine
 * File: C++_Game_Engine_Client\InputHandler.cpp
 */

#include "InputHandler.h"

InputHandler::InputHandler()
{
	for (int i = 0; i < 26; i++)
	{
		mKeyMaps[i] = (sf::Key::Code)(i + 97);
		mKeyReverseMaps[(i + 97)] = i;
	}
	for (int i = 0; i < 10; i++)
	{
		mKeyMaps[i + 26] = (sf::Key::Code)(i + 48);
		mKeyReverseMaps[(i + 48)] = i + 26;
	}
	for (int i = 0; i < 65; i++)
	{
		mKeyMaps[i + 36] = (sf::Key::Code)(i + 256);
		mKeyReverseMaps[(i + 256)] = i + 36;
	}
}

void InputHandler::RunIteration(sf::RenderWindow& App)
{
	const sf::Input& input = App.GetInput();

	// Replace previous states with current states.
	mPrevMouseLeftClick = mMouseLeftClick;
	mPrevMouseRightClick = mMouseRightClick;
	mPrevMouseMiddleClick = mMouseMiddleClick;

	// Replace previous key codes with current ones.
	for (int i = 0; i < 101; i++)
	{
		mPrevKeyCodes[i] = mKeyCodes[i];
	}

	// Update current states.
	mMouseLeftClick = input.IsMouseButtonDown(sf::Mouse::Button::Left);
	mMouseRightClick = input.IsMouseButtonDown(sf::Mouse::Button::Right);
	mMouseMiddleClick = input.IsMouseButtonDown(sf::Mouse::Button::Middle);

	// So let's update all the key-codes.
	for (int i = 0; i < 101; i++)
	{
		mKeyCodes[i] = input.IsKeyDown(mKeyMaps[i]);
	}
}