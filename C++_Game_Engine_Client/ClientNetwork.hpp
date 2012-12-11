/*
 * Project: C++_Game_Engine_Client
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 10 December 2012
 * Purpose: To provide a Network Interface for a Client for a 2D C++ Game Engine
 * File: C++_Game_Engine_Client\ClientNetwork.hpp
 */

#pragma once
#include "SFML\Network.hpp"
#include <time.h>

class ClientNetwork
{
	public:
		enum PacketType { C_KeepAlive = 0, };

		ClientNetwork();
		ClientNetwork(int port, sf::IPAddress ipAddress, int keepaliveDelay = 250); // Default Keep-Alives Delay set to 250ms.
		~ClientNetwork();
		bool Connect();
		bool RunIteration();
		bool IsAlive();
		bool SendPacket(PacketType code, bool falseOnDisconnectOnly = false);
		bool SendPacket(sf::Packet packet, bool falseOnDisconnectOnly = false);
	private:
		clock_t mLastKeepalive;
		sf::SocketTCP mClient;
		int mPort;
		sf::IPAddress mIPAddress;
		int mKeepaliveDelay;
};