#pragma once
#include<string>
#include<vector>
#include"Item.h"
#include"GameCharacter.h"

#ifndef ROOM_H
#define ROOM_H

class Room
{
public:
	int pos;
	bool isExit;
	std::vector<Item> items;
	std::vector<GameCharacter> enemies;

public:
	Room(int position = 0, bool isExit = false, std::vector<Item> items = std::vector<Item>(),std::vector<GameCharacter> enemies = std::vector<GameCharacter>());
	void clearLoot();
	void clearEnemies();

};

#endif // !ROOM_H

