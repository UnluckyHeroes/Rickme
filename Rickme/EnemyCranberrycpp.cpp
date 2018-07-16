#include "Application.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "Module_Players.h"
#include "EnemyRapier.h"
#include "Animation.h"
#include "ModuleTextures.h"
#include "EnemyCranberry.h"
EnemyCranBerry::EnemyCranBerry(int x, int y) :Enemy(x, y) {

	Idl.PushBack({});
	Idl.loop = true;
	Idl.speed = 0.5;

	Up.PushBack({});
	Up.loop = true;
	Up.speed = 0.5;

	Down.PushBack({});
	Down.loop = true;
	Down.speed = 0.5;

	Right.PushBack({});
	Right.loop = true;
	Right.speed = 0.5;

	Left.PushBack({});
	Left.loop = true;
	Left.speed = 0.5;

	animation = &Idl;

	EnemyCranBerryTextures = App->textures->Load("HERE GOES THE PATH, LUCHO CHECK THE PATH ");

	collider = App->collision->AddCollider({ 0,0,50,50 }, COLLIDER_TYPE::COLLIDER_ENEMY);
}
void EnemyCranBerry::Move() {
	//LOG("NEW ANGLE IS: %i", angle;);
	if (App->players->IsEnabled()) {
		playerPosition = App->players->playerPosition;
		radians = atan2((position.y - playerPosition.y), (position.x - playerPosition.x));
	}
	else {
		LOG("Player is dead or is not in the room, enemies don't move");
	}
	angle = radians * (180 / PI);
	if (radians < 0) {
		angle += 360;
	}

	//Animation depending on the angle explained here: https://prnt.sc/k5t63x
	if (angle <= 45 && angle >= 0) {
		animation = &Right;
	}
	if (angle <= 90 && angle >= 45) {
		animation = &Up;
	}
	if (angle <= 135 && angle >= 90) {
		animation = &Up;
	}
	if (angle <= 180 && angle >= 135) {
		animation = &Left;
	}
	if (angle <= 225 && angle >= 180) {
		animation = &Left;
	}
	if (angle <= 270 && angle >= 225) {
		animation = &Down;
	}
	if (angle <= 315 && angle >= 270) {
		animation = &Down;
	}
	if (angle <= 360 && angle >= 315) {
		animation = &Right;
	}
	position.x += speed * 0.02*(playerPosition.x - position.x); //MOVEMENT
	position.y += speed * 0.02*(playerPosition.y - position.y);
}

void EnemyCranBerry::OnCollision(Collider *c1) {

}