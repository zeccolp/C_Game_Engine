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
		std::cout << "Enter a number for what you wish to do: " << std::endl << "------" << std::endl << "-1: Exit" << std::endl << " 0: Main Menu" << std::endl << " 1: Map Editor" << std::endl;
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
			int menu = 0;
			int selectedIndex = 0;
			int delay = 0;
			int totalOptions = 16;

			// Create the Image we will be using.
			sf::Image image;
			if (!image.LoadFromFile("Content\\Map_Editor_Tool_Icons.png"))
			{
				App.Close();
				std::cout << "There was an issue loading the icons.";
			}
			image.SetSmooth(false);

			// Create one of our sprites. (We need more than 30.)
			sf::Sprite sprite;
			sprite.SetImage(image);
			sprite.SetSubRect(sf::IntRect(32, 0, 64, 32));

			// Create our array of sprites.
			sf::Sprite sprites[35];

			// Load up the array of sprites, set the positions, etc.
			for (int i = 0; i < 15; i++)
			{
				sprites[i].SetImage(image);
				sprites[i].SetSubRect(sf::IntRect(0, (i / 5) * 32, 32, (i / 5) * 32 + 32));
				sprites[i].SetPosition(400 + (cos(i * PI * 2 / totalOptions - PI / 2) * 96), 300 + (sin(i * PI * 2 / totalOptions - PI / 2) * 96));
				sprites[i + 15].SetImage(image);
				sprites[i + 15].SetSubRect(sf::IntRect(32, (i % 5) * 32, 64, (i % 5) * 32 + 32));
				sprites[i + 15].SetPosition(400 + (cos(i * PI * 2 / totalOptions - PI / 2) * 96), 300 + (sin(i * PI * 2 / totalOptions - PI / 2) * 96));
			}

			// Add the P
			sprites[30].SetImage(image);
			sprites[30].SetSubRect(sf::IntRect(0, 96, 32, 128));
			sprites[30].SetPosition(400 + (cos(15 * PI * 2 / totalOptions - PI / 2) * 96), 300 + (sin(15 * PI * 2 / totalOptions - PI / 2) * 96));

			// Setup our reference sprite for the center-circle.
			sprites[31].SetImage(image);
			sprites[31].SetPosition(400, 300);
			sprites[32].SetImage(image);
			sprites[32].SetPosition(400, 300);

			// Setup our center-circle and pointer.
			sprites[33].SetImage(image);
			sprites[33].SetSubRect(sf::IntRect(0, 160, 64, 224));
			sprites[33].SetCenter(32, 32);
			sprites[33].SetPosition(416, 316);
			sprites[34].SetImage(image);
			sprites[34].SetSubRect(sf::IntRect(0, 224, 64, 288));
			sprites[34].SetCenter(32, 32);
			sprites[34].SetPosition(416, 316);

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
						int delta = Event.MouseWheel.Delta;

						// Check what menu we are in.
						if (menu == 0)
						{
							// No menu. Join the main menu.
							menu = 1;
							selectedIndex = 0;
							std::cout << selectedIndex;
						}
						else if (menu == 1)
						{
							// Main menu. Let's circle around it.
							selectedIndex += (delta > 0 ? -1 : 1);

							if (selectedIndex > 15)
								selectedIndex = 0;
							else if (selectedIndex < 0)
								selectedIndex = 15;

							std::cout << selectedIndex;
						}

						// Setup the delay so that it slows how many scrolls per second.
						delay = 4;
					}
					else if (Event.Type == sf::Event::MouseButtonPressed && delay == 0)
					{
						// Check what button was clicked.
						if (Event.MouseButton.Button == sf::Mouse::Button::Right)
						{
							// What menu are we in?
							if (menu == 1)
								menu--; // Main menu, leave it.
							else if (menu >= 2 && menu < 18)
							{
								// A sub menu, go to the main menu.
								selectedIndex = menu - 2;
								menu = 1;
							}
						}
						else if (Event.MouseButton.Button == sf::Mouse::Button::Left)
						{
							// The left button was pressed, are we in the main menu?
							if (menu == 1)
							{
								// Yes, let's join the submenu.
								menu = selectedIndex + 2;
								sprites[31].SetSubRect(sprites[selectedIndex].GetSubRect());
								sprites[32].SetSubRect(sprites[selectedIndex + 15].GetSubRect());
								selectedIndex = 0;
							}
						}

						// Setup the delay so nothing is processed too quickly.
						delay = 4;
					}
					else if (Event.Type == sf::Event::Resized)
					{
						WindowView = sf::View(sf::FloatRect(0, 0, Event.Size.Width, Event.Size.Height));
					}
				}

				// Decrement the Delay as needed.
				if (delay > 0)
					delay--;

				// What menu are we in?
				if (menu == 1)
				{
					// Main menu, loop through the sprites.
					for (int i = 0; i < 15; i++)
					{
						// Is this our selected area?
						if (i == selectedIndex)
						{
							// Yes, set the colour to Green.
							sprites[i + 15].SetColor(sf::Color(0, 255, 0, 255));
						}
						else
						{
							// No, set the colour to White.
							sprites[i + 15].SetColor(sf::Color(255, 255, 255, 255));
						}

						// Draw all the sprites.
						App.Draw(sprites[i]);
						App.Draw(sprites[i + 15]);
					}

					App.Draw(sprites[30]);

					// Let's setup our rotation sprites.
					sprites[34].SetRotation((-(selectedIndex * PI * 2 / totalOptions) + (PI / 2)) / PI * 180);

					// Draw the rotation sprites.
					App.Draw(sprites[33]);
					App.Draw(sprites[34]);

					//sprite.SetPosition(400 + (cos(selectedIndex * PI * 2 / 15) * 96), 300 + (sin(selectedIndex * PI * 2 / 15) * 96));
					//App.Draw(sprite);
				}
				else if (menu > 1)
				{
					// If we're in a submenu, let's draw the submenu thing.
					App.Draw(sprites[31]);
					App.Draw(sprites[32]);

					// Let's setup our rotation sprites.
					sprites[34].SetRotation((-(selectedIndex * PI * 2 / totalOptions) + (PI / 2)) / PI * 180);

					// Draw the rotation sprites.
					App.Draw(sprites[33]);
					App.Draw(sprites[34]);
				}

				// Display window on screen
				App.Display();
			}
		}
	}

	// End of Programme
#if DEBUG
	system("pause");
#endif
	return 0;
}