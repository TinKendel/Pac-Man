#include "MainMenu.hpp"
#include "DrawText.hpp"
#include "Global.hpp"

MainMenu::MainMenu(float width, float height)//, sf::RenderWindow& i_window)
{
	font.loadFromFile("Fonts/PixelOperator.ttf");

	//Play
	
	mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(sf::Color::White);
	mainMenu[0].setString("Play");
	mainMenu[0].setPosition(400, 300);

	////Game Settings

	//mainMenu[1].setFont(font);
	//mainMenu[1].setFillColor(sf::Color::White);
	//mainMenu[1].setString("Game Difficulty");
	//mainMenu[1].setPosition(400, 400);

	//Highscores

	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(sf::Color::White);
	mainMenu[1].setString("Highscores");
	mainMenu[1].setPosition(400, 400);


	//Exit
	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(sf::Color::White);
	mainMenu[2].setString("Exit");
	mainMenu[2].setPosition(400, 500);

	MainMenuSelected = -1;
};

MainMenu::~MainMenu()
{
	
}

void MainMenu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < Max_main_menu; i++)
	{
		window.draw(mainMenu[i]);
	}
}

void MainMenu::MoveUp()
{
	if (MainMenuSelected - 1 >= 0)
	{
		mainMenu[MainMenuSelected].setFillColor(sf::Color::White);

		MainMenuSelected--;
		if (MainMenuSelected == -1)
		{
			MainMenuSelected = 2;
		}
		mainMenu[MainMenuSelected].setFillColor(sf::Color::Blue);
	}
}

void MainMenu::MoveDown()
{
	if (MainMenuSelected + 1 <= Max_main_menu)
	{
		mainMenu[MainMenuSelected].setFillColor(sf::Color::White);
		MainMenuSelected++;

		if (MainMenuSelected == 3)
		{
			MainMenuSelected = 0;
		}
		mainMenu[MainMenuSelected].setFillColor(sf::Color::Blue);
	}
}

OptionsMenu::OptionsMenu(float width, float height)
{
	font.loadFromFile("Fonts/PixelOperator.ttf");

	//Normal

	optionsMenu[0].setFont(font);
	optionsMenu[0].setFillColor(sf::Color::White);
	optionsMenu[0].setString("Normal");
	optionsMenu[0].setPosition(336, 252);



	//Hard

	optionsMenu[1].setFont(font);
	optionsMenu[1].setFillColor(sf::Color::White);
	optionsMenu[1].setString("Hard");
	optionsMenu[1].setPosition(336, 352);

	//Insane

	optionsMenu[2].setFont(font);
	optionsMenu[2].setFillColor(sf::Color::White);
	optionsMenu[2].setString("Insane");
	optionsMenu[2].setPosition(336, 452);


	////Exit
	//mainMenu[3].setFont(font);
	//mainMenu[3].setFillColor(sf::Color::White);
	//mainMenu[3].setString("Exit");
	//mainMenu[3].setPosition(400, 600);

	OptionsMenuSelected = -1;
};

OptionsMenu::~OptionsMenu()
{

}

void OptionsMenu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < Max_options_menu; i++)
	{
		window.draw(optionsMenu[i]);
	}
}

void OptionsMenu::MoveUp()
{
	if (OptionsMenuSelected - 1 >= 0)
	{
		optionsMenu[OptionsMenuSelected].setFillColor(sf::Color::White);

		OptionsMenuSelected--;
		if (OptionsMenuSelected == -1)
		{
			OptionsMenuSelected = 2;
		}
		optionsMenu[OptionsMenuSelected].setFillColor(sf::Color::Blue);
	}
}

void OptionsMenu::MoveDown()
{
	if (OptionsMenuSelected + 1 <= Max_options_menu)
	{
		optionsMenu[OptionsMenuSelected].setFillColor(sf::Color::White);
		OptionsMenuSelected++;

		if (OptionsMenuSelected == 3)
		{
			OptionsMenuSelected = 0;
		}
		optionsMenu[OptionsMenuSelected].setFillColor(sf::Color::Blue);
	}
}