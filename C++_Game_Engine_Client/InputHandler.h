/*
 * Project: C++_Game_Engine_Client
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 16 December 2012
 * Purpose: To provide an Input Handler for a Client for a 2D C++ Game Engine
 * File: C++_Game_Engine_Client\InputHandler.h
 */

#pragma once
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include <string>

class InputHandler
{
	public:
		InputHandler();
		void RunIteration(sf::RenderWindow& App);
		bool MouseLeftClicked();
		bool MouseRightClicked();
		bool KeyTyped(sf::Key::Code code);
		std::string ProcessInput(std::string text, bool allowNewlines = false, bool allowSpaces = false, bool allowSymbols = false);
	private:
		bool mMouseLeftClick;
		bool mPrevMouseLeftClick;
		bool mMouseRightClick;
		bool mPrevMouseRightClick;
		bool mMouseMiddleClick;
		bool mPrevMouseMiddleClick;
		bool mKeyCodes[101];
		bool mPrevKeyCodes[101];
		sf::Key::Code mKeyMaps[101];
		int mKeyReverseMaps[321];
};