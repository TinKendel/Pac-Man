#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#define Max_main_menu 3
#define Max_options_menu 3

class MainMenu 
{
public:
	MainMenu(float width, float hight);

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();

	int MainMenuPressed() {
		return MainMenuSelected;
	}
	~MainMenu();

private:
	int MainMenuSelected;
	sf::Font font;
	sf::Text mainMenu[Max_main_menu];
};

class OptionsMenu
{
public:
	OptionsMenu(float width, float hight);

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();

	int OptionsMenuPressed() {
		return OptionsMenuSelected;
	}
	~OptionsMenu();

private:
	int OptionsMenuSelected;
	sf::Font font;
	sf::Text optionsMenu[Max_options_menu];
};