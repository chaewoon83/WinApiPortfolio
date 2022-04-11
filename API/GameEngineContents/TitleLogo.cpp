#include "TitleLogo.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>


TitleLogo::TitleLogo() 
{
}

TitleLogo::~TitleLogo() 
{
}

void TitleLogo::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	CreateRenderer("TitleLogo.bmp");
}
 
void TitleLogo::Update()
{

}
void TitleLogo::Render()
{
	//DebugRectRender();

}
