#include "Map1FRoom3TreasureBox.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>


Map1FRoom3TreasureBox::Map1FRoom3TreasureBox()
{
}

Map1FRoom3TreasureBox::~Map1FRoom3TreasureBox()
{
}

//맵들의 통로는 오른쪽으로 한 픽셀 지워놓는다 (안그러면 안움직임)

void Map1FRoom3TreasureBox::Start()
{
	SetPosition({ 1536 + 32, 481 + 32 +4128});
	TreasureBoxRenderer_ = CreateRenderer("TreasureBox.bmp"); //64*64 size
}
 
void Map1FRoom3TreasureBox::Update()
{

}
void Map1FRoom3TreasureBox::Render()
{
	//DebugRectRender();

}
