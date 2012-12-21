/*
 * Project: C++_Game_Engine_Server
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 9 December 2012
 * Purpose: To provide a Network Interface for a Server for a 2D C++ Game Engine
 * File: C++_Game_Engine_Server\ServerNetwork.h
 */

#pragma once
#include "Player.h"
#include "GeneralPacket.h"

class ServerNetwork
{
	public:
		enum PacketType { C_KeepAlive = 0, S_KeepAlive, C_BlankPacket, S_BlankPacket, C_LocationUpdate, S_LocationUpdate, C_Login, S_Login, C_Register, S_Register };

		ServerNetwork(int port);
		~ServerNetwork();
		void RunIteration(Player* players, int playerCount);
		void Packet(PacketType packetType, Player& player, GeneralPacket buffer);
	private:
		sf::SocketTCP mListener;
};