#include <array>
#include <chrono> //chrono is the name of a header, but also of a sub-namespace: All the elements in this header 
//are not defined directly under the std namespace (like most of the standard library) but under the std::chrono namespace.
//#include <ctime> // This header file contains definitions of functions to get and manipulate date and time information.
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
#include <fstream>
#include <utility>
#include <windows.h>

#include "Global.hpp"
#include "DrawText.hpp"
#include "Pacman.hpp"
#include "Ghost.hpp"
#include "GhostManager.hpp"
#include "ConvertSketch.hpp"
#include "DrawMap.hpp"
#include "MapCollision.hpp"

#include "RandomMap.hpp"
#include "Sounds.hpp"
#include "MainMenu.hpp"
#include "HighscoreMenu.hpp"
#include "Sorting.hpp"
#include "AddName.hpp"

int main()
{
	int hs_score = 0;
	int difficulty;
	GhostManager ghost_manager;
	std::string player_name;
	player_name = "";
	bool new_higscore_reached = 0;

	//std::array <std::array<std::string, 32>, 1> optionsMap_list;
	//optionsMap_list = optionsMap();

	//std::array<std::array<Cell, 32>, 50> outline_map;
	//outline_map = convert_outline_sketch(optionsMap_list[0]);
	
	//Background za Pac-Man
	//sf::Sprite mm_background;
	//sf::Texture mm_texture;

	//mm_texture.loadFromFile("Resources/Images/pac-man-logo.png");

	//mm_background.setTexture(mm_texture);
	//mm_background.setScale(0.148, 0.148);
	//mm_background.setPosition( 0, 249);

	sf::Font font;
	sf::Text text;
	
	font.loadFromFile("Fonts/PixelOperator.ttf");
	text.setFont(font);
	text.setFillColor(sf::Color::White);
	text.setString("Chomper");
	text.setCharacterSize(120);
	text.setPosition(160, 50);

	sf::Font font_hs;
	sf::Text text_hs;

	font_hs.loadFromFile("Fonts/PixelOperator.ttf");
	text_hs.setFont(font);
	text_hs.setFillColor(sf::Color::Blue);
	text_hs.setString("Insert player name of eight characters\n	   and press Space:");
	text_hs.setCharacterSize(17);
	text_hs.setPosition(48, 190);

	sf::String playerInput;
	sf::Text playerText;

	playerText.setFont(font);
	playerText.setFillColor(sf::Color::Cyan);
	playerText.setCharacterSize(17);
	playerText.setPosition(182, 208);

	sf::Font font_end;
	sf::Text text_end;

	font_end.loadFromFile("Fonts/PixelOperator.ttf");
	text_end.setFont(font_end);
	text_end.setFillColor(sf::Color::Blue);
	text_end.setString("High Score has been added \n Press Enter to continue!");
	text_end.setCharacterSize(17);
	text_end.setPosition(91, 110);

	//Difficulty png-s
	sf::Sprite op_sprite_packman;
	sf::Texture op_texture_packman;
	op_texture_packman.loadFromFile("Resources/Images/Pac-Man-0.png");
	op_sprite_packman.setTexture(op_texture_packman);
	op_sprite_packman.setPosition(0, 0);
	op_sprite_packman.setScale(0.15, 0.15);

	sf::Sprite op_sprite_blinky;
	sf::Texture op_texture_blinky;
	op_texture_blinky.loadFromFile("Resources/Images/Blinky.png");
	op_sprite_blinky.setTexture(op_texture_blinky);
	op_sprite_blinky.setPosition(410, 422);
	op_sprite_blinky.setScale(0.15, 0.15);

	sf::Sprite op_sprite_clyde;
	sf::Texture op_texture_clyde;
	op_texture_clyde.loadFromFile("Resources/Images/Clyde.png");
	op_sprite_clyde.setTexture(op_texture_clyde);
	op_sprite_clyde.setPosition(410, 222);
	op_sprite_clyde.setScale(0.15, 0.15);

	sf::Sprite op_sprite_pinky;
	sf::Texture op_texture_pinky;
	op_texture_pinky.loadFromFile("Resources/Images/Pinky.png");
	op_sprite_pinky.setTexture(op_texture_pinky);
	op_sprite_pinky.setPosition(410, 322);
	op_sprite_pinky.setScale(0.15, 0.15);

	sf::RenderWindow Main_Menu(sf::VideoMode(CELL_SIZE * MAP_WIDTH * SCREEN_RESIZE, (FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT) * SCREEN_RESIZE), "Main Menu for Chomper", sf::Style::Close); // Pac-Man
	MainMenu mainMenu(Main_Menu.getSize().x, Main_Menu.getSize().y);//, window);

	while (Main_Menu.isOpen())
	{
		sf::Event event;
		while (Main_Menu.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				Main_Menu.close();
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					Main_Menu.close();
				}
			}

			if (event.type == sf::Event::KeyPressed) //ili KeyReleased
			{
				if (event.key.code == sf::Keyboard::Up)
				{
					mainMenu.MoveUp();
					break;
				}
				
				if (event.key.code == sf::Keyboard::Down)
				{
					mainMenu.MoveDown();
					break;
				}

				if (event.key.code == sf::Keyboard::Return)
				{
					sf::RenderWindow window(sf::VideoMode(CELL_SIZE * MAP_WIDTH * SCREEN_RESIZE, (FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT) * SCREEN_RESIZE), "Chomper", sf::Style::Close); //Pac-Man
					
					sf::RenderWindow Highscores(sf::VideoMode(CELL_SIZE * MAP_WIDTH * SCREEN_RESIZE, (FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT) * SCREEN_RESIZE), "Highscore", sf::Style::Close);

					int x = mainMenu.MainMenuPressed();
					if (x == 0)
					{
						Highscores.close();
						//window.close();


						sf::RenderWindow Game_options(sf::VideoMode(CELL_SIZE * MAP_WIDTH * SCREEN_RESIZE, (FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT) * SCREEN_RESIZE), "Game Difficulty", sf::Style::Close);
						OptionsMenu game_options(Game_options.getSize().x, Game_options.getSize().y);

						

						while (Game_options.isOpen())
						{

							difficulty = 0;

							sf::Event o_event;
							while (Game_options.pollEvent(o_event))
							{
								if (o_event.type == sf::Event::Closed)
								{
									Game_options.close();
								}

								if (o_event.type == sf::Event::KeyPressed)
								{
									if (o_event.key.code == sf::Keyboard::Escape)
									{
										Game_options.close();
									}
								}

								if (o_event.type == sf::Event::KeyPressed) //ili KeyReleased
								{
									if (o_event.key.code == sf::Keyboard::Up)
									{
										game_options.MoveUp();
										break;
									}

									if (o_event.key.code == sf::Keyboard::Down)
									{
										game_options.MoveDown();
										break;
									}

									if (o_event.key.code == sf::Keyboard::Return)
									{
										int y = game_options.OptionsMenuPressed();
										if (y == 0)
										{
											Game_options.close();
											difficulty = 1;
										}

										if (y == 1)
										{
											Game_options.close();
											difficulty = 2;
										}

										if (y == 2)
										{
											Game_options.close();
											difficulty = 3;
										}
									}
								}

								
							}
							//Game_options.clear(); // radi i bez toga
							//draw_map(outline_map, Game_options);
							Game_options.draw(op_sprite_packman);
							Game_options.draw(op_sprite_blinky);
							Game_options.draw(op_sprite_clyde);
							Game_options.draw(op_sprite_pinky);		

							/*Game_options.draw(text_hs);
							Game_options.draw(playerText);*/

							game_options.draw(Game_options);

							Game_options.display();

							
						}
						if (difficulty > 0)
						{
							score = 0;
							while (window.isOpen())
							{
								sf::Event p_event;
								while (window.pollEvent(p_event))
								{
									if (p_event.type == sf::Event::Closed)
									{
										window.close();
									}

									if (p_event.type == sf::Event::KeyPressed)
									{
										if (p_event.key.code == sf::Keyboard::Escape)
										{
											window.close();
										}
									}
								}
								Highscores.close();


								SoundManager gameSounds;

								gameSounds.s_munch.setVolume(5);

								gameSounds.s_siren.setLoop(true);

								gameSounds.s_energizer.setLoop(true);

								std::fstream myfile_normal;
								std::fstream myfile_hard;
								std::fstream myfile_insane;
								int high_score;
								int higher_score_ttl;

								srand(time(NULL));
								//dobivamo random index za mapu
								int randomIndex = rand() % 4;

								//Is the game won?
								bool game_won = 0;

								//Used to make the game framerate-independent.
								unsigned lag = 0;

								unsigned char level = 0;

								//Similar to lag, used to make the game framerate-independent.
								std::chrono::time_point<std::chrono::steady_clock> previous_time;

								std::array <std::array<std::string, MAP_HEIGHT>, 4> map_sketch;

								map_sketch = randomMap();

								std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> map;

								////Initial ghost positions.
								std::array<Position, 4> ghost_positions;


								sf::Event event;

								//sf::RenderWindow window(sf::VideoMode(CELL_SIZE * MAP_WIDTH * SCREEN_RESIZE, (FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT) * SCREEN_RESIZE), "Pac-Man", sf::Style::Close); //672,704 ovo je big dick matematika
								//Resizing the window.
								window.setView(sf::View(sf::FloatRect(0, 0, CELL_SIZE * MAP_WIDTH, FONT_HEIGHT + CELL_SIZE * MAP_HEIGHT)));

								//GhostManager ghost_manager;
								Pacman pacman;

								//Generating a random seed.
								srand(static_cast<unsigned>(time(0)));

								map = convert_sketch(map_sketch[randomIndex], ghost_positions, pacman);

								ghost_manager.reset(level, ghost_positions, gameSounds, difficulty);

								//Get the current time and store it in a variable.
								previous_time = std::chrono::steady_clock::now();

								while (1 == window.isOpen())
								{
									//Here we're calculating the lag.
									unsigned delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time).count();

									lag += delta_time;

									previous_time += std::chrono::microseconds(delta_time);
									//While the lag exceeds the maximum allowed frame duration.
									while (FRAME_DURATION <= lag)
									{
										//We decrease the lag.
										lag -= FRAME_DURATION;

										while (1 == window.pollEvent(event))
										{
											switch (event.type)
											{
											case sf::Event::Closed:
											{
												//Making sure the player can close the window.
												window.close();
												//Main_Menu.recreate();
											}
											case sf::Event::KeyPressed:
											{
												if (event.key.code == sf::Keyboard::Escape)
												{
													window.close();
												}
											}
											}
										}

										if (0 == game_won && 0 == pacman.get_dead())
										{
											

											if (!player_name.size() == 0)
											{
												player_name = "";
												playerInput.clear();
												playerText.setString("");
											}
											game_won = 1;

											pacman.update(level, map, gameSounds, difficulty);

											ghost_manager.update(level, map, pacman, gameSounds, difficulty);


											//We're checking every cell in the map.
											for (const std::array<Cell, MAP_HEIGHT>& column : map)
											{
												for (const Cell& cell : column)
												{
													if (Cell::Pellet == cell) //And if at least one of them has a pellet.
													{
														game_won = 0; //The game is not yet won.

														break;
													}
												}
											}

											if (1 == game_won)
											{
												pacman.set_animation_timer(0);
											}
										}
										else if (1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) //Restarting the game.
										{
											if (!player_name.size() == 0)
											{
												player_name = "";
												playerInput.clear();
												playerText.setString("");
											}

											game_won = 0;

											if (1 == pacman.get_dead())
											{
												level = 0;
											}
											else
											{
												//After each win we reduce the duration of attack waves and energizers.
												level++;
											}

											int randomIndex_2 = rand() % 4;

											while (randomIndex == randomIndex_2)
											{
												randomIndex_2 = rand() % 4;
											}

											randomIndex = randomIndex_2;

											map = convert_sketch(map_sketch[randomIndex_2], ghost_positions, pacman);

											ghost_manager.reset(level, ghost_positions, gameSounds, difficulty);

											pacman.reset();

										}

										if (FRAME_DURATION > lag)
										{
											window.clear();

											if (0 == game_won && 0 == pacman.get_dead())
											{
												draw_map(map, window);

												ghost_manager.draw(GHOST_FLASH_START >= pacman.get_energizer_timer(), window, gameSounds);

												draw_text(0, CELL_SIZE * MAP_HEIGHT, "Level: " + std::to_string(1 + level), window);

												std::string text3 = "Score: ";
												draw_text((CELL_SIZE * MAP_WIDTH - (text3.length() + 10) * 8) / 2, CELL_SIZE * MAP_HEIGHT, "Score: " + std::to_string(score), window);

												std::string text4 = "High Score: ";

												std::string txt_output;
												
												if (difficulty == 1)
												{
													myfile_normal.open("Resources/High Score/High Score Normal.txt");


													int first_line = 0;
													while (getline(myfile_normal, txt_output)) {
														first_line++;
														if (first_line == 1)
														{
															txt_output;
															break;
														}
													}
													std::pair <std::string, int> name_highscore(txt_output.substr(0, 8), stoi(txt_output.substr(9, 16)));
													high_score = (name_highscore.second);
													draw_text(CELL_SIZE * MAP_WIDTH - (text4.length() + 5) * 8, CELL_SIZE * MAP_HEIGHT, "High Score: " + std::to_string(high_score), window);

													std::string txt_output_last_score;
													int last_line = 0;
													while (getline(myfile_normal, txt_output_last_score)) {
														last_line++;
														if (last_line == 9)
														{
															txt_output;
															break;
														}
													}

													std::pair <std::string, int> lowest_hs(txt_output_last_score.substr(0, 8), stoi(txt_output_last_score.substr(9, 16)));
													higher_score_ttl = lowest_hs.second;

													if (score > higher_score_ttl)
													{
														high_score = score;
														new_higscore_reached = 1;
													}


													hs_score = score;
													myfile_normal.close();
												}
												else if ( difficulty == 2)
												{
													myfile_hard.open("Resources/High Score/High Score Hard.txt");


													int first_line = 0;
													while (getline(myfile_hard, txt_output)) {
														first_line++;
														if (first_line == 1)
														{
															txt_output;
															break;
														}
													}

													std::pair <std::string, int> name_highscore(txt_output.substr(0, 8), stoi(txt_output.substr(9, 16)));
													high_score = (name_highscore.second);
													draw_text(CELL_SIZE * MAP_WIDTH - (text4.length() + 5) * 8, CELL_SIZE * MAP_HEIGHT, "High Score: " + std::to_string(high_score), window);



													std::string txt_output_last_score;
													int last_line = 0;
													while (getline(myfile_hard, txt_output_last_score)) {
														last_line++;
														if (last_line == 9)
														{
															txt_output;
															break;
														}
													}

													std::pair <std::string, int> lowest_hs(txt_output_last_score.substr(0, 8), stoi(txt_output_last_score.substr(9, 16)));
													higher_score_ttl = lowest_hs.second;

													if (score > higher_score_ttl)
													{
														high_score = score;
														new_higscore_reached = 1;
													}

													hs_score = score;
													myfile_hard.close();
												}
												else
												{
													myfile_insane.open("Resources/High Score/High Score Insane.txt");


													int first_line = 0;
													while (getline(myfile_insane, txt_output)) {
														first_line++;
														if (first_line == 1)
														{
															txt_output;
															break;
														}
													}
													std::pair <std::string, int> name_highscore(txt_output.substr(0, 8), stoi(txt_output.substr(9, 16)));
													high_score = (name_highscore.second);
													draw_text(CELL_SIZE * MAP_WIDTH - (text4.length() + 5) * 8, CELL_SIZE * MAP_HEIGHT, "High Score: " + std::to_string(high_score), window);


													std::string txt_output_last_score;
													int last_line = 0;
													while (getline(myfile_insane, txt_output_last_score)) {
														last_line++;
														if (last_line == 9)
														{
															txt_output;
															break;
														}
													}

													std::pair <std::string, int> lowest_hs(txt_output_last_score.substr(0, 8), stoi(txt_output_last_score.substr(9, 16)));
													higher_score_ttl = lowest_hs.second;

													if (score > higher_score_ttl)
													{
														high_score = score;
														new_higscore_reached = 1;
													}

													hs_score = score;
													myfile_insane.close();
												}
												
											}

											pacman.draw(game_won, window);

											if (1 == pacman.get_animation_over())
											{
												if (1 == game_won)
												{
													gameSounds.Stop_all_sounds();
													std::string text1 = "Next level!";
													draw_text(((CELL_SIZE * MAP_HEIGHT) / 2) - (text1.length() * 8 / 2), ((CELL_SIZE * MAP_WIDTH) / 2) - strlen("Next level!"), text1, window);
												}
												else
												{
													gameSounds.Stop_all_sounds();
													std::string text2 = "Game over";
													draw_text(((CELL_SIZE * MAP_HEIGHT) / 2) - (text2.length() * 8 / 2), ((CELL_SIZE * MAP_WIDTH) / 2) - strlen("Game over"), "Game over", window);

													//provjera jeli dosegnut novi HS
													if (new_higscore_reached == 1)
													{
														window.draw(text_hs);
														//draw_text(((CELL_SIZE * MAP_HEIGHT) / 2) - (strlen("Insert player name") * 8 / 2), ((CELL_SIZE * MAP_WIDTH) / 2) - strlen("Insert player name"), "Insert player name", window);
														//std::cin >> player_name;


														//player_name = "";

														if (event.type == sf::Event::TextEntered)
														{
															std::cout << "Player name size: " << player_name.size() << std::endl;
															std::cout << player_name << std::endl;
															if (player_name.size() < 8)
															{
																std::cout << " prvi if " << player_name.size() << '\n';

																if ((event.text.unicode > 32) && (event.text.unicode < 128))
																{

																	std::cout << char(event.text.unicode);
																	playerInput += char(event.text.unicode);
																	playerText.setString(playerInput);
																	player_name += char(event.text.unicode);
																	std::cout << " drugi if " << player_name.size() << '\n';
																	//izbjegavati koristit funkciju sleep jer je specificna za operativni sustav
																	Sleep(155);
																}

																std::cout << "Izaso sam iz if uvjeta za pisanje" << '\n';
															}
															if ((player_name.size() > 0) && (event.text.unicode == 8))
															{

																playerInput = playerInput.substring(0, playerInput.getSize() - 1);
																playerText.setString(playerInput);
																player_name = player_name.substr(0, player_name.size() - 1);
																Sleep(155);
															}

														}
													
														if ((player_name.size() == 8) && (event.key.code == sf::Keyboard::Space))
														{
															window.draw(text_end);

															if (difficulty == 1)
															{
																myfile_normal.open("Resources/High Score/High Score Normal.txt");

																sort_txt(player_name, true, hs_score, difficulty);
																//myfile << high_score;
																myfile_normal.close();

																score = 0;
																hs_score = 0;
															}
															else if (difficulty == 2)
															{
																myfile_hard.open("Resources/High Score/High Score Hard.txt");

																sort_txt(player_name, true, hs_score, difficulty);
																//myfile << high_score;
																myfile_hard.close();

																score = 0;
																hs_score = 0;
															}
															else if (difficulty == 3)
															{
																myfile_insane.open("Resources/High Score/High Score Insane.txt");

																sort_txt(player_name, true, hs_score, difficulty);
																//myfile << high_score;
																myfile_insane.close();

																score = 0;
																hs_score = 0;
															}
														}
														
													}
												}

											}
											window.draw(playerText);
											window.display();
										}
									}
								}

							}
						}
					}
					if (x == 1)
					{
						

						while (Highscores.isOpen())
						{
							//HighScoreMenu highscore_menu;
							sf::Event h_event;
							while (Highscores.pollEvent(h_event))
							{
								if (h_event.type == sf::Event::Closed)
								{
									Highscores.close();
								}

								if (h_event.type == sf::Event::KeyPressed)
								{
									if (h_event.key.code == sf::Keyboard::Escape)
									{
										Highscores.close();
									}
								}
								

							}
							window.close();
							Highscores.clear();



							displayHighscores(Highscores, difficulty = 0, score);



							Highscores.display();
						}
					}
					if (x == 2)
					{
						Main_Menu.close();
					}
					break;
				}
			}
		}
		Main_Menu.clear();
		//Main_Menu.draw(mm_background);
		Main_Menu.draw(text);
		mainMenu.draw(Main_Menu);
		Main_Menu.display();
	}
}