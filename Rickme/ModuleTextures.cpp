#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"

#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

ModuleTextures::ModuleTextures() : Module()
{
	for (uint i = 0; i < MAX_TEXTURES; ++i)
		textures[i] = nullptr;
}

// Destructor
ModuleTextures::~ModuleTextures()
{}

// Called before render is available
bool ModuleTextures::Init()
{
	LOG("Init Image library");
	bool ret = true;

	// load support for the PNG image format
	int flags = IMG_INIT_PNG;
	int init = IMG_Init(flags);

	if ((init & flags) != flags)
	{
		SDL_ClearError();
		LOG("Could not initialize Image lib. IMG_Init: %s \n", IMG_GetError());
		ret = false;
		SDL_ClearError();

	}

	return ret;
}

// Called before q	uitting
bool ModuleTextures::CleanUp()
{
	LOG("Freeing textures and Image library");

	for (uint i = 0; i < MAX_TEXTURES; ++i)
		if (textures[i] != nullptr)
			SDL_DestroyTexture(textures[i]);

	IMG_Quit();
	return true;
}

// Load new texture from file path
SDL_Texture* const ModuleTextures::Load(const char* path)
{
	SDL_Texture* texture = NULL;
	SDL_Surface* surface = IMG_Load(path);

	if (surface == NULL)
	{
		SDL_ClearError();
		LOG("Could not load surface with path: %s. IMG_Load: %s \n", path, IMG_GetError());
		SDL_ClearError();

	}
	else
	{
		texture = SDL_CreateTextureFromSurface(App->render->renderer, surface);

		if (texture == NULL)
		{
			LOG("Unable to create texture from surface! SDL Error: %s\n %s \n", SDL_GetError(), path);
			SDL_ClearError();

		}
		else
		{
			for (int i = 0; i < MAX_TEXTURES; ++i)
			{
				if (textures[i] == nullptr) //@AndresSala
				{
					i = textureCounter;
					textures[textureCounter] = texture;
					break;
				}
				else if (i == (MAX_TEXTURES - 1)) //AndresSala
				{
					LOG("Unable to load texture, capacity overfload! SDL Error: %s \n", SDL_GetError());
					SDL_ClearError();

				}
			}



		}

		SDL_FreeSurface(surface);
	}

	return texture;
}

bool ModuleTextures::Unload(SDL_Texture* texture)
{
	bool ret = false;

	if (texture != nullptr)
	{
		for (int i = 0; i < MAX_TEXTURES; ++i)
		{
			if (textures[i] == texture)
			{
				textures[i] = nullptr;
				ret = true;
				break;
			}
		}

		SDL_DestroyTexture(texture);
	}

	return ret;
}

void ModuleTextures::GetSize(const SDL_Texture* texture, uint& width, uint& height) const
{
	SDL_QueryTexture((SDL_Texture*)texture, NULL, NULL, (int*)&width, (int*)&height);
}