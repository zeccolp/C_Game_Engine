/*
 * Project: C++_Game_Engine_Server
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 9 December 2012
 * Purpose: To provide a Network Interface for a Server for a 2D C++ Game Engine
 * File: C++_Game_Engine_Server\ServerNetwork.hpp
 */

#pragma once
#include "Player.hpp"

class ServerNetwork
{
	public:
		ServerNetwork(int port);
		~ServerNetwork();
		void RunIteration(Player* players, int playerCount);
	private:
		sf::SocketTCP mListener;
};