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

bool InputHandler::MouseLeftClicked()
{
	return (this->mMouseLeftClick & !this->mPrevMouseLeftClick);
}

bool InputHandler::MouseRightClicked()
{
	return (this->mMouseRightClick & !this->mPrevMouseRightClick);
}

bool InputHandler::KeyTyped(sf::Key::Code code)
{
	return (this->mKeyCodes[this->mKeyReverseMaps[code]] & !this->mPrevKeyCodes[this->mKeyReverseMaps[code]]);
}

std::string InputHandler::ProcessInput(std::string text, bool allowNewlines, bool allowSpaces, bool allowSymbols)
{
	std::string newString = text;
	if (this->KeyTyped(sf::Key::Code::Back))
	{
		if (text.length() > 0)
		{
			newString = "";
			newString.append(text.c_str(), text.length() - 1);
		}
	}
	else
	{
		for (int i = 0; i < 26; i++)
		{
			if (this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::LShift]] || this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::RShift]])
			{
				if (this->KeyTyped(this->mKeyMaps[i]))
				{
					char add[1] = {(this->mKeyMaps[i] - 32)};
					newString.append(add, 1);
				}
			}
			else
			{
				if (this->KeyTyped(this->mKeyMaps[i]))
				{
					char add[1] = {(this->mKeyMaps[i])};
					newString.append(add, 1);
				}
			}
		}

		for (int i = 0; i < 10; i++)
		{
			if (!(this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::LShift]] || this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::RShift]]))
			{
				if (this->KeyTyped(this->mKeyMaps[i + 26]) || this->KeyTyped(this->mKeyMaps[i + 75]))
				{
					char add[1] = {(this->mKeyMaps[i + 26])};
					newString.append(add, 1);
				}
			}
		}

		if (allowNewlines)
		{
			if (this->KeyTyped(sf::Key::Code::Return))
			{
				char add[1] = {'\n'};
				newString.append(add, 1);
			}
		}

		if (allowSpaces)
		{
			if (this->KeyTyped(sf::Key::Code::Space))
			{
				char add[1] = {' '};
				newString.append(add, 1);
			}
		}

		if (allowSymbols)
		{
			char add[1] = {'\n'};
			
			if (this->KeyTyped(sf::Key::Code::BackSlash))
			{
				if (this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::LShift]] || this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::RShift]])
					add[0] = '|';
				else
					add[0] = '\\';
			}
			else if (this->KeyTyped(sf::Key::Code::Comma))
			{
				if (this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::LShift]] || this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::RShift]])
					add[0] = '<';
				else
					add[0] = ',';
			}
			else if (this->KeyTyped(sf::Key::Code::Period))
			{
				if (this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::LShift]] || this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::RShift]])
					add[0] = '>';
				else
					add[0] = '.';
			}
			else if (this->KeyTyped(sf::Key::Code::Slash))
			{
				if (this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::LShift]] || this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::RShift]])
					add[0] = '?';
				else
					add[0] = '/';
			}
			else if (this->KeyTyped(sf::Key::Code::Tilde))
			{
				if (this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::LShift]] || this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::RShift]])
					add[0] = '~';
				else
					add[0] = '`';
			}
			else if (this->KeyTyped(sf::Key::Code::LBracket))
			{
				if (this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::LShift]] || this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::RShift]])
					add[0] = '{';
				else
					add[0] = '[';
			}
			else if (this->KeyTyped(sf::Key::Code::RBracket))
			{
				if (this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::LShift]] || this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::RShift]])
					add[0] = '}';
				else
					add[0] = ']';
			}
			else if (this->KeyTyped(sf::Key::Code::SemiColon))
			{
				if (this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::LShift]] || this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::RShift]])
					add[0] = ':';
				else
					add[0] = ';';
			}
			else if (this->KeyTyped(sf::Key::Code::Quote))
			{
				if (this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::LShift]] || this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::RShift]])
					add[0] = '\"';
				else
					add[0] = '\'';
			}
			else if (this->KeyTyped(sf::Key::Code::Dash))
			{
				if (this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::LShift]] || this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::RShift]])
					add[0] = '_';
				else
					add[0] = '-';
			}
			else if (this->KeyTyped(sf::Key::Code::Equal))
			{
				if (this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::LShift]] || this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::RShift]])
					add[0] = '+';
				else
					add[0] = '=';
			}
			else if (this->KeyTyped(sf::Key::Code::Num1))
			{
				if (this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::LShift]] || this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::RShift]])
					add[0] = '!';
			}
			else if (this->KeyTyped(sf::Key::Code::Num2))
			{
				if (this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::LShift]] || this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::RShift]])
					add[0] = '@';
			}
			else if (this->KeyTyped(sf::Key::Code::Num3))
			{
				if (this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::LShift]] || this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::RShift]])
					add[0] = '#';
			}
			else if (this->KeyTyped(sf::Key::Code::Num4))
			{
				if (this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::LShift]] || this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::RShift]])
					add[0] = '$';
			}
			else if (this->KeyTyped(sf::Key::Code::Num5))
			{
				if (this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::LShift]] || this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::RShift]])
					add[0] = '%';
			}
			else if (this->KeyTyped(sf::Key::Code::Num6))
			{
				if (this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::LShift]] || this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::RShift]])
					add[0] = '#';
			}
			else if (this->KeyTyped(sf::Key::Code::Num7))
			{
				if (this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::LShift]] || this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::RShift]])
					add[0] = '&';
			}
			else if (this->KeyTyped(sf::Key::Code::Num8))
			{
				if (this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::LShift]] || this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::RShift]])
					add[0] = '*';
			}
			else if (this->KeyTyped(sf::Key::Code::Num9))
			{
				if (this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::LShift]] || this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::RShift]])
					add[0] = '(';
			}
			else if (this->KeyTyped(sf::Key::Code::Num0))
			{
				if (this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::LShift]] || this->mKeyCodes[this->mKeyReverseMaps[sf::Key::Code::RShift]])
					add[0] = ')';
			}
			else if (this->KeyTyped(sf::Key::Code::Add))
			{
				add[0] = '+';
			}
			else if (this->KeyTyped(sf::Key::Code::Subtract))
			{
				add[0] = '-';
			}
			else if (this->KeyTyped(sf::Key::Code::Multiply))
			{
				add[0] = '*';
			}
			else if (this->KeyTyped(sf::Key::Code::Divide))
			{
				add[0] = '/';
			}

			if (add[0] != '\n')
				newString.append(add, 1);
		}
	}

	return newString;
}