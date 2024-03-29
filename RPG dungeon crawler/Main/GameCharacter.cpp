#include "GameCharacter.h"

GameCharacter::GameCharacter(std::string n, int h, int a, int d) {

	name = n;
	maxHealth = h;
	currentHealth = h;
	attack = a;
	defence = d;
}

int GameCharacter::takeDamage(int amount) {
	int damage = amount - defence;

	if (damage < 0) {
		damage = 0;
	}
	currentHealth -= damage;
	return damage;

}

bool GameCharacter::checkIsDead() {

	//std::cout << "current health = " << currentHealth << std::endl;

	return currentHealth <= 0;

}