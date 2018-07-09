#include "Module_Players.h"

Module_Players::Module_Players() {	//@Joan Marín

}

Module_Players::Module_Players(player_number playerNumber_) {

	if (playerNumber_ == player_number::PLAYER_1) {

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

Module_Players::~Module_Players()
{}

bool Module_Players::Start() {}

bool Module_Players::CleanUp() {}

update_status Module_Players::Update() {



	Move();

	if (App->input->keyboard[shootKey] == KEY_STATE::KEY_REPEAT)
		Shoot();

}

void const Module_Players::Move() {

	if (App->input->keyboard[leftKey] == KEY_STATE::KEY_REPEAT) {
		playerPosition.x -= playerSpeed;
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

void const Module_Players::Shoot() {

}