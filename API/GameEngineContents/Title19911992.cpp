#include "Title19911992.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include "TitleTimeObject.h"

Title19911992::Title19911992() 
	:IsNintendoLogoExist_(false)
{
}

Title19911992::~Title19911992() 
{
}

void Title19911992::Start()
{
	SetPosition({ GameEngineWindow::GetScale().x *0.5f , GameEngineWindow::GetScale().y * 0.85f});
	IsNintendoLogoExist_ = false;
	//SetScale({ 500,500 });
}
 
void Title19911992::Update()
{
	if (3.0f < TitleTimeObject::TimeLine_ )
	{
		if (false == IsNintendoLogoExist_)
		{
			NintendoLogo_ = CreateRenderer("Title19911992.bmp");
			IsNintendoLogoExist_ = true;
		}

	}
}
void Title19911992::Render()
{
	//DebugRectRender();

}
