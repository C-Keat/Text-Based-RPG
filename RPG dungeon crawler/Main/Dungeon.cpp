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
	else if (room->items.size() != 0 && room->enemies.size() != 0) {
		//handle room with enemy and chest
		handleRoomWithEnemyAndLoot(room);

	}
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

void Dungeon::handleRoomWithEnemyAndLoot(Room* room) {

	//logic for room handeling
	std::string input;
	//fight first before being able to get to the chest 
	
	handleRoomWithEnemy(room);

	//after fight over, handle the chest
	std::cout << "After defeating the enemys its clear they were guarding a chest!";
	//std::string actions[] = { "a. Loot the chest", "b. Move to another room" };
	std::vector<std::string> actions{ "a. Loot the chest", "b. Move to another room" };

	while (true && input != "b")
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

			//need to clear the enemy that is actually dead not the whole room
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
	//got to capture the number of enemys in the room, not just the one at the front so that the fight continues until all are dead
	//GameCharacter enemy = room->enemies.front();

	//need to print the number of enemies in room

	std::vector<GameCharacter> enemy = room->enemies;

	std::cout << "You enter the room and see " << enemy.size() + 1 << " " << enemy.front().name << "!" << std::endl;
	std::cout << "You will have to fight them one at a time, the room is too small to do anything else or you can run" << std::endl;

	std::vector<std::string> actions;

	while (true)
	{
		enemy = room->enemies;

		actions.push_back("a. fight the " + enemy.front().name);
		actions.push_back("b. Move back to previous room!");

		printActions(actions.size(), actions); 
		std::cin >> input;


		if (input == "a") {
			//fight
			if (enemy.size() != 0) {
				handleFightActions(&enemy.front());
			}
			else {
				std::cout << "There are no more enemies to fight" << std::endl;
				return;
			}	
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
		//the middle row
		if (room->pos == 0 || room->pos == 3 || room->pos == 6) {

			actions.push_back("a. Move right");
			actions.push_back("b. Move left");
			actions.push_back("c. Move up");

			if (room->pos == 3 || room->pos == 6) {
				actions.push_back("d. Move back");
			}

			printActions(actions.size(), actions);

			std::cin >> input;

			if (input == "a") {
				//middle row - move right

				if (rooms.size() >= 3 && room->pos == 0) {
					player.changeRoom(&rooms[room->pos + 1]);
				}
				else if (rooms.size() >= 6 && room->pos == 3) {
					player.changeRoom(&rooms[room->pos + 1]);
				}
				else if (rooms.size() >= 9 && room->pos == 6) {
					player.changeRoom(&rooms[room->pos + 1]);
				}
				else {
					std::cout << "That door goes no where, try another" << std::endl;
					player.changeRoom(&rooms[room->pos]);
				}

				actions.clear();
				return;
			}
			else if (input == "b") {
				//middle row - move left

				if (rooms.size() >= 3 && room->pos == 0) {
					player.changeRoom(&rooms[room->pos + 2]);
				}
				else if (rooms.size() >= 6 && room->pos == 3) {
					player.changeRoom(&rooms[room->pos + 2]);
				}
				else if (rooms.size() >= 9 && room->pos == 6) {
					player.changeRoom(&rooms[room->pos + 2]);
				}
				else {
					std::cout << "That door goes no where, try another" << std::endl;
					player.changeRoom(&rooms[room->pos]);
				}

				actions.clear();
				return;
			}
			else if (input == "c") {
				//middle row - move up

				if (rooms.size() >= 3 && room->pos == 0) {
					player.changeRoom(&rooms[room->pos + 3]);
				}
				else if (rooms.size() >= 6 && room->pos == 3) {
					player.changeRoom(&rooms[room->pos + 3]);
				}
				else {
					std::cout << "That door goes no where, try another" << std::endl;
					player.changeRoom(&rooms[room->pos]);
				}

				actions.clear();
				return;
			}
			else if (input == "d" && room->pos == 3 || input == "d" && room->pos == 6) {
				//move down
				player.changeRoom(&rooms[room->pos - 3]);
				actions.clear();
				return;
			}
			else
			{
				std::cout << "Please select the valid choice\n";
			}

		}

		//the left row
		if (room->pos == 2 || room->pos == 5 || room->pos == 8) {

			actions.push_back("a. Move right");
			actions.push_back("b. Move up");
			if (room->pos == 5 || room->pos == 8) {
				actions.push_back("c. Move down");
			}

			printActions(actions.size(), actions);

			std::cin >> input;

			if (input == "a") {
				//left row - move right

				if (rooms.size() >= 3 && room->pos == 2) {
					player.changeRoom(&rooms[room->pos - 2]);
				}
				else if (rooms.size() >= 5 && room->pos == 5) {
					player.changeRoom(&rooms[room->pos - 2]);
				}
				else if (rooms.size() >= 8 && room->pos == 8) {
					player.changeRoom(&rooms[room->pos - 2]);
				}

				actions.clear();
				return;
			}
			else if (input == "b") {
				//left row - move up

				if (rooms.size() >= 5 && room->pos == 2) {
					player.changeRoom(&rooms[room->pos + 3]);
				}
				else if (rooms.size() >= 8 && room->pos == 5) {
					player.changeRoom(&rooms[room->pos + 3]);
				}
				else {
					std::cout << "That door goes no where, try another" << std::endl;
					player.changeRoom(&rooms[room->pos]);
				}

				actions.clear();
				return;
			}
			else if (input == "c") {
				//left row - move down

				if (rooms.size() >= 5 && room->pos == 5) {
					player.changeRoom(&rooms[room->pos - 3]);
				}
				else if (rooms.size() >= 8 && room->pos == 8) {
					player.changeRoom(&rooms[room->pos - 3]);
				}

				actions.clear();
				return;
			}
			else
			{
				std::cout << "Please select the valid choice\n";
			}

		}

		//the right row

		if (room->pos == 1 || room->pos == 4 || room->pos == 7) {

			actions.push_back("a. Move left");
			actions.push_back("b. Move up");
			if (room->pos == 4 || room->pos == 7) {
				actions.push_back("c. Move down");
			}

			printActions(actions.size(), actions);

			std::cin >> input;

			if (input == "a") {
				//right row - move left

				if (rooms.size() >= 3 && room->pos == 1) {
					player.changeRoom(&rooms[room->pos - 1]);
				}
				else if (rooms.size() >= 4 && room->pos == 4) {
					player.changeRoom(&rooms[room->pos - 1]);
				}
				else if (rooms.size() >= 7 && room->pos == 7) {
					player.changeRoom(&rooms[room->pos - 1]);
				}

				actions.clear();
				return;
			}
			else if (input == "b") {
				//right row - move up

				if (rooms.size() >= 4 && room->pos == 1) {
					player.changeRoom(&rooms[room->pos + 3]);
				}
				else if (rooms.size() >= 7 && room->pos == 4) {
					player.changeRoom(&rooms[room->pos + 3]);
				}
				else {
					std::cout << "That door goes no where, try another" << std::endl;
					player.changeRoom(&rooms[room->pos]);
				}

				actions.clear();
				return;
			}
			else if (input == "c") {
				//left row - move down

				if (rooms.size() >= 4 && room->pos == 4) {
					player.changeRoom(&rooms[room->pos - 3]);
				}
				else if (rooms.size() >= 7 && room->pos == 7) {
					player.changeRoom(&rooms[room->pos - 3]);
				}

				actions.clear();
				return;
			}
			else
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