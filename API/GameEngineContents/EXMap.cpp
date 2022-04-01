#include "EXMap.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>


EXMap::EXMap() 
{
}

EXMap::~EXMap() 
{
}
 // y 7200

void EXMap::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	//SetScale(GameEngineWindow::GetScale());
	GameEngineRenderer* Renderer;
	//SetScale({ 600, 600 });
	float4 ImagePos = {};
	Renderer = CreateRenderer("ExMapColMap.bmp");
	//��������  0,0 �� �������� �߾ӿ� ��ġ�ȴ� ( �״�� ���� �̹��� ©�� )
	//�̹���, Rect�� 0, 0 �� �������� ������ �Ʒ��� ��ġ�ȴ�
	ImagePos.x = (Renderer->GetImage()->GetScale().Half().x - GameEngineWindow::GetScale().Half().x);
	ImagePos.y = (Renderer->GetImage()->GetScale().Half().y - GameEngineWindow::GetScale().Half().y);
	Renderer->SetPivot(ImagePos);
}
 
void EXMap::Update()
{

}
void EXMap::Render()
{
	//DebugRectRender();

}
