#ifndef	__MODULEPLAYER_H__
#define	__MODULEPLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleInput.h"
#include "Application.h"


struct SDL_Texture;

enum PLAYER_NUMBER {
	PLAYER_1,
	PLAYER_2
};

enum WEAPON {
	PISTOL,
	SHOTGUN,
	RIFLE
};

//The modifier will add different effects to the weapon: damage, slow effect,etc.
enum MODIFIER {
	NAIL,
	ELECRTICITY,
	FIRE,
	NONE
};

class ModulePlayer :public Module{
public:

	ModulePlayer(PLAYER_NUMBER playerNumber_);
	~ModulePlayer();

	bool Init();
	update_status Update();
	bool CleanUp();

	void OnCollision();

	void PickGun();
	void PickMod();
	void const Move();
	void const Shoot();

	PLAYER_NUMBER playerNumber; //This variable will tell if it's player 1, or player 2, etc. and by this, it will load different animations, textures,etc. All in the constructor

	uint playerSpeed = 2;		//Speed at which the player moves
	
	iPoint playerPosition;		//Position of the player {x,y}
	
	WEAPON currentWeapon;		//Current weapon of the player
	MODIFIER currentModifier;	//Current modifier of the weapon

private:
	
	//These variables will define the controls of the player
	
	SDL_Scancode upwardsKey;	//Go upwards
	SDL_Scancode downwardsKey;	//Go downwards
	SDL_Scancode leftKey;		//Go left
	SDL_Scancode rightKey;		//Go right
	SDL_Scancode shootKey;		//Shoot

	SDL_Texture *playerTexture = nullptr; //texture of the player sprites
};





#endif // 

