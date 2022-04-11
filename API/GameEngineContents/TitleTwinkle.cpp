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
			Twinkle1_->ChangeAnimation("Twinkle2");
			CurrentTwinkle_ = 2;
			return;
		}

		else if (2 == CurrentTwinkle_ && Twinkle1_->IsEndAnimation())
		{
			Twinkle1_->SetPivot(TwinklePos3_);
			Twinkle1_->ChangeAnimation("Twinkle3");
			CurrentTwinkle_ = 3;
			return;

		}

		else if (3 == CurrentTwinkle_ && Twinkle1_->IsEndAnimation())
		{
			Twinkle1_->SetPivot(TwinklePos4_);
			Twinkle1_->ChangeAnimation("Twinkle4");
			CurrentTwinkle_ = 4;
			return;
		}

		else if (4 == CurrentTwinkle_ && Twinkle1_->IsEndAnimation())
		{
			Twinkle1_->SetPivot(TwinklePos1_);
			Twinkle1_->ChangeAnimation("Twinkle1");
			CurrentTwinkle_ = 1;
			return;
		}
	}

	if (13 < TitleTimeObject::TimeLine_ && false == IsTwinkleExist_)
	{
		Twinkle1_ = CreateRenderer();
		Twinkle1_->SetPivot(TwinklePos1_);
		Twinkle1_->CreateAnimation("TitleTwinkle.bmp", "Twinkle1", 0, 8, 0.1f, false);
		Twinkle1_->CreateAnimation("TitleTwinkle.bmp", "Twinkle2", 0, 8, 0.1f, false);
		Twinkle1_->CreateAnimation("TitleTwinkle.bmp", "Twinkle3", 0, 8, 0.1f, false);
		Twinkle1_->CreateAnimation("TitleTwinkle.bmp", "Twinkle4", 0, 8, 0.1f, false);
		Twinkle1_->ChangeAnimation("Twinkle1");
		IsTwinkleExist_ = true;
		CurrentTwinkle_ = 1;
	}

}
void TitleTwinkle::Render()
{
	//DebugRectRender();

}
