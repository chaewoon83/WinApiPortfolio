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
	//ũ��� 64x64, ��ġ�� 192, 124��
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
