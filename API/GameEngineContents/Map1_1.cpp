#include "Map1_1.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>


Map1_1::Map1_1() 
{
}

Map1_1::~Map1_1() 
{
}

void Map1_1::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 512, 237 });
	//�Ʒ����� ���� ���������� �� ������ ���´�
	CreateRenderer("ExMap.bmp");
	//CreateRendererToScale("HPBAR.bmp", float4(100.0f, 20.0f), RenderPivot::CENTER, {0, -100});
}
 
void Map1_1::Update()
{

}
void Map1_1::Render()
{
	//DebugRectRender();

}
