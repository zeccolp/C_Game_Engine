/*
 * Project: C++_Game_Engine_Client
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 19 December 2012
 * Purpose: To provide Editors for a 2D C++ Game Engine
 * File: C++_Game_Engine_Editors\RadialMenu.cpp
 */

#include "RadialMenu.h"
#define PI 3.14159265358979323846

RadialMenu::RadialMenu()
{
	this->mSelectedIndex = 0;
	this->mIsSelected = false;
	this->mNumItems = 0;
}

RadialMenu::RadialMenu(int totalSprites)
{
	this->mSelectedIndex = 0;
	this->mIsSelected = false;
	this->mNumItems = totalSprites;
	this->mItems = new sf::Sprite[this->mNumItems];
}

RadialMenu::~RadialMenu()
{
}

void RadialMenu::CreateSprites(sf::IntRect * rectangles, sf::Image& image)
{
	for (int i = 0; i < this->mNumItems; i++)
	{
		this->mItems[i].SetImage(image);
		this->mItems[i].SetSubRect(rectangles[i]);
		this->mItems[i].SetPosition(this->mViewWidth / 2 + (cos(i * PI * 2 / this->mNumItems - PI / 2) * 96), this->mViewHeight / 2 + (sin(i * PI * 2 / this->mNumItems - PI / 2) * 96));
		//this->mItems[i].SetCenter((rectangles[i].Right - rectangles[i].Left) / 2, (rectangles[i].Top - rectangles[i].Bottom) / 2);
	}
}

void RadialMenu::MouseScroll(bool up)
{
	if (!this->mIsSelected)
	{
		if (up)
			this->mSelectedIndex--;
		else
			this->mSelectedIndex++;

		if (this->mSelectedIndex >= this->mNumItems)
			this->mSelectedIndex = 0;
		else if (this->mSelectedIndex < 0)
			this->mSelectedIndex = this->mNumItems - 1;
	}
}

void RadialMenu::Draw(sf::RenderWindow& App, bool drawSelection)
{
	if (!this->mIsSelected && !drawSelection)
	{
		for (int i = 0; i < this->mNumItems; i++)
		{
			if (i == this->mSelectedIndex)
				this->mItems[i].SetColor(sf::Color(0, 255, 0, 255));
			else
				this->mItems[i].SetColor(sf::Color(255, 255, 255, 255));

			App.Draw(this->mItems[i]);
		}
	}
	else if (this->mIsSelected && drawSelection)
		App.Draw(this->mSelectedItem);
}

int RadialMenu::Select()
{
	this->mIsSelected = true;
	this->mSelectedItem = this->mItems[this->mSelectedIndex];
	this->mSelectedItem.SetPosition(this->mViewWidth / 2, this->mViewHeight / 2);

	return this->mGoToMenu[this->mSelectedIndex];
}

int RadialMenu::UnSelect()
{
	this->mIsSelected = false;
	this->mSelectedIndex = 0;

	return this->mGoBackMenu;
}

void RadialMenu::SetView(int width, int height)
{
	this->mViewWidth = width;
	this->mViewHeight = height;

	for (int i = 0; i < this->mNumItems; i++)
	{
		this->mItems[i].SetPosition(this->mViewWidth / 2 + (cos(i * PI * 2 / this->mNumItems - PI / 2) * 96), this->mViewHeight / 2 + (sin(i * PI * 2 / this->mNumItems - PI / 2) * 96));
	}
}

void RadialMenu::SetMenus(int * goToMenu, int goBackMenu)
{
	this->mGoToMenu = goToMenu;
	this->mGoBackMenu = goBackMenu;
}

int RadialMenu::GetSelectedIndex()
{
	return this->mSelectedIndex;
}

int RadialMenu::GetTotalItems()
{
	return this->mNumItems;
}