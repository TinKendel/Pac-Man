#include <SFML/Graphics.hpp>
#include <string>
//#include <iostream>
#include <array>

#include "DrawText.hpp"
#include "Global.hpp"



void draw_text(unsigned short i_x, unsigned short i_y, const std::string& i_text, sf::RenderWindow& i_window)
{
	sf::Sprite character_sprite;
	sf::Texture font_texture;

	unsigned char character_width;

	short character_x = i_x;
	short character_y = i_y;

	font_texture.loadFromFile("Resources/Images/Font.png");

	//There are 96 characters in the font texture.
	character_width = font_texture.getSize().x / 96;

	character_sprite.setTexture(font_texture);

	int N = i_text.length();


	for (int i = 0; i < N ; i++)
	{
		//std::cout << int(i_text.at(i)) - 32 << std::endl;
		//i_text.at(i) -> uzimamo slovo iz stringa na indexu i i oduzimamo ga sa 32
		//32 zato jer nam je pocetni karakter SPACE koji nije ko i u ASCII tablici ali cemo zamislit da je, a ovo slovo c++ pretvara u ASCII vrijednost te kada se oduzima sa 32
		//odabere tocni pixel sa slike gdje ocitava zeljeno slovo
		character_sprite.setTextureRect(sf::IntRect((i_text.at(i) - 32) * character_width, 0, character_width, FONT_HEIGHT));
		character_sprite.setPosition(character_x, character_y);
		character_x += character_width;
		i_window.draw(character_sprite);
	};
}


