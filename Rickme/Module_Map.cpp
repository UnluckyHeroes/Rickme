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
	topDoor.y = 90 * 0 + offsetBorders.y;
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
	backgroundText = App->textures->Load("Assets/Sprites/User_Interface/Intro/logo-background.png");
	titleText = App->textures->Load("Assets/Sprites/User_Interface/Intro/logo.png");
	viscoGamesText = App->textures->Load("Assets/Sprites/User_Interface/Intro/visco_games.png");
	//orangeLettersText = App->textures->Load("Assets/Sprites/Backgrounds/1_FullMap.png");
	//whiteLettersText = App->textures->Load("Assets/Sprites/Backgrounds/1_FullMap.png");

	App->player1->bluePower = LEVEL_1;		// Flag/counter for blue power level
	App->player1->orangePower = LEVEL_0;	// Flag/counter for orange power level
	App->player1->yellowPower = LEVEL_0;	// Flag/counter for yellow power level
	App->player1->greenPower = LEVEL_0;		// Flag/counter for green power level

	App->player2->bluePower = LEVEL_1;		// Flag/counter for blue power level
	App->player2->orangePower = LEVEL_0;	// Flag/counter for orange power level
	App->player2->yellowPower = LEVEL_0;	// Flag/counter for yellow power level
	App->player2->greenPower = LEVEL_0;		// Flag/counter for green power level

	App->player1->Disable();
	App->shieldsP1->Disable();

	App->player2->Disable();
	App->shieldsP2->Disable();

	App->enemies->Disable();
	App->collision->Disable();

	//Music
	MusicMainMenu = App->mixer->LoadMusic("Assets/Audio/Music/02_Title.ogg");
	Mix_VolumeMusic(MUSICVol);
	Mix_FadeInMusic(MusicMainMenu, 0, 1000);

	return ret;
}

// Update: draw background
update_status Module_Map::Update()
{
	App->render->Blit(backgroundText, 0, 0, &backgroundRect); // background
	App->render->Blit(titleText, 52, 60, &titleBoxRect); // logo back mark
	App->render->Blit(titleText, 36, 27, &titleRect); // logo
	App->render->Blit(viscoGamesText, 75, 160, &viscoGamesRect); // Visco Games

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
	{
		App->fade->FadeToBlack(this, App->stage1, 0.5);
	}

	if (App->input->keyboard[SDL_SCANCODE_1] == 1 && App->input->debugMode == true) //press for 1 player mode @AndresSala
	{
		App->input->secondPlayerState = false;
	}


	if (App->input->keyboard[SDL_SCANCODE_2] == 1 && App->input->debugMode == true) // press for 2 players mode  @AndresSala
	{
		App->input->secondPlayerState = true;
	}

	return UPDATE_CONTINUE;
}

bool Module_Map::CleanUp()
{
	App->player1->Disable();
	App->shieldsP1->Disable();
	App->player2->Disable();
	App->shieldsP2->Disable();

	LOG("Unloading Main Menu");
	App->textures->Unload(backgroundText);
	App->textures->Unload(titleText);
	App->textures->Unload(viscoGamesText);
	//App->textures->Unload(orangeLettersText);
	//App->textures->Unload(whiteLettersText);
	Mix_FadeOutMusic(TIMEFADE);
	App->mixer->UnloadMusic(MusicMainMenu);

	return true;
}

void Module_Map::allocateRoomDrawing() {	// Position room drawing tiles
	ushort posX = 142;	// 3x3 tilemap used to draw the room (426x270px, 142x90px/tile)
	ushort posY = 90;

	for (int i = 0; i < 3; i++) {	
		for (int j = 0; j < 3; j++) {
			roomDrawing[i][j].x = posX * j + offsetBorders;
			roomDrawing[i][j].y = posY * i + offsetBorders;
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
			roomDrawing[i][j].x = posX * j + offsetRoomInterior;
			roomDrawing[i][j].y = posY * i + offsetRoomInterior;
			roomDrawing[i][j].w = posX;
			roomDrawing[i][j].h = posY;
		}
	}
}