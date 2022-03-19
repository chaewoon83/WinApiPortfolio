#include "UISelectedItem.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>


UISelectedItem::UISelectedItem() 
{
}

UISelectedItem::~UISelectedItem() 
{
}

void UISelectedItem::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 500,500 });
}
 
void UISelectedItem::Update()
{

}
void UISelectedItem::Render()
{
	DebugRectRender();

}
