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
	SetScale({ 500,500 });
}
 
void TitleLogo::Update()
{

}
void TitleLogo::Render()
{
	DebugRectRender();

}
