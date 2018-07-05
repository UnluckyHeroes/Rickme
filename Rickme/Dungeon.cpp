#include <ctime>
#include <cstdlib>
#include "Application.h"
#include "Globals.h"
#include "Dungeon.h"

Dungeon::Dungeon(dungeon_levels dungeonLevel) : first(nullptr), playerRoom(nullptr), last(nullptr), numRooms(0) {
	assert(dungeonLevel >= dungeon_levels::LEVEL_1 && dungeonLevel <= dungeon_levels::LEVEL_5 && "Dungeon level must be between 1 and 5");

	srand(time(NULL));

	switch (dungeonLevel) {
	case dungeon_levels::LEVEL_1:
		maxRooms = 8;
		maxEnemies = rand() % (25 - 10 + 1) + 10;
		timer = timeToMiliseconds(3, 0);
		break;
	case dungeon_levels::LEVEL_2:
		maxRooms = 10;
		maxEnemies = rand() % (30 - 15 + 1) + 15;
		timer = timeToMiliseconds(3, 20);
		break;
	case dungeon_levels::LEVEL_3:
		maxRooms = 12;
		maxEnemies = rand() % (35 - 20 + 1) + 20;
		timer = timeToMiliseconds(3, 40);
		break;
	case dungeon_levels::LEVEL_4:
		maxRooms = 14;
		maxEnemies = rand() % (45 - 25 + 1) + 25;
		timer = timeToMiliseconds(4, 0);
		break;
	case dungeon_levels::LEVEL_5:
		maxRooms = 15;
		maxEnemies = rand() % (55 - 35 + 1) + 35;
		timer = timeToMiliseconds(4, 30);
		break;
	}
}

Dungeon::~Dungeon() {
	clear();
}

void Dungeon::pushRoom() {
	if (numRooms == 0) {
		first = last = new Room;
		first->roomLocation.x = currentPosition.x;
		first->roomLocation.x = currentPosition.y;
		first->next = nullptr;
	} else {
		Room *tempRoom = new Room;
		last->next = tempRoom;
		last = tempRoom;
	}
	numRooms++;
}

void Dungeon::popRoom() {
	assert(numRooms > 0 && "Cannot pop_front from an empty list.");

	if (numRooms == 1) {
		delete first;
		first = last = nullptr;
	} else {
		Room *newfirst = first->next;
		delete first;
		first = newfirst;
	}
	numRooms--;
}

void Dungeon::clear() {
	while (numRooms > 0)
		popRoom();
}

void Dungeon::generateDungeon(ushort roomsLeft, ushort enemiesLeft, Room *currentRoom, dungeon_levels dungeonLevel) {	// maxRooms, maxEnemies, firstRoom

	if (roomsLeft == maxRooms) {
		pushRoom();
	}

	else if (roomsLeft > 0 && currentRoom->numDoors < 4) {
		if (currentRoom->topRoom == nullptr) {
			if (rand() % 4 == 0) {								// 25% chance of new room
				pushRoom();										// Create room and add to the list
				currentRoom->numDoors += 1;						// Add the new room's door to counter
				currentRoom->topRoom = last;					// Created room is now last room on list
				currentRoom->generateRoom();
				generateDungeon(--roomsLeft, enemiesLeft, last);	// Use new room to create more
			}
		}
		if (currentRoom->rightRoom == nullptr) {
			if (rand() % 4 == 0) {
				pushRoom();
				currentRoom->numDoors += 1;
				currentRoom->rightRoom = last;
				
				generateDungeon(--roomsLeft, enemiesLeft, last);
			}
		}
		if (currentRoom->bottomRoom == nullptr) {
			if (rand() % 4 == 0) {
				pushRoom();
				currentRoom->numDoors += 1;
				currentRoom->bottomRoom = last;
				
				generateDungeon(--roomsLeft, enemiesLeft, last);
			}
		}
		if (currentRoom->leftRoom == nullptr) {
			if (rand() % 4 == 0) {
				pushRoom();
				currentRoom->numDoors += 1;
				currentRoom->leftRoom = last;
				
				generateDungeon(--roomsLeft, enemiesLeft, last);
			}
		}
	}
}