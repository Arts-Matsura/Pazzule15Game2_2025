#include "sentence.h"

namespace {
	std::string BOSS_NAMES[] = {"炎獄の魔王 エンジャーク",
								"漆黒の邪神 ハセガーワT",
								"氷結の蒼龍 ゼロクリス",
								"龍王 グレンドラゴ",
								"超神龍 オーバーワールド" };
}




Sentence::Sentence(int num)
{
	charCount = 0;
	frame = 0;
	byte = 0;

	isAction = true;

	nowPos = Vector2(880, 650);
	nextPos = Vector2(900, 650);

	bossName = BOSS_NAMES[num - 1].c_str();

	nowSentence =  "";
	nextSentence = bossName + "があらわれた！！";

	fontHandle = CreateFontToHandle(
		"KHドット道玄坂16", // フォント名
		32,               // サイズ
		3                 // 太さ
	);

	state = STATE::NEXT_START;
}

Sentence::~Sentence()
{
}


int GetCharBytes(unsigned char c)
{
	// UTF-8 の先頭バイト判定
	if ((c & 0x80) == 0x00) return 1;      // 0xxxxxxx (ASCII)
	if ((c & 0xE0) == 0xC0) return 2;      // 110xxxxx
	if ((c & 0xF0) == 0xE0) return 3;      // 1110xxxx (日本語)
	if ((c & 0xF8) == 0xF0) return 4;      // 11110xxx
	return 1;
}

void Sentence::Update()
{
	if (!isAction)
		return;


	std::string drawText = "";


	switch (state)
	{
	case Sentence::NOW_UP:
		nowPos.y -= 8.0f;
		if (nowPos.y < 450)
		{
			nowPos.y = 650;
			nowSentence = "";
			state = STATE::NEXT_START;
		}
		break;
	case Sentence::NEXT_START:

		frame++;
		if (frame % 3 == 0)
		{
			if (byte < nextSentence.size())
			{
				byte += GetCharBytes(
					static_cast<unsigned char>(nextSentence[byte])
				);
			}
			else
			{
				// ★ 全文字表示完了
				//nextSentence.clear();   // empty() 状態にする
				state = STATE::NOW_CHANGE; // 次の状態へ
			}
		}

		// charCount文字分だけ切り出す
		nowSentence = nextSentence.substr(0, byte);

		break;
	case Sentence::NOW_CHANGE:
		break;
	}
}

void Sentence::Draw()
{
	//nowを上に持ち上げて
	//nextを一文字ずつ描画
	//全て描画したらnextをnowに代入しnextとisActionを初期化

	/*DrawStringToHandle(
		nextPos.x, nextPos.y,
		nextSentence.c_str(),
		GetColor(255, 255, 255),
		fontHandle
	);*/
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(850, 600, 1550, 800, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawBox(850, 600, 1550, 800, GetColor(255, 255, 255), FALSE);

	DrawStringToHandle(
		nowPos.x, 650,
		nowSentence.c_str(),
		GetColor(255, 255, 255),
		fontHandle
	);
}

void Sentence::SetNextSentence(std::string next)
{
	if (state != STATE::NOW_CHANGE)
		return;

	state = STATE::NOW_UP;
	nextSentence = next;
	isAction = true;
	frame = 0;
	byte = 0;
}
