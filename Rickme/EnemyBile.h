#pragma once
#ifndef ENEMY_BILE_H
#define ENEMY_BILE_H
#include "Enemy.h"

class EnemyBile : public Enemy {

private:
	uint speed = 1;
	uint life = 10;
	uint score = 150;
public:

	EnemyBile(int x, int y);
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
	SDL_Texture * EnemyBileTextures;

public:
	bool PlayerInTheRoom = false;

public:
	float radians;
	float angle;
};








#endif