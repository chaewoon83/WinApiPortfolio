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
	//�Ʒ����� ���� ���������� �� ������ ���´�
	CreateRenderer("UILayout.bmp");
}
 
void UILayout::Update()
{

}
void UILayout::Render()
{
	//DebugRectRender();
}
