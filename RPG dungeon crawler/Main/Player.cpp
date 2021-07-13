#include "Player.h"

//called apone creation
Player::Player(std::string n, int h, int a, int d) : GameCharacter(n,h,a,d) {
	Item dagger = Item("Dagger", 0, 5, 0);
	addItem(dagger);
}

void Player::addItem(Item item) {

	inventory.push_back(item);
	increaseStats(item.health, item.attack, item.defence);
}

void Player::increaseStats(int h, int a, int d) {

	currentHealth += h;
	maxHealth += h;
	attack += a;
	defence += d;

}

void Player::printStats() {

	std::cout << "Current Health: " << currentHealth << "\nAttack: " << attack << "\nDefence: " << defence << std::endl;

}

void Player::lootRoom(Room* room) {

	std::vector<Item> items = room->items;
	for (int i = 0; i < items.size(); i++) {
		addItem(items[i]);
	}


}
void Player::changeRoom(Room* newRoom) {

	previousRoom = currentRoom;
	std::cout << "You enter room" << newRoom->pos << std::endl;

	currentRoom = newRoom;

}
