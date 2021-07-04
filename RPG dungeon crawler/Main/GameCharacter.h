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
	GameCharacter(std::string, int, int, int);
	int takeDamage(int);
	bool checkIsDead();

};
#endif GAMECHARACTER_H

