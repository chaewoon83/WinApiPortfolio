#include "UIHeart.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>


UIHeart::UIHeart() 
{
}

UIHeart::~UIHeart() 
{
}

void UIHeart::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 500,500 });
}
 
void UIHeart::Update()
{

}
void UIHeart::Render()
{
	DebugRectRender();

}
