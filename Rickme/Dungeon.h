#ifndef __DUNGEON_H__
#define __DUNGEON_H__	// @Carles Homs

#include "Module.h"
#include "Globals.h"
#include "Room.h"

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")

enum class room_types {
	NORMAL,
	START,
	FINISH
};

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
	// List management functions
	void pushRoom();
	void popRoom();
	void clear();

	// Room management
	Room *first = nullptr;
	Room *last = nullptr;
	Room *playerRoom = nullptr;

	Room_Position currentPosition = { 0, 0 };

public:
	void generateDungeon(ushort numRooms, ushort numEnemies, Room *currentRoom, dungeon_levels dungeonLevel);

	//Rooms
	ushort numRooms;
	ushort maxRooms;

	//Enemies
	ushort numEnemies;
	ushort maxEnemies;

	uint timer;	// Challenge mode timer

	//Music 
	//Mix_Music * MusicMainMenu = nullptr;
};

#endif	// __LEVEL_H__