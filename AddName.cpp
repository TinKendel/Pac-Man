//#include "AddName.hpp"
//#include "SFML\Graphics.hpp"
//
//#include <iostream>
//#include <string>
//
//std::string add_name(std::string player_name, sf::RenderWindow& window)
//{
//	sf::Font font;
//	sf::String playerInput;
//	sf::Text playerText;
//
//	font.loadFromFile("Fonts/PixelOperator.ttf");
//
//	playerText.setFont(font);
//	playerText.setFillColor(sf::Color::White);
//	playerText.setCharacterSize(13);
//	playerText.setPosition(67, 230);
//
//	sf::Event event;
//	while (window.pollEvent(event))
//	{
//		if (event.type == sf::Event::TextEntered)
//		{
//			if (player_name.size() < 9)
//			{
//				if (event.text.unicode < 128)
//				{
//					std::cout << char(event.text.unicode);
//					playerInput += char(event.text.unicode);
//					playerText.setString(playerInput);
//					player_name += playerInput;
//					window.draw(playerText);
//					std::cout << player_name.size();
//				}
//			}
//			
//		}
//	}
//
//	return player_name;
//};
//
////if (player_name.size() < 9)
//	//	{
//	//		std::cout << " prvi if " <<player_name.size() << '\n';
//
//	//		if ((event.text.unicode >= 32) && (event.text.unicode < 128))
//	//		{
//	//					
//	//			//std::cout << char(event.text.unicode);
//	//			playerInput += char(event.text.unicode);
//	//			playerText.setString(playerInput);
//	//			player_name += playerInput;
//	//			std::cout << " drugi if " << player_name.size() << '\n';
//	//			// 
//	//			//izbjegavati koristit funkciju sleep jer je specificna za operativni sustav
//	//			//Sleep(155);
//	//		}
//	//		else if (event.text.unicode == 8)
//	//		{
//	//			playerInput = playerInput.substring(0, playerInput.getSize() - 1);
//	//		}