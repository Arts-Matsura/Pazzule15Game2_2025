#include "sound.h"

#include "../Library/resourceLoader.h"

Sound::Sound()
{
	soundHandle[SOUND::START] = ResourceLoader::LoadSoundMem("data\\Sound\\start_sound.wav");
	soundHandle[SOUND::ATTACK] = ResourceLoader::LoadSoundMem("");

	BGMHandle[BGM::TITLE] = ResourceLoader::LoadSoundMem("data\\Sound\\Title_BGM.wav");
	BGMHandle[BGM::PLAY] = ResourceLoader::LoadSoundMem("data\\Sound\\Play_BGM.wav");
	BGMHandle[BGM::RESULT] = ResourceLoader::LoadSoundMem("data\\Sound\\Title_BGM.wav");
}

Sound::~Sound()
{
}

void Sound::Update()
{
}

void Sound::SetPlaySound(SOUND sound, int volume)
{
	if (sound != SOUND::SOUND_MAX)
	{
		PlaySoundMem(soundHandle[sound], DX_PLAYTYPE_BACK);
		SetVolumeSoundMem(volume, soundHandle[sound]);
	}
}

void Sound::SetPlayBGM(BGM bgm, int volume)
{
	if (bgm != BGM::BGM_MAX)
	{
		PlaySoundMem(BGMHandle[bgm], DX_PLAYTYPE_LOOP);
		SetVolumeSoundMem(volume, BGMHandle[bgm]);
	}
}

void Sound::StopPlayBGM()
{
	for (int i = 0; i < BGM::BGM_MAX; i++)
		StopSoundMem(BGMHandle[i]);
}
