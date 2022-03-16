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

}

void TitleLogo::Update()
{

}
void TitleLogo::Render()
{
	Rectangle(GameEngineWindow::GETHDC(), 100, 100, 500, 500);
}
