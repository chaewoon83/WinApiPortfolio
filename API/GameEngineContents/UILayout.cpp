#include "UILayout.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>


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
	CreateRenderer("UILayout.bmp");
}
 
void UILayout::Update()
{

}
void UILayout::Render()
{
	//DebugRectRender();
}
