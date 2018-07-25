#include "Audio.h"

Audio* Audio::_staticAudio = NULL;

Audio::Audio()
{
	_channelCounterFX = 0;
	_channelCounterBGM = 0;
}

Audio::~Audio()
{
	if(_soundFXs.size() > 0)
	{
		for(unsigned int i = 0; i < _soundFXs.size(); i++)
		{
			Mix_FreeChunk(_soundFXs[i].soundFX);
		}
		_soundFXs.clear();
	}
	
	if(_BGMs.size() > 0)
	{
		for(unsigned int i = 0; i < _BGMs.size(); i++)
		{
			Mix_FreeMusic(_BGMs[i].music);
		}
		_BGMs.clear();
	}
	Mix_CloseAudio();
}

Audio* Audio::GetInstance()
{
	if(_staticAudio == NULL)
	{
		_staticAudio = new Audio();
	}

	return _staticAudio;
}

void Audio::AddSoundFX(std::string filename, std::string tag)
{
	SoundData temp;
	temp.soundFX = Mix_LoadWAV(filename.c_str());
	temp.tag = tag;
	temp.channel = _channelCounterFX++;
	temp.volume = 90;

	_soundFXs.push_back(temp);
}

void Audio::AddMusic(std::string filename, std::string tag)
{
	MusicData temp;
	temp.music = Mix_LoadMUS(filename.c_str());
	temp.tag = tag;
	temp.channel = _channelCounterBGM++;
	//Locked at 70% of max volume as requested my the musician.
	temp.volume = 90;

	_BGMs.push_back(temp);
}

void Audio::SetVolumeAll(int volume)
{
	SetVolumeAllMusic(volume);
	SetVolumeAllSFX(volume);
}

void Audio::SetVolumeAllMusic(int volume)
{
	for (unsigned int i = 0; i < _BGMs.size(); i++)
		_BGMs[i].volume = volume;
}

void Audio::SetVolumeAllSFX(int volume)
{
	for (unsigned int i = 0; i < _soundFXs.size(); i++)
		_soundFXs[i].volume = volume;
}

void Audio::SetVolumeMusic(int volume, std::string tag)
{
	SoundData temp;
	if(FindByTag(tag, temp))
	{
		Mix_VolumeMusic(temp.volume);
		UpdateSoundData(temp);
	}
}

void Audio::SetVolumeSFX(int volume, std::string tag)
{
	SoundData temp;
	if(FindByTag(tag, temp))
	{
		Mix_VolumeChunk(temp.soundFX, volume);
		UpdateSoundData(temp);
	}
}

void Audio::PlayMusic(int loop, std::string tag)
{
	MusicData temp;
	if(FindByTag(tag, temp))
	{
		if(Mix_Playing(temp.channel) == 0)
		{
			Mix_PlayMusic(temp.music, loop);
			Mix_VolumeMusic(temp.volume);
			UpdateMusicData(temp);
		}
	}
}

void Audio::PlaySFX(std::string tag)
{
	SoundData temp;
	if(FindByTag(tag, temp))
	{
		if(Mix_Playing(temp.channel) == 0)
		{
			Mix_PlayChannel(temp.channel, temp.soundFX, 0);
			Mix_VolumeChunk(temp.soundFX, temp.volume);
			UpdateSoundData(temp);
		}
	}
}

void Audio::StopMusic()
{
	Mix_HaltMusic();
}

void Audio::StopSFX(std::string tag)
{
	SoundData temp;
	if(FindByTag(tag, temp))
	{
		Mix_HaltChannel(temp.channel);
		UpdateSoundData(temp);
	}
}

void Audio::StopAll()
{
	Mix_HaltMusic();
	for(unsigned int i = 0; i < _soundFXs.size(); i++)
	{
		Mix_HaltChannel(_soundFXs[i].channel);
	}
}

void Audio::PauseMusic()
{
	Mix_PauseMusic();
}

void Audio::PauseSFX(std::string tag)
{
	SoundData temp;
	if(FindByTag(tag, temp))
	{
		Mix_Pause(temp.channel);
		UpdateSoundData(temp);
	}
}

void Audio::PauseAll()
{
	Mix_PauseMusic();
	for(unsigned int i = 0; i < _soundFXs.size(); i++)
	{
		Mix_Pause(_soundFXs[i].channel);
	}
}

void Audio::UpdateSoundData(SoundData soundData)
{
	if(_soundFXs.size() <= 0)
		return;
	
	SoundData temp;
	temp.soundFX = soundData.soundFX;
	temp.tag = soundData.tag;
	temp.channel = soundData.channel;
	temp.volume = soundData.volume;

	for(unsigned int i = 0; i < _soundFXs.size(); i++)
	{
		if(_soundFXs[i].tag == soundData.tag)
		{
			_soundFXs[i] = temp;
			break;
		}
	}
}

bool Audio::FindByTag(std::string tag, SoundData& soundData)
{
	if(_soundFXs.size() <= 0)
		return false;

	for(unsigned int i = 0; i < _soundFXs.size(); i++)
	{
		SoundData temp = _soundFXs[i];
		if(temp.tag == tag)
		{
			soundData = _soundFXs[i];
			return true;
		}
	}
	return false;
}

void Audio::UpdateMusicData(MusicData musicData)
{
	if(_BGMs.size() <= 0)
		return;
	
	MusicData temp;
	temp.music = musicData.music;
	temp.tag = musicData.tag;
	temp.channel = musicData.channel;
	temp.volume = musicData.volume;

	for(unsigned int i = 0; i < _BGMs.size(); i++)
	{
		if(_BGMs[i].tag == musicData.tag)
		{
			_BGMs[i] = temp;
			break;
		}
	}
}

bool Audio::FindByTag(std::string tag, MusicData& musicData)
{
	if(_BGMs.size() <= 0)
		return false;

	for(unsigned int i = 0; i < _BGMs.size(); i++)
	{
		MusicData temp = _BGMs[i];
		if(temp.tag == tag)
		{
			musicData = _BGMs[i];
			return true;
		}
	}
	return false;
}

void Audio::CleanAll()
{
	StopAll();

	if(_soundFXs.size() > 0)
	{
		for(unsigned int i = 0; i < _soundFXs.size(); i++)
		{
			Mix_FreeChunk(_soundFXs[i].soundFX);
		}
		_soundFXs.clear();
	}
	
	if(_BGMs.size() > 0)
	{
		for(unsigned int i = 0; i < _BGMs.size(); i++)
		{
			Mix_FreeMusic(_BGMs[i].music);
		}
		_BGMs.clear();
	}

	_channelCounterFX = 0;
	_channelCounterBGM = 0;
}