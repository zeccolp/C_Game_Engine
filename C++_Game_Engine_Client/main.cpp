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
#include "GameMenu.h"
#include "InputHandler.h"
#include "Map.h"

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

	// Let's create our Menu to be used a little later.
	Menu * menu = new MainMenu(MyFont);

	// Setup a reference to what menu we are on.
	Menu::NewMenu menuName = Menu::M_MainMenu;

	// Create an Input Handler.
	InputHandler inputHandler = InputHandler();
	
	// Start main loop
	while (App.IsOpened())
	{
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

		// Run an iteration of the Input Handler.
		inputHandler.RunIteration(App);

		// This should call the MainMenu::RunIteration(sf::RenderWindow, ClientNetwork) or the GameMenu::RunIteration(sf::RenderWindow, ClientNetwork) as appropriate.
		Menu::NewMenu newMenu = menu->RunIteration(App, network, player);

		// If the menu we are going to is not the same as where we are, let's do stuff.
		if (newMenu != menuName)
		{
			// Where are you going?
			if (newMenu == Menu::M_MainMenu)
			{
				// You're going to the Main Menu.
				menu = new MainMenu(MyFont);
				menuName = Menu::M_MainMenu;
			}
			else if (newMenu == Menu::M_GameMenu)
			{
				// You're going to the Game Menu
				menu = new GameMenu(MyFont);
				menuName = Menu::M_GameMenu;
			}
		}

		// Display window on screen
		App.Display();
	}

	// End of Programme
#if DEBUG
	system("pause");
#endif
	return 0;
}