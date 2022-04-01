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
	//아래부터 넣은 렌더러들이 맨 위부터 나온다
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
