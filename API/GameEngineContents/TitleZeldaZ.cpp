#include "TitleZeldaZ.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include "TitleTimeObject.h"

TitleZeldaZ::TitleZeldaZ() 
{
}

TitleZeldaZ::~TitleZeldaZ() 
{
}

void TitleZeldaZ::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	IsTitleZeldaZExist_ = false;
}
 
void TitleZeldaZ::Update()
{
	if (11.7f < TitleTimeObject::TimeLine_)
	{
		if (false == IsTitleZeldaZExist_)
		{
			TitleZeldaZ_ = CreateRenderer("TitleZeldaZ.bmp");
			IsTitleZeldaZExist_ = true;
		}

	}
}
void TitleZeldaZ::Render()
{
	//DebugRectRender();

}
