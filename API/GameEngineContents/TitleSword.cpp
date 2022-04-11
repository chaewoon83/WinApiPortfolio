#include "TitleSword.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include "TitleTimeObject.h"

//Sword Pos, x = Center-262, y = Cneter

TitleSword::TitleSword()
	:IsSwordExist_(false)
{
}

TitleSword::~TitleSword() 
{
}

void TitleSword::Start()
{
	SetPosition({ GameEngineWindow::GetScale().Half().x - 262.0f , 0});
	IsSwordExist_ = false;
	SwordPos_ = { 512, 0 };
}
 
void TitleSword::Update()
{
	if (13 < TitleTimeObject::TimeLine_ && false == IsSwordExist_)
	{
		Sword_ = CreateRenderer("TitleSword.bmp");

		IsSwordExist_ = true;
	}

	if (13 < TitleTimeObject::TimeLine_ && 13.125 > TitleTimeObject::TimeLine_)
	{
		if (true == IsSwordExist_)
		{
			SetMove({0 , GameEngineTime::GetDeltaTime() * 896 * 4});
		}
	}
}
void TitleSword::Render()
{
	//DebugRectRender();

}
