#include <array>
#include <cmath>
#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>

#include "Sounds.hpp"
#include "Global.hpp"
#include "Pacman.hpp"
#include "Ghost.hpp"
#include "GhostManager.hpp"


GhostManager::GhostManager() :
	current_wave(0),
	wave_timer(LONG_SCATTER_DURATION),
	ghosts({ Ghost(0), Ghost(1), Ghost(2), Ghost(3)})
{

}

void GhostManager::draw(bool i_flash, sf::RenderWindow& i_window, SoundManager& gameSounds)
{
	for (Ghost& ghost : ghosts)
	{
		ghost.draw(i_flash, i_window, gameSounds); 
	}
}

void GhostManager::reset(unsigned char i_level, const std::array<Position, 4>& i_ghost_positions, SoundManager& gameSounds, int difficulty)
{
	current_wave = 0;

	//This is how we're increasing the difficulty.

	//Postavljam wave times vezan za scatter mode
	switch (difficulty)
	{
		case 1:
		{
			wave_timer = static_cast<unsigned short>(LONG_SCATTER_DURATION / pow(2, i_level));
			break;
		}
		case 2:
		{
			wave_timer = static_cast<unsigned short>(SHORT_SCATTER_DURATION);
			break;
		}
		case 3:
		{
			wave_timer = static_cast<unsigned short>(128);
			break;
		}
	}

	for (unsigned char a  = 0; a < 4; a++)
	{
		ghosts[a].set_position(i_ghost_positions[a].x, i_ghost_positions[a].y); // We define thgrough pointers where all of the ghosts will spawn 
	}

	// Ghost door
	for (Ghost& ghost : ghosts) 
	{
		//We use the blue ghost to get the location of the house and the red ghost to get the location of the exit.
		ghost.reset(ghosts[2].get_position(), ghosts[0].get_position(), gameSounds); // koristi kako bi duhovi samo jednom u zivotu koristili vrata, kroz svakog prolazimo jer ih crveni netreba koristit
	}
}

void GhostManager::update(unsigned char i_level, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, Pacman& i_pacman, SoundManager& gameSounds, int difficulty)
{
	if (0 == i_pacman.get_energizer_timer()) //We won't update the wave timer when Pacman is energized.
	{
		if (0 == wave_timer) 
		{
			if (7 > current_wave)
			{
				current_wave++;

				for (Ghost& ghost : ghosts)
				{
					ghost.switch_mode();
				}
			}

			//I took the rules from the website.
			//Wave timer se mijenja sa levelom tako da me duhovi dulje love i kraæe se krecu slobodno
			//Nema veze sa koliko energizer radi da nebi opet doslo do zabune
			switch (difficulty)
			{
				case 1:
				{
					std::cout << "difficulty 1 wave_timer is 512" << std::endl;
					if (1 == current_wave % 2)
					{
						wave_timer = CHASE_DURATION;
					}
					else if (2 == current_wave)
					{
						wave_timer = static_cast<unsigned short>(LONG_SCATTER_DURATION / pow(2, i_level));
					}
					else
					{
						wave_timer = static_cast<unsigned short>(SHORT_SCATTER_DURATION / pow(2, i_level));
					}
					
					break;
				}
				case 2:
				{
					std::cout << "difficulty 2 wave_timer is 256" << std::endl;
					if (1 == current_wave % 2)
					{
						wave_timer = SHORT_CHASE_DURATION;
					}
					else if (2 == current_wave)
					{
						wave_timer = static_cast<unsigned short>(SHORT_SCATTER_DURATION);// / pow(2, i_level));
					}
					else
					{
						wave_timer = static_cast<unsigned short>(SHORT_SCATTER_DURATION);// / pow(2, i_level));
					}
					
					break;
				}
				case 3:
				{
					std::cout << "difficulty 3 wave_timer is 0" << std::endl;
					if (1 == current_wave % 2)
					{
						wave_timer = 0;
						
					}
					
					break;
				}
			}
			
		}
		//bez ovoga nece me napdat, treba postojat neki brojac kako bi duhovi znali nakon nekog trena opet lovit pacmana
		else
		{
			wave_timer --;
		}
	}

	for (Ghost& ghost : ghosts)
	{
		ghost.update(i_level, i_map, ghosts[0], i_pacman, gameSounds, difficulty);
		
		//std::cout << "sound status before if is " << gameSounds.s_siren.getStatus() << std::endl;
	}
	if (gameSounds.s_siren.getStatus() != 2 && ghosts[0].get_frightened_mode() == 0 && ghosts[3].get_frightened_mode() == 0 && ghosts[1].get_frightened_mode() == 0 && ghosts[2].get_frightened_mode() == 0)
	{
		//		gameSounds.s_siren.setLoop(true);
		gameSounds.s_energizer.stop();
		gameSounds.s_siren.play();
		std::cout << "sound status after if is " << gameSounds.s_siren.getStatus() << std::endl;
		std::cout << "should play siren" << std::endl;
	}
}