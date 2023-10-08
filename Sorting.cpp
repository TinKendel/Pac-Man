#include "Sorting.hpp"

#include <algorithm>
#include <iostream>
#include <array>
#include <fstream>
#include <string>

void sort_txt(bool add, int& score, int difficulty)
{
	std::fstream myfile_normal;
	std::fstream myfile_hard;
	std::fstream myfile_insane;
	myfile_normal.open("Resources/High Score/High Score Normal.txt");
	myfile_hard.open("Resources/High Score/High Score Hard.txt");
	myfile_insane.open("Resources/High Score/High Score Insane.txt");

	std::string txt_output_hs;

	int i = 0;

	std::array<int, 10> arr;
	int n = 10;

	if (difficulty == 0 && add == false)
	{
		//Normal difficulty
		while (getline(myfile_normal, txt_output_hs))
		{
			arr[i] = stoi(txt_output_hs);
			i++;
		};

		myfile_normal.close();
		myfile_normal.open("Resources/High Score/High Score Normal.txt");
		//myfile.clear();

		//Bubble sort
		for (int i = 0; i < n - 1; i++)
		{
			for (int j = 0; j < n - i - 1; j++)
			{
				if (arr[j] < arr[j + 1])
				{

					int temp = arr[j];
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
				myfile_normal << arr[i] << '\n';
			}
			else
			{
				myfile_normal << arr[i];
			}
		}
		myfile_normal.close();

		//Hard difficulty

		i = 0;
		while (getline(myfile_hard, txt_output_hs))
		{
			arr[i] = stoi(txt_output_hs);
			i++;
		};

		myfile_hard.close();
		myfile_hard.open("Resources/High Score/High Score Hard.txt");

		//Bubble sort
		for (int i = 0; i < n - 1; i++)
		{
			for (int j = 0; j < n - i - 1; j++)
			{
				if (arr[j] < arr[j + 1])
				{

					int temp = arr[j];
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
				myfile_hard << arr[i] << '\n';
			}
			else
			{
				myfile_hard << arr[i];
			}
		}
		myfile_hard.close();

		//Insane difficulty

		i = 0;
		while (getline(myfile_insane, txt_output_hs))
		{
			arr[i] = stoi(txt_output_hs);
			i++;
		};

		myfile_insane.close();
		myfile_insane.open("Resources/High Score/High Score Insane.txt");

		//Bubble sort
		for (int i = 0; i < n - 1; i++)
		{
			for (int j = 0; j < n - i - 1; j++)
			{
				if (arr[j] < arr[j + 1])
				{

					int temp = arr[j];
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
				myfile_insane << arr[i] << '\n';
			}
			else
			{
				myfile_insane << arr[i];
			}
		}
		myfile_insane.close();
	}
	else
	{
		
		if (difficulty == 1)
		{
			std::array<int, 11> comparing_arr;
			int m = 11;

			while (getline(myfile_normal, txt_output_hs))
			{
				comparing_arr[i] = stoi(txt_output_hs);
				i++;
			};

			comparing_arr[10] = score;

			myfile_normal.close();
			myfile_normal.open("Resources/High Score/High Score Normal.txt");

			//Bubble sort
			for (int i = 0; i < m - 1; i++)
			{
				for (int j = 0; j < m - i - 1; j++)
				{
					if (comparing_arr[j] < comparing_arr[j + 1])
					{

						int temp = comparing_arr[j];
						comparing_arr[j] = comparing_arr[j + 1];
						comparing_arr[j + 1] = temp;
					}
				}
			}

			for (int i = 0; i < 10; i++)
			{
				arr[i] = comparing_arr[i];
			}

			//upisivanje u TXT
			for (int i = 0; i < n; i++)
			{
				if (i < 9)
				{
					//std::cout << arr[i] << std::endl;
					myfile_normal << arr[i] << '\n';
				}
				else
				{
					myfile_normal << arr[i];
				}

			}
			myfile_normal.close();
		}
		else if (difficulty == 2)
		{
			std::array<int, 11> comparing_arr;
			int m = 11;

			while (getline(myfile_hard, txt_output_hs))
			{
				comparing_arr[i] = stoi(txt_output_hs);
				i++;
			};

			comparing_arr[10] = score;

			myfile_hard.close();
			myfile_hard.open("Resources/High Score/High Score Hard.txt");

			//Bubble sort
			for (int i = 0; i < m - 1; i++)
			{
				for (int j = 0; j < m - i - 1; j++)
				{
					if (comparing_arr[j] < comparing_arr[j + 1])
					{

						int temp = comparing_arr[j];
						comparing_arr[j] = comparing_arr[j + 1];
						comparing_arr[j + 1] = temp;
					}
				}
			}

			for (int i = 0; i < 10; i++)
			{
				arr[i] = comparing_arr[i];
			}

			//upisivanje u TXT
			for (int i = 0; i < n; i++)
			{
				if (i < 9)
				{
					//std::cout << arr[i] << std::endl;
					myfile_hard << arr[i] << '\n';
				}
				else
				{
					myfile_hard << arr[i];
				}

			}
			myfile_hard.close();
		}
		else if (difficulty == 3)
		{
			std::array<int, 11> comparing_arr;
			int m = 11;

			while (getline(myfile_insane, txt_output_hs))
			{
				comparing_arr[i] = stoi(txt_output_hs);
				i++;
			};

			comparing_arr[10] = score;

			myfile_insane.close();
			myfile_insane.open("Resources/High Score/High Score Insane.txt");

			//Bubble sort
			for (int i = 0; i < m - 1; i++)
			{
				for (int j = 0; j < m - i - 1; j++)
				{
					if (comparing_arr[j] < comparing_arr[j + 1])
					{

						int temp = comparing_arr[j];
						comparing_arr[j] = comparing_arr[j + 1];
						comparing_arr[j + 1] = temp;
					}
				}
			}

			for (int i = 0; i < 10; i++)
			{
				arr[i] = comparing_arr[i];
			}

			//upisivanje u TXT
			for (int i = 0; i < n; i++)
			{
				if (i < 9)
				{
					//std::cout << arr[i] << std::endl;
					myfile_insane << arr[i] << '\n';
				}
				else
				{
					myfile_insane << arr[i];
				}

			}
			myfile_insane.close();
		}
	}
	myfile_normal.close();
	myfile_hard.close();
	myfile_insane.close();
};

