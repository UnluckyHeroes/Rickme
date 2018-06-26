#ifndef __Module_Player_1_H__
#define __Module_Player_1_H__	//@CarlesHoms

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "Player.h"

#include "SDL_mixer/include/SDL_mixer.h"

struct SDL_Texture;
struct Collider;

class Module_Player_1 : public Player
{
public:
	Module_Player_1();
	~Module_Player_1();

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

#endif	// __Module_Player_1_H__