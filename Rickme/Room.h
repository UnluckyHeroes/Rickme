#ifndef __ROOM_H__
#define __ROOM_H__	// @Carles Homs

#include "Module.h"
#include "Globals.h"
#include "Dungeon.h"
#include "p2Point.h"

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")

enum class dungeon_levels;
class Dungeon;

enum class door_layout {
	TOP_LEFT,
	TOP,
	TOP_RIGHT,
	MIDDLE_LEFT,
	MIDDLE,
	MIDDLE_RIGHT,
	BOTTOM_LEFT,
	BOTTOM,
	BOTTOM_RIGHT,

	DOOR_TOP,
	DOOR_LEFT,
	DOOR_RIGHT,
	DOOR_BOTTOM,
};

enum class room_types {
	NORMAL,
	START,
	BOSS,
	FINISH
};

enum class object_list {	//Enumeration of all things that can be filling a tile
	NONE,
	
	TABLE,
	CRYOPOD
};

class Room {
public:
	Room();
	~Room();

public:
	void generateRoom(dungeon_levels paramDungeonLevel, room_types paramRoomType);
	void addObjects(dungeon_levels paramDungeonLevel, room_types paramRoomType);
	void addEnemies(dungeon_levels dungeonLevel);

	// Flags for room doors
	bool topDoor;
	bool rightDoor;
	bool bottomDoor;
	bool leftDoor;
	
	//Things within the room
	ushort numObjects;
	ushort numEnemies;
	ushort numDoors;

	ushort maxObjects;
	ushort maxDoors;

	room_types roomType;
	iPoint position;

	//Music 
	//Mix_Music * MusicMainMenu = nullptr;
};

#endif	// __ROOM_H__