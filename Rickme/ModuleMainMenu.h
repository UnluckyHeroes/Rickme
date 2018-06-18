#ifndef __ModuleMainMenu_H__
#define __ModuleMainMenu_H__	// @CarlesHoms

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")

struct SDL_Texture;

class ModuleMainMenu : public Module
{
public:
	ModuleMainMenu();
	~ModuleMainMenu();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	//Textures
	SDL_Texture* backgroundText = nullptr;
	SDL_Texture* titleText = nullptr;
	SDL_Texture* viscoGamesText = nullptr;
	//SDL_Texture* orangeLettersText = nullptr;
	//SDL_Texture* whiteLettersText = nullptr;

	//Rectangles
	SDL_Rect backgroundRect;
	SDL_Rect titleBoxRect;
	SDL_Rect titleRect;
	SDL_Rect viscoGamesRect;

	//Music 
	Mix_Music * MusicMainMenu = nullptr;
};

#endif