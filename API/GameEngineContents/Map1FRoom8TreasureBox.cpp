#include "Map1FRoom8TreasureBox.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>


Map1FRoom8TreasureBox::Map1FRoom8TreasureBox()
{
}

Map1FRoom8TreasureBox::~Map1FRoom8TreasureBox()
{
}

//맵들의 통로는 오른쪽으로 한 픽셀 지워놓는다 (안그러면 안움직임)

void Map1FRoom8TreasureBox::Start()
{
	SetPosition({ 416 + 32, 2336 + 32 });
	TreasureBoxRenderer_ = CreateRenderer("TreasureBox.bmp"); //64*64 size
}
 
void Map1FRoom8TreasureBox::Update()
{

}
void Map1FRoom8TreasureBox::Render()
{
	//DebugRectRender();

}
