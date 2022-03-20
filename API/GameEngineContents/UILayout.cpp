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
	SetScale(GameEngineWindow::GetScale());
}
 
void UILayout::Update()
{

}
void UILayout::Render()
{
	DebugRectRender();
}
