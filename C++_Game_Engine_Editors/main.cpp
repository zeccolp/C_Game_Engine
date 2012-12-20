/*
 * Project: C++_Game_Engine_Client
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 17 December 2012
 * Purpose: To provide Editors for a 2D C++ Game Engine
 * File: C++_Game_Engine_Editors\main.cpp
 */

#include <iostream>
#include <cmath>
#include "SFML\Audio.hpp"
#include "SFML\Config.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Network.hpp"
#include "SFML\System.hpp"
#include "SFML\Window.hpp"
#include "RadialMenu.h"

#define PI 3.14159265358979323846

int main()
{
	// Create our item reference.
	int nextItem = 0;

	// While we haven't requested to exit the menu.
	while (nextItem != -1)
	{
		// Reset the number. (Didn't seem to work, we'll need to clear CIN.
		nextItem = 0;

		// Prompt and read new number.
		std::cout << "Enter a number for what you wish to do: " << std::endl << "------" << std::endl << "-1: Exit" << std::endl << " 0: Main Menu" << std::endl << " 1: Map Editor" << std::endl << "-----" << std::endl << "Command: ";
		std::cin >> nextItem;

		if (nextItem == 1)
		{
			// Create the main window
			sf::RenderWindow App(sf::VideoMode(800, 600, 32), "C++ Game Engine MapEditor");
			App.SetFramerateLimit(60);

			// Create our view and set the window to it.
			sf::View WindowView = App.GetView();
			App.SetView(WindowView);

			// Get a reference to the input manager associated to our window, and store it for later use
			const sf::Input& Input = App.GetInput();

			// Create our variables.
			int menu = -1;
			int delay = 0;

			// Create our menu's.
			int totalMenus = 3;
			RadialMenu * rMenus = new RadialMenu[totalMenus];

			// Create the Image we will be using.
			sf::Image image;
			if (!image.LoadFromFile("Content\\Map_Editor_Tool_Icons.png"))
			{
				App.Close();
				std::cout << "There was an issue loading the icons.";
			}
			image.SetSmooth(false);

			// Create our array of sprites.
			sf::Sprite sprites[2];

			// Setup our center-circle and pointer.
			sprites[0].SetImage(image);
			sprites[0].SetSubRect(sf::IntRect(0, 160, 64, 224));
			sprites[0].SetCenter(32, 32);
			sprites[0].SetPosition(416, 316);
			sprites[1].SetImage(image);
			sprites[1].SetSubRect(sf::IntRect(0, 224, 64, 288));
			sprites[1].SetCenter(32, 32);
			sprites[1].SetPosition(416, 316);
			
			// Setup our menus.
			for (int i = 0; i < totalMenus; i++)
			{
				if (i == 2)
				{
					rMenus[i] = RadialMenu(2);
					sf::IntRect rectangles[2] = {sf::IntRect(0, 0, 32, 32), sf::IntRect(0, 32, 32, 64)};
					int goToMenu[2] = {3, 3};
					rMenus[i].SetView(800, 600);
					rMenus[i].SetMenus(goToMenu, 1);
					rMenus[i].CreateSprites(rectangles, image);
				}
				else if (i == 1)
				{
					rMenus[i] = RadialMenu(5);
					sf::IntRect rectangles[5] = {sf::IntRect(32, 0, 64, 32), sf::IntRect(32, 32, 64, 64), sf::IntRect(32, 64, 64, 96), sf::IntRect(32, 96, 64, 128), sf::IntRect(32, 128, 64, 160)};
					int goToMenu[5] = {2, 2, 2, 2, 2};
					rMenus[i].SetView(800, 600);
					rMenus[i].SetMenus(goToMenu, 0);
					rMenus[i].CreateSprites(rectangles, image);
				}
				else if (i == 0)
				{
					rMenus[i] = RadialMenu(4);
					sf::IntRect rectangles[4] = {sf::IntRect(0, 0, 32, 32), sf::IntRect(0, 32, 32, 64), sf::IntRect(0, 64, 32, 96), sf::IntRect(0, 96, 32, 128)};
					int goToMenu[4] = {1, 1, 1, 1};
					rMenus[i].SetView(800, 600);
					rMenus[i].SetMenus(goToMenu, -1);
					rMenus[i].CreateSprites(rectangles, image);
				}
			}

			// Start main loop
			while (App.IsOpened())
			{
				// Clean the screen
				App.Clear(sf::Color(255, 255, 255));

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

					// If we moved the wheel within the delay.
					if ((Event.Type == sf::Event::MouseWheelMoved) && delay == 0)
					{
						// Setup the delta. (Only needed for positive/negative)
						bool delta = Event.MouseWheel.Delta > 0 ? true : false;
						
						// Check what menu we are in.
						if (menu == -1)
						{
							// No menu. Join the main menu.
							menu = 0;
						}
						else
						{
							rMenus[menu].MouseScroll(delta);
						}

						// Setup the delay so that it slows how many scrolls per second.
						delay = 4;

					}
					else if (Event.Type == sf::Event::MouseButtonPressed && delay == 0)
					{
						// Check what button was clicked.
						if (Event.MouseButton.Button == sf::Mouse::Button::Right)
						{
							menu = rMenus[menu].UnSelect();
							rMenus[menu].UnSelect();
						}
						else if (Event.MouseButton.Button == sf::Mouse::Button::Left)
						{
							menu = rMenus[menu].Select();
						}

						// Setup the delay so nothing is processed too quickly.
						delay = 4;
					}
					else if (Event.Type == sf::Event::Resized)
					{
						WindowView = sf::View(sf::FloatRect(0, 0, Event.Size.Width, Event.Size.Height));
						rMenus[0].SetView(Event.Size.Width, Event.Size.Height);
						rMenus[1].SetView(Event.Size.Width, Event.Size.Height);
						rMenus[2].SetView(Event.Size.Width, Event.Size.Height);
						sprites[0].SetPosition(Event.Size.Width / 2 + 16, Event.Size.Height / 2 + 16);
						sprites[1].SetPosition(Event.Size.Width / 2 + 16, Event.Size.Height / 2 + 16);
					}
				}

				// Decrement the Delay as needed.
				if (delay > 0)
					delay--;

				if (menu != -1)
				{
					if (menu > 0)
					{
						for (int i = 0; i < menu; i++)
						{
							rMenus[i].Draw(App, true);
						}
					}

					rMenus[menu].Draw(App);
				
					sprites[1].SetRotation((-(rMenus[menu].GetSelectedIndex() * PI * 2 / rMenus[menu].GetTotalItems()) + (PI / 2)) / PI * 180);
					App.Draw(sprites[0]);
					App.Draw(sprites[1]);
				}

				// Display window on screen
				App.Display();
			}
		}

		// Write a blank line so we don't run over something.
		std::cout << std::endl;
	}

	// End of Programme
#if DEBUG
	system("pause");
#endif
	return 0;
}