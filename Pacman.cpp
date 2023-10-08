#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <array>
#include <iostream>

#include "Global.hpp"
#include "Pacman.hpp"
#include "MapCollision.hpp"
#include "Sounds.hpp"
#include "GhostManager.hpp"

GhostManager ghost_manger;

Pacman::Pacman() :
	animation_over(0),
	dead(0),
	direction(0),
	energizer_timer(0),
	position({ 0, 0 })
{

}

bool Pacman::get_animation_over()
{
	return animation_over;
}

void Pacman::set_animation_timer(unsigned short i_animation_timer)
{
	animation_timer = i_animation_timer;
}

bool Pacman::get_dead()
{
	return dead;
}

unsigned char Pacman::get_direction() 
{
	return direction;
}

unsigned short Pacman::get_energizer_timer() 
{
	return energizer_timer;
}

void Pacman::draw(bool i_victory, sf::RenderWindow& i_window)
{
	unsigned char frame = static_cast<unsigned char>(floor(animation_timer / static_cast<float>(PACMAN_ANIMATION_SPEED))); 

	sf::Sprite sprite;

	sf::Texture texture;

	sprite.setPosition(position.x, position.y);

	if (1 == dead || 1 == i_victory)
	{
		if (animation_timer < PACMAN_DEATH_FRAMES * PACMAN_ANIMATION_SPEED)
		{
			animation_timer++;

			texture.loadFromFile("Resources/Images/PacmanDeath" + std::to_string(CELL_SIZE) + ".png");

			sprite.setTexture(texture);
			sprite.setTextureRect(sf::IntRect(CELL_SIZE * frame, 0, CELL_SIZE, CELL_SIZE));

			i_window.draw(sprite);
		}
		else
		{
			//You can only die once.
			animation_over = 1;
		}
	}
	else
	{
		texture.loadFromFile("Resources/Images/Pacman" + std::to_string(CELL_SIZE) + ".png");

		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(CELL_SIZE * frame, CELL_SIZE * direction, CELL_SIZE, CELL_SIZE));

		i_window.draw(sprite);

		animation_timer = (1 + animation_timer) % (PACMAN_ANIMATION_FRAMES * PACMAN_ANIMATION_SPEED);
	}

	/*
	sf::CircleShape circle(CELL_SIZE / 2);
	circle.setFillColor(sf::Color::Yellow);
	circle.setPosition(position.x, position.y);

	i_window.draw(circle);
	*/
}

void Pacman::reset()
{
	animation_over = 0;
	dead = 0;

	direction = 0;
	
	animation_timer = 0;
	energizer_timer = 0;
}

void Pacman::set_dead(bool i_dead, SoundManager& gameSounds)
{
	dead = i_dead;

	if (1 == dead)
	{
		//Making sure that the animation starts from the beginning.
		gameSounds.s_death.play();
		gameSounds.Stop_all_sounds();
		animation_timer = 0;
	}
	score = 0;
}

void Pacman::set_position(short i_x,short i_y)
{
	position = {i_x, i_y};
}

void Pacman::update(bool i_level, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, SoundManager& gameSounds, int difficulty)
{
	std::array<bool, 4> walls{};
	walls[0] = map_collision(0, 0, PACMAN_SPEED + position.x, position.y, i_map, gameSounds);
	walls[1] = map_collision(0, 0, position.x, position.y - PACMAN_SPEED, i_map, gameSounds);
	walls[2] = map_collision(0, 0, position.x - PACMAN_SPEED, position.y, i_map, gameSounds);
	walls[3] = map_collision(0, 0, position.x, PACMAN_SPEED + position.y, i_map, gameSounds);

	if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (0 == walls[0]) //You can't turn in this direction if there's a wall there.
		{
			direction = 0;
		}
	}

	if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (0 == walls[1])
		{
			direction = 1;
		}
	}

	if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (0 == walls[2])
		{
			direction = 2;
		}
	}

	if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (0 == walls[3])
		{
			direction = 3;
		}
	}

	if (0 == walls[direction])
	{
		switch (direction)
		{
			case 0:
			{
				position.x += PACMAN_SPEED;

				break;
			}
			case 1:
			{
				position.y -= PACMAN_SPEED;

				break;
			}
			case 2:
			{
				position.x -= PACMAN_SPEED;

				break;
			}
			case 3:
			{
				position.y += PACMAN_SPEED;
			}
		}
	}

	// Warp tunel
	if (-CELL_SIZE >= position.x)
	{
		position.x = CELL_SIZE * MAP_WIDTH - PACMAN_SPEED;
	}
	else if (CELL_SIZE * MAP_WIDTH <= position.x)
	{
		position.x = PACMAN_SPEED - CELL_SIZE;
	}

	if (1 == map_collision(1, 0, position.x, position.y, i_map, gameSounds)) //When Pacman eats an energizer... or a pellet
	{
		//He becomes energized!
		//energizer_timer = static_cast<unsigned short>(ENERGIZER_DURATION);
		 
		switch (difficulty)
		{
			case 1:
			{
				std::cout << "I am energized, difficulty ONE" << std::endl;
				energizer_timer = static_cast<unsigned short>(ENERGIZER_DURATION); // / pow(2, i_level));
				break;
			}
			case 2:
			{
				std::cout << "I am energized, difficulty TWO" << std::endl;
				energizer_timer = static_cast<unsigned short>(SHORT_ENERGIZER_DURATION);
				std::cout << energizer_timer << std::endl;
				break;
			}
			case 3:
			{
				std::cout << "I am energized, difficulty THREE" << std::endl;
				energizer_timer = static_cast<unsigned short>(0);
				break;
			}
		}
	}
	else // Smanjuje duration energizer timera u trenutnoj mapi ( ako je duration 7 sec on ga odbrojava do 0)
	{
		energizer_timer = std::max(0, energizer_timer - 1);
		//if (energizer_timer == 1)
		//{
		//	gameSounds.s_siren.play();
		//}
	}
}

Position Pacman::get_position()
{
	return position;
}
