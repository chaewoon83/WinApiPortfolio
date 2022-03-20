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
	SetPosition({300, 100});
	SetScale({ 100,100 });
}
 
void UISelectedItem::Update()
{

}
void UISelectedItem::Render()
{
	DebugRectRender();

}
