#include "back.h"
#include "../Library/resourceLoader.h"
#include "Screen.h"

#include "boss.h"

Back::Back()
{
	bookimage = ResourceLoader::LoadGraph("data\\2D\\book.png");
	bookbackimage = ResourceLoader::LoadGraph("data\\2D\\leftback.png");
	boximage = ResourceLoader::LoadGraph("data\\2D\\box.png");
	backbackimage = ResourceLoader::LoadGraph("data\\2D\\gameback.png");
}

Back::~Back()
{
}

void Back::Update()
{
}

void Back::Draw()
{
	DrawRectRotaGraph(Screen::WIDTH / 2, Screen::HEIGHT / 2, 0, 0, 1280, 720, 2.0f, 0.0f, backbackimage, true);
	
	DrawRectRotaGraph(200, 450, 0, 0, 1024, 732, 1.3f * FindGameObject<Boss>()->InversionLevel(), 0.0f, bookbackimage, true);
	DrawRectRotaGraph(390, 450, 0, 0, 788, 900, 1.05f * FindGameObject<Boss>()->InversionLevel(), 0.0f, bookimage, true);
	DrawRectRotaGraph(FindGameObject<Boss>()->CenterPosition().x, FindGameObject<Boss>()->CenterPosition().y, 0, 0, 504, 504, 1.2f * FindGameObject<Boss>()->InversionLevel(), 0.0f, boximage, true);
}
