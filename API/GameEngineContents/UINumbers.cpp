#include "UINumbers.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

//UIRupee Numbers
//1. coordinate(260, 96) size(28 28)
//1. 274, 110
//2. + 4, +size
//3. + 4, +size
//
//UIBomb Numbers
//1. coordinate(388, 96) size(28 28)
//1. 402, 110
//2. + 4, +size
//3. + 4, +size
//
//UIArrow Numbers
//1. coordinate(484, 96) size(28 28)
//1. 498, 110
//2. + 4, +size
//3. + 4, +size
//
//UIKey Numbers
//1. coordinate(580, 96) size(28 28)
//1. 594, 110
//2. + 4, +size
//3. + 4, +size
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
	//DebugRectRender();

}
