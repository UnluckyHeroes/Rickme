#include "ModulePlayer.h"


ModulePlayer::ModulePlayer(PLAYER_NUMBER playerNumber_){ //@Joan Marín
	
	if (playerNumber_ == PLAYER_NUMBER::PLAYER_1) {

		/*	Stablish controls for player 1:
		Going left  ->	A
		Going right ->	D
		Going up	->	W
		Going down	->	S
		Shoot		-> Space bar */
		
		leftKey = SDL_SCANCODE_A;
		rightKey = SDL_SCANCODE_D;
		upwardsKey = SDL_SCANCODE_W;
		downwardsKey = SDL_SCANCODE_S;
		shootKey = SDL_SCANCODE_SPACE;
	}

}

ModulePlayer::~ModulePlayer()
{}

bool ModulePlayer::Start(){}

bool ModulePlayer::CleanUp(){}

update_status ModulePlayer::Update(){
	
	

	Move();
	
	if (App->input->keyboard[shootKey] == KEY_STATE::KEY_REPEAT)
		Shoot();

}

void const ModulePlayer::Move() {

	if (App->input->keyboard[leftKey]==KEY_STATE::KEY_REPEAT){
		playerPosition.x-= playerSpeed;
	}

	if (App->input->keyboard[rightKey] == KEY_STATE::KEY_REPEAT) {
		playerPosition.x += playerSpeed;
	}

	if (App->input->keyboard[upwardsKey] == KEY_STATE::KEY_REPEAT) {
		playerPosition.y -= playerSpeed;
	}

	if (App->input->keyboard[downwardsKey] == KEY_STATE::KEY_REPEAT) {
		playerPosition.y += playerSpeed;
	}
};

void const ModulePlayer::Shoot() {

}