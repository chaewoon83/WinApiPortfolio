#include "TitleTwinkle.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include "TitleTimeObject.h"

TitleTwinkle::TitleTwinkle() 
	:TwinklePos1_({GameEngineWindow::GetScale().Half().x + 245, GameEngineWindow::GetScale().Half().y + 91}),
	 TwinklePos2_({ GameEngineWindow::GetScale().Half().x + 77, GameEngineWindow::GetScale().Half().y -72}),
	 TwinklePos3_({ GameEngineWindow::GetScale().Half().x -91, GameEngineWindow::GetScale().Half().y + 83 }),
	 TwinklePos4_({ GameEngineWindow::GetScale().Half().x -323, GameEngineWindow::GetScale().Half().y -68 }),
	 CurrentTwinkle_(0)
{
}

TitleTwinkle::~TitleTwinkle() 
{
}

void TitleTwinkle::Start()
{
	SetPosition({0,0});

}
 
void TitleTwinkle::Update()
{


	if (true == IsTwinkleExist_)
	{
		if (1 == CurrentTwinkle_ && Twinkle1_->IsEndAnimation())
		{
			Twinkle1_->SetPivot(TwinklePos2_);
			CurrentTwinkle_ = 2;
		}

		else if (2 == CurrentTwinkle_ && Twinkle1_->IsEndAnimation())
		{
			Twinkle1_->SetPivot(TwinklePos3_);
			CurrentTwinkle_ = 3;
		}

		else if (3 == CurrentTwinkle_ && Twinkle1_->IsEndAnimation())
		{
			Twinkle1_->SetPivot(TwinklePos4_);
			CurrentTwinkle_ = 4;
		}

		else if (4 == CurrentTwinkle_ && Twinkle1_->IsEndAnimation())
		{
			Twinkle1_->SetPivot(TwinklePos1_);
			CurrentTwinkle_ = 1;
		}
	}

	if (13 < TitleTimeObject::TimeLine_ && false == IsTwinkleExist_)
	{
		Twinkle1_ = CreateRenderer();
		Twinkle1_->SetPivot(TwinklePos1_);
		Twinkle1_->CreateAnimation("TitleTwinkle.bmp", "Twinkle1", 0, 10, 0.05f, true);
		Twinkle1_->ChangeAnimation("Twinkle1");
		IsTwinkleExist_ = true;
		CurrentTwinkle_ = 1;
	}

}
void TitleTwinkle::Render()
{
	//DebugRectRender();

}
