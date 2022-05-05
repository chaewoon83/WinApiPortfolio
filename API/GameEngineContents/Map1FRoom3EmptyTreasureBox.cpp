#include "Map1FRoom3EmptyTreasureBox.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>


Map1FRoom3EmptyTreasureBox::Map1FRoom3EmptyTreasureBox()
{
}

Map1FRoom3EmptyTreasureBox::~Map1FRoom3EmptyTreasureBox()
{
}

//맵들의 통로는 오른쪽으로 한 픽셀 지워놓는다 (안그러면 안움직임)

void Map1FRoom3EmptyTreasureBox::Start()
{
	SetPosition({ 1536 + 32, 481 + 32 +4128});
	TreasureBoxRenderer_ = CreateRenderer("EmptyTreasureBox.bmp"); //64*64 size
	CreateCollision("Block", { 64, 64 });
}
 
void Map1FRoom3EmptyTreasureBox::Update()
{

}
void Map1FRoom3EmptyTreasureBox::Render()
{
	//DebugRectRender();

}
