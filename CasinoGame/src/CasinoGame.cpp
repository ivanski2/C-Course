//============================================================================
// Name        : CasinoGame.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <string>
#include "pugixml.hpp"
#include "pugiconfig.hpp"
#include <iostream>
#include <map>
#include <algorithm>
#include <utility>
#include <cmath>
#include <climits>
using namespace std;
#include "Hall.h"
#include "Casino.h"
#include "Game.h"



Casino casino;
	casino.loadHalls();
	while (true) {
		cout << "1.Profit of hall and its games"<< endl;
		cout << "2.Daily profit of casino" << endl;
		cout << "3.Least played game in hall" << endl;
		cout << "4.Most played game in casino" << endl;
		cout << "5.Most profitable game in casino" << endl;
		cout << "6.Search for game level" << endl;
		int choice;
		std::cin >> choice;
		if(choice == 1){
			casino.showProfit();
			continue;
		}
		else if (choice == 2) {
			casino.showCasinoProfitToday();
			continue;
		}
		else if (choice == 3) {
			for (int i = 0;i < casino.halls.size();i++) {
				std::pair<std::string, int> pair = casino.halls[i].getLeastPlayed();
				cout << "Least played for hall:" << i << "->"<<pair.first<<":"<<pair.second<< endl;
			}
			continue;
		}
		else if (choice == 4) {
			std::pair<std::string, int> pair = casino.getMostPlayed();
			cout << "Most played game in casino:" << "->" << pair.first << ":" << pair.second << endl;
			continue;
		}
		else if (choice == 5) {
			std::pair<std::string, int> pair = casino.getMostProfitable();
			cout << "Most profitable game in casino:" << "->" << pair.first << ":" << pair.second << endl;
			continue;
		}
		else if (choice == 6) {
			cout << "Enter game to search" << endl;
			std::string choice;
			std::cin >> choice;
			std::pair<std::string, int> pair = casino.getGameLevel(choice);
			cout << "Game level:" << "->" << pair.first << ":" << pair.second << endl;
			continue;
		}
