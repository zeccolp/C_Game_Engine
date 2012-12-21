/*
 * Project: C++_Game_Engine_Client
 * Author: Elliott Brown (EBrown8534)
 * Date Created: 16 December 2012
 * Purpose: To provide a Main-Menu for a Client for a 2D C++ Game Engine
 * File: C++_Game_Engine_Client\MainMenu.cpp
 */

#include "MainMenu.h"

MainMenu::MainMenu()
{

}

MainMenu::MainMenu(sf::Font font)
{
	// Copy the local parameter to our Class Member for our Font.
	this->mFont = font;

	// Update our Buttons, create the text, reference the font of our Member.
	this->mLoginButton = sf::String("Login", this->mFont, 18.0f);
	this->mRegisterButton = sf::String("Register", this->mFont, 18.0f);

	// Get the location of the buttons.
	sf::FloatRect lRect = this->mLoginButton.GetRect();
	sf::FloatRect rRect = this->mRegisterButton.GetRect();

	// Center them to the Screen.
	this->mLoginButton.SetPosition(400 - (lRect.Right / 2), 300 - (lRect.Bottom));
	this->mRegisterButton.SetPosition(400 - (rRect.Right / 2), 300 + (rRect.Bottom));

	// Create our Action and Cancel Buttons. (They're for later.)
	this->mActionButton = sf::String("Action", this->mFont, 18.0f);
	this->mCancelButton = sf::String("Cancel", this->mFont, 18.0f);

	// Create our Action Title (It's for later.)
	this->mActionTitle = sf::String("Action Title", this->mFont, 24.0f);

	// Create our Username, Password and Email. (Again, for later.)
	this->mUsername = sf::String("Username: ", this->mFont, 18.0f);
	this->mPassword = sf::String("Password: ", this->mFont, 18.0f);
	this->mEmail = sf::String("Email: ", this->mFont, 18.0f);

	// We're at the MainMenu, I hope.
	mMenuAction = MenuAction::M_MainMenu;

	this->mWaitingOnNetwork = false;
	this->mUsernameAct = "Elliott";
	this->mPasswordAct = "Password";
	this->mEmailAct = "Email";
}

void MainMenu::SetFont(sf::Font font)
{
	// Set our Class Member font to the parameter font.
	this->mFont = font;
}

