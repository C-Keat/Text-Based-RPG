#include "Room.h"

Room::Room(int p, bool ie, std::vector<Item> items, std::vector<GameCharacter> enemies) {
	pos = p;
	isExit = ie;
	this->items = items;
	this->enemies = enemies;
}

void Room::clearLoot() {
	items.clear();
}

void Room::clearEnemies() {

	enemies.clear();

}