#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "Module.h"
#include "Globals.h"
#include "SDL_mixer/include/SDL_mixer.h"

#define MAX_SONGS 500
#define MAX_EFFECTS 500

enum Repetitions {

	LOOP = -1,
	ONCE,
	TWICE,
	THRICE

};

class ModuleAudio : public Module {
public:

	ModuleAudio();

	// Destructor
	~ModuleAudio();


	bool Init();

	// Called before quitting
	bool CleanUp();

	// Audio methods
	void StopEffect(Mix_Chunk* to_stop);
	void StopAudio();
	void ResetState();
	void PlayMusic(Mix_Music* to_play, Repetitions n_times);
	void PlaySoundEffect(Mix_Chunk* to_play);
	bool IsPlaying();

	// Utility methods
	Mix_Music* const LoadMusic(const char* path);
	Mix_Chunk* const LoadSoundEffect(const char* path);
	bool UnloadMusic(Mix_Music* music);
	bool UnloadSoundEffect(Mix_Chunk* effect);


	Mix_Music * songs[MAX_SONGS];
	uint last_song = 0;

	Mix_Chunk* sound_effects[MAX_EFFECTS];
	uint last_effect = 0;

	Mix_Music* prev_song;

};

#endif
