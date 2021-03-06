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
#include "../C++_Game_Engine_Client/Map.h"

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
			// Setup and prompt for map size.
			int width, height, layers;
			std::cout << "Enter map size (Width Height Layers) then press enter: ";
			std::cin >> width >> height >> layers;

			// Create the map.
			std::cout << "Creating map of size " << width << "W, " << height << "H, " << layers << "ML, " << layers << "FL." << std::endl;
			Map thisMap(width, height, (layers * 2));

			// Tell them we're creating the window.
			std::cout << "Creating window." << std::endl;

			// Create the main window
			sf::RenderWindow App(sf::VideoMode(800, 600, 32), "C++ Game Engine MapEditor");
			App.SetFramerateLimit(60);

			// Create our view and set the window to it.
			sf::View WindowView = App.GetView();
			App.SetView(WindowView);

			// Get a reference to the input manager associated to our window, and store it for later use
			const sf::Input& Input = App.GetInput();

			std::cout << "Window created. Loading memory." << std::endl;

			// Create our variables.
			bool inMenu = true;
			int menu = -1;
			int delay = 0;

			// Create our menu's.
			int totalMenus = 3;
			RadialMenu * rMenus = new RadialMenu[totalMenus];

			// Setup our firstFocus variable.
			bool firstFocus = false;

			// Load up a font.
			sf::Font font;
			if (!font.LoadFromFile("Fonts\\consolab.ttf"))
			{
				App.Close();
				std::cout << "There was an issue loading the font.";
			}

			// Create the text to display.
			sf::String text;
			text.SetFont(font);
			text.SetSize(18.0f);
			text.SetText("Please click inside the window to get started.");
			text.SetPosition(400 - (text.GetRect().Right - text.GetRect().Left) / 2, 300);
			text.SetColor(sf::Color(0, 0, 0, 255));

			// Create the Image we will be using.
			sf::Image image;
			if (!image.LoadFromFile("Content\\Map_Editor_Tool_Icons.png"))
			{
				App.Close();
				std::cout << "There was an issue loading the icons.";
			}
			image.SetSmooth(false);

			// Create the current property and sub-layer.
			unsigned int currentProperty = 0;
			unsigned int currentSubLayer = 0;

			// Create the currently selected tile.
			unsigned int currentTile = 15;

			// Create the current non-menu menu.
			unsigned short int currentNonMenu = 0;

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
					rMenus[i] = RadialMenu(layers);

					sf::IntRect * rectangles = new sf::IntRect[layers];
					int * goToMenu = new int[layers];
					for (int l = 0; l < layers; l++)
					{
						rectangles[l] = sf::IntRect(32, 32 * l, 64, 32 + 32 * l);
						goToMenu[l] = -1;
					}

					rMenus[i].SetView(800, 600);
					rMenus[i].SetMenus(goToMenu, 0);
					rMenus[i].CreateSprites(rectangles, image);
				}
				else if (i == 0)
				{
					rMenus[i] = RadialMenu(4);
					sf::IntRect rectangles[4] = {sf::IntRect(0, 0, 32, 32), sf::IntRect(0, 32, 32, 64), sf::IntRect(0, 64, 32, 96), sf::IntRect(0, 96, 32, 128)};
					int goToMenu[4] = {1, 1, 1, -1};
					rMenus[i].SetView(800, 600);
					rMenus[i].SetMenus(goToMenu, -1);
					rMenus[i].CreateSprites(rectangles, image);
				}
			}
			
			std::cout << "Loaded memory. Opening window." << std::endl;

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
						if (firstFocus)
						{
							// Setup the delta. (Only needed for positive/negative)
							bool delta = Event.MouseWheel.Delta > 0 ? true : false;
						
							// Check what menu we are in.
							if (inMenu && menu == -1)
							{
								// No menu. Join the main menu.
								menu = 0;
								rMenus[menu].UnSelect();
							}
							else if (inMenu)
							{
								rMenus[menu].MouseScroll(delta);
							}

							// Setup the delay so that it slows how many scrolls per second.
							delay = 4;
						}
					}
					
					if (Event.Type == sf::Event::MouseButtonPressed && delay == 0)
					{
						if (firstFocus)
						{
							// Check what button was clicked.
							if (Event.MouseButton.Button == sf::Mouse::Button::Right)
							{
								if (inMenu && menu > -1)
								{
									menu = rMenus[menu].UnSelect();
									rMenus[menu].UnSelect();
								}
								else if (inMenu)
								{
									if (currentProperty >= 1 && currentProperty <= 2)
									{
										int mouseX = Input.GetMouseX() / 32;
										int mouseY = Input.GetMouseY() / 32;
										
										if (mouseX >= 0 && mouseX < width && mouseY >= 0 && mouseY < height)
											thisMap.SetTile(mouseX, mouseY, 0, (currentProperty - 1) * (layers) + currentSubLayer);
									}
								}
							}
							else if (Event.MouseButton.Button == sf::Mouse::Button::Left)
							{
								if (inMenu && menu == 0)
								{
									currentProperty = rMenus[menu].GetSelectedIndex();
									menu = rMenus[menu].Select();
									rMenus[menu].UnSelect();
								}
								else if (inMenu && menu == 1)
								{
									currentSubLayer = rMenus[menu].GetSelectedIndex();
									menu = rMenus[menu].Select();
									rMenus[menu].UnSelect();
								}
								else if (inMenu)
								{
									if (currentProperty >= 1 && currentProperty <= 2)
									{
										int mouseX = Input.GetMouseX() / 32;
										int mouseY = Input.GetMouseY() / 32;

										if (mouseX >= 0 && mouseX < width && mouseY >= 0 && mouseY < height)
											thisMap.SetTile(mouseX, mouseY, currentTile, (currentProperty - 1) * (layers) + currentSubLayer);
									}
								}
							}

							// Setup the delay so nothing is processed too quickly.
							delay = 4;
						}
						else
							firstFocus = true;
					}
					
					if (Event.Type == sf::Event::Resized)
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

				if (firstFocus)
				{
					// Draw the Map. (Built into the map class. Lucky us! YAY! :D)
					thisMap.Draw(App);

					if (inMenu && menu != -1)
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
				}
				else
				{
					App.Draw(text);
				}

				// Display window on screen
				App.Display();
			}

			std::cout << "Closed window. Destroying loaded memory." << std::endl;
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