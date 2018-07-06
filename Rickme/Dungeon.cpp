#include <ctime>
#include <cstdlib>
#include "Application.h"
#include "Globals.h"
#include "Dungeon.h"

Dungeon::Dungeon(dungeon_levels dungeonLevel) : playerRoom(nullptr), numRooms(0) {
	assert(dungeonLevel >= dungeon_levels::LEVEL_1 && dungeonLevel <= dungeon_levels::LEVEL_5 && "Dungeon level must be between 1 and 5");

	srand(time(NULL));

	for (int i = 0; i < 10; i++) {		// Initialize all map pointers to nullptr
		for (int j = 0; j < 10; j++) {
			dungeonMap[i][j] = nullptr;
		}
	}

	switch (dungeonLevel) {
	case dungeon_levels::LEVEL_1:								// Define dungeon values based on its level
		maxRooms = 8;
		minEnemies = 10;
		maxEnemies = 25;
		timer = timeToMiliseconds(3, 0);
		break;
	case dungeon_levels::LEVEL_2:
		maxRooms = 10;
		minEnemies = 15;
		maxEnemies = 30;
		timer = timeToMiliseconds(3, 20);
		break;
	case dungeon_levels::LEVEL_3:
		maxRooms = 12;
		minEnemies = 20;
		maxEnemies = 35;
		timer = timeToMiliseconds(3, 40);
		break;
	case dungeon_levels::LEVEL_4:
		maxRooms = 14;
		minEnemies = 25;
		maxEnemies = 45;
		timer = timeToMiliseconds(4, 0);
		break;
	case dungeon_levels::LEVEL_5:
		maxRooms = 15;
		minEnemies = 35;
		maxEnemies = 55;
		timer = timeToMiliseconds(4, 30);
		break;
	}

	numRooms = 0;
	numEnemies = 0;
}

Dungeon::~Dungeon() {	// Delete dungeon
	clear();
}

void Dungeon::pushRoom() {	// Create room and allocate it's position on the map
	if (numRooms == 0) {
		first = last = new Room;
		first->next = nullptr;
	}
	else {
		Room *tempRoom = new Room;
		last->next = tempRoom;
		last = tempRoom;
	}
	numRooms++;
}

void Dungeon::popRoom() {	// Delete first room on the list
	assert(numRooms > 0 && "Cannot delete a room from an empty list.");

	if (numRooms == 1) {
		delete first;
		first = last = nullptr;
	}
	else {
		Room *newfirst = first->next;
		delete first;
		first = newfirst;
	}
	numRooms--;
}

void Dungeon::clear() {	// Delete all rooms starting by the first
	while (numRooms > 0)
		popRoom();
}

void Dungeon::generateDungeon(ushort positionX, ushort positionY) {

	if (numRooms == 0) {	// Create starting room
		dungeonMap[positionX][positionY] = new Room;
		dungeonMap[positionX][positionY]->roomType = room_types::START;
		numRooms++;
	}

	if (numRooms == maxRooms) {	// Create boss room
		dungeonMap[positionX][positionY] = new Room;
		dungeonMap[positionX][positionY]->roomType = room_types::BOSS;
		numRooms++;
	}

	if (numRooms < maxRooms	// Potential new room for each side of the current room, doesn't run (else) when it's the boss room
		&& dungeonMap[positionX][positionY]->topDoor == false
		&& positionY + 1 < maxVertical
		&& rand() % 4 == 0) {	// 25% chance of new room
		dungeonMap[positionX][positionY]->topDoor = true;						// Mark new exit for current room

		dungeonMap[positionX][positionY + 1] = new Room;						// Create new room on required position in the map
		dungeonMap[positionX][positionY + 1]->bottomDoor = true;				// Mark entrance door to currnet room in new room
		dungeonMap[positionX][positionY + 1]->roomType = room_types::NORMAL;	// Assign room type

		numRooms++;																// Increase number of rooms by 1
		generateDungeon(positionX, positionY + 1);								// Use new room to create more
	}
	if (numRooms < maxRooms
		&& dungeonMap[positionX][positionY]->rightDoor == false
		&& positionX + 1 < maxHorizontal
		&& rand() % 4 == 0) {	// 25% chance of new room
		dungeonMap[positionX][positionY]->rightDoor = true;

		dungeonMap[positionX + 1][positionY] = new Room;
		dungeonMap[positionX + 1][positionY]->leftDoor = true;
		dungeonMap[positionX + 1][positionY]->roomType = room_types::NORMAL;

		numRooms++;
		generateDungeon(positionX + 1, positionY);			// Use new room to create more
	}
	if (numRooms < maxRooms
		&& dungeonMap[positionX][positionY]->bottomDoor == false
		&& positionY - 1 >= 0
		&& rand() % 4 == 0) {	// 25% chance of new room
		dungeonMap[positionX][positionY]->bottomDoor = true;

		dungeonMap[positionX][positionY - 1] = new Room;
		dungeonMap[positionX][positionY - 1]->topDoor = true;
		dungeonMap[positionX][positionY - 1]->roomType = room_types::NORMAL;

		numRooms++;
		generateDungeon(positionX, positionY - 1);			// Use new room to create more
	}
	if (numRooms < maxRooms
		&& dungeonMap[positionX][positionY]->leftDoor == false
		&& positionX - 1 >= 0
		&& rand() % 4 == 0) {	// 25% chance of new room
		dungeonMap[positionX][positionY]->leftDoor = true;

		dungeonMap[positionX - 1][positionY] = new Room;
		dungeonMap[positionX - 1][positionY]->rightDoor = true;
		dungeonMap[positionX - 1][positionY]->roomType = room_types::NORMAL;

		numRooms++;
		generateDungeon(positionX - 1, positionY);			// Use new room to create more
	}

	dungeonMap[positionX][positionY]->generateRoom(dungeonMap[positionX][positionY]->roomType);
}