#include "Map1FRoom4TreasureBox.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>


Map1FRoom4TreasureBox::Map1FRoom4TreasureBox()
{
}

Map1FRoom4TreasureBox::~Map1FRoom4TreasureBox()
{
}

//�ʵ��� ��δ� ���������� �� �ȼ� �������´� (�ȱ׷��� �ȿ�����)

void Map1FRoom4TreasureBox::Start()
{
	SetPosition({ 3649 + 32, 1120 + 32 + 4128});
	TreasureBoxRenderer_ = CreateRenderer("TreasureBox.bmp"); //64*64 size
}
 
void Map1FRoom4TreasureBox::Update()
{

}
void Map1FRoom4TreasureBox::Render()
{
	//DebugRectRender();

}
