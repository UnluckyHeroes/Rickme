#define _CRT_SECURE_NO_WARNINGS

#include "ModuleUI.h"
#include "Globals.h"
#include "Application.h"

#include <iostream>
#include <string.h>
#include <cstdio>

ModuleUI::ModuleUI() {}


ModuleUI::~ModuleUI() {}

bool ModuleUI::Start() {

	//P1Score = 0;
	//ReadmeCoins = 0.1;
	//Stability = 50;

	//font = ("PATH", "REPRESENTATION", 2); //Same error than in header

	return true;
}

bool ModuleUI::CleanUp() {

	/*UnloadFont(font);*/
	return true;
}

update_status ModuleUI::Update() {

	return UPDATE_CONTINUE;
}

int ModuleUI::LoadFont(const char* texture_path, const char* characters, uint rows)
{
	//int id = -1;

	//if (texture_path == nullptr || characters == nullptr || rows == 0)
	//{
	//	LOG("Could not load font\n");
	//	return id;
	//}

	//SDL_Texture* tex = App->textures->Load(texture_path);

	//if (tex == nullptr || strlen(characters) >= MAX_FONT_CHARS)
	//{
	//	LOG("Could not load font at %s with characters '%s \n'", texture_path, characters);
	//	return id;
	//}

	//id = 0;
	//for (; id < MAX_FONTS; ++id)
	//	if (fonts[id].graphic == nullptr)
	//		break;

	//if (id == MAX_FONTS)
	//{
	//	LOG("Cannot load font %s. Array is full (max %d).\n", texture_path, MAX_FONTS);
	//	return id;
	//}

	//fonts[id].graphic = tex; // graphic: pointer to the texture
	//fonts[id].rows = rows; // rows: rows of characters in the texture
	//fonts[id].len = strlen(characters); // len: length of the table

	//									// TODO 1: Finish storing font data

	//									// table: array of chars to have the list of characters
	//strcpy_s(fonts[id].table, characters);
	//// row_chars: amount of chars per row of the texture
	//fonts[id].row_chars = strlen(characters) / rows;
	//// char_w: width of each character
	//// char_h: height of each character
	//App->textures->GetSize(tex, fonts[id].char_w, fonts[id].char_h);
	//fonts[id].char_w /= fonts[id].row_chars;
	//fonts[id].char_h /= rows;

	//LOG("Successfully loaded BMP font from %s", texture_path);

	//return id;
	return 1;
}


void ModuleUI::UnloadFont(int font_id)
{
	/*if (font_id >= 0 && font_id < MAX_FONTS && fonts[font_id].graphic != nullptr)
	{
		App->textures->Unload(fonts[font_id].graphic);
		fonts[font_id].graphic = nullptr;
		LOG("Successfully Unloaded BMP font_id %d", font_id);
	}*/
}


void ModuleUI::BlitText(int x, int y, int font_id, const char* text) const
{
	/*if (text == nullptr || font_id < 0 || font_id >= MAX_FONTS || fonts[font_id].graphic == nullptr)
	{
		LOG("Unable to render text with bmp font id %d\n", font_id);
		return;
	}

	const Font* font = &fonts[font_id];
	SDL_Rect rect;
	uint len = strlen(text);

	rect.w = font->char_w;
	rect.h = font->char_h;

	for (uint i = 0; i < len; ++i)
	{

		int c = 0;
		for (; c < fonts[font_id].len; ++c)
		{
			if (text[i] == fonts[font_id].table[c])
				break;
		}

		uint col = c % fonts[font_id].row_chars;
		uint row = c / fonts[font_id].row_chars;

		rect.x = col * fonts[font_id].char_w;
		rect.y = row * fonts[font_id].char_h;

		App->render->Blit(font->graphic, x + (i*font->char_w), y, &rect, 1.0f, false);
	}*/
}