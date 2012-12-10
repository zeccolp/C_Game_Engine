/*
 * Project: C++_Game_Engine_Server
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 9 December 2012
 * Purpose: To provide a Network Interface for a Server for a 2D C++ Game Engine
 * File: C++_Game_Engine_Server\ServerNetwork.cpp
 */

#include <iostream>
#include <time.h>
#include "SFML\Audio.hpp"
#include "SFML\Config.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Network.hpp"
#include "SFML\System.hpp"
#include "SFML\Window.hpp"
#include "ServerNetwork.hpp"
#include "Player.hpp"

ServerNetwork::ServerNetwork(int port)
{
	// Try to open the port we need.
	if (!mListener.Listen(port))
		std::cout << "Error! Could not initialize listener!";
	else
		std::cout << "Network seems to have initialized correctly." << std::endl;

	// Unblock the networking.
	mListener.SetBlocking(false);
}

ServerNetwork::~ServerNetwork()
{
	
}

void ServerNetwork::RunIteration(Player* players, int playerCount)
{
	// Check for Network Connections
	sf::SocketTCP Client;
	sf::IPAddress ClientAddress;

	if (mListener.Accept(Client, &ClientAddress) != sf::Socket::Done)
	{
		// Connection failed. Nothing to do.
	}
	else
	{
		// Someone is trying to connect, try to find an open spot.
		bool didConnect = false;

		// Loop through possibilities.
		for (int p = 0; p < playerCount; p++)
		{
			// If this spot is open and there has not yet been a connection
			if (players[p].GetConnected() == false && !didConnect)
			{
				// Connect our player.
				players[p].SetClient(Client);
				players[p].SetAddress(ClientAddress);
				players[p].SetConnected(true);
				didConnect = true;
			}

			// If they connected, break the loop.
			if (didConnect)
				break;
		}

		// We couldn't find a spot, close their connection.
		if (!didConnect)
			Client.Close();
		else
			std::cout << "Client connected: " << ClientAddress;
	}
	
	// Loop through all the players so we can see if they sent anything
	for (int p = 0; p < playerCount; p++)
	{
		// If we have a connection, we'll want to process it.
		if (players[p].GetConnected())
		{
			// Get their Client
			sf::SocketTCP PlayerClient = players[p].GetClient();

			// Setup variables.
			char Buffer[128];
			std::size_t Received;

			// Read from the buffer.
			sf::Socket::Status status = PlayerClient.Receive(Buffer, sizeof(Buffer), Received);

			// If it was a bad read, we might have more to do.
			if (status != sf::Socket::Done)
			{
				// If it was a disconnect, we have more to do.
				if (status == sf::Socket::Disconnected)
				{
					// Close the client, set the connection to disconnected, and alert the server to the disconnect.
					PlayerClient.Close();
					players[p].SetConnected(false);
					std::cout << "Client (" << players[p].GetAddress() << ") disconnected." << std::endl;
				}
				else
				{
					// Output the status so we can tell what happened.
					std::cout << status;
				}
			}
			else // Just tell us what they sent and if they're valid or not.
				std::cout << Buffer << players[p].GetClient().IsValid();
			
			// Update the player client.
			players[p].SetClient(PlayerClient);
		}
	}
}