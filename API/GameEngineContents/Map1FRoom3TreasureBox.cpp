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

//�ʵ��� ��δ� ���������� �� �ȼ� �������´� (�ȱ׷��� �ȿ�����)

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
