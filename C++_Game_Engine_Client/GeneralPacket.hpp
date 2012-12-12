/*
 * Project: C++_Game_Engine_Client
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 11 December 2012
 * Purpose: To provide a General Packet for a Client for a 2D C++ Game Engine
 * File: C++_Game_Engine_Client\GeneralPacket.hpp
 */

#pragma once
#include "SFML\Network.hpp"
#include "SFML\Graphics.hpp"
#include "Player.hpp"

class GeneralPacket : public sf::Packet
{
	public:
		friend GeneralPacket& operator <<(GeneralPacket& packet, Player& player);
		friend GeneralPacket& operator <<(GeneralPacket& packet, sf::Vector2f& vector);
	private:
};