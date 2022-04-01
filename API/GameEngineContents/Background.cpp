#include "Background.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>


Background::Background() 
{
}

Background::~Background() 
{
}

void Background::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	GameEngineRenderer* Renderer_ = CreateRenderer();
	
	//SetScale({ 500,500 });
}
 
void Background::Update()
{

}
void Background::Render()
{
	//DebugRectRender();

}
