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

//�ʵ��� ��δ� ���������� �� �ȼ� �������´� (�ȱ׷��� �ȿ�����)

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
