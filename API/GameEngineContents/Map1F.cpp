#include "Map1F.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>


Map1F::Map1F() 
{
}

Map1F::~Map1F() 
{
}

void Map1F::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half()*4);
	//�Ʒ����� ���� ���������� �� ������ ���´�
	CreateRenderer("EastPalace1F.bmp");
	//CreateRendererToScale("HPBAR.bmp", float4(100.0f, 20.0f), RenderPivot::CENTER, {0, -100});
}
 
void Map1F::Update()
{

}
void Map1F::Render()
{
	DebugRectRender();

}
