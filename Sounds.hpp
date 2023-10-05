#pragma once

#include <iostream>
#include <SFML/Audio.hpp>

class SoundManager {
public:
	SoundManager();

	//Munch Sound
	void Munch_play();
	void Munch_stop();

	sf::SoundBuffer sb_munch;
	sf::Sound s_munch;

	//Energizer Sound
	void Energizer_play();
	void Energizer_stop();

	sf::SoundBuffer sb_energizer;
	sf::Sound s_energizer;

	//Siren sound
	void Siren_play();
	void Siren_stop();

	sf::SoundBuffer sb_siren;
	sf::Sound s_siren;

	//Eat ghost
	void EatGhost_play();
	void EatGhost_stop();

	sf::SoundBuffer sb_eatGhost;
	sf::Sound s_eatGhost;

	//Retreating ghost
	//void Retreating_play();
	//void Retreating_stop();

	//sf::SoundBuffer sb_retreating;
	//sf::Sound s_retreating;

	sf::SoundBuffer sb_death;
	sf::Sound s_death;

	//Stop all sounds
	void Stop_all_sounds();
};

