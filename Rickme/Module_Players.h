#ifndef	__MODULEP_LAYERS_H__
#define	__MODULE_PLAYERS_H__	//@JoanMarín

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "Player.h"
#include "ModuleInput.h"
#include "Application.h"

struct SDL_Texture;

enum class player_number {
	PLAYER_1,
	PLAYER_2
};

enum weapon {
	PISTOL,
	SHOTGUN,
	RIFLE
};

//The modifier will add different effects to the weapon: damage, slow effect,etc.
enum modifier {
	NAIL,
	ELECRTICITY,
	FIRE,
	NONE
};

class Module_Players :public Module {
public:

	Module_Players();
	Module_Players(player_number playerNumber_);
	~Module_Players();

	bool Start();
	bool Init();
	update_status Update();
	bool CleanUp();

	void OnCollision();

	void PickGun();
	void PickMod();

	void const Move();			//Player movement

	void const Aim();			//Determines in which direction the player is aiming at
	void const Shoot();			//Shoot

	uint playerSpeed = 2;		//Speed at which the player moves

	iPoint playerPosition;		//Position of the player {x,y}

	weapon currentWeapon;		//Current weapon of the player
	modifier currentModifier;	//Current modifier of the weapon

private:

	uint hp;					//Player health points

								//These variables will define the controls of the player

	SDL_Scancode upwardsKey;	//Go upwards
	SDL_Scancode downwardsKey;	//Go downwards
	SDL_Scancode leftKey;		//Go left
	SDL_Scancode rightKey;		//Go right
	SDL_Scancode shootKey;		//Shoot

	SDL_Texture *playerTexture = nullptr; //texture of the player sprites
};

#endif // MODULE_PLAYERS

