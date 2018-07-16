#pragma once
#ifndef ENEMY_CRANBERRY_H
#define ENEMY_CRANBERRY_H
#include "Enemy.h"

class EnemyCranBerry : public Enemy {

private:
	uint speed = 2;
	uint life = 8;
	uint score = 100;
public:

	EnemyCranBerry(int x, int y);
	void Move();
	virtual void OnCollision(Collider *collider) override;

public:
	Animation Idl;
	Animation Up;
	Animation Down;
	Animation Right;
	Animation Left;
public:
	iPoint playerPosition;

public:
	SDL_Texture * EnemyCranBerryTextures;

public:
	bool PlayerInTheRoom = false;

public:
	float radians;
	float angle;
};












#endif // !ENEMY_CRANBERRY_H
