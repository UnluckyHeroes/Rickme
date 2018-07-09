/*#include <ctime>
#include <cstdlib>
#include "Application.h"
#include "Globals.h"
#include "Dungeon.h"

Dungeon::Dungeon(dungeon_levels dungeonLevel) : first(nullptr), playerRoom(nullptr), last(nullptr), numRooms(0) {
	assert(dungeonLevel >= dungeon_levels::LEVEL_1 && dungeonLevel <= dungeon_levels::LEVEL_5 && "Dungeon level must be between 1 and 5");

	srand(time(NULL));
	
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
	} else {
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
	} else {
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

void Dungeon::generateDungeon(Room *currentRoom) {	// tempPointer

	if (numRooms == 0) {	// Special condition for first room here
		pushRoom();
		currentRoom = last;		
		currentRoom->roomLocation.x = 0;
		currentRoom->roomLocation.y = 0;
		currentRoom->roomType = room_types::START;
		numRooms++;
		generateDungeon(currentRoom);
	}

	else if (numRooms == maxRooms) {
		
	}

	else {
		if (numRooms < maxRooms && currentRoom->numDoors < 4 && currentRoom->topRoom == nullptr) {
			if (rand() % 4 == 0) {	// 25% chance of new room
				pushRoom();																	// Create room and add to the list
				currentRoom->topRoom = last;												// Pointer topRoom points to last room created
				currentRoom->topRoom->bottomRoom = currentRoom;								// Link newly created room to current room
				currentRoom->topRoom->roomLocation.x = currentRoom->roomLocation.x;			// Assign x position based on currentRooms
				currentRoom->topRoom->roomLocation.y = currentRoom->roomLocation.y + 1;		// Assign y position based on currentRooms
				currentRoom->topRoom->numDoors += 1;										// Increase door number on new room
				currentRoom->numDoors += 1;													// Increase door number on current room
				numRooms++;
				generateDungeon(last);			// Use new room to create more
			}
		}
		if (numRooms < maxRooms && currentRoom->numDoors < 4 && currentRoom->rightRoom == nullptr) {
			if (rand() % 4 == 0) {	// 25% chance of new room
				pushRoom();																	// Create room and add to the list
				currentRoom->rightRoom = last;												// Pointer topRoom points to last room created
				currentRoom->rightRoom->leftRoom = currentRoom;								// Link newly created room to current room
				currentRoom->rightRoom->roomLocation.x = currentRoom->roomLocation.x + 1;	// Assign x position based on currentRooms
				currentRoom->rightRoom->roomLocation.y = currentRoom->roomLocation.y;		// Assign y position based on currentRooms
				currentRoom->rightRoom->numDoors += 1;										// Increase door number on new room
				currentRoom->numDoors += 1;													// Increase door number on current room
				numRooms++;
				generateDungeon(last);			// Use new room to create more
			}
		}
		if (numRooms < maxRooms && currentRoom->numDoors < 4 && currentRoom->bottomRoom == nullptr) {
			if (rand() % 4 == 0) {	// 25% chance of new room
				pushRoom();																	// Create room and add to the list
				currentRoom->bottomRoom = last;												// Pointer topRoom points to last room created
				currentRoom->bottomRoom->topRoom = currentRoom;								// Link newly created room to current room
				currentRoom->bottomRoom->roomLocation.x = currentRoom->roomLocation.x;		// Assign x position based on currentRooms
				currentRoom->bottomRoom->roomLocation.y = currentRoom->roomLocation.y - 1;	// Assign y position based on currentRooms
				currentRoom->bottomRoom->numDoors += 1;										// Increase door number on new room
				currentRoom->numDoors += 1;													// Increase door number on current room
				numRooms++;
				generateDungeon(last);			// Use new room to create more
			}
		}
		if (numRooms < maxRooms && currentRoom->numDoors < 4 && currentRoom->leftRoom == nullptr) {
			if (rand() % 4 == 0) {	// 25% chance of new room
				pushRoom();																	// Create room and add to the list
				currentRoom->leftRoom = last;												// Pointer topRoom points to last room created
				currentRoom->leftRoom->rightRoom = currentRoom;								// Link newly created room to current room
				currentRoom->leftRoom->roomLocation.x = currentRoom->roomLocation.x - 1;	// Assign x position based on currentRooms
				currentRoom->leftRoom->roomLocation.y = currentRoom->roomLocation.y;		// Assign y position based on currentRooms
				currentRoom->leftRoom->numDoors += 1;										// Increase door number on new room
				currentRoom->numDoors += 1;													// Increase door number on current room
				numRooms++;
				generateDungeon(last);			// Use new room to create more
			}
		}
		currentRoom->generateRoom(dungeonLevel);	// Generate current room's content
	}
}*/