#include <array>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Global.hpp"
#include "Pacman.hpp"
#include "Ghost.hpp"
#include "MapCollision.hpp"
#include "Sounds.hpp"

Ghost::Ghost(unsigned char i_id) :
	id(i_id)
{

}

bool Ghost::pacman_collision(const Position& i_pacman_position)
{
	if (position.x > i_pacman_position.x - CELL_SIZE && position.x < CELL_SIZE + i_pacman_position.x)
	{
		if (position.y > i_pacman_position.y - CELL_SIZE && position.y < CELL_SIZE + i_pacman_position.y)
		{
			return 1;
		}
	}

	return 0;
}

void Ghost::draw(bool i_flash, sf::RenderWindow& i_window, SoundManager& gameSounds)
{
	//Current frame of the animation.
	unsigned char body_frame = static_cast<unsigned char>(floor(animation_timer / static_cast<float>(GHOST_ANIMATION_SPEED)));

	sf::Sprite body;
	sf::Sprite face;

	sf::Texture texture;
	texture.loadFromFile("Resources/Images/Ghost" + std::to_string(CELL_SIZE) + ".png");

	body.setTexture(texture);
	body.setPosition(position.x, position.y);
	//Animation is basically a quick display of similar images.
	//So that's what we're doing here.
	//SetTextureRect podstavlja mali "kvadrat" unutar slike koji æe on oèitavat umjesto cijele slike
	//IntRect je poseban tip podatka koji sa danim vrijednostima daje kvadrat.
	//Left lijevi stranicu, top je gornja dok Width i Height dodaju svoju velicinu na vec definriane stranice te tako stvarju kvadrat koji ocitava sprite 
	body.setTextureRect(sf::IntRect(CELL_SIZE * body_frame, 0, CELL_SIZE, CELL_SIZE));

	face.setTexture(texture);
	face.setPosition(position.x, position.y);


	//The "I'm not frightened" look.
	if (0 == frightened_mode)
	{
		switch (id)
		{
			case 0:
			{
				//Red color
				body.setColor(sf::Color(255, 0, 0));

				break;
			}
			case 1:
			{
				//Pink color
				body.setColor(sf::Color(255, 182, 255));

				break;
			}
			case 2:
			{
				//Cyan color (I still don't understand why they called it blue)
				body.setColor(sf::Color(0, 255, 255));

				break;
			}
			case 3:
			{
				//Orange color
				body.setColor(sf::Color(255, 182, 85));

				break;
			}
		}

		//gameSounds.s_energizer.stop();

		face.setTextureRect(sf::IntRect(CELL_SIZE * direction, CELL_SIZE, CELL_SIZE, CELL_SIZE));

		i_window.draw(body);
	}
	//The "Maybe I am frightened" look. When we eat the energizers
	else if (1 == frightened_mode)
	{
		gameSounds.s_siren.stop();
		body.setColor(sf::Color(36, 36, 255)); // Ovo je plava boja koju dobe kada pojedemo energizer
		//The face remains the same regardless of where the gohst is going right now.
		face.setTextureRect(sf::IntRect(4 * CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE));

		if (1 == i_flash && 0 == body_frame % 2) // U ovom dijelu se desava flashanje duha kada je pri kraju plašljenja 
		{
			body.setColor(sf::Color(255, 255, 255));
			face.setColor(sf::Color(255, 0, 0));
		}
		else
		{
			body.setColor(sf::Color(36, 36, 255));
			face.setColor(sf::Color(255, 255, 255));
		}

		i_window.draw(body);
	}
	//Ghost is dead
	else
	{
		//We only draw the face because Pacman stole the body.
		face.setTextureRect(sf::IntRect(CELL_SIZE * direction, 2 * CELL_SIZE, CELL_SIZE, CELL_SIZE));
	}

	i_window.draw(face);

	//--------------------------------------<        This is to prevent overflowing.         >-
	// Ovaj dio utjeèe na animacije i brine se da briše prijašnje animacije kako bi stvorilo sto realistièniji prikaz
	animation_timer = (1 + animation_timer) % (GHOST_ANIMATION_FRAMES * GHOST_ANIMATION_SPEED);
}

void Ghost::reset(const Position& i_home, const Position& i_home_exit, SoundManager& gameSounds) 
{
	movement_mode = 0;
	//Everyone can use the door except the red ghost.
	//Because I hate the red ghost. 
	use_door = 0 < id;

	direction = 0;
	frightened_mode = 0;
	frightened_speed_timer = 0;

	animation_timer = 0;
	gameSounds.s_siren.play();

	home = i_home;
	home_exit = i_home_exit;
	target = i_home_exit;
}

void Ghost::set_position(short i_x, short i_y)
{
	position = { i_x, i_y };
}

float Ghost::get_target_distance(unsigned char i_direction) 
{
	short x = position.x;
	short y = position.y;

	//We'll imaginarily move the ghost in a given direction and calculate the distance to the target.
	switch (i_direction)
	{
		case 0:
		{
			x += GHOST_SPEED;

			break;
		}
		case 1:
		{
			y -= GHOST_SPEED;

			break;
		}
		case 2:
		{
			x -= GHOST_SPEED;

			break;
		}
		case 3:
		{
			y += GHOST_SPEED;
		}
	}

	//I used the Pythagoras' theorem.
	return static_cast<float>(sqrt(pow(x - target.x, 2) + pow(y - target.y, 2)));
}

void Ghost::switch_mode() 
{
	movement_mode = 1 - movement_mode;
}

void Ghost::update(unsigned char i_level, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH>& i_map, Ghost& i_ghost_0, Pacman& i_pacman, SoundManager& gameSounds, int difficulty)
{
	//Can the ghost move?
	bool move = 0;

	//If this is greater than 1, that means that the ghost has reached the intersection.
	//We don't consider the way back as an available way.
	unsigned char available_ways = 0;


	unsigned char speed = GHOST_SPEED;


	//Here the ghost starts and stops being frightened.
	//Provjeravamo dali je duh mrtav, dali samo bjezi od nas ili nas napada
	if (difficulty != 2)
	{
		if (0 == frightened_mode && i_pacman.get_energizer_timer() == ENERGIZER_DURATION) // / pow(2, i_level))
		{
			frightened_speed_timer = GHOST_FRIGHTENED_SPEED;

			frightened_mode = 1;
			std::cout << "setting frightened_mode = 1" << std::endl;
		}
		else if (0 == i_pacman.get_energizer_timer() && 1 == frightened_mode)
		{
			frightened_mode = 0;
			std::cout << "setting frightened_mode = 0" << std::endl;
			//gameSounds.s_siren.setLoop(true);
			//gameSounds.s_siren.play();
		}
	}
	else
	{
		if (0 == frightened_mode && i_pacman.get_energizer_timer() == SHORT_ENERGIZER_DURATION) // / pow(2, i_level))
		{
			frightened_speed_timer = GHOST_FRIGHTENED_SPEED;

			frightened_mode = 1;
		}
		else if (0 == i_pacman.get_energizer_timer() && 1 == frightened_mode)
		{
			frightened_mode = 0;
		}
	}
	

	//I used the modulo operator in case the ghost goes outside the grid.
	if (2 == frightened_mode && 0 == position.x % GHOST_ESCAPE_SPEED && 0 == position.y % GHOST_ESCAPE_SPEED) // kada je duh mrtav a to vidimo preko frightened_mode = 2 dajemo im vecu brzinu
	{
		speed = GHOST_ESCAPE_SPEED;
	}

	update_target(i_pacman.get_direction(), i_ghost_0.get_position(), i_pacman.get_position());

	std::array<bool, 4> walls{};
	walls[0] = map_collision(0, use_door, speed + position.x, position.y, i_map, gameSounds);
	walls[1] = map_collision(0, use_door, position.x, position.y - speed, i_map, gameSounds);
	walls[2] = map_collision(0, use_door, position.x - speed, position.y, i_map, gameSounds);
	walls[3] = map_collision(0, use_door, position.x, speed + position.y, i_map, gameSounds);


	if (1 != frightened_mode)
	{
		//I used 4 because using a number between 0 and 3 will make the ghost move in a direction it can't move.
		unsigned char optimal_direction = 4; // Stacionrana pozicija, od 0 do 3 su smjerovi kretanja 

		//The ghost can move.
		move = 1;

		for (unsigned char a = 0; a < 4; a++)
		{
			//bool suprotni_smjer ==  (2 + direction) % 4;
			//ghosts can't turn back! (Unless they really have to)
			if (a == (2 + direction) % 4) // Preventiraj da duh ide u natrag ili mu zabrani 
			{
				continue;
			}
			else if (0 == walls[a]) // Provjerava jeli postoji tamo zid ili ne 
			{
				if (4 == optimal_direction)
				{
					optimal_direction = a; //postavlja optimal direction na 4 samo ako nema na krizanju niti jendog zida //inace je 0 jer je definiran na samom startu ko 4
				}

				available_ways++; // povecava se do broja slobodnih prolaza na krizanju

				if (get_target_distance(a) < get_target_distance(optimal_direction))
				{
					//The optimal direction is the direction that's closest to the target.
					optimal_direction = a;
				}
			}
		}

		if (1 < available_ways) // ako ima vise od jedan moguceg prolaza  ulazi u if statement // dalje se granja na else ako je 0 
		{
			//When the ghost is at the intersection, it chooses the optimal direction.
			direction = optimal_direction; //direction prima vrijednost od op_d
		}
		else
		{
			if (4 == optimal_direction) // klasika, provjerava dali je 4 jednak optimal direction, ako nije ide na else
			{
				//"Unless they have to" part.
				direction = (2 + direction) % 4; // okrece leda jer nema drugog puta
			}
			else
			{
				direction = optimal_direction; //pohranjuej op_d vrijednost unutar direction
			}
		}
	}
	else
	{
		//I used rand() because I figured that we're only using randomness here, and there's no need to use a whole library for it.
		unsigned char random_direction = rand() % 4; // uzima random broj izmedu 0 sve do N-1 u ovom slucaju 4-1

		if (0 == frightened_speed_timer)
		{
			//The ghost can move after a certain number of frames.
			move = 1;

			frightened_speed_timer = GHOST_FRIGHTENED_SPEED;

			for (unsigned char a = 0; a < 4; a++)
			{
				//They can't turn back even if they're frightened.
				if (a == (2 + direction) % 4)
				{
					continue;
				}
				else if (0 == walls[a])
				{
					available_ways++;
				}
			}

			if (0 < available_ways) //provjeravamo kolko imamo onda mogucih puteva
			{
				while (1 == walls[random_direction] || random_direction == (2 + direction) % 4) // provjeravamo jeli true == zid OR random_d == modulu
				{
					//We keep picking a random direction until we can use it.
					random_direction = rand() % 4; //dobivamo random broj izmedu 0 i 3
				}

				direction = random_direction; // i taj random boroj spremamo u direction
			}
			else
			{
				//If there's no other way, it turns back.
				direction = (2 + direction) % 4;
			}
		}
		else
		{
			frightened_speed_timer--;
		}
	}

	float difficulty_modifier = 0;


	if (difficulty == 3)
	{
		difficulty_modifier = 1;
	}


	//If the ghost can move, we move it.
	if (1 == move)
	{
		switch (direction) // iz prijasnje petlje imamo direction koje je random dobiven i duh ce krenut u taj random smjer preko case-a
		{
			case 0: // kroz case mi mu samo dajemo "brzinu" u jendom smjeru sve dok ne dode do iducek krizanja
			{
				position.x += speed + difficulty_modifier;

				break;
			}
			case 1:
			{
				position.y -= speed + difficulty_modifier;

				break;
			}
			case 2:
			{
				position.x -= speed + difficulty_modifier;

				break;
			}
			case 3:
			{
				position.y += speed + difficulty_modifier;

				break;
			}
		}

		//Warping.
		//When the ghost leaves the map, we move it to the other side.
		if (-CELL_SIZE >= position.x)
		{
			position.x = CELL_SIZE * MAP_WIDTH - speed;
		}
		else if (position.x >= CELL_SIZE * MAP_WIDTH)
		{
			position.x = speed - CELL_SIZE;
		}

	}

	if (1 == pacman_collision(i_pacman.get_position()))
	{
		if (0 == frightened_mode) //When the ghost is not frightened and collides with Pacman, we kill Pacman.
		{
			i_pacman.set_dead(1, gameSounds);
			gameSounds.s_siren.stop();
			gameSounds.Stop_all_sounds();
		}
		else //Otherwise, the ghost starts running towards the house.
		{
			use_door = 1;

			frightened_mode = 2;

			target = home;

			gameSounds.s_eatGhost.play();
			//gameSounds.s_retreating.play();
			/*if (gameSounds.s_eatGhost.getStatus() == sf::Sound::Status::Stopped)
				gameSounds.s_retreating.play();*/
		}
	}
}

void Ghost::update_target(unsigned char i_pacman_direction, const Position& i_ghost_0_position, const Position& i_pacman_position)
{
	if (1 == use_door) //If the ghost can use the door.
	{
		if (position == target)
		{
			if (home_exit == target) //If the ghost has reached the exit.
			{
				use_door = 0; //It can no longer use the door.
			}
			else if (home == target) //If the ghost has reached its home.
			{
				frightened_mode = 0; //It stops being frightened.

				target = home_exit; //And starts leaving the house.
			}
		}
	}
	else
	{
		if (0 == movement_mode) //The scatter mode
		{
			//Each ghost goes to the corner it's assigned to.
			switch (id)
			{
				case 0: //Red ghost goes to the top right corner
				{
					target = { CELL_SIZE * (MAP_WIDTH - 1), 0 };

					break;
				}
				case 1:
				{
					target = { 0, 0 };

					break;
				}
				case 2:
				{
					target = { CELL_SIZE * (MAP_WIDTH - 1), CELL_SIZE * (MAP_HEIGHT - 1) };

					break;
				}
				case 3:
				{
					target = { 0, CELL_SIZE * (MAP_HEIGHT - 1) };
				}
			}
		}
		else //The chase mode
		{
			switch (id)
			{
				case 0: //The red ghost will chase Pacman.
				{
					target = i_pacman_position;

					break;
				}
				case 1: //The pink ghost will chase the 4th cell in front of Pacman.
				{
					target = i_pacman_position;

					switch (i_pacman_direction)
					{
						case 0:
						{
							target.x += CELL_SIZE * GHOST_1_CHASE;

							break;
						}
						case 1:
						{
							target.y -= CELL_SIZE * GHOST_1_CHASE;

							break;
						}
						case 2:
						{
							target.x -= CELL_SIZE * GHOST_1_CHASE;

							break;
						}
						case 3:
						{
							target.y += CELL_SIZE * GHOST_1_CHASE;
						}
					}

					break;
				}
				case 2: //The blue ghost.
				{
					target = i_pacman_position;

					//Getting the second cell in front of Pacman.
					switch (i_pacman_direction)
					{
						case 0:
						{
							target.x += CELL_SIZE * GHOST_2_CHASE;

							break;
						}
						case 1:
						{
							target.y -= CELL_SIZE * GHOST_2_CHASE;

							break;
						}
						case 2:
						{
							target.x -= CELL_SIZE * GHOST_2_CHASE;

							break;
						}
						case 3:
						{
							target.y += CELL_SIZE * GHOST_2_CHASE;
						}
					}

					//We're sending a vector from the red ghost to the second cell in front of Pacman.
					//Then we're doubling it.
					target.x += target.x - i_ghost_0_position.x;
					target.y += target.y - i_ghost_0_position.y;

					break;
				}
				case 3: //The orange ghost will chase Pacman until it gets close to him. Then it'll switch to the scatter mode.
				{
					//Using the Pythagoras' theorem again.
					if (CELL_SIZE * GHOST_3_CHASE <= sqrt(pow(position.x - i_pacman_position.x, 2) + pow(position.y - i_pacman_position.y, 2)))
					{
						target = i_pacman_position;
					}
					else
					{
						target = { 0, CELL_SIZE * (MAP_HEIGHT - 1) };
					}
				}
			}
		}
	}
}

Position Ghost::get_position()
{
	return position;
}

char Ghost::get_frightened_mode()
{
	return frightened_mode;
};