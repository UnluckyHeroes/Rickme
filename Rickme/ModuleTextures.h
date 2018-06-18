#ifndef __ModuleTextures_H__
#define __ModuleTextures_H__

#include "Module.h"
#include "Globals.h"

#define MAX_TEXTURES 1000	// Maximum possible textures.

struct SDL_Texture;

class ModuleTextures : public Module
{
public:
	ModuleTextures();
	~ModuleTextures();

	bool Init();
	bool CleanUp();

	SDL_Texture* const Load(const char* path);
	bool Unload(SDL_Texture* texture);

	void GetSize(const SDL_Texture* texture, uint& width, uint& height) const;

public:
	SDL_Texture* textures[MAX_TEXTURES];	// Array of textures, allocates all textures and limitates the amount possible
	uint last_texture = 0;

private:
	int textureCounter = 0;
};

#endif // __ModuleTextures_H__