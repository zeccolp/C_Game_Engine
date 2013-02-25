/*
 * Project: C++_Game_Engine_Client
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 21 December 2012
 * Purpose: To provide a Map for a Client for a 2D C++ Game Engine
 * File: C++_Game_Engine_Client\Map.cpp
 */

#include "Map.h"

Map::Map()
{

}

Map::Map(int width, int height, int layers)
{
	this->mWidth = width;
	this->mHeight = height;
	this->mLayers = layers;
	this->mTiles = new int[this->mWidth * this->mHeight * this->mLayers];

	this->mTileset.LoadFromFile("Tilesets\\0.png");
	this->mTileset.SetSmooth(false);

	this->mSprites = new sf::Sprite[this->mWidth * this->mHeight * this->mLayers];

	for (int l = 0; l < this->mLayers; l++)
	{
		for (int i = 0; i < this->mWidth * this->mHeight; i++)
		{
			this->mSprites[i].SetImage(this->mTileset);
			this->mSprites[i].SetSubRect(sf::IntRect(0, 0, 32, 32));
			this->mSprites[i].SetBlendMode(sf::Blend::Mode::Alpha);
			this->mSprites[i].SetPosition(i % this->mWidth * 32, i / this->mWidth * 32);
		}
	}
}

void Map::Draw(sf::RenderWindow &App)
{
	for (int i = 0; i < this->mWidth * this->mHeight * this->mLayers; i++)
	{
		App.Draw(this->mSprites[i]);
	}
}

void Map::SetTile(int mapX, int mapY, int setTile, int layer)
{
	int x = setTile % (this->mTileset.GetWidth() / 32);
	int y = setTile / (this->mTileset.GetWidth() / 32);
	int index = mapY * this->mWidth + mapX + (layer * this->mHeight * this->mWidth);
	
	this->mSprites[index].SetImage(this->mTileset);
	this->mSprites[index].SetSubRect(sf::IntRect(x * 32, y * 32, x * 32 + 32, y * 32 + 32));
	this->mSprites[index].SetBlendMode(sf::Blend::Mode::Alpha);
	this->mSprites[index].SetPosition((index % (this->mWidth * this->mHeight)) % this->mWidth * 32, (index % (this->mWidth * this->mHeight)) / this->mWidth * 32);
}