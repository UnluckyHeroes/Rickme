#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "Module_Map.h"

Module_Map::Module_Map()	//@CarlesHoms
{
	//Doors to allocate colliders
	SDL_Rect topDoor;
	SDL_Rect rightDoor;
	SDL_Rect bottomDoor;
	SDL_Rect leftDoor;

	SDL_Rect roomDrawing[3][3];	// 3x3 tilemap used to draw the room (426x270px, 142x90px/tile)
	SDL_Rect tileMap[6][9];	// 6x9 tilemap used to position things on within the room (332x180px, 55x20/tile)

	//Tiling Rects: Starting from top left, left to right
	roomDrawing[0][0].x = 40;
	roomDrawing[0][0].y = 116;
	roomDrawing[0][0].w = 167;
	roomDrawing[0][0].h = 15;

	roomDrawing[0][1].x = 40;
	roomDrawing[0][1].y = 116;
	roomDrawing[0][1].w = 167;
	roomDrawing[0][1].h = 15;

	roomDrawing[0][2].x = 40;
	roomDrawing[0][2].y = 116;
	roomDrawing[0][2].w = 167;
	roomDrawing[0][2].h = 15;

	roomDrawing[1][0].x = 40;
	roomDrawing[1][0].y = 116;
	roomDrawing[1][0].w = 167;
	roomDrawing[1][0].h = 15;

	roomDrawing[1][1].x = 40;
	roomDrawing[1][1].y = 116;
	roomDrawing[1][1].w = 167;
	roomDrawing[1][1].h = 15;

	roomDrawing[1][2].x = 40;
	roomDrawing[1][2].y = 116;
	roomDrawing[1][2].w = 167;
	roomDrawing[1][2].h = 15;

	roomDrawing[2][0].x = 40;
	roomDrawing[2][0].y = 116;
	roomDrawing[2][0].w = 167;
	roomDrawing[2][0].h = 15;

	roomDrawing[2][1].x = 40;
	roomDrawing[2][1].y = 116;
	roomDrawing[2][1].w = 167;
	roomDrawing[2][1].h = 15;

	roomDrawing[2][2].x = 40;
	roomDrawing[2][2].y = 116;
	roomDrawing[2][2].w = 167;
	roomDrawing[2][2].h = 15;

	//Door Rects
	topDoor.x = 40;
	topDoor.y = 116;
	topDoor.w = 167;
	topDoor.h = 15;

	rightDoor.x = 40;
	rightDoor.y = 116;
	rightDoor.w = 167;
	rightDoor.h = 15;

	bottomDoor.x = 40;
	bottomDoor.y = 116;
	bottomDoor.w = 167;
	bottomDoor.h = 15;

	leftDoor.x = 40;
	leftDoor.y = 116;
	leftDoor.w = 167;
	leftDoor.h = 15;
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