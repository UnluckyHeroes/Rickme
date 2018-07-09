#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"


struct SDL_Texture;
struct Collider;

class Enemy
{
protected:
	
	Collider* collider = nullptr;
	

public:
	Animation * animation = nullptr;
	iPoint position;
	SDL_Texture *sprites;

	int life = 1;	// Standard value for all enemies
	uint score = 100; //Standart score of all enemies
public:
	Enemy(int x, int y);
	//Enemy(int x, int y,int life,int score);
	virtual ~Enemy();

	const Collider* GetCollider() const;

	virtual void Move() {};
	virtual void Draw(SDL_Texture* sprites);
	virtual void OnCollision(Collider* collider);
	virtual void Fire() {};


};

#endif // __ENEMY_H__