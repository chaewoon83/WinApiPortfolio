#include "UINumbers.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>


UINumbers::UINumbers() 
{
}

UINumbers::~UINumbers() 
{
}

void UINumbers::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 500,500 });
}
 
void UINumbers::Update()
{

}
void UINumbers::Render()
{
	DebugRectRender();

}
