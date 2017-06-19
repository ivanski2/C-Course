/*
 * Hall.h
 *
 *  Created on: 19.06.2017 ã.
 *      Author: ivanski
 */

#ifndef HALL_H_
#define HALL_H_

class Hall {
public:
	std::string name;
	std::vector<Game> games;
	std::pair<std::string, int> getLeastPlayed() {
		std::map <std::string, int> map;
		std::string leastPlayedName;
		int leastPlayedCount = INT_MAX;
		for (int i = 0; i < games.size(); i++) {
			Game game = games[i];
			map[game.name] = map[game.name] + 1;
		}
		for (std::map <std::string, int> ::iterator it = map.begin(); it != map.end(); ++it)
		{
			if (it->second < leastPlayedCount) {
				leastPlayedCount = it->second;
				leastPlayedName = it->first;
			}
		}
		return make_pair(leastPlayedName, leastPlayedCount);
	}
};

#endif /* HALL_H_ */
