#ifndef __PLAYER_H__
#define __PLAYER_H__	//@CarlesHoms

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

#include "SDL_mixer/include/SDL_mixer.h"

struct SDL_Texture;
struct Collider;

enum class player_number {
	PLAYER_1,
	PLAYER_2,
	PLAYER_3,
	PLAYER_4
};

enum weapon {
	PISTOL,
	SHOTGUN,
	RIFLE
};

enum modifier {	//The modifier will add different effects to the weapon: damage, slow effect,etc.
	NAIL,
	ELECRTICITY,
	FIRE,
	NONE
};

class Player
{
public:
	Player(player_number paramPlayerNumber);
	~Player();

	bool Start();
	bool Init();
	update_status Update();
	bool CleanUp();

public:

	void OnCollision(Collider* c1, Collider* c2);

	SDL_Texture* graphics = nullptr;

	void const Move();			//Player movement
	void const Aim();			//Determines in which direction the player is aiming at
	void const Shoot();			//Shoot

	uint playerSpeed = 2;		//Speed at which the player moves

	iPoint playerPosition;		//Position of the player {x,y}

	weapon currentWeapon;		//Current weapon of the player
	modifier currentModifier;	//Current modifier of the weapon

private:

	uint healthPoints;			//Player health points

	//These variables will define the controls of the player
	SDL_Scancode upwardsKey;	//Go upwards
	SDL_Scancode downwardsKey;	//Go downwards
	SDL_Scancode leftKey;		//Go left
	SDL_Scancode rightKey;		//Go right
	SDL_Scancode shootKey;		//Shoot

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