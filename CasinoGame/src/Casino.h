/*
 * Casino.h
 *
 *  Created on: 19.06.2017 ã.
 *      Author: ivanski
 */

#ifndef CASINO_H_
#define CASINO_H_
# include<vector>
using namespace std;
class Casino {
public:
	std::vector<Hall> halls;
	std::vector<std::string> files = { "hall1.xml" ,"hall2.xml" ,"hall3.xml" };
	void loadHalls() {
		for (int i = 0; i < files.size(); i++) {
			halls.push_back(loadHall(files[i]));
		}
	}

	Hall loadHall(std::string fileName) {
		Hall newHallObject;
		newHallObject.name = fileName;
		pugi::xml_document doc;
		pugi::xml_parse_result result = doc.load_file(fileName.c_str());
		pugi::xml_node hall = doc.child("hall");
		for (pugi::xml_node game = hall.first_child(); game;
			game = game.next_sibling()) {
			std::string name = game.child("name").text().as_string();
			int id = game.child("id").text().as_int();
			int level = game.child("level").text().as_int();
			int startcredit = game.child("startcredit").text().as_int();
			int endcredit = game.child("endcredit").text().as_int();
			Game gameObject(id, name, level, startcredit, endcredit);
			newHallObject.games.push_back(gameObject);
		}
		return newHallObject;
	}
	std::pair<std::string, int> getMostPlayed() {
		std::map <std::string, int> map;
		std::string mostPlayedName;
		int mostPlayedCount = 0;

		for (int k = 0; k < halls.size();k++) {
			Hall hall = halls[k];
			for (int i = 0; i < hall.games.size(); i++) {
				Game game = hall.games[i];
				map[game.name] = map[game.name] + 1;
			}

		}
		for (std::map <std::string, int> ::iterator it = map.begin(); it != map.end(); ++it)
		{
			if (it->second > mostPlayedCount) {
				mostPlayedCount = it->second;
				mostPlayedName = it->first;
			}
		}
		return make_pair(mostPlayedName, mostPlayedCount);
	}

	std::pair<std::string, int> getMostProfitable() {
		std::map <std::string, int> map;
		std::string mostProfitableName;
		int mostProfit= 0;

		for (int k = 0; k < halls.size();k++) {
			Hall hall = halls[k];
			for (int i = 0; i < hall.games.size(); i++) {
				Game game = hall.games[i];
				map[game.name] = map[game.name] + game.startcredit-game.endcredit;
			}

		}
		for (std::map <std::string, int> ::iterator it = map.begin(); it != map.end(); ++it)
		{
			if (it->second > mostProfit) {
				mostProfit = it->second;
				mostProfitableName = it->first;
			}
		}
		return make_pair(mostProfitableName, mostProfit);
	}
	std::pair<std::string, int> getGameLevel(std::string nameOfGame) {
		for (int k = 0; k < halls.size();k++) {
			Hall hall = halls[k];
			for (int i = 0; i < hall.games.size(); i++) {
				Game game = hall.games[i];
				if (game.name == nameOfGame) {
					return make_pair(game.name, game.level);
				}
			}

		}
		return std::make_pair("Game not found!", -1);
	}
	void showProfit() {
		for (int i = 0; i < halls.size(); i++) {
			cout << "Hall " << i << ": " << endl;
			int winForHall = 0;
			for (int k = 0; k < halls[i].games.size(); k++) {
				Game game = halls[i].games[k];
				int winForGame = game.startcredit - game.endcredit;
				cout << "Game " << k << " win credits: " << winForGame << endl;
				winForHall +=winForGame;
			}
			cout << "Hall " << i << " win credits: " << winForHall << endl;
		}
	}

	void showCasinoProfitToday() {
		int profit = 0;
		for (int i = 0; i < halls.size(); i++) {
			int winForHall = 0;
			for (int k = 0; k < halls[i].games.size(); k++) {
				Game game = halls[i].games[k];
				int winForGame = game.startcredit - game.endcredit;
				winForHall = +winForGame;
			}
			profit += winForHall;
		}
		cout << "Casino win credits: " << profit << endl;
	}
};
#endif /* CASINO_H_ */
