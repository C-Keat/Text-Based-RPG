// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include"Dungeon.h"
#include"GameCharacter.h"
#include"Item.h"
#include"Player.h"
#include"Room.h"
#include"RoomTree.h"
#include<time.h>

int main()
{
    (srand(time(NULL)));
    std::cout << "Welcome to our dungeon crawler! What is you name?" << std::endl;
    std::string playerName;
    std::cin >> playerName;
    //player starting stats
    int startingHealth = 100, startingAttack = 20, startingDefence = 10;

    //create the player and print the players stats for the IRL player
    Player player = Player(playerName, startingHealth, startingAttack, startingDefence);
    player.printStats();
   
    //definding games items
    Item sword = Item("Sword", 0, 20, 0);
    Item armour = Item("Armour", 0, 0, 15);
    Item shield = Item("Shield", 0, 0, 10);
    
    //definding the enemys
    GameCharacter goblin = GameCharacter("Goblin", 50, 15, 5);
    GameCharacter ogar = GameCharacter("Ogar", 100, 20, 10);
    GameCharacter boss = GameCharacter("Demon", 200, 30, 15);

    //create the weapon and armour rooms
    std::vector<Item> weaponRoom{ sword };
    std::vector<Item> armourRoom{ armour,shield };
    std::vector<Item> itemInsertRoom;

    //create the goblin and ogar Rooms
    std::vector<GameCharacter> goblinRoom;
    std::vector<GameCharacter> ogarRoom;
    std::vector<GameCharacter> bossRoom{ boss };
    std::vector<GameCharacter> enemyInsertRoom;

    Dungeon mainDungeon = Dungeon(player);

    //enemy number variables:
    int numberOfOgars = 0, numberOfGoblins = 0;

    int roomNumber = (rand() % 10) + 1;

    //check to make sure that the dungeon is not lower than 3 rooms large
    while (roomNumber < 3)
    {
        roomNumber = (rand() % 10) + 1;
    }

    int itemInsertNumber, enemyInsertNumber;

    cout << "Number of rooms generated: " << roomNumber << endl;

    for (int i = 0; i < roomNumber; i++)
    {

        itemInsertNumber = (rand() % 3) + 1;

        //creating the items that will be inserted into the room
        switch (itemInsertNumber)
        {
        case 1:
            //makes the insert room a weapon room
            itemInsertRoom = weaponRoom;
            break;
            
        case 2:
            //makes the insert room a armour room
            itemInsertRoom = armourRoom;
            break;

        case 3:
            //no items in the room
            itemInsertRoom = std::vector<Item>();
            break;
        }

        //creating the enemys that will be inserted into the room

        enemyInsertNumber = (rand() % 3) + 1;

        cout << "\n" << "Number of enemies: " << enemyInsertNumber << endl;

        switch (enemyInsertNumber)
        {
        case 1:
            //make the enemy insert room a gobline room
            numberOfGoblins = (rand() % 4) + 1;
            for (int i = 0; i < numberOfGoblins; i++)
            {
                goblinRoom.push_back(goblin);
            }
            enemyInsertRoom = goblinRoom;

            goblinRoom.clear();
            break;

        case 2:
            // set enemyInsertRoom to a Ogar room
            numberOfOgars = (rand() % 2) + 1;
            for (int i = 0; i < numberOfOgars; i++)
            {
                ogarRoom.push_back(ogar);
            }
            enemyInsertRoom = ogarRoom;

            ogarRoom.clear();
            break;

        case 3:
            //set enemy insert room to empty
            enemyInsertRoom = std::vector<GameCharacter>();
            break;
        }

        //random room is pushed back into the dungeons rooms
        mainDungeon.rooms.push_back(Room(i, false, itemInsertRoom, enemyInsertRoom));

    }
    
    mainDungeon.rooms.push_back(Room(roomNumber + 1, true, vector<Item>(), bossRoom));
    

    while (true)
    {
        int result = mainDungeon.runDungeon();

        if (result == 0) {
            std::cout << "GOODBYE THANKS FOR PLAYING!";
            break;
        } 
    }
}

//First room set up
    //Room firstRoom = Room(0, false, std::vector<Item>(), std::vector<GameCharacter>()); //an empty room
    //

    ////Second room set up - it has a sword in it
    //Item sword = Item("Sword", 0, 20, 0);
    //std::vector<Item> secondRoomItems;
    //secondRoomItems.push_back(sword);
    //Room secondRoom = Room(1, false, secondRoomItems, std::vector<GameCharacter>());
    //

    ////Set up the third room - this has a goblin in it
    //GameCharacter goblinEnemy = GameCharacter("Goblin", 50, 15, 5);
    //std::vector<GameCharacter> thirdRoomEnemys;
    //thirdRoomEnemys.push_back(goblinEnemy);
    //Room thirdRoom = Room(2, false, std::vector<Item>(), thirdRoomEnemys);

    ////set up the fourth room
    //GameCharacter bossEnemy = GameCharacter("Big Monster", 100, 20, 10);
    //std::vector<GameCharacter> fourthRoomEnemys;
    //fourthRoomEnemys.push_back(bossEnemy);
    //Room fourthRoom = Room(3, true, std::vector<Item>(), fourthRoomEnemys);

    //
    ////creating the dungeon
    //Dungeon mainDungeon = Dungeon(player);

    //mainDungeon.rooms.push_back(firstRoom);
    //mainDungeon.rooms.push_back(secondRoom);
    //mainDungeon.rooms.push_back(thirdRoom);
    //mainDungeon.rooms.push_back(fourthRoom);
    //

    //mainDungeon.rooms[0] = firstRoom;
    //mainDungeon.rooms[1] = secondRoom;
    //mainDungeon.rooms[2] = thirdRoom;
    //mainDungeon.rooms[3] = fourthRoom;