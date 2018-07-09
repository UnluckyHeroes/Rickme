#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__	// @CarlesHoms @Andres

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"
#include "Path.h"

#define MAX_ACTIVE_PARTICLES 3000		// Make dymanic array for final game
#define DEFAULT_VALUE -1

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

struct Particle
{
	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	iPoint position;
	Path particlePath;
	float fPositionHorizontal, fPositionVertical;
	int arraySize = DEFAULT_VALUE;	// Id that marks the array size
	int arrayId = DEFAULT_VALUE;	// Id needed to delete the full particle array, default for non arrays
	//int damage = 1;
	//int shotType = DEFAULT_VALUE;	// Id for blue and orange power particles
	fPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;

	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();
};

class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	bool Start();
	bool Init();
	update_status Update();
	bool CleanUp();

	void SetParticleArray(Particle* particleArray, int arraySize, int startX, int startY, int particleSizeX, int particleSizeY, int movX, int movY, float speedX, float speedY, int particleLife, int laserDamage = 1, float animSpeed = 0.0f, bool animLoop = false);
	void AddParticle(const Particle& particle, int x, int y, int shotType = DEFAULT_VALUE, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0);
	//void AddParticlePath(const Particle& particle, int x, int y, int shotType = DEFAULT_VALUE, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0);
	void AddParticleArray(Particle* particleArray, int arraySize, int x, int y, int movX, int movY, int shotType = DEFAULT_VALUE, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0);
	void ArrayListNext();
	void OnCollision(Collider* c1, Collider* c2) override;

private:
	SDL_Texture* graphics = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];
	uint last_particle = 0;

public:
	// Particle life values
	/*int shortLife;
	int mediumLife;
	int longLife;*/

	// List of Ids needed to delete the full particle array
	int arrayIdList;

	//@Andres
	//Particle explosion;  //ring 
};

#endif // __MODULEPARTICLES_H__