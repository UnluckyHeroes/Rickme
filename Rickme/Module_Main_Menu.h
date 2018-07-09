#ifndef __MODULE_MAIN_MENU_H__
#define __MODULE_MAIN_MENU_H__	// @DídacRomero

#include "Module.h"
#include "Globals.h"

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")

struct SDL_Texture;

class Module_Main_Menu : public Module
{
public:
	Module_Main_Menu();
	~Module_Main_Menu();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	//Textures
	SDL_Texture* backgroundText = nullptr;
	SDL_Texture* titleText = nullptr;
	SDL_Texture* viscoGamesText = nullptr;

	//Rectangles
	SDL_Rect backgroundRect;
	SDL_Rect titleBoxRect;
	SDL_Rect titleRect;
	SDL_Rect viscoGamesRect;

	//Music 
	Mix_Music * MusicMainMenu = nullptr;
};

#endif	// __MODULE_MAIN_MENU_H__

// Developer Note (Carles): I'm using this as reference for screen modules, we are not using this currently.