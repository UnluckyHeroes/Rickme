#include "Globals.h"
#include "Application.h"
#include "Player.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleMixer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleUI.h"

Player::Player()	// @CarlesHoms @Andres
{
	
}

Player::~Player()
{}

// Load assets
bool Player::Start()
{
	bool ret = true;

	return ret;
}

// Update: draw background
update_status Player::Update()	// Moves the ship and changes it's printed sprite depending on a counter.
{

	return UPDATE_CONTINUE;
}

bool Player::CleanUp()
{
	

	return true;
}

void Player::OnCollision(Collider* c1, Collider* c2)
{
	
}