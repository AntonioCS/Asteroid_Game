#pragma once

constexpr int NUM_SCORES{ 10 };

class high_score {
public:
	high_score() {
		//Open score files for reading in binary
		SDL_RWops* high_scores_file = SDL_RWFromFile("data/10_top _high_scores_file.txt", "r+b");
		if (high_scores_file == nullptr) { std::cout << "hi score file not loaded\n"; }
/*		//Initialize data
		for (int i = 0; i < NUM_SCORES; ++i)
		{
			SDL_RWwrite(high_scores_file, &init_table_hi_score[i], sizeof(Sint32), 1);
		}

		//Close file handler
		SDL_RWclose(high_scores_file);*/

		// load data
		for (int i = 0; i < NUM_SCORES; ++i)
		{
			std::cout << table_hi_score[i] << "\n";
			SDL_RWread(high_scores_file, &table_hi_score[i], sizeof(Sint32), 1);
		}
		//Close file handler
		SDL_RWclose(high_scores_file);

		//Open name files for reading in binary
		SDL_RWops* name_file = SDL_RWFromFile("data/10_top _names_file.txt", "r+b");
		if (name_file == nullptr) { std::cout << "name file not loaded\n"; }
/*		//Initialize data
		for (int i = 0; i < NUM_SCORES; ++i)
		{
			tmp_name = init_table_names[i];
			SDL_RWwrite(name_file, &tmp_name, sizeof(char), 1);
		}

		//Close file handler
		SDL_RWclose(name_file);*/

		// load data

		SDL_RWread(name_file, table_names, sizeof(char), 10);
	/*	for (int i = 0; i < NUM_SCORES; ++i)
		{
		//	std::cout << name_file[i] << "\n";
			SDL_RWread(name_file, &table_names[i], sizeof(char), 1);
		}
		//Close file handler*/
		SDL_RWclose(name_file);
		

	}



//	Sint32 init_table_hi_score[NUM_SCORES] = { 0,10,200, 3000, 40000, 500000, 6000000, 700, 80, 9 };
	Sint32 table_hi_score[NUM_SCORES];
//	std::vector<std::string> init_table_names = { "AAA","BBB", "CCC", "DDD", "EEE", "FFF", "GGG", "HHH", "III", "JJJ" };
//	std::vector<char> init_table_names = { 'A','B', 'C', 'D', 'E', 'F', 'G',  'H', 'I', 'J' };
	
	//char table_names[NUM_SCORES];
	char table_names[1][NUM_SCORES];
	
private:
	char tmp_name;
	std::string tmp_s{ "0" };
};


