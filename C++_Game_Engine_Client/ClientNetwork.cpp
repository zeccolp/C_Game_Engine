/*
 * Project: C++_Game_Engine_Client
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 10 December 2012
 * Purpose: To provide a Network Interface for a Client for a 2D C++ Game Engine
 * File: C++_Game_Engine_Client\ClientNetwork.cpp
 */

#include <time.h>
#include <iostream>
#include "SFML\Network.hpp"
#include "ClientNetwork.h"

ClientNetwork::ClientNetwork(int port, sf::IPAddress ipAddress, int keepaliveDelay)
{
	mPort = port;
	mIPAddress = ipAddress;
	mLastKeepalive = clock();
	mKeepaliveDelay = keepaliveDelay;
	mConnected = false;
}

ClientNetwork::~ClientNetwork()
{
	mClient.Close();
}

bool ClientNetwork::Connect()
{
	// Check if we are currently connected.
	if (!mConnected)
	{
		if (mClient.Connect(mPort, mIPAddress) != sf::Socket::Done)
		{
			mLastKeepalive = clock();
			return false;
		}
		else
		{
			mClient.SetBlocking(false);

			mConnected = true;
			mLastKeepalive = clock();
			return true;
		}
	}
	else
	{
		return true;
	}
}

bool ClientNetwork::RunIteration(Player& player)
{
	if (mConnected)
	{
		// Will only return false if the socket has disconnected.
		bool isAlive = IsAlive();

		// Will only return false if disconnect or receive error
		bool receiveStatus = Receive(player, true);

		// Will return false if socket has disconnected or errored on receive.
		return isAlive & receiveStatus;
	}
	else
	{
		return false;
	}
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

bool ClientNetwork::Receive(Player& player, bool trueOnNoData)
{
	// Setup our Packet and status.
	sf::Packet receive;
	sf::Socket::Status status = mClient.Receive(receive);

	// Check if anything was recieved
	if (status == sf::Socket::Status::Done)
	{
		// Process packet logic here
		sf::Int8 packetID;
		receive >> packetID;

		switch (packetID)
		{
			case S_LocationUpdate:
				float x;
				float y;
				receive >> x >> y;
				player.SetRealPosition(sf::Vector2f(x, y));
				std::cout << x << y;
				break;
		}

		return true;
	}
	else if (status == sf::Socket::Status::NotReady && trueOnNoData)
	{
		// Socket wasn't ready and they want us to pretend that's good, return true.
		return true;
	}

	// Something bad happened, return false.
	return false;
}

bool ClientNetwork::SendPacket(PacketType code, bool falseOnDisconnectOnly)
{
	// Setup the packet code.
	sf::Uint8 pCode = code;
	
	// Write to the packet buffer.
	sf::Packet buffer;
	buffer << pCode;

	// Send the buffer and check if it worked.
	return SendPacket(buffer, falseOnDisconnectOnly);
}

bool ClientNetwork::SendPacket(sf::Packet packet, bool falseOnDisconnectOnly)
{
	// Send the buffer and check if it worked.
	sf::Socket::Status status = mClient.Send(packet);
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
	else
	{
		// Update the last keepalive time. (Why? Because if we were successful in sending a packet then clearly the connection is still live.)
		mLastKeepalive = clock();
	}

	// Clearly it worked, or we're not reporting on the failure it had.
	return true;
}