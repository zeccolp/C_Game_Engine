/*
 * Project: C++_Game_Engine_Client
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 10 December 2012
 * Purpose: To provide a Network Interface for a Client for a 2D C++ Game Engine
 * File: C++_Game_Engine_Client\ClientNetwork.h
 */

#pragma once
#include "Player.h"
#include "SFML\Network.hpp"
#include "GeneralPacket.h"

class ClientNetwork
{
	public:
		enum PacketType { C_KeepAlive = 0, S_KeepAlive, C_BlankPacket, S_BlankPacket, C_LocationUpdate, S_LocationUpdate, C_Login, S_Login, C_Register, S_Register };

		ClientNetwork(int port, sf::IPAddress ipAddress, int keepaliveDelay = 1000); // Default Keep-Alives Delay set to 1000ms.
		~ClientNetwork();
		bool Connect();
		bool RunIteration(Player& player);
		bool IsAlive();
		bool Receive(Player& player, bool trueOnNoData = false);
		bool SendPacket(PacketType code, bool falseOnDisconnectOnly = false);
		bool SendPacket(sf::Packet packet, bool falseOnDisconnectOnly = false);
		void Close();
	private:
		clock_t mLastKeepalive;
		sf::SocketTCP mClient;
		int mPort;
		sf::IPAddress mIPAddress;
		int mKeepaliveDelay;
		bool mConnected;
};