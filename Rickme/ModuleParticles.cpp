#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
//#include "ModulePlayer1.h"
#include "Path.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()	// @Andres @CarlesHoms
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{}

// Called before render is available
bool ModuleParticles::Init()
{
	LOG("Init Module Particles");
	bool ret = true;

	// Particle life values
	/*shortLife = 1000;
	mediumLife = 2000;
	longLife = 3000;*/

	/*redRocketDown.anim.PushBack({ 2, 99, 16, 9 });
	redRocketDown.anim.PushBack({ 1, 113, 16, 9 });
	redRocketDown.anim.PushBack({ 3, 129, 16, 9 });
	redRocketDown.anim.PushBack({ 4, 142, 16, 9 });
	redRocketDown.anim.PushBack({ 3, 158, 16, 9 });
	redRocketDown.anim.PushBack({ 2, 173, 16, 9 });
	redRocketDown.anim.PushBack({ 3, 188, 16, 9 });
	redRocketDown.anim.PushBack({ 4, 202, 16, 9 });
	redRocketDown.anim.loop = true;
	redRocketDown.speed.x = 0.0f;
	redRocketDown.speed.y = 2.0f;
	redRocketDown.life = mediumLife;
	redRocketDown.anim.speed = 0.7f;*/

	// Parameter list: (Particle* particleArray, int arraySize, int startX, int startY, int particleSizeX,
	// int particleSizeY, int movX, int movY, float speedX, float speedY, int life, int animSpeed = 0.0f, bool animLoop = false)

	/*SetParticleArray(upRightGreen2, 4, 114, 34, 4, 12, 4, -4, 4.0f, -4.0f, shortLife, 2);
	SetParticleArray(downRightGreen2, 4, 114, 46, 4, 12, 4, 4, 4.0f, 4.0f, shortLife, 2);
	SetParticleArray(upLeftGreen2, 4, 108, 34, 4, 12, -4, -4, -4.0f, -4.0f, shortLife, 2);
	SetParticleArray(downLeftGreen2, 4, 108, 46, 4, 12, -4, 4, -4.0f, 4.0f, shortLife, 2);*/

	// Explosion particle // @Andres
	/*explosion.anim.PushBack({ 505, 34, 4, 4 });
	explosion.anim.PushBack({ 512, 26, 12, 12 });
	explosion.anim.PushBack({ 528, 6, 32, 32 });
	explosion.anim.PushBack({ 563, 7, 30, 30 });
	explosion.anim.PushBack({ 597, 8, 30, 30 });
	explosion.anim.PushBack({ 518, 46, 30, 30 });
	explosion.anim.PushBack({ 552, 47, 30, 30 });
	explosion.anim.PushBack({ 587, 45, 32, 32 });
	explosion.anim.PushBack({ 524, 82, 32, 32 });
	explosion.anim.PushBack({ 571, 82, 32, 32 });
	explosion.anim.loop = false;
	explosion.anim.speed = 1.5f;
	explosion.anim.Finished();*/

	return ret;
}

// Load assets
bool ModuleParticles::Start()
{
	// List of Ids needed to delete the full particle array, counter resets to one each time
	arrayIdList = 0;

	LOG("Loading particles");
	graphics = App->textures->Load(".png");

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)	// @CarlesHoms
	{
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			/*if (p->arrayId > DEFAULT_VALUE)		// If array Id shows that the particle processed is part of a particle array
			{
				if (active[i]->shotType == PLAYER_1_BLUE_SHOT)
				{
					App->player1->currentBlue -= 1;
				}

				else if (active[i]->shotType == PLAYER_1_ORANGE_SHOT)
				{
					App->player1->currentOrange -= 1;
				}

				else if (active[i]->shotType == PLAYER_2_BLUE_SHOT)
				{
					App->player2->currentBlue -= 1;
				}

				else if (active[i]->shotType == PLAYER_2_ORANGE_SHOT)
				{
					App->player2->currentOrange -= 1;
				}

				int arrayIdMarker = p->arrayId;

				for (uint j = 0; j < MAX_ACTIVE_PARTICLES; j++)
				{
					if (active[j] != nullptr && active[j]->arrayId == arrayIdMarker)
					{
						delete active[j];
						active[j] = nullptr;
					}
				}

				continue;
			}*/

			/*if (p->shotType == PLAYER_1_BLUE_SHOT)
			{
				App->player1->currentBlue -= 1;
			}*/

			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));

			if (p->fx_played == false)
			{
				p->fx_played = true;
				// Play particle fx here
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Parameter list: (Particle* particleArray, int arraySize, int particleSizeX, int particleSizeY, int startX, int startY, int movX, int movY, float speedX, float speedY, int life, int animSpeed, bool animLoop)
void ModuleParticles::SetParticleArray(Particle* particleArray, int arraySize, int startX, int startY, int particleSizeX, int particleSizeY, int movX, int movY, float speedX, float speedY, int particleLife, int laserDamage, float animSpeed, bool animLoop) // Carles edit
{
	for (int i = 0; i < arraySize; i++)	// @CarlesHoms
	{
		particleArray[i].anim.PushBack({ startX + movX * i, startY + movY * i, particleSizeX, particleSizeY });
		particleArray[i].anim.loop = animLoop;
		particleArray[i].speed.x = speedX;
		particleArray[i].speed.y = speedY;
		particleArray[i].life = particleLife;
		//particleArray[i].laserDamage = laserDamage;
		particleArray[i].anim.speed = animSpeed;
	}
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, int shotType, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)	// @CarlesHoms
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = (int)p->fPositionHorizontal;
			p->position.y = (int)p->fPositionVertical;
			if (collider_type == COLLIDER_PLAYER_SHOT)
			{
				p->fPositionHorizontal = x + App->render->camera.x / SCREEN_SIZE;
				p->fPositionVertical = y + App->render->camera.y / SCREEN_SIZE;
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
				p->collider->SetPos(p->position.x, p->position.y);
			}

			else if (collider_type != COLLIDER_NONE)
			{
				p->fPositionHorizontal = x;
				p->fPositionVertical = y;
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			}

			else
			{
				p->fPositionHorizontal = x;
				p->fPositionVertical = y;
			}

			active[i] = p;
			break;
		}
	}
}

void ModuleParticles::AddParticleArray(Particle* particleArray, int arraySize, int x, int y, int movX, int movY, int shotType, COLLIDER_TYPE collider_type, Uint32 delay)	// Carles edit
{
	uint i = 0;

	for (int j = 0; j < arraySize; j++)	// @CarlesHoms
	{
		for (i; i < MAX_ACTIVE_PARTICLES; ++i)
		{
			if (active[i] == nullptr)
			{
				Particle* p = new Particle(particleArray[j]);
				p->born = SDL_GetTicks() + delay;
				p->fPositionHorizontal = x + App->render->camera.x / SCREEN_SIZE + movX * j;
				p->fPositionVertical = y + App->render->camera.y / SCREEN_SIZE + movY * j;
				p->position.x = (int)p->fPositionHorizontal;
				p->position.y = (int)p->fPositionVertical;
				p->arrayId = arrayIdList;
				p->arraySize = arraySize;
				if (collider_type != COLLIDER_NONE)
				{
					p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
					p->collider->SetPos(p->position.x, p->position.y);
				}
				active[i] = p;
				break;
			}
		}
	}

	ArrayListNext();
}

void ModuleParticles::ArrayListNext()
{
	if (arrayIdList < MAX_ACTIVE_PARTICLES)
		arrayIdList++;

	else { arrayIdList = 0; }
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			if (active[i]->arrayId > DEFAULT_VALUE)
			{
				int arrayIdMarker = active[i]->arrayId;

				for (uint j = 0; j < MAX_ACTIVE_PARTICLES; j++)
				{
					if (active[j] != nullptr && active[j]->arrayId == arrayIdMarker)
					{
						delete active[j];
						active[j] = nullptr;
					}
				}
			}

			else
			{
				delete active[i];
				active[i] = nullptr;
			}
			
			break;
		}
	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
	anim(p.anim),
	position(p.position),
	fPositionHorizontal(p.fPositionHorizontal),
	fPositionVertical(p.fPositionVertical),
	speed(p.speed),
	fx(p.fx),
	born(p.born),
	life(p.life),
	arrayId(p.arrayId),
	arraySize(p.arraySize),
	particlePath(p.particlePath)
{}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;		// EXCEPTION THROWN CONSTANT BUGG HERE
}

bool Particle::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if (((int)SDL_GetTicks() - (int)born) > (int)life)
			ret = false;
	}

	else if (anim.Finished())	// carles edit (else was above the if, i didn't like it)
		ret = false;

	if (position.x > App->render->camera.x / SCREEN_SIZE + SCREEN_WIDTH)	// carles edit, bullets outside the screen will die
		ret = false;

	//if (SDL_GetTicks() >= born)	// This addition will make the particle spawn with the marked delay in AddParticle()
	//{								// CAUTION: The origin position does not change, therefore not following the camera with the delay, needs fixing if this is needed

	fPositionHorizontal += speed.x; //+ camera movemenet
	fPositionVertical += speed.y; //+ camera movemenet

	position.x = (int)fPositionHorizontal;
	position.y = (int)fPositionVertical;

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
	//}

	return ret;
}