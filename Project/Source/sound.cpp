#include "sound.h"

#include "../Library/resourceLoader.h"

Sound::Sound()
{
	soundHandle[SOUND::START] = ResourceLoader::LoadSoundMem("data\\Sound\\start_sound.wav");
	soundHandle[SOUND::ATTACK] = ResourceLoader::LoadSoundMem("data\\Sound\\attack_Sound.wav");
	soundHandle[SOUND::ATTACKHIT_01] = ResourceLoader::LoadSoundMem("data\\Sound\\magicHit_Sound_1.wav");
	soundHandle[SOUND::ATTACKHIT_02] = ResourceLoader::LoadSoundMem("data\\Sound\\magicHit_Sound_2.wav");
	soundHandle[SOUND::ATTACKPLASMA] = ResourceLoader::LoadSoundMem("data\\Sound\\magicHitPlasma_Sound.mp3");
	soundHandle[SOUND::BOSSATTACK] = ResourceLoader::LoadSoundMem("data\\Sound\\bossAttack_Sound.wav");
	soundHandle[SOUND::CLOUD] = ResourceLoader::LoadSoundMem("data\\Sound\\cloud_Sound.wav");
	soundHandle[SOUND::DARKNESS] = ResourceLoader::LoadSoundMem("data\\Sound\\darkness_Sound.wav");
	soundHandle[SOUND::INVERSION] = ResourceLoader::LoadSoundMem("data\\Sound\\inversion_Sound.wav");
	soundHandle[SOUND::FIRST_VOICE] = ResourceLoader::LoadSoundMem("data\\Sound\\bossVoiceFirst_Sound.wav");
	soundHandle[SOUND::END_VOICE] = ResourceLoader::LoadSoundMem("data\\Sound\\bossVoiceEnd_Sound.wav");
	soundHandle[SOUND::BOSS_DOWN] = ResourceLoader::LoadSoundMem("data\\Sound\\bossDown_Sound.wav");
	soundHandle[SOUND::GAME_CLEAR] = ResourceLoader::LoadSoundMem("data\\Sound\\gameClear_Sound.mp3");
	

	BGMHandle[BGM::TITLE] = ResourceLoader::LoadSoundMem("data\\Sound\\Title_BGM.wav");
	BGMHandle[BGM::PLAY] = ResourceLoader::LoadSoundMem("data\\Sound\\Play_BGM.wav");
	BGMHandle[BGM::RESULT] = ResourceLoader::LoadSoundMem("data\\Sound\\Title_BGM.wav");
}

Sound::~Sound()
{
	for (int i = 0; i < SOUND::SOUND_MAX; i++)
	{
		if (soundHandle[i] != -1)
		{
			DeleteSoundMem(soundHandle[i]);
			soundHandle[i] = -1;
		}
	}

	for (int i = 0; i < BGM::BGM_MAX; i++)
	{
		if (BGMHandle[i] != -1)
		{
			DeleteSoundMem(BGMHandle[i]);
			BGMHandle[i] = -1;
		}
	}
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
