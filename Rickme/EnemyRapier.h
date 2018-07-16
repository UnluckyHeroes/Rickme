#pragma once
#ifndef ENEMY_RAPIER_H__
#define ENEMY_RAPIER_H__
#include "Enemy.h"

class EnemyRapier : public Enemy {

private:
	uint speed = 3;
	uint life = 5;
	uint score = 100;
public:

	EnemyRapier(int x, int y);
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
	SDL_Texture * EnemyRapierTextures;

public:
	bool PlayerInTheRoom = false;
	
public: 
	float radians;
	float angle;
};




#endif