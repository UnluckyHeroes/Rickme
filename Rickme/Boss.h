#pragma once
#ifndef BOSS_H
#define BOSS_H
#include "Module.h"
#include "p2Point.h"
#include "Animation.h"
#include "Globals.h"

class Boss : public Module{
public:
	Boss(int x, int y, int room) {};
	~Boss() {};
	virtual void Move() {};
	virtual void Draw(SDL_Texture *sprites);
	virtual void OnCollision(Collider *collider);
public:
	uint life = 30;
	uint speed = 1;
	uint damage = 1;
	uint score = 250;
public:
	Animation BossAnims;
public:
	SDL_Texture * BossTexture;
}

#endif
