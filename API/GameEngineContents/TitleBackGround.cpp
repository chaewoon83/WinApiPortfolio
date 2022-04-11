#include "TitleBackGround.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include "TitleTimeObject.h"

TitleBackGround::TitleBackGround() 
	:IsBackGroundExist_(false)
{
}

TitleBackGround::~TitleBackGround() 
{
}

void TitleBackGround::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	CreateRenderer("BlackBackGround.bmp");
	IsBackGroundExist_ = false;
}

void TitleBackGround::Update()
{
	if (14.0f < TitleTimeObject::TimeLine_)
	{
		if (false == IsBackGroundExist_)
		{
			BackGround_ = CreateRenderer("TitleBackGround.bmp");
			IsBackGroundExist_ = true;
		}
	}
}

void TitleBackGround::Render()
{
	//DebugRectRender();

}