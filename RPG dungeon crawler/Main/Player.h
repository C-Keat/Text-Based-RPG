#pragma once
#include "GameCharacter.h"
#include "Room.h"


#ifndef PLAYER_H
#define PLAYER_H

class Player : public GameCharacter
{
public:
	Room *currentRoom, *previousRoom;
	std::vector<Item> inventory;
	
public:
	Player(std::string="", int=0, int=0, int=0);
	void addItem(Item);
	void increaseStats(int, int, int);
	void lootRoom(Room *);
	void changeRoom(Room *);
	void printStats();


};

#endif PLAYER_H