Menu::NewMenu MainMenu::RunIteration(sf::RenderWindow &App, ClientNetwork &network, Player& player)
{
	// Get a reference to the input manager associated to our window, and store it for later use
	const sf::Input& Input = App.GetInput();

	// Get mouse states.
	unsigned int MouseX          = Input.GetMouseX();
	unsigned int MouseY          = Input.GetMouseY();
	bool MouseLeftClick          = Input.IsMouseButtonDown(sf::Mouse::Left);
	bool MouseRightClick         = Input.IsMouseButtonDown(sf::Mouse::Right);

	// Check if we are waiting on the network.
	if (this->mWaitingOnNetwork)
	{
		// We are, see if we have a packet.
		if (network.Receive(player))
		{
			// We do. No matter what it is we're done waiting.
			this->mWaitingOnNetwork = false;

			// If the players name was not set, return to the game menu.
			if (player.GetName() != "")
				return Menu::NewMenu::M_GameMenu;

			// Otherwise, there was no name set, set the response to say error.
			this->mResponse.SetPosition(0, 0);
			this->mResponse.SetText("There was an error processing your request!");
			this->mDisplayResponse = true;
		}
	}

	// If we're displaying the response, display it.
	if (this->mDisplayResponse)
		App.Draw(this->mResponse);

	// What menu are we in?
	if (mMenuAction == MenuAction::M_MainMenu)
	{
		// Main Menu. Draw our Login and Register Buttons.
		App.Draw(this->mLoginButton);
		App.Draw(this->mRegisterButton);
		
		// Reset the active input.
		mActiveInput = 0;

		if (!this->mWaitingOnNetwork)
		{
			// Did we click?
			if (MouseLeftClick == true)
			{
				// Yes, get the position of the Login and Register buttons.
				sf::FloatRect lRect = this->mLoginButton.GetRect();
				sf::FloatRect rRect = this->mRegisterButton.GetRect();

				// Find out if we were in either of them.
				if (MouseX >= lRect.Left && MouseX <= lRect.Right &&
					MouseY >= lRect.Top && MouseY <= lRect.Bottom)
				{
					// We were in the Login Button.
					mMenuAction = MenuAction::M_Login;
				}
				else if (MouseX >= rRect.Left && MouseX <= rRect.Right &&
					MouseY >= rRect.Top && MouseY <= rRect.Bottom)
				{
					// We were in the Register Button.
					mMenuAction = MenuAction::M_Register;
				}
			}
		}
	}
	else if (mMenuAction == MenuAction::M_Login)
	{
		// Login Menu, let's update our Action Title and Buttons.
		this->mActionTitle.SetText("Login Menu");
		this->mActionButton.SetText("Login");

		// Update the button positions.
		sf::FloatRect actionTitlePos = this->mActionTitle.GetRect();
		sf::FloatRect actionButtonPos = this->mActionButton.GetRect();
		sf::FloatRect cancelButtonPos = this->mCancelButton.GetRect();
		sf::FloatRect usernamePos = this->mUsername.GetRect();
		sf::FloatRect passwordPos = this->mPassword.GetRect();
		this->mActionTitle.SetPosition(400 - (actionTitlePos.Right - actionTitlePos.Left) / 2, 300 - (actionTitlePos.Bottom - actionTitlePos.Top) - (usernamePos.Bottom - usernamePos.Top) - 12);
		this->mUsername.SetPosition(400 - (usernamePos.Right - usernamePos.Left) / 2, 300 - (usernamePos.Bottom - usernamePos.Top) - 6);
		this->mPassword.SetPosition(400 - (passwordPos.Right - passwordPos.Left) / 2, 300);
		this->mActionButton.SetPosition(400 - (actionButtonPos.Right - actionButtonPos.Left) - 6, 300 + (passwordPos.Bottom - passwordPos.Top) + 6);
		this->mCancelButton.SetPosition(400 + 6, 300 + (passwordPos.Bottom - passwordPos.Top) + 6);

		// Reset the colours.
		this->mUsername.SetColor(sf::Color(255, 255, 255, 255));
		this->mPassword.SetColor(sf::Color(255, 255, 255, 255));

		// Make the current input stand out.
		if (mActiveInput == 0)
			this->mUsername.SetColor(sf::Color(0, 255, 0, 255));
		else if (mActiveInput == 1)
			this->mPassword.SetColor(sf::Color(0, 255, 0, 255));

		// Draw our Action Title
		App.Draw(this->mActionTitle);
		
		// Draw our "Input" fields
		App.Draw(this->mUsername);
		App.Draw(this->mPassword);

		// Draw our Buttons.
		App.Draw(this->mActionButton);
		App.Draw(this->mCancelButton);
		
		if (!this->mWaitingOnNetwork)
		{
			// Did we click?
			if (MouseLeftClick == true)
			{
				// Yes, get the position of the Login and Register buttons.
				sf::FloatRect aRect = this->mActionButton.GetRect();
				sf::FloatRect cRect = this->mCancelButton.GetRect();
				sf::FloatRect uRect = this->mUsername.GetRect();
				sf::FloatRect pRect = this->mPassword.GetRect();

				// Find out if we were in either of them.
				if (MouseX >= aRect.Left && MouseX <= aRect.Right &&
					MouseY >= aRect.Top && MouseY <= aRect.Bottom)
				{
					// We were in the Action Button. Create a packet.
					GeneralPacket packet;

					// Write a login packet.
					sf::Uint8 pCode = ClientNetwork::PacketType::C_Login;
					packet << pCode << this->mUsernameAct << this->mPasswordAct;

					// Connect to the network.
					if (network.Connect())
					{
						// Send the login packet, wait for the network.
						network.SendPacket(packet, false);
						this->mWaitingOnNetwork = true;
					}
				}
				else if (MouseX >= cRect.Left && MouseX <= cRect.Right &&
					MouseY >= cRect.Top && MouseY <= cRect.Bottom)
				{
					// We were in the Cancel Button.
					mMenuAction = MenuAction::M_MainMenu;
					this->mDisplayResponse = false;
				}
				else if (MouseX >= uRect.Left && MouseX <= uRect.Right &&
					MouseY >= uRect.Top && MouseY <= uRect.Bottom)
				{
					// We were in the Username
					mActiveInput = 0;
				}
				else if (MouseX >= pRect.Left && MouseX <= pRect.Right &&
					MouseY >= pRect.Top && MouseY <= pRect.Bottom)
				{
					// We were in the Password
					mActiveInput = 1;
				}
			}
		}
	}
	else if (mMenuAction == MenuAction::M_Register)
	{
		// Login Menu, let's update our Action Title and Buttons.
		this->mActionTitle.SetText("Register Menu");
		this->mActionButton.SetText("Register");

		// Update the button positions.
		sf::FloatRect actionTitlePos = this->mActionTitle.GetRect();
		sf::FloatRect actionButtonPos = this->mActionButton.GetRect();
		sf::FloatRect cancelButtonPos = this->mCancelButton.GetRect();
		sf::FloatRect usernamePos = this->mUsername.GetRect();
		sf::FloatRect passwordPos = this->mPassword.GetRect();
		sf::FloatRect emailPos = this->mEmail.GetRect();
		this->mActionTitle.SetPosition(400 - (actionTitlePos.Right - actionTitlePos.Left) / 2, 300 - (actionTitlePos.Bottom - actionTitlePos.Top) - 6 - (usernamePos.Bottom - usernamePos.Top) - 6);
		this->mUsername.SetPosition(400 - (usernamePos.Right - usernamePos.Left) / 2, 300 - (usernamePos.Bottom - usernamePos.Top) - 6);
		this->mPassword.SetPosition(400 - (passwordPos.Right - passwordPos.Left) / 2, 300);
		this->mEmail.SetPosition(400 - (emailPos.Right - emailPos.Left) / 2, 300 + (emailPos.Bottom - emailPos.Top) + 6);
		this->mActionButton.SetPosition(400 - (actionButtonPos.Right - actionButtonPos.Left) - 6, 300 + (passwordPos.Bottom - passwordPos.Top) + 6 + (emailPos.Bottom - emailPos.Top) + 6);
		this->mCancelButton.SetPosition(400 + 6, 300 + (passwordPos.Bottom - passwordPos.Top) + 6 + (emailPos.Bottom - emailPos.Top) + 6);

		// Reset the colours.
		this->mUsername.SetColor(sf::Color(255, 255, 255, 255));
		this->mPassword.SetColor(sf::Color(255, 255, 255, 255));
		this->mEmail.SetColor(sf::Color(255, 255, 255, 255));

		// Make the current input stand out.
		if (mActiveInput == 0)
			this->mUsername.SetColor(sf::Color(0, 255, 0, 255));
		else if (mActiveInput == 1)
			this->mPassword.SetColor(sf::Color(0, 255, 0, 255));
		else if (mActiveInput == 2)
			this->mEmail.SetColor(sf::Color(0, 255, 0, 255));

		// Draw our Action Title
		App.Draw(this->mActionTitle);
		
		// Draw our "Input" fields
		App.Draw(this->mUsername);
		App.Draw(this->mPassword);
		App.Draw(this->mEmail);

		// Draw our Buttons.
		App.Draw(this->mActionButton);
		App.Draw(this->mCancelButton);
		
		if (!this->mWaitingOnNetwork)
		{
			// Did we click?
			if (MouseLeftClick == true)
			{
				// Yes, get the position of the Login and Register buttons.
				sf::FloatRect aRect = this->mActionButton.GetRect();
				sf::FloatRect cRect = this->mCancelButton.GetRect();
				sf::FloatRect uRect = this->mUsername.GetRect();
				sf::FloatRect pRect = this->mPassword.GetRect();
				sf::FloatRect eRect = this->mEmail.GetRect();

				// Find out if we were in either of them.
				if (MouseX >= aRect.Left && MouseX <= aRect.Right && 
					MouseY >= aRect.Top && MouseY <= aRect.Bottom)
				{
					// We were in the Action Button. Create a packet.
					GeneralPacket packet;

					// Write a register packet.
					sf::Uint8 pCode = ClientNetwork::PacketType::C_Register;
					packet << pCode << this->mUsernameAct << this->mPasswordAct << this->mEmailAct;

					// Connect to the network.
					if (network.Connect())
					{
						// Send a register packet, wait on the network.
						network.SendPacket(packet, false);
						this->mWaitingOnNetwork = true;
					}
				}
				else if (MouseX >= cRect.Left && MouseX <= cRect.Right &&
					MouseY >= cRect.Top && MouseY <= cRect.Bottom)
				{
					// We were in the Cancel Button.
					mMenuAction = MenuAction::M_MainMenu;
					this->mDisplayResponse = false;
				}
				else if (MouseX >= uRect.Left && MouseX <= uRect.Right &&
					MouseY >= uRect.Top && MouseY <= uRect.Bottom)
				{
					// We were in the Username
					mActiveInput = 0;
				}
				else if (MouseX >= pRect.Left && MouseX <= pRect.Right &&
					MouseY >= pRect.Top && MouseY <= pRect.Bottom)
				{
					// We were in the Password
					mActiveInput = 1;
				}
				else if (MouseX >= eRect.Left && MouseX <= eRect.Right &&
					MouseY >= eRect.Top && MouseY <= eRect.Bottom)
				{
					// We were in the Email
					mActiveInput = 2;
				}
			}
		}
	}
	
	// Nothing happened, return to the main menu.
	return Menu::M_MainMenu;
}