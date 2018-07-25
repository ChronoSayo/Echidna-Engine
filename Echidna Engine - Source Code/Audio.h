#pragma once
#ifndef AUDIO_H_INCLUDED
#define AUDIO_H_INCLUDED

#include "SDL_mixer.h"
#include <iostream>
#include <vector>
#include <string>

/*Organizes all implemented audio. Call sound effects or background music from this class. Add a tag for each added audio. Supports only .wav.*/
class Audio
{
public:
	static Audio* GetInstance();

	Audio();
	~Audio();

	void AddSoundFX(std::string filename, std::string tag);
	void AddMusic(std::string filename, std::string tag);

	/*0 - 128.*/
	void SetVolumeAll(int volume);
	/*0 - 128.*/
	void SetVolumeAllMusic(int volume);
	/*0 - 128.*/
	void SetVolumeAllSFX(int volume);
	/*0 - 128.*/
	void SetVolumeSFX(int volume, std::string tag);
	/*0 - 128.*/
	void SetVolumeMusic(int volume, std::string tag);

	/*-1 for infinite.*/
	void PlayMusic(int loop, std::string tag);
	void PlaySFX(std::string tag);
	void StopMusic();
	void StopSFX(std::string tag);
	void StopAll();
	void PauseMusic();
	void PauseSFX(std::string tag);
	void PauseAll();

	void CleanAll();

private:
	static Audio* _staticAudio;
	
	struct MusicData
	{
		Mix_Music* music;
		std::string tag;
		int channel;
		int volume;
	};

	struct SoundData
	{
		Mix_Chunk* soundFX;
		std::string tag;
		int channel;
		int volume;
	};

	std::vector<MusicData> _BGMs;
	std::vector<SoundData> _soundFXs;
	int _channelCounterFX, _channelCounterBGM;

	bool FindByTag(std::string tag, SoundData& soundData);
	void UpdateSoundData(SoundData soundData);

	bool FindByTag(std::string tag, MusicData& musicData);
	void UpdateMusicData(MusicData musicData);
};

#endif