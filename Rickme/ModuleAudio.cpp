#include "Application.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )



ModuleAudio::ModuleAudio() : Module()	// @JoanMar�n
{
	for (uint i = 0; i < MAX_SONGS; ++i)
	{
		songs[i] = nullptr;
	}

	for (uint i = 0; i < MAX_EFFECTS; ++i)
	{
		sound_effects[i] = nullptr;
	}
}

// Destructor
ModuleAudio::~ModuleAudio()
{}

bool ModuleAudio::Init()
{
	LOG("Init Audio library");
	bool ret = true;

	// Now it's time for some audio

	// Create mixer --
	int flags = Mix_Init(MIX_INIT_OGG);
	if (!flags)
	{
		LOG("Could not init mixer SDL Error: %s \n", SDL_GetError());
		bool ret = false;
	}
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048); //frequency, format, channels, chunk

	return ret;
}


// Called before quitting
bool ModuleAudio::CleanUp()
{
	LOG("Freeing audio and Mixer library");

	Mix_HaltMusic();

	for (uint i = 0; i < MAX_SONGS; i++) {
		if (songs[i] != nullptr) {
			Mix_FreeMusic(songs[i]);
		}
	}
	for (uint i = 0; i < MAX_EFFECTS; i++) {
		if (sound_effects[i] != nullptr) {
			Mix_FreeChunk(sound_effects[i]);
		}
	}

	Mix_CloseAudio();
	Mix_Quit();

	return true;
}


void ModuleAudio::StopAudio() {

	Mix_HaltMusic();
	ResetState();
}

void ModuleAudio::StopEffect(Mix_Chunk* to_stop)
{
	for (uint i = 0; i < MAX_EFFECTS; i++) {
		if (sound_effects[i] == to_stop) {
			to_stop->volume = 0;
			break;
		}
	}
}

void ModuleAudio::ResetState() {

	prev_song = nullptr;
}


void ModuleAudio::PlayMusic(Mix_Music* to_play, Repetitions n_times) {

	if (to_play != prev_song) {
		/*Mix_PlayMusic(to_play, n_times);*/
		Mix_FadeInMusic(to_play, 1, 1000);
		//Mix_VolumeMusic(MIX_MAX_VOLUME / 3);
		prev_song = to_play;
	}
}


void ModuleAudio::PlaySoundEffect(Mix_Chunk* to_play) {

	Mix_PlayChannel(-1, to_play, 0);
}


bool ModuleAudio::IsPlaying() {

	if (Mix_PlayingMusic() == 1) return true;
	else return false;
}


Mix_Music* const ModuleAudio::LoadMusic(const char* path) {

	Mix_Music* music = nullptr;
	music = Mix_LoadMUS(path);

	if (music == nullptr) {
		LOG("Could not load song with path: %s. Error: %s.", path, Mix_GetError());
	}
	else {
		songs[last_song++] = music;
	}

	return music;
}


Mix_Chunk* const ModuleAudio::LoadSoundEffect(const char* path) {

	Mix_Chunk* effect = nullptr;
	effect = Mix_LoadWAV(path);

	if (effect == nullptr) {
		LOG("Could not load sound effect with path: %s. Error: %s.", path, Mix_GetError());
	}
	else {
		sound_effects[last_effect++] = effect;
	}

	return effect;
}


bool ModuleAudio::UnloadMusic(Mix_Music* music) {

	for (uint i = 0; i < MAX_SONGS; i++) {
		if (songs[i] == music) {
			Mix_FreeMusic(songs[i]);
			songs[i] = nullptr;
			break;
		}
	}
	return true;
}


bool ModuleAudio::UnloadSoundEffect(Mix_Chunk* effect) {

	for (uint i = 0; i < MAX_SONGS; i++) {
		if (sound_effects[i] == effect) {
			Mix_FreeChunk(sound_effects[i]);
			sound_effects[i] = nullptr;
			break;
		}
	}
	return true;
}