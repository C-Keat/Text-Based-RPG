#pragma once
#include<string>

#include"Room.h"
#include"Player.h"

#ifndef DUNGEON_H
#define DUNGEON_H

class Dungeon
{

//attributes
public:
	Player player;
	std::vector<Room> rooms;

//functions
public:
	Dungeon(Player);
	int runDungeon();
	void enterRoom(Room*);
	void handleEmptyRoom(Room*);
	void handleRoomWithChest(Room*);
	void handleRoomWithEnemy(Room*);
	void handleRoomWithEnemyAndLoot(Room*);
	void handleLootActions(Room*);
	void handleFightActions(GameCharacter*);
	void handleMovementActions(Room*);
	void printActions(int, std::vector<std::string>);
	int performEndGameLogic();


};
#endif DUNGEON_H


