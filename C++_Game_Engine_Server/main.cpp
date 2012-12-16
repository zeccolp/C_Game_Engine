/*
 * Project: C++_Game_Engine_Server
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 9 December 2012
 * Purpose: To provide a Server for a 2D C++ Game Engine
 * File: C++_Game_Engine_Server\main.cpp
 */

#include <iostream>
#include <time.h>
#include "SFML\Audio.hpp"
#include "SFML\Config.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Network.hpp"
#include "SFML\System.hpp"
#include "SFML\Window.hpp"
#include "ServerNetwork.h"
#include "Player.h"

int main()
{	
	// Setup our players.
	const int playerCount = 256;
	Player * players = new Player [playerCount];
	
	// Initialize our Network
	ServerNetwork network((int)8081);

	// Go into the Server Loop.
	while (true)
	{
		// Update the networking.
		network.RunIteration(players, playerCount);

		// Prevent 100% CPU usage.
		Sleep(1);
	}

	// End of Programme
#if DEBUG
	system("pause");
#endif
	return 0;
}