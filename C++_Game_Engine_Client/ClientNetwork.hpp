#pragma once
#include "SFML\Network.hpp"
#include <time.h>

class ClientNetwork
{
	public:
		enum PacketType { C_KeepAlive = 0, };

		ClientNetwork();
		ClientNetwork(int port, sf::IPAddress ipAddress, int keepaliveDelay = 250);
		~ClientNetwork();
		bool Connect();
		bool RunIteration();
		bool IsAlive();
		bool SendPacket(PacketType code, bool falseOnDisconnectOnly = false);
	private:
		clock_t mLastKeepalive;
		sf::SocketTCP mClient;
		int mPort;
		sf::IPAddress mIPAddress;
		int mKeepaliveDelay;
};