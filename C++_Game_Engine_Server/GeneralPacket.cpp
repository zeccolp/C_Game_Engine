/*
 * Project: C++_Game_Engine_Server
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 21 December 2012
 * Purpose: To provide a General Packet for a Server for a 2D C++ Game Engine
 * File: C++_Game_Engine_Server\GeneralPacket.cpp
 */

#include "GeneralPacket.h"

GeneralPacket& operator <<(GeneralPacket& packet, Player& player)
{
	// This will get complicated again, as adding natural types defined in sf::Packet require implicit conversions.

	// Create our reference to packet.
	GeneralPacket thisPacket = packet;

	// Write to the packet.
	thisPacket << player.GetName();
	thisPacket << player.GetPosition() << player.GetSprite() << player.GetDirection();

	// Change-up the references.
	packet = thisPacket;

	// Return the reference needed.
	return packet;
}

GeneralPacket& operator <<(GeneralPacket& packet, sf::Vector2f& vector)
{
	// This is a little more complicated, as an implicit conversion from sf::Packet to GeneralPacket is necessary.

	// Create a reference to "packet".
	GeneralPacket thisPacket = packet;
	
	// Write to the packet
	thisPacket << vector.x << vector.y;

	// Re-reference our "packet" to our reference.
	packet = thisPacket;

	// Return. Now when "thisPacket" is destroyed, another reference will pick it up.
	return packet;
}