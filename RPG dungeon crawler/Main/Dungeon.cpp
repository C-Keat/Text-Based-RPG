#include "Dungeon.h"
#include "Player.h"
#include<iostream>

Dungeon::Dungeon(Player p)  {

	player = p;

}

void Dungeon::enterRoom(Room* room) {

	if (room->enemies.size() != 0) {
		//handle room with enemy
		handleRoomWithEnemy(room);
	}
	else if(room->items.size() != 0){
		//handle room with chest
		handleRoomWithChest(room);
	}
	//else if (room->items.size() != 0 && room->items.size() != 0) handle room with chest and enemys
	else {
		handleEmptyRoom(room);
	}

}

void Dungeon::printActions(int numActions, std::vector<std::string> actions) {

	std::cout << "choose an action:\n";

	for (int i = 0; i < numActions; i++)
	{
		std::cout << actions[i] << "\n";
	}


}

void Dungeon::handleFightActions(GameCharacter * enemy) {
	
	std::string input;
	std::vector<std::string> actions { "a. Attack", "b. Retreat" };
	int playerDamage;
	int enemyDamage;

	while (true)
	{
		printActions(2, actions); 
		std::cin >> input;
		//handle player actions
		if (input == "a") {
			//attack
			playerDamage = enemy->takeDamage(player.attack);
			std::cout << "Your attack does " << playerDamage << " damage!" << std::endl;
			std::cout << "The enemy has " << enemy->currentHealth << " health remaining" << std::endl;
			//check to see if the enemy is dead			
		}
		else if (input == "b")
		{
			//retreat to last room
			player.changeRoom(player.previousRoom);
			enterRoom(player.currentRoom);
			return;
		}
		else {
			std::cout << "Please selected a valid option" << std::endl;
		}

		//check if the enemy is dead?
		if (enemy->checkIsDead()) {
			
			std::cout << "You have killed the " << enemy->name << "\n";
			player.increaseStats(10, 5, 5);
			std::cout << "Your new stats are: " << std::endl;
			player.printStats();

			//clear the room
			player.currentRoom->clearEnemies();
			return;
		}

		//The enemy is attacking
		std::cout << "The enemy is attacking you!\n";
		
		//the enemy hits
		enemyDamage = player.takeDamage(player.attack);
		std::cout << "The enemys attack does " << enemyDamage << " damage!" << std::endl;
		std::cout << "You now have " << player.currentHealth << " health left\n";
		if (player.checkIsDead())
		{
			return;
		}				
	}
}

void Dungeon::handleRoomWithEnemy(Room* room) {
	
	std::string input;
	GameCharacter enemy = room->enemies.front();

	std::cout << "You enter the room and see a " << enemy.name << "!";
	std::vector<std::string> actions{ "a. fight the " + enemy.name, "b. Move back to previous room" };

	while (true)
	{
		printActions(actions.size(), actions); 
		std::cin >> input;

		if (input == "a") {
			//fight
			handleFightActions(&enemy);
			return;
		}
		else if (input == "b")
		{
			player.changeRoom(player.previousRoom);
			enterRoom(player.currentRoom);
			return;
		}
		else {
			std::cout << "Please selected a valid option" << std::endl;
		}

	}
}

void Dungeon::handleLootActions(Room* room) {

	Item item = room->items.front();
	int roomISize = room->items.size();

	player.lootRoom(room);
	room->clearLoot();

	for (int i = 0; i < roomISize; i++) //printing the item that is found in the chest, based on the num in the chest
	{
		std::cout << "You open the chest and find a " << item.name << std::endl;
		std::cout << "Your health is now " << player.currentHealth << ", Attack: " << player.attack << ", Defence: " << player.defence << std::endl;
	}
}

