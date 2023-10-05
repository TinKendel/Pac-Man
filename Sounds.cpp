#include "Sounds.hpp"
#include "SFML/Audio.hpp"

SoundManager::SoundManager() {
	sb_munch.loadFromFile("Resources/Sound/munch_short.wav");
	s_munch.setBuffer(sb_munch);

	sb_energizer.loadFromFile("Resources/Sound/power_pellet.wav");
	s_energizer.setBuffer(sb_energizer);

	sb_siren.loadFromFile("Resources/Sound/siren_1.wav");
	s_siren.setBuffer(sb_siren);

	sb_eatGhost.loadFromFile("Resources/Sound/eat_ghost_into_retreating.wav");
	s_eatGhost.setBuffer(sb_eatGhost);

	//sb_retreating.loadFromFile("Resources/Sound/retreating.wav");
	//s_retreating.setBuffer(sb_retreating);

	sb_death.loadFromFile("Resources/Sound/death_1.wav");
	s_death.setBuffer(sb_death);
};

//Munch Sound
void SoundManager::Munch_play() {
	s_munch.play();
};

void SoundManager::Munch_stop() {
	s_munch.stop();
};

//Energizer Sound
void SoundManager::Energizer_play() {
	s_energizer.play();
};

void SoundManager::Energizer_stop() {
	s_energizer.stop();
};

//Siren Sound
void SoundManager::Siren_play() {
	s_siren.play();
};

void SoundManager::Siren_stop() {
	s_siren.stop();
};

//Eat ghost
void SoundManager::EatGhost_play() {
	s_eatGhost.play();
};

void SoundManager::EatGhost_stop() {
	s_eatGhost.stop();
};

void SoundManager::Stop_all_sounds() {
	s_munch.stop();
	s_eatGhost.stop();
	s_energizer.stop();
	s_siren.stop();
};