#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <utility>

#include "HighscoreMenu.hpp"
#include "Sorting.hpp"


void displayHighscores(sf::RenderWindow& HS, int difficulty, int score)
{
	std::string name;
	sort_txt(name, false, score, difficulty);

	int n = 1;
	//Header
	sf::Font font;
	sf::Text text;

	sf::Text t_normal;
	sf::Text t_hard;
	sf::Text t_insane;

	sf::Text text_score;

	font.loadFromFile("Fonts/PixelOperator.ttf");
	
		text.setFont(font);
		text.setFillColor(sf::Color::White);
		text.setString("Highscores");
		text.setCharacterSize(60);
		text.setPosition(210, 50);

		t_normal.setFont(font);
		t_normal.setFillColor(sf::Color::White);
		t_normal.setString("Normal");
		t_normal.setCharacterSize(40);
		t_normal.setPosition(74, 130);

		t_hard.setFont(font);
		t_hard.setFillColor(sf::Color::White);
		t_hard.setString("Hard");
		t_hard.setCharacterSize(40);
		t_hard.setPosition(298, 130);

		t_insane.setFont(font);
		t_insane.setFillColor(sf::Color::White);
		t_insane.setString("Insane");
		t_insane.setCharacterSize(40);
		t_insane.setPosition(498, 130);


		text_score.setFont(font);
		text_score.setFillColor(sf::Color::White);
		text_score.setCharacterSize(30);

		std::string txt_output_hs;
		

		std::fstream myfile_normal;
		std::fstream myfile_hard;
		std::fstream myfile_insane;
		myfile_normal.open("Resources/High Score/High Score Normal.txt");
		myfile_hard.open("Resources/High Score/High Score Hard.txt");
		myfile_insane.open("Resources/High Score/High Score Insane.txt");

		for (int i = 0; i < 10; i++)
		{
			
			while (getline(myfile_normal, txt_output_hs))
			{
				//std::cout << txt_output_hs;
				//std::pair <std::string, std::string> name_hs (txt_output_hs.substr(0, 8), txt_output_hs.substr(9, 20));
				std::pair <std::string, std::string> name_hs(txt_output_hs.substr(0, 8), txt_output_hs.substr(9, 16));
				//std::tuple<std::string, std::string> hs_tuple (txt_output_hs,txt_output_hs);
				text_score.setString(std::to_string(n) + ". " + name_hs.first + " " + name_hs.second);// +name_hs.second ); // +"             " + diff);
				text_score.setPosition(30 , 150 + (25 * n));

				HS.draw(text_score);

				n++;
			}

			n = 1;

			while (getline(myfile_hard, txt_output_hs))
			{

				std::pair <std::string, std::string> name_hs(txt_output_hs.substr(0, 8), txt_output_hs.substr(9, 16));
				text_score.setString(std::to_string(n) + ". " + name_hs.first + " " + name_hs.second);
				text_score.setPosition(250, 150 + (25 * n));

				HS.draw(text_score);

				n++;
			}

			n = 1;

			while (getline(myfile_insane, txt_output_hs))
			{

				std::pair <std::string, std::string> name_hs(txt_output_hs.substr(0, 8), txt_output_hs.substr(9, 16));
				text_score.setString(std::to_string(n) + ". " + name_hs.first + " " + name_hs.second);
				text_score.setPosition(460, 150 + (25 * n));

				HS.draw(text_score);

				n++;
			}

		}

		myfile_normal.close();
		HS.draw(text);
		HS.draw(t_normal);
		HS.draw(t_hard);
		HS.draw(t_insane);
}