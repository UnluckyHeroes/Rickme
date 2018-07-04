#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleMixer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"
#include "ModuleFont.h"
#include "ModuleUserInterface.h"
#include "ModuleAudio.h"

#include "ModulePlayer.h"
//#include "ModuleMainMenu.h"
#include "ModuleEnemies.h"

Application::Application()
{
	int i = 0;
	modules[i++] = window = new ModuleWindow();
	modules[i++] = render = new ModuleRender();
	modules[i++] = input = new ModuleInput();
	modules[i++] = textures = new ModuleTextures();
	modules[i++] = mixer = new ModuleMixer();
	modules[i++] = audio = new ModuleAudio();
	//modules[i++] = mainMenu = new ModuleMainMenu();
	//modules[i++] = scoreboard = new ModuleScoreboard();
	modules[i++] = particles = new ModuleParticles();
	modules[i++] = enemies = new ModuleEnemies();
	modules[i++] = player1 = new ModulePlayer(PLAYER_1);
	//modules[i++] = player1 = new ModulePlayer1();
	modules[i++] = collision = new ModuleCollision();
	modules[i++] = UI = new ModuleUserInterface();
	modules[i++] = fonts = new ModuleFont();
	modules[i++] = fade = new ModuleFadeToBlack();
}

Application::~Application()
{
	for (int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	// Disable all non-core modules that will be enabled later in the game
	
	//player1->Disable();
	//player2->Disable();
	enemies->Disable();

	// Disable all screens
	//mainMenu->Disable();
	//scoreboard->Disable();

	for (int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for (int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Start();

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}