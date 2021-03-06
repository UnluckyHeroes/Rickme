#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 17

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleMixer;
class ModuleAudio;
class ModuleFadeToBlack;
class ModulePlayer;
class ModulePlayer1;
class ModuleParticles;
class ModuleMainMenu;
class ModuleScoreboard;
class ModuleCollision;
class ModuleEnemies;
class ModuleFont;
class ModuleUserInterface;

class Application
{
public:

	Module* modules[NUM_MODULES] = { nullptr };
	ModuleWindow* window = nullptr;
	ModuleRender* render = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleMixer* mixer = nullptr;
	ModuleAudio* audio = nullptr;
	ModuleFadeToBlack* fade = nullptr;
	ModulePlayer1* player1 = nullptr;
	ModuleParticles* particles = nullptr;
	ModuleMainMenu* mainMenu = nullptr;
	ModuleScoreboard* scoreboard = nullptr;
	ModuleCollision* collision = nullptr;
	ModuleEnemies* enemies = nullptr;
	ModuleFont* fonts = nullptr;
	ModuleUserInterface* UI = nullptr;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__