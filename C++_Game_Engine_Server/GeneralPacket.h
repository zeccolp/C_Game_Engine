/*
 * Project: C++_Game_Engine_Server
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 21 December 2012
 * Purpose: To provide a General Packet for a Server for a 2D C++ Game Engine
 * File: C++_Game_Engine_Server\GeneralPacket.h
 */

#pragma once
#include "SFML\Network.hpp"
#include "SFML\Graphics.hpp"
#include "Player.h"

class GeneralPacket : public sf::Packet
{
	public:
		friend GeneralPacket& operator <<(GeneralPacket& packet, Player& player);
		friend GeneralPacket& operator <<(GeneralPacket& packet, sf::Vector2f& vector);
		friend sf::Packet;
	private:
};