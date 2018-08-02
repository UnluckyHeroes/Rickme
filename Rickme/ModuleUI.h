#ifndef __MODULE_UI_H__
#define __MODULE_UI_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "Application.h"
#include "p2Point.h"

#include "SDL/include/SDL_pixels.h"
#include "SDL_mixer/include/SDL_mixer.h"
#pragma comment(lib,"SDL_mixer/libx86/SDL2_mixer.lib")

#include <stdio.h>
#include <cstdio>

#define MAX_FONTS 10
#define MAX_FONT_CHARS 256

typedef unsigned int uint;
struct SDL_Texture;

struct Font {

	char table[MAX_FONT_CHARS];
	SDL_Texture* graphic = nullptr;

	uint rows, len, char_w, char_h, row_chars;
};

class ModuleUI : public Module {
public:

	ModuleUI();
	~ModuleUI();

	bool Start();
	update_status Update();
	bool CleanUp();

public: 

	//Functions
	int LoadFont(const char* texture_path, const char *characters, uint rows = 1);
	void UnloadFont(int font_id);
	void BlitText(int x, int y, int bmp_font_id, const char *text) const;

public: 

	//Font ID
	int Font = -1;

	//P1 Score
	uint P1Score;
	char P1_Score_Text[10];

	//Score for Ranking
	uint Ranking_Score;

	//Readme Parameter
	float ReadmeCoins;
	char Readme_Text[10];

	//Stability
	char Stability_Text[10];
	uint Stability;

private:

	//Font fonts[MAX_FONTS]; //WTF is this error?
};

#endif





//----------------- FOR THE RANKING -----------------\\

//struct rank {
//
//	char name[3];
//	int score;
//};



/*FILE* Ranking;
uint a = 0;
struct rank ranking[9];

//To put the name in the ranking
int counter;
char name1;
char name2;
char name3;
bool cpressed = false;
bool c2pressed = false;
bool c3pressed = false;
bool ccompleted = false;
char NewName[4] = "RCK";
char New[4];

uint counterRanking;

char* abecedary = "ABCDEFGHIJKLMN0PQRSTUVWXYZ";
char* abecedary2 = "ABCDEFGHIJKLMN0PQRSTUVWXYZ";
char* abecedary3 = "ABCDEFGHIJKLMN0PQRSTUVWXYZ";
int selector = 0;
int selector2 = 0;
int selector3 = 0;

//Ranking Functions
void BlitRanking(struct rank array[9]);
void WriteName();
void ChangeRanking(FILE *pFile, char *path, int Score); */