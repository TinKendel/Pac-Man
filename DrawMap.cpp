#include <array>
#include <SFML/Graphics.hpp>

#include "Global.hpp"
#include "DrawMap.hpp"

// Potrebno mi je skuzit setTextureRect i IntRect

void draw_map(const std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, sf::RenderWindow& i_window)
{


	sf::Sprite sprite;

	sf::Texture texture;
	texture.loadFromFile("Resources/Images/Map" + std::to_string(CELL_SIZE) + ".png");

	sprite.setTexture(texture);

	for (unsigned char a = 0; a < MAP_WIDTH; a++)
	{
		for (unsigned char b = 0; b < MAP_HEIGHT; b++)
		{
			sprite.setPosition(static_cast<float>(CELL_SIZE * a), static_cast<float>(CELL_SIZE * b));

			//We just crop out what we need from the texture.
			switch (i_map[a][b])
			{
				case Cell::Door:
				{
					sprite.setTextureRect(sf::IntRect(2 * CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE));

					i_window.draw(sprite);

					break;
				}
				case Cell::Energizer:
				{
					sprite.setTextureRect(sf::IntRect(CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE));

					i_window.draw(sprite);

					break;
				}
				case Cell::Pellet:
				{
					sprite.setTextureRect(sf::IntRect(0, CELL_SIZE, CELL_SIZE, CELL_SIZE));

					i_window.draw(sprite);

					break;
				}
				case Cell::Wall:
				{
					bool down = 0;
					bool left = 0;
					bool right = 0;
					bool up = 0;

					if (b < MAP_HEIGHT - 1)
					{
						if (Cell::Wall == i_map[a][1 + b])
						{
							down = 1;
						}
					}

					//Since we have warp tunnels, we need to draw them as if they're connected.
					if (0 < a)
					{
						if (Cell::Wall == i_map[a - 1][b])
						{
							left = 1;
						}
					}
					else //ovo sluzi  kako bi dodalo povezanost warp tunela s lijeve na desnu stranu bez toga onda je "zatvoren tunel" tj zidovi koji su oko njega
					{
						left = 1;
					}

					if (a < MAP_WIDTH - 1)
					{
						if (Cell::Wall == i_map[1 + a][b])
						{
							right = 1;
						}
					}
					else
					{
						right = 1;
					}

					if (0 < b)
					{
						if (Cell::Wall == i_map[a][b - 1])
						{
							up = 1;
						}
					}
					//--------------------------------------------<         DISTRIBUTIVE PROPERTY!         >----------------------------
					sprite.setTextureRect(sf::IntRect(CELL_SIZE * (down + 2 * (left + 2 * (right + 2 * up))), 0, CELL_SIZE, CELL_SIZE));

					i_window.draw(sprite);
				}
			}
		}
	}
}





//cell_shape.setPosition(CELL_SIZE * a, CELL_SIZE * b);

//sf::RectangleShape cell_shape(sf::Vector2f(CELL_SIZE, CELL_SIZE));
//
//sf::CircleShape circle_shape;
//circle_shape.setFillColor(sf::Color(255, 182, 170));
//
//sf::RectangleShape door(sf::Vector2f(CELL_SIZE, CELL_SIZE));
//
//sf::CircleShape energizer;
//energizer.setFillColor(sf::Color(255, 182, 170));
//
//
//
//for (unsigned char a = 0; a < MAP_WIDTH; a++)
//{
//	for (unsigned char b = 0; b < MAP_HEIGHT; b++)
//	{
//		switch (i_map[a][b])
//		{
//		case Cell::Pellet:
//		{
//			circle_shape.setRadius(CELL_SIZE / 8);
//			circle_shape.setPosition(CELL_SIZE * a + (CELL_SIZE / 2 - circle_shape.getRadius()), CELL_SIZE * b + (CELL_SIZE / 3.5 + circle_shape.getRadius())); // ovih 3.5 sam ja iz svoje glave radio jer nije pokazo do kraja svoju matematiku pa sam pogado doslovno
//			circle_shape.setPosition(CELL_SIZE * a, CELL_SIZE * b);
//			i_window.draw(circle_shape);
//
//			break;
//		}
//		case Cell::Wall:
//		{
//			cell_shape.setFillColor(sf::Color(36, 36, 255));
//			cell_shape.setPosition(CELL_SIZE * a, CELL_SIZE * b);
//
//			i_window.draw(cell_shape);
//
//			break;
//		}
//		case Cell::Door:
//		{
//			door.setFillColor(sf::Color::Cyan);
//			door.setPosition(a * CELL_SIZE, b * CELL_SIZE);
//
//			i_window.draw(door);
//
//			break;
//		}
//		case Cell::Energizer:
//		{
//			energizer.setRadius(CELL_SIZE / 4);
//			energizer.setPosition(CELL_SIZE * a + (CELL_SIZE / 2.5 - circle_shape.getRadius()), CELL_SIZE * b + (CELL_SIZE / 5 + circle_shape.getRadius()));
//
//			i_window.draw(energizer);
//
//			break;
//		}
//		}