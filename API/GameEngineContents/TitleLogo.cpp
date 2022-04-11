#include "TitleLogo.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include "TitleTimeObject.h"

TitleLogo::TitleLogo() 
	:IsTitleLogoExist_(false)
{
}

TitleLogo::~TitleLogo() 
{
}

void TitleLogo::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	IsTitleLogoExist_ = false;
	//CreateRenderer("TitleLogo.bmp");
}
 
void TitleLogo::Update()
{
	if (11.7f < TitleTimeObject::TimeLine_)
	{
		if (false == IsTitleLogoExist_)
		{
			TitleLogo_ = CreateRenderer("TitleLogo.bmp");
			IsTitleLogoExist_ = true;
		}

	}
}
void TitleLogo::Render()
{
	//DebugRectRender();

}
