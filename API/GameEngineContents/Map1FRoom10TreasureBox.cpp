#include "Map1FRoom10TreasureBox.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>


Map1FRoom10TreasureBox::Map1FRoom10TreasureBox()
{
}

Map1FRoom10TreasureBox::~Map1FRoom10TreasureBox()
{
}

//맵들의 통로는 오른쪽으로 한 픽셀 지워놓는다 (안그러면 안움직임)

void Map1FRoom10TreasureBox::Start()
{

	SetPosition({ 3008 + 64, 2880 + 48 });
	TreasureBoxRenderer_ = CreateRenderer("BigTreasureBox.bmp"); //128 96
}

void Map1FRoom10TreasureBox::Update()
{

}
void Map1FRoom10TreasureBox::Render()
{
	//DebugRectRender();

}
