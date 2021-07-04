#pragma once
#include<string>
#include<iostream>

#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H
class GameCharacter
{
public:
	std::string name;
	int maxHealth, currentHealth, attack, defence;
	GameCharacter(std::string name, int health, int attack, int defence);
	int takeDamage(int);
	bool checkIsDead();

};
#endif GAMECHARACTER_H

