/*
 * Project: C++_Game_Engine_Client
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 19 December 2012
 * Purpose: To provide Editors for a 2D C++ Game Engine
 * File: C++_Game_Engine_Editors\RadialMenu.h
 */

#pragma once
#include "SFML\Graphics.hpp"

class RadialMenu {
	public:
		RadialMenu();
		RadialMenu(int totalSprites);
		~RadialMenu();
		void CreateSprites(sf::IntRect * rectangles, sf::Image& image);
		void MouseScroll(bool up);
		void Draw(sf::RenderWindow& App, bool drawSelection = false);
		int Select();
		int UnSelect();
		void SetView(int width, int height);
		void SetMenus(int * goToMenu, int goBackMenu);
		int GetSelectedIndex();
		int GetTotalItems();
	private:
		bool mIsSelected;
		int mSelectedIndex;
		sf::Sprite * mItems;
		int * mGoToMenu;
		sf::Sprite mSelectedItem;
		int mNumItems;
		int mViewWidth;
		int mViewHeight;
		int mGoBackMenu;
};