/*
 * Game.h
 *
 *  Created on: 19.06.2017 ã.
 *      Author: ivanski
 */

#ifndef GAME_H_
#define GAME_H_

class Game {
public:
	int id;
	std::string name;
	int level;
	int startcredit;
	int endcredit;
	Game(int id, std::string name, int level, int startcredit, int endcredit) : id(id), name(name), level(level), startcredit(startcredit), endcredit(endcredit)
	{
	}
};

#endif /* GAME_H_ */
