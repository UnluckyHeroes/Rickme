#ifndef __MODULE_MAP_H__
#define __MODULE_MAP_H__	// @CarlesHoms

#include "Module.h"
#include "Globals.h"
#include "Dungeon.h"
#include "Room.h"

struct SDL_Texture;

struct Offset {
	ushort x;
	ushort y;
};

class Module_Map : public Module
{
public:
	Module_Map();
	~Module_Map();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	void allocateRoomDrawing();;
	void allocateRoomTiling();

	Room_Position playerRoom;

	//Textures
	SDL_Texture* roomText = nullptr;
	SDL_Texture* objectsText = nullptr;

	//Screen offsets
	Offset offsetBorders = { 27, 0 };	// Black borders on the screen
	Offset offsetRoomInterior = { 27 + 48, 0 + 45 };	// Black borders + room walls

	//Doors to allocate colliders
	SDL_Rect topDoor;
	SDL_Rect rightDoor;
	SDL_Rect bottomDoor;
	SDL_Rect leftDoor;

	SDL_Rect roomDrawing[3][3];	// 3x3 tilemap used to draw the room (426x270px, 142x90px/tile)
	SDL_Rect tileMap[6][9];	// 6x9 tilemap used to position things on within the room (332x180px, 55x20/tile)

};

#endif	// __MODULE_MAP_H__