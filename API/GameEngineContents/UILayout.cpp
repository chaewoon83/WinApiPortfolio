#include "UILayout.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

UILayout::UILayout() 
{
}

UILayout::~UILayout() 
{
}

void UILayout::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 1024, 896 });
	//�Ʒ����� ���� ���������� �� ������ ���´�
	GameEngineRenderer* Renderer = CreateRenderer("UILayout.bmp");
	Renderer->CameraEffectOff();
}
 
void UILayout::Update()
{

}
void UILayout::Render()
{
	//DebugRectRender();
}
