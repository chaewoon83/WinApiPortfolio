#include "TitleNintenPresents.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include "TitleTimeObject.h"


TitleNintenPresents::TitleNintenPresents() 
{
}

TitleNintenPresents::~TitleNintenPresents() 
{
}

void TitleNintenPresents::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	IsNintendoPresentsExist_ = false;
}
 
void TitleNintenPresents::Update()
{
	if (0 < TitleTimeObject::TimeLine_ && 2.5f > TitleTimeObject::TimeLine_)
	{
		if (false == IsNintendoPresentsExist_)
		{
			NintendoPresents_ = CreateRenderer("TitleNintendoPresents.bmp");
			IsNintendoPresentsExist_ = true;
		}

	}

	if (2.5f < TitleTimeObject::TimeLine_)
	{
		if (true == IsNintendoPresentsExist_ && false == IsNintendoPresentsDeath_)
		{
			NintendoPresents_->Death();
			IsNintendoPresentsDeath_ = true;
		}
	}


}

void TitleNintenPresents::Render()
{
	//DebugRectRender();

}
