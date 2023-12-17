#include "Sorting.hpp"

#include <iostream>
#include <array>
#include <fstream>
#include <string>
#include <utility>

void sort_txt(std::string& name, bool add, int& score, int difficulty)
{
	std::fstream myfile_normal;
	std::fstream myfile_hard;
	std::fstream myfile_insane;
	myfile_normal.open("Resources/High Score/High Score Normal.txt");
	myfile_hard.open("Resources/High Score/High Score Hard.txt");
	myfile_insane.open("Resources/High Score/High Score Insane.txt");

	std::string txt_output_hs;

	int i = 0;

	std::array<std::pair<std::string, int>, 10> arr;
	int n = 10;

	if (difficulty == 0 && add == false)
	{
		//Normal difficulty

		while (getline(myfile_normal, txt_output_hs))
		{
			std::pair<std::string, int> name_hs(txt_output_hs.substr(0, 8), stoi(txt_output_hs.substr(9, 16)));
			arr[i] = name_hs;
			i++;
		};

		//while (getline(myfile_normal, txt_output_hs))
		//{
		//	arr[i] = stoi(txt_output_hs);
		//	i++;
		//};

		myfile_normal.close();
		myfile_normal.open("Resources/High Score/High Score Normal.txt");

		//Bubble sort
		for (int i = 0; i < n - 1; i++)
		{
			for (int j = 0; j < n - i - 1; j++)
			{
				if (arr[j].second < arr[j + 1].second)
				{

					std::pair <std::string, int> temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
				}
			}
		}

		//inserting values into the file
		for (int i = 0; i < n; i++)
		{
			//std::cout << arr[i] << std::endl;
			if (i < 9)
			{
				myfile_normal << arr[i].first << "," << arr[i].second << '\n';
			}
			else
			{
				myfile_normal << arr[i].first << "," << arr[i].second;
			}
		}
		myfile_normal.close();

		//Hard difficulty

		i = 0;
		while (getline(myfile_hard, txt_output_hs))
		{
			std::pair<std::string, int> name_hs(txt_output_hs.substr(0, 8), stoi(txt_output_hs.substr(9, 16)));
			arr[i] = name_hs;
			i++;
		};

		myfile_hard.close();
		myfile_hard.open("Resources/High Score/High Score Hard.txt");

		//Bubble sort
		for (int i = 0; i < n - 1; i++)
		{
			for (int j = 0; j < n - i - 1; j++)
			{
				if (arr[j].second < arr[j + 1].second)
				{

					std::pair <std::string, int> temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
				}
			}
		}

		for (int i = 0; i < n; i++)
		{
			//std::cout << arr[i] << std::endl;
			if (i < 9)
			{
				myfile_hard << arr[i].first << "," << arr[i].second << '\n';
			}
			else
			{
				myfile_hard << arr[i].first << "," << arr[i].second;
			}
		}
		myfile_hard.close();

		//Insane difficulty

		i = 0;
		while (getline(myfile_insane, txt_output_hs))
		{
			std::pair<std::string, int> name_hs(txt_output_hs.substr(0, 8), stoi(txt_output_hs.substr(9, 16)));

			arr[i] = name_hs;
			i++;
		};

		myfile_insane.close();
		myfile_insane.open("Resources/High Score/High Score Insane.txt");

		//Bubble sort
		for (int i = 0; i < n - 1; i++)
		{
			for (int j = 0; j < n - i - 1; j++)
			{
				if (arr[j].second < arr[j + 1].second)
				{

					std::pair <std::string, int> temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
				}
			}
		}

		for (int i = 0; i < n; i++)
		{
			//std::cout << arr[i] << std::endl;
			if (i < 9)
			{
				myfile_insane << arr[i].first << "," << arr[i].second << '\n';
			}
			else
			{
				myfile_insane << arr[i].first << "," << arr[i].second;
			}
		}
		myfile_insane.close();
	}
	else
	{
		
		if (difficulty == 1)
		{
			std::array<std::pair<std::string, int>, 11> comparing_arr;
			int m = 11;

			while (getline(myfile_normal, txt_output_hs))
			{
				std::pair<std::string, int> name_hs(txt_output_hs.substr(0, 8), stoi(txt_output_hs.substr(9, 16)));
				comparing_arr[i] = name_hs;
				i++;
			};

			std::pair <std::string, int> new_pair (name, score);
			comparing_arr[10] = new_pair;

			myfile_normal.close();
			myfile_normal.open("Resources/High Score/High Score Normal.txt");

			//Bubble sort
			for (int i = 0; i < m - 1; i++)
			{
				for (int j = 0; j < m - i - 1; j++)
				{
					if (comparing_arr[j].second < comparing_arr[j + 1].second)
					{

						std::pair <std::string, int> temp = comparing_arr[j];
						comparing_arr[j] = comparing_arr[j + 1];
						comparing_arr[j + 1] = temp;
					}
				}
			}

			for (int i = 0; i < 10; i++)
			{
				arr[i] = comparing_arr[i];
			}

			//writing in TXT
			for (int i = 0; i < n; i++)
			{
				if (i < 9)
				{
					//std::cout << arr[i] << std::endl;
					myfile_normal << arr[i].first << "," <<arr[i].second << '\n';
				}
				else
				{
					myfile_normal << arr[i].first << "," << arr[i].second;
				}

			}
			myfile_normal.close();
		}
		else if (difficulty == 2)
		{
			std::array<std::pair<std::string, int>, 11> comparing_arr;
			int m = 11;

			while (getline(myfile_hard, txt_output_hs))
			{
				std::pair<std::string, int> name_hs(txt_output_hs.substr(0, 8), stoi(txt_output_hs.substr(9, 16)));
				comparing_arr[i] = name_hs;
				i++;
			};

			std::pair <std::string, int> new_pair(name, score);
			comparing_arr[10] = new_pair;

			myfile_hard.close();
			myfile_hard.open("Resources/High Score/High Score Hard.txt");

			//Bubble sort
			for (int i = 0; i < m - 1; i++)
			{
				for (int j = 0; j < m - i - 1; j++)
				{
					if (comparing_arr[j].second < comparing_arr[j + 1].second)
					{

						std::pair <std::string, int> temp = comparing_arr[j];
						comparing_arr[j] = comparing_arr[j + 1];
						comparing_arr[j + 1] = temp;
					}
				}
			}

			for (int i = 0; i < 10; i++)
			{
				arr[i] = comparing_arr[i];
			}

			for (int i = 0; i < n; i++)
			{
				if (i < 9)
				{
					//std::cout << arr[i] << std::endl;
					myfile_hard << arr[i].first << "," <<arr[i].second << '\n';
				}
				else
				{
					myfile_hard << arr[i].first << "," << arr[i].second;
				}

			}
			myfile_hard.close();
		}
		else if (difficulty == 3)
		{
			std::array<std::pair<std::string, int>, 11> comparing_arr;
			int m = 11;

			while (getline(myfile_insane, txt_output_hs))
			{
				std::pair<std::string, int> name_hs(txt_output_hs.substr(0, 8), stoi(txt_output_hs.substr(9, 16)));
				comparing_arr[i] = name_hs;
				i++;
			};

			std::pair <std::string, int> new_pair(name, score);
			comparing_arr[10] = new_pair;

			myfile_insane.close();
			myfile_insane.open("Resources/High Score/High Score Insane.txt");

			//Bubble sort
			for (int i = 0; i < m - 1; i++)
			{
				for (int j = 0; j < m - i - 1; j++)
				{
					if (comparing_arr[j].second < comparing_arr[j + 1].second)
					{

						std::pair <std::string, int> temp = comparing_arr[j];
						comparing_arr[j] = comparing_arr[j + 1];
						comparing_arr[j + 1] = temp;
					}
				}
			}

			for (int i = 0; i < 10; i++)
			{
				arr[i] = comparing_arr[i];
			}

			for (int i = 0; i < n; i++)
			{
				if (i < 9)
				{
					//std::cout << arr[i] << std::endl;
					myfile_insane << arr[i].first << "," << arr[i].second << '\n';
				}
				else
				{
					myfile_insane << arr[i].first << "," << arr[i].second;
				}

			}
			myfile_insane.close();
		}
	}
	myfile_normal.close();
	myfile_hard.close();
	myfile_insane.close();
};

