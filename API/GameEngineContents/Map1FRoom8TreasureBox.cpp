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

//�ʵ��� ��δ� ���������� �� �ȼ� �������´� (�ȱ׷��� �ȿ�����)

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
