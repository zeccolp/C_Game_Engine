/*
 * Project: C++_Game_Engine_Client
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 10 December 2012
 * Purpose: To provide a Network Interface for a Client for a 2D C++ Game Engine
 * File: C++_Game_Engine_Client\ClientNetwork.cpp
 */

#include <time.h>
#include "SFML\Network.hpp"
#include "ClientNetwork.hpp"

ClientNetwork::ClientNetwork()
{
	mLastKeepalive = clock();
	mKeepaliveDelay = 250;
}

ClientNetwork::ClientNetwork(int port, sf::IPAddress ipAddress, int keepaliveDelay)
{
	mPort = port;
	mIPAddress = ipAddress;
	mLastKeepalive = clock();
	mKeepaliveDelay = keepaliveDelay;
}

ClientNetwork::~ClientNetwork()
{
	mClient.Close();
}

bool ClientNetwork::Connect()
{
	if (mClient.Connect(mPort, mIPAddress) != sf::Socket::Done)
		return false;
	else
		return true;

	mLastKeepalive = clock();
}

bool ClientNetwork::RunIteration()
{
	return IsAlive();
}

bool ClientNetwork::IsAlive()
{
	// Get the current time and check if it's time to send a new keepalive.
	clock_t now = clock();
	if (now - mLastKeepalive > mKeepaliveDelay)
	{
		// It's time, send a packet and if false return false.
		if (!SendPacket(PacketType::C_KeepAlive, true))
			return false;

		// Otherwise update the last keepalive time.
		mLastKeepalive = now;
	}

	// Return true.
	return true;
}

bool ClientNetwork::SendPacket(PacketType code, bool falseOnDisconnectOnly)
{
	// Setup the packet code.
	sf::Uint8 pCode = code;
		
	// Write to the packet buffer.
	sf::Packet buffer;
	buffer << code;

	// Send the buffer and check if it worked.
	sf::Socket::Status status = mClient.Send(buffer);
	if (status != sf::Socket::Done)
	{
		// How are we returning our false's? If it's disconnect only, we need to know.
		if (falseOnDisconnectOnly)
		{
			// This is the purpose of keepalives, if the reason it failed was a disconnect return false.
			if (status == sf::Socket::Status::Disconnected)
				return false;
		}
		else
		{
			// Nah, we return false on everything.
			return false;
		}
	}

	// I guess it was good, return true.
	return true;
}