/*#ifndef __ROOM_H__
#define __ROOM_H__	// @Carles Homs

#include "Module.h"
#include "Globals.h"
#include "Dungeon.h"

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")

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
	FINISH
};

enum class object_list {	//Enumeration of all things that can be filling a tile
	NONE,

	TABLE,
	CRYOPOD
};

struct Room_Position {
	int x;
	int y;
};

class Room {
public:
	Room();
	~Room();

public:
	void generateRoom(dungeon_levels dungeonLevel);
	void addEnemies(dungeon_levels dungeonLevel);

	SDL_Rect roomDrawing[3][3];	// 3x3 tilemap used to draw the room (426x270px, 142x90px/tile)
	SDL_Rect tileMap[6][9];	// 6x9 tilemap used to position things on within the room (332x180px, 55x20/tile)

							//Pointers to surrounding rooms for the player to navigate
	Room *rightRoom = nullptr;
	Room *leftRoom = nullptr;
	Room *topRoom = nullptr;
	Room *bottomRoom = nullptr;

	Room *next = nullptr;	// Pointer to the room created after this one, used for level management

							//Things within the room
	ushort numObjects;
	ushort numEnemies;
	ushort numDoors;

	room_types roomType;
	Room_Position roomLocation;

	//Music 
	//Mix_Music * MusicMainMenu = nullptr;
};

#endif	// __ROOM_H__*/