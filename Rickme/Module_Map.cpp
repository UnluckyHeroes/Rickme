#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "Module_Map.h"

Module_Map::Module_Map()	//@CarlesHoms
{
	allocateRoomDrawing();	// Position room drawing squares
	allocateRoomTiling();	// Position room tiling squares

	//Door Rects (3x3 tilemap used to draw the room (426x270px, 142x90px/tile))
	topDoor.x = 142 * 1 + offsetBorders.x;
	topDoor.y = 90 * 0 + offsetBorders.y;	// THIS IS FOR TEXTURE ALLOCATION, NO OFFSET SHOULD BE APPLIED
	topDoor.w = 142;
	topDoor.h = 90;

	rightDoor.x = 142 * 2 + offsetBorders.x;
	rightDoor.y = 90 * 1 + offsetBorders.y;
	rightDoor.w = 142;
	rightDoor.h = 90;

	bottomDoor.x = 142 * 1 + offsetBorders.x;
	bottomDoor.y = 90 * 2 + offsetBorders.y;
	bottomDoor.w = 142;
	bottomDoor.h = 90;

	leftDoor.x = 142 * 0 + offsetBorders.x;
	leftDoor.y = 90 * 1 + offsetBorders.y;
	leftDoor.w = 142;
	leftDoor.h = 90;
}

Module_Map::~Module_Map() {}

// Load assets
bool Module_Map::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	roomText = App->textures->Load("");
	objectsText = App->textures->Load("");

	switch (playerLevel) {
	case dungeon_levels::LEVEL_1:
		createdDungeon = new Dungeon(dungeon_levels::LEVEL_1);
		break;
	case dungeon_levels::LEVEL_2:
		createdDungeon = new Dungeon(dungeon_levels::LEVEL_2);
		break;
	case dungeon_levels::LEVEL_3:
		createdDungeon = new Dungeon(dungeon_levels::LEVEL_3);
		break;
	case dungeon_levels::LEVEL_4:
		createdDungeon = new Dungeon(dungeon_levels::LEVEL_4);
		break;
	case dungeon_levels::LEVEL_5:
		createdDungeon = new Dungeon(dungeon_levels::LEVEL_5);
		break;
	}

	createdDungeon->generateDungeon(createdDungeon->startingPos.x, createdDungeon->startingPos.y, playerLevel);
	playerRoom = { createdDungeon->startingPos.x, createdDungeon->startingPos.y };

	//Music
	/*MusicMainMenu = App->mixer->LoadMusic("Assets/Audio/Music/02_Title.ogg");
	Mix_VolumeMusic(MUSICVol);
	Mix_FadeInMusic(MusicMainMenu, 0, 1000);*/

	return ret;
}

// Update: draw background
update_status Module_Map::Update()
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			App->render->Blit(roomText, roomDrawing[i][j].x, roomDrawing[i][j].y, &roomDrawing[i][j]);
		}
	}

	drawDoors();	// Draw all doors on current room and add their colliders

	//if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	//{
	//	App->fade->FadeToBlack(this, App->stage1, 0.5);
	//}

	//if (App->input->keyboard[SDL_SCANCODE_1] == 1 && App->input->debugMode == true) //press for 1 player mode @AndresSala
	//{
	//	App->input->secondPlayerState = false;
	//}


	//if (App->input->keyboard[SDL_SCANCODE_2] == 1 && App->input->debugMode == true) // press for 2 players mode  @AndresSala
	//{
	//	App->input->secondPlayerState = true;
	//}

	return UPDATE_CONTINUE;
}

bool Module_Map::CleanUp()
{
	LOG("Unloading Main Menu");
	App->textures->Unload(roomText);
	App->textures->Unload(objectsText);

	/*Mix_FadeOutMusic(TIMEFADE);
	App->mixer->UnloadMusic(MusicMainMenu);*/

	delete createdDungeon;	// Dungeon destructor deletes all rooms inside
	createdDungeon = nullptr;

	return true;
}

void Module_Map::allocateRoomDrawing() {	// Position room drawing tiles
	ushort posX = 142;	// 3x3 tilemap used to draw the room (426x270px, 142x90px/tile)
	ushort posY = 90;

	for (int i = 0; i < 3; i++) {	
		for (int j = 0; j < 3; j++) {
			roomDrawing[i][j].x = posX * j + offsetBorders.x;
			roomDrawing[i][j].y = posY * i + offsetBorders.y;
			roomDrawing[i][j].w = posX;
			roomDrawing[i][j].h = posY;
		}
	}
}

void Module_Map::allocateRoomTiling() {	// Position room interior tiles
	ushort posX = 55;	// 6x9 tilemap used to position things on within the room (332x180px, 55x20/tile)
	ushort posY = 20;

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 9; j++) {
			roomDrawing[i][j].x = posX * j + offsetRoomInterior.x;
			roomDrawing[i][j].y = posY * i + offsetRoomInterior.y;
			roomDrawing[i][j].w = posX;
			roomDrawing[i][j].h = posY;
		}
	}
}

void Module_Map::drawDoors() {
	if (createdDungeon->dungeonMap[playerRoom.x][playerRoom.y]->topDoor == true) {	// Draw top door
		App->render->Blit(roomText, topDoor.x, topDoor.y, &roomDrawing[0][1]);
		// addCollider;
	}
	if (createdDungeon->dungeonMap[playerRoom.x][playerRoom.y]->rightDoor == true) {	// Draw right door
		App->render->Blit(roomText, rightDoor.x, rightDoor.y, &roomDrawing[1][2]);
		// addCollider;
	}
	if (createdDungeon->dungeonMap[playerRoom.x][playerRoom.y]->bottomDoor == true) {	// Draw bottom door
		App->render->Blit(roomText, bottomDoor.x, bottomDoor.y, &roomDrawing[2][1]);
		// addCollider;
	}
	if (createdDungeon->dungeonMap[playerRoom.x][playerRoom.y]->leftDoor == true) {	// Draw left door
		App->render->Blit(roomText, leftDoor.x, leftDoor.y, &roomDrawing[1][0]);
		// addCollider;
	}
}