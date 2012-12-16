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
#include "ClientNetwork.h"
#include "Player.h"
#include "GeneralPacket.h"
#include "Menu.h"
#include "MainMenu.h"

int main()
{
	// Output standard headers.
	std::cout << "C++ Game Engine Client" << std::endl << "Enter the IP of the Server you wish to connect to: (will connect on port 8081)" << std::endl;
	std::string ip;
	std::cin >> ip;

	// Create the main window
	sf::RenderWindow App(sf::VideoMode(800, 600, 32), "C++ Game Engine");
	App.SetFramerateLimit(60);

	// Get a reference to the input manager associated to our window, and store it for later use
	const sf::Input& Input = App.GetInput();

	// Create and connect to the Server.
	ClientNetwork network(8081, ip);
	if (!network.Connect())
		return -1;

	// Create our player object.
	Player player;

	// Create the font object.
	sf::Font MyFont;

	// Try to load some font from our fonts folder.
	if (!MyFont.LoadFromFile("Fonts\\consola.ttf"))
	{
		// Just close if we errored.
		App.Close();
	}

	// Setup the Text object
	sf::String Text("Hello", MyFont, 18);

	// Let's create our Menu to be used a little later.
	Menu * menu = new MainMenu(MyFont);

	// Start main loop
	while (App.IsOpened())
	{
		// This will return false only if our Keepalives failed.
		if (!network.RunIteration(player))
			App.Close();

		// Clean the screen
		App.Clear();

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
		bool MouseLeftClick          = Input.IsMouseButtonDown(sf::Mouse::Left);
		bool MouseRightClick         = Input.IsMouseButtonDown(sf::Mouse::Right);

		// Check for movement.
		if (Input.IsKeyDown(sf::Key::W))
			player.Move(0x01, network);
		if (Input.IsKeyDown(sf::Key::S))
			player.Move(0x02, network);
		if (Input.IsKeyDown(sf::Key::A))
			player.Move(0x04, network);
		if (Input.IsKeyDown(sf::Key::D))
			player.Move(0x08, network);

		// Update the player. (Internal synchronization logic and whatnot.)
		player.Update();

		// Update the Text Position and draw it.
		Text.SetPosition(player.GetDisplayPosition(true));
		App.Draw(Text);

		// This should call the MainMenu::RunIteration(sf::RenderWindow, ClientNetwork)
		menu->RunIteration(App, network);

		// Display window on screen
		App.Display();
	}

	// End of Programme
#if DEBUG
	system("pause");
#endif
	return 0;
}