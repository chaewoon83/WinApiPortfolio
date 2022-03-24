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
	//크기는 64x64, 위치는 192, 124다
	SetPosition({192, 124});
	SetScale({64, 64});
}
 
void UISelectedItem::Update()
{

}
void UISelectedItem::Render()
{
	//DebugRectRender();

}
