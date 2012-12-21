/*
 * Project: C++_Game_Engine_Client
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 21 December 2012
 * Purpose: To provide a Map for a Client for a 2D C++ Game Engine
 * File: C++_Game_Engine_Client\Map.h
 */

#pragma once
#include <string>

class Map {
	public:
		Map();
	private:
		std::string mName;
		int mWidth;
		int mHeight;
		int * mTiles;
};