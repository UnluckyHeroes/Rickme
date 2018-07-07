#include <ctime>
#include <cstdlib>
#include "Application.h"
#include "Globals.h"
#include "Dungeon.h"

Dungeon::Dungeon(dungeon_levels dungeonLevel) : playerRoom(nullptr), numRooms(0) {
	assert(dungeonLevel >= dungeon_levels::LEVEL_1 && dungeonLevel <= dungeon_levels::LEVEL_5 && "Dungeon level must be between 1 and 5");

	srand(time(NULL));

	for (int i = 0; i < maxHorizontal; i++) {		// Initialize all map pointers to nullptr
		for (int j = 0; j < maxVertical; j++) {
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
	
	for (int i = 0; i < maxHorizontal; i++) {	// Delete all rooms in the dungeon
		for (int j = 0; j < maxVertical; j++) {
			if (dungeonMap[i][j] != nullptr) {
				delete dungeonMap[i][j];
				dungeonMap[i][j] = nullptr;
			}
		}
	}
}

void Dungeon::linkRooms(ushort positionX, ushort positionY) {	// Function that has a 25% chance of adding doors to surrounding rooms
	if (positionY + 1 < maxVertical && dungeonMap[positionX][positionY + 1] != nullptr && rand() % 4 == 0)
		dungeonMap[positionX][positionY + 1]->topDoor = true;

	if (positionX + 1 < maxHorizontal && dungeonMap[positionX + 1][positionY] != nullptr && rand() % 4 == 0)
		dungeonMap[positionX + 1][positionY]->rightDoor = true;

	if (positionY - 1 > 0 && dungeonMap[positionX][positionY - 1] != nullptr && rand() % 4 == 0)
		dungeonMap[positionX][positionY - 1]->bottomDoor = true;

	if (positionX - 1 > 0 && dungeonMap[positionX - 1][positionY] != nullptr && rand() % 4 == 0)
		dungeonMap[positionX - 1][positionY]->leftDoor = true;
}

bool Dungeon::putDoor(ushort paramNumRooms) {	// Function that returns if a room should be created

	bool ret = true;

	if (paramNumRooms > 16)	// Limit at 16% door chance (16 being the number of rooms is a coincidence, chance rate is decided by operation below)
		paramNumRooms = 16;

	if (rand() % 100 <= 80 - paramNumRooms * 4);	// Starts at 80% door probability, decays for each room created until 16% minimum chance
	else
		ret = false;

	return ret;
}

void Dungeon::generateDungeon(ushort positionX, ushort positionY, dungeon_levels paramDungeonLevel) {

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
		&& dungeonMap[positionX][positionY]->topDoor == false					// Check that a room has not already been created
		&& positionY + 1 < maxVertical											// Check if rooms would be off limits
		&& dungeonMap[positionX][positionY + 1] == nullptr						// Check that a room is not already occupying that space
		&& putDoor(numRooms) == true) {											// Function that checks by probability if a room is created

		dungeonMap[positionX][positionY]->topDoor = true;						// Mark new exit for current room

		dungeonMap[positionX][positionY + 1] = new Room;						// Create new room on required position in the map
		dungeonMap[positionX][positionY + 1]->bottomDoor = true;				// Mark entrance door to currnet room in new room
		dungeonMap[positionX][positionY + 1]->roomType = room_types::NORMAL;	// Assign room type

		linkRooms(positionX, positionY + 1);									// Probability of linking room to surrounding rooms (25% chance each)

		numRooms++;																// Increase number of rooms by 1
		generateDungeon(positionX, positionY + 1, paramDungeonLevel);								// Use new room to create more
	}
	if (numRooms < maxRooms
		&& dungeonMap[positionX][positionY]->rightDoor == false
		&& positionX + 1 < maxHorizontal
		&& dungeonMap[positionX + 1][positionY] == nullptr
		&& putDoor(numRooms) == true) {

		dungeonMap[positionX][positionY]->rightDoor = true;

		dungeonMap[positionX + 1][positionY] = new Room;
		dungeonMap[positionX + 1][positionY]->leftDoor = true;
		dungeonMap[positionX + 1][positionY]->roomType = room_types::NORMAL;

		linkRooms(positionX + 1, positionY);

		numRooms++;
		generateDungeon(positionX + 1, positionY, paramDungeonLevel);			// Use new room to create more
	}
	if (numRooms < maxRooms
		&& dungeonMap[positionX][positionY]->bottomDoor == false
		&& positionY - 1 >= 0
		&& dungeonMap[positionX][positionY - 1] == nullptr
		&& putDoor(numRooms) == true) {

		dungeonMap[positionX][positionY]->bottomDoor = true;

		dungeonMap[positionX][positionY - 1] = new Room;
		dungeonMap[positionX][positionY - 1]->topDoor = true;
		dungeonMap[positionX][positionY - 1]->roomType = room_types::NORMAL;

		linkRooms(positionX, positionY - 1);

		numRooms++;
		generateDungeon(positionX, positionY - 1, paramDungeonLevel);			// Use new room to create more
	}
	if (numRooms < maxRooms
		&& dungeonMap[positionX][positionY]->leftDoor == false
		&& positionX - 1 >= 0
		&& dungeonMap[positionX - 1][positionY] == nullptr
		&& putDoor(numRooms) == true) {

		dungeonMap[positionX][positionY]->leftDoor = true;

		dungeonMap[positionX - 1][positionY] = new Room;
		dungeonMap[positionX - 1][positionY]->rightDoor = true;
		dungeonMap[positionX - 1][positionY]->roomType = room_types::NORMAL;

		linkRooms(positionX - 1, positionY);

		numRooms++;
		generateDungeon(positionX - 1, positionY, paramDungeonLevel);			// Use new room to create more
	}

	dungeonMap[positionX][positionY]->generateRoom(paramDungeonLevel, dungeonMap[positionX][positionY]->roomType);
}