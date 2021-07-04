// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include"Dungeon.h"
#include"GameCharacter.h"
#include"Item.h"
#include"Player.h"
#include"Room.h"


int main()
{
    std::cout << "Welcome to our dungeon crawler! What is you name?" << std::endl;
    std::string playerName;
    std::cin >> playerName;
    //player starting stats
    int startingHealth = 100, startingAttack = 20, startingDefence = 10;

    Player player = Player(playerName, startingHealth, startingAttack, startingDefence);

    player.printStats();
    
    //First room set up
    Room firstRoom = Room(0, false, std::vector<Item>(), std::vector<GameCharacter>()); //an empty room
    

    //Second room set up - it has a sword in it
    Item sword = Item("Sword", 0, 20, 0);
    std::vector<Item> secondRoomItems;
    secondRoomItems.push_back(sword);
   
    Room secondRoom = Room(1, false, secondRoomItems, std::vector<GameCharacter>());
    

    //Set up the third room - this has a goblin in it
    GameCharacter goblinEnemy = GameCharacter("Goblin", 50, 15, 5);
    std::vector<GameCharacter> thirdRoomEnemys;
    thirdRoomEnemys.push_back(goblinEnemy);
      
    Room thirdRoom = Room(2, false, std::vector<Item>(), thirdRoomEnemys);

    //set up the fourth room
    GameCharacter bossEnemy = GameCharacter("Big Monster", 100, 20, 10);
    std::vector<GameCharacter> fourthRoomEnemys;
    fourthRoomEnemys.push_back(bossEnemy);

    Room fourthRoom = Room(3, true, std::vector<Item>(), fourthRoomEnemys);

    
    //creating the dungeon
    Dungeon mainDungeon = Dungeon(player);
    mainDungeon.rooms[0] = firstRoom;
    mainDungeon.rooms[1] = secondRoom;
    mainDungeon.rooms[2] = thirdRoom;
    mainDungeon.rooms[3] = fourthRoom;


    while (true)
    {
        int result = mainDungeon.runDungeon();

        if (result == 0) {
            std::cout << "GOODBYE THANKS FOR PLAYING!";
            break;
        }
        
    }
}