void Dungeon::handleRoomWithChest(Room* room) {
	
	std::string input;
	std::cout << "You enter the room and see a large chest in the middle!";
	//std::string actions[] = { "a. Loot the chest", "b. Move to another room" };
	std::vector<std::string> actions{ "a. Loot the chest", "b. Move to another room" };

	while (true)
	{
		printActions(actions.size(), actions); 
		std::cin >> input;

		if (input == "a") {
			//loot chest
			handleLootActions(room);
			return;
		}
		else if (input == "b")
		{
			return;
		}
		else {
			std::cout << "Please selected a valid option" << std::endl;
		}
	}
}

void Dungeon::handleEmptyRoom(Room* room) {
	
	std::string input;
	
	std::cout << "You enter the room, but it is empty ";
	//std::string actions[] = { "a. Move to another room" };
	std::vector<std::string> actions{ "a. Move to another room" };

	while (true)
	{
		printActions(actions.size(), actions);
		std::cin >> input;

		if (input == "a") {
			return;
		}
		else {
			std::cout << "Please selected a valid option" << std::endl;
		}

	}

}

void Dungeon::handleMovementActions(Room* room) {
	
	std::vector<std::string> actions;
	std::string input;

	while (true)
	{
		if (room->pos == 0) {
			actions.push_back("a. Move right");
			actions.push_back("b. Move left");
			printActions(actions.size(), actions);
			
			std::cin >> input;

			if (input == "a") {
				player.changeRoom(&rooms[1]);
				actions.clear();
				return;
			}
			else if (input == "b") {
				//auto it = find(&rooms.begin(), &rooms.end(), int index)
				player.changeRoom(&rooms[2]);
				actions.clear();
				return;
			}
			else
			{
				std::cout << "Please select the valid choice\n";
			}

		}
		else if (room->pos == 1)
		{
			//std::string actions[] = { "a. Move left"};
			actions.push_back("a. Move left");
			
			printActions(actions.size(), actions);
			
			std::cin >> input;

			if (input == "a") {
				player.changeRoom(&rooms[0]);
				actions.clear();
				return;
			}
			else
			{
				std::cout << "Please select the valid choice\n";
			}
		}
		else if (room->pos == 2)
		{
			actions.push_back("a. Move up");
			actions.push_back("b. Move right");

			printActions(actions.size(), actions);
			
			std::cin >> input;

			if (input == "a") {
				player.changeRoom(&rooms[0]);
				actions.clear();
				return;
			}
			else if (input == "b") {
				player.changeRoom(&rooms[3]);
				actions.clear();
				return;
			}
			else
			{
				std::cout << "Please select the valid choice\n";
			}
		}
		else
		{
			actions.push_back("a. Move left");
			printActions(actions.size(), actions);

			std::cin >> input;

			if (input == "a") {
				player.changeRoom(&rooms[2]);
				actions.clear();
				return;
			}else
			{
				std::cout << "Please select the valid choice\n";
			}

		}
	}
}

int Dungeon::performEndGameLogic() {
	std::vector<std::string> actions{ "a. Yes","b. No" };
	
	while (true)
	{
		printActions(actions.size(), actions);
		std::string input;
		std::cin >> input;
		if (input == "a")
		{
			return 1;
		}
		else if (input == "b") {
			return 0;
		}
		else {
			std::cout << "Please selected a valid option\n";
		}

	}
}

int Dungeon::runDungeon() {

	std::cout << "Welcome to the dungeon! Inside you will find true tressure" << std::endl;
	player.currentRoom = &rooms[0];
	player.previousRoom = &rooms[0];

	while (true)
	{
		//enter the room
		enterRoom(player.currentRoom);
		//check if dead taking place
		//player.printStats();
		if (player.checkIsDead() == true) {
			//lose the game
			std::cout << "Game over! Your Dead Try again?\n";
			return performEndGameLogic();
		}
		else{
			if (player.currentRoom->isExit) {
				if (player.currentRoom->enemies.size() == 0) {
					std::cout << "YOU WIN! Play again?";
					return performEndGameLogic();
				}
			}
		}
		//movement options
		handleMovementActions(player.currentRoom);

	}

}