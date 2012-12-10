/*
 * Project: C++_Game_Engine_Client
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 9 December 2012
 * Purpose: To provide a Client for a 2D C++ Game Engine
 * File: C++_Game_Engine_Client\main.cpp
 */

#include <iostream>
#include "SFML\Audio.hpp"
#include "SFML\Config.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Network.hpp"
#include "SFML\System.hpp"
#include "SFML\Window.hpp"

int main()
{
	std::cout << "Test" << std::endl;
	std::string ip;
	std::cin >> ip;

	// Create the main window
    sf::Window App(sf::VideoMode(800, 600, 32), "SFML Events");
	App.SetFramerateLimit(75);

    // Get a reference to the input manager associated to our window, and store it for later use
    const sf::Input& Input = App.GetInput();

	sf::SocketTCP Client;
	if (Client.Connect(8081, ip) != sf::Socket::Done)
	{
		// Error...
		return -1;
	}

    // Start main loop
    while (App.IsOpened())
    {
        // Process events
        sf::Event Event;
        while (App.GetEvent(Event))
        {
            // Close window : exit
            if (Event.Type == sf::Event::Closed)
                App.Close();

            // Escape key : exit
            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
                App.Close();
        }

		// Get mouse states.
        unsigned int MouseX          = Input.GetMouseX();
        unsigned int MouseY          = Input.GetMouseY();
		bool MouseLeftClick			 = Input.IsMouseButtonDown(sf::Mouse::Left);
		bool MouseRightClick		 = Input.IsMouseButtonDown(sf::Mouse::Right);

		char Buffer[] = "Hi guys ! ";
		Buffer[9] = clock();
		sf::Socket::Status status = Client.Send(Buffer, sizeof(Buffer));
		if (status != sf::Socket::Done)
		{
			if (status == sf::Socket::Status::Disconnected)
				App.Close();

			// Error...
			std::cout << "Error";
		}
		std::cout << Client.IsValid();

        // Display window on screen
        App.Display();
    }

	Client.Close();

	// End of Programme
#if DEBUG
	system("pause");
#endif
	return 0;
}