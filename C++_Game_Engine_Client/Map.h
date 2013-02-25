/*
 * Project: C++_Game_Engine_Client
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 21 December 2012
 * Purpose: To provide a Map for a Client and Map Editor for a 2D C++ Game Engine
 * File: C++_Game_Engine_Client\Map.h
 */

#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Map {
	public:
		Map();
		Map(int width, int height, int layers);
		void Draw(sf::RenderWindow & App);
		void SetTile(int mapX, int mapY, int setTile, int layer);
	private:
		std::string mName;
		int mWidth;
		int mHeight;
		int mLayers;
		int * mTiles;
		sf::Sprite * mSprites;
		sf::Image mTileset;
};