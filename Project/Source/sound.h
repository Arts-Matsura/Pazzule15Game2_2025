#pragma once
#include "../Library/gameObject.h"

class Sound :public GameObject {
public:
	Sound();
	~Sound();
	void Update()override;

	enum BGM {
		TITLE = 0,
		PLAY,
		RESULT,
		BGM_MAX
	};

	enum SOUND {
		START = 0,
		ATTACK,
		SOUND_MAX
	};

	void SetPlaySound(SOUND sound, int volume);
	void SetPlayBGM(BGM bgm, int  volume);
	void StopPlayBGM();
private:
	int BGMHandle[BGM_MAX];
	int soundHandle[SOUND_MAX];
};