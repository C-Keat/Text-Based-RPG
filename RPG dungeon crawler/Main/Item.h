#pragma once
#include<string>

#ifndef ITEM_H
#define ITEM_H

class Item
{
public:
	std::string name;
	int health, attack, defence;
	Item(std::string, int health, int attack, int defence);
	void ItemDefiner();

};
#endif ITEM_H

