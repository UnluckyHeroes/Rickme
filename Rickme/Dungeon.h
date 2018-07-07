#ifndef __DUNGEON_H__
#define __DUNGEON_H__	// @Carles Homs

#include "Module.h"
#include "Globals.h"
#include "Room.h"

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")

enum class dungeon_levels {
	LEVEL_1,
	LEVEL_2,
	LEVEL_3,
	LEVEL_4,
	LEVEL_5
};

class Dungeon {
public:
	Dungeon(dungeon_levels dungeonLevel) {};
	~Dungeon();

public:
	void generateDungeon(ushort positionX, ushort PositionY, dungeon_levels paramDungeonLevel);
	void allocateDoors(ushort positionX, ushort positionY);
	bool putDoor(ushort paramNumRooms);

	// Map
	ushort maxHorizontal = 10;
	ushort maxVertical = 10;
	Room *dungeonMap[10][10];
	Room *playerRoom;
	Room_Position currentPos = { 4, 4 };

	//Rooms
	ushort numRooms;
	ushort maxRooms;

	//Enemies
	ushort numEnemies;
	ushort minEnemies;
	ushort maxEnemies;

	uint timer;	// Challenge mode timer

	//Music 
	//Mix_Music * MusicMainMenu = nullptr;
};

#endif	// __LEVEL_H__