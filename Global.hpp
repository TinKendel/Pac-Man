#pragma once
#include <array>

extern int score;
//constexpr  std::array<int, 3>difficulty{ 0, 1, 2 };
//extern int high_score;

constexpr unsigned char CELL_SIZE = 16;
constexpr unsigned char FONT_HEIGHT = 16;

//I start counting everything from 0, so this is actually the second ghost.
//The website used smaller cells, so I'm setting smaller values.
//Which cell in front of Pacman the pink ghost will target.
constexpr unsigned char GHOST_1_CHASE = 2;
//Which cell in front of Pacman the blue ghost will use to calculate the target.
constexpr unsigned char GHOST_2_CHASE = 1;
//If the distance between the orange ghost and Pacman is less than this value, the orange ghost will go into the scatter mode.
constexpr unsigned char GHOST_3_CHASE = 4;
//How many frames are in the ghost body animation
constexpr unsigned char GHOST_ANIMATION_FRAMES = 6;

constexpr unsigned char GHOST_ANIMATION_SPEED = 4;
//The speed of the ghost after the Pacman touches it while being energized.
constexpr unsigned char GHOST_ESCAPE_SPEED = 4;

//The higher the value, the slower the ghost.
constexpr unsigned char GHOST_FRIGHTENED_SPEED = 3;

constexpr unsigned char GHOST_SPEED = 1;
constexpr unsigned char MAP_HEIGHT = 21;
constexpr unsigned char MAP_WIDTH = 21;
constexpr unsigned char PACMAN_ANIMATION_FRAMES = 6;
constexpr unsigned char PACMAN_ANIMATION_SPEED = 4;
constexpr unsigned char PACMAN_DEATH_FRAMES = 12;
constexpr unsigned char PACMAN_SPEED = 2;
constexpr unsigned char SCREEN_RESIZE = 2;

//This is in frames. 
constexpr unsigned short CHASE_DURATION = 1024;
constexpr unsigned short SHORT_CHASE_DURATION = 256;
constexpr unsigned short ENERGIZER_DURATION = 512;
constexpr unsigned short SHORT_ENERGIZER_DURATION = 256;
constexpr unsigned short FRAME_DURATION = 16667;
constexpr unsigned short GHOST_FLASH_START = 64;
constexpr unsigned short LONG_SCATTER_DURATION = 512;
constexpr unsigned short SHORT_SCATTER_DURATION = 256;


enum Cell
{
	Door,
	Empty,
	Energizer,
	Pellet,
	Wall
};

struct Position
{
	short x;
	short y;

	bool operator==(const Position& i_position)
	{
		return this->x == i_position.x && this->y == i_position.y;
	}
};