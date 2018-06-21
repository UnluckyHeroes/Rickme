#ifndef __PLAYER_H__
#define __PLAYER_H__	//@CarlesHoms

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

#include "SDL_mixer/include/SDL_mixer.h"

struct SDL_Texture;
struct Collider;

class Player : public Module
{
public:
	Player();
	~Player();

	bool Start();
	update_status Update();
	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2) override;
	void checkBluePowerParticleLimit();

public:

	SDL_Texture* graphics = nullptr;

	// Animations

	// Animation pointers

	// Player rectangle

	// Sprite sizes in pixels

	//Music 
	//Mix_Chunk *type1Shot = nullptr;	// Mark used channels

	//Collider

	//Debug Purpose Variables
	//bool godMode;
};

#endif	// __PLAYER_H__