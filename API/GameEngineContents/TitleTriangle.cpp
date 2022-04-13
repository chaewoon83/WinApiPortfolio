#include "TitleTriangle.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include "TitleTimeObject.h"


TitleTriangle::TitleTriangle() 
{
}

TitleTriangle::~TitleTriangle() 
{
}
// 1024 : 896
//64*64크기 
//위 패딩 44
//아래패딩 48
//좌우 패딩 8

// TopTriangle -> GameEngineWindow::GetScale().Half() + float4{0, ( - 32 * 2) - 22 + 8}
// start(512, 0)
// end(512, 370)
// speed(92.5, 0)
//BotRightTriangle->SetPivot(GameEngineWindow::GetScale().Half() + float4{ (+32 * 2) + 16, (+32 * 2) + 22 });
// (1024, 896)
// (592, 524)
// (108, -93)
//BotLeftTriangle->SetPivot(GameEngineWindow::GetScale().Half() + float4{ ( - 32 * 2 )- 16, (+ 32 * 2) + 22});
// (0, 896)
// (432, 524)
// (148, 93)

void TitleTriangle::Start()
{
	IsTriangleExist_ = false;
	TopTrianglePos_ = {512, 0};
	BotRightTrianglePos_ = {1024, 896};
	BotLeftTrianglePos_ = {0, 896};
	SetPosition({ 0,0 });

}
 
void TitleTriangle::Update()
{
	if (5 < TitleTimeObject::TimeLine_ && false == IsTriangleExist_)
	{
		TopTriangle = CreateRenderer();
		TopTriangle->SetPivot(TopTrianglePos_);
		TopTriangle->CreateAnimation("trianglebmp.bmp", "TopTriangle", 0, 169, 0.035f, false);
		TopTriangle->ChangeAnimation("TopTriangle");

		BotRightTriangle = CreateRenderer();
		BotRightTriangle->SetPivot(BotLeftTrianglePos_);
		BotRightTriangle->CreateAnimation("trianglebmp.bmp", "BotRightTriangle", 0, 169, 0.035f, false);
		BotRightTriangle->ChangeAnimation("BotRightTriangle");

		BotLeftTriangle = CreateRenderer();
		BotLeftTriangle->SetPivot(BotRightTrianglePos_);
		BotLeftTriangle->CreateAnimation("trianglebmp.bmp", "BotLeftTriangle", 0, 169, 0.035f, false);
		BotLeftTriangle->ChangeAnimation("BotLeftTriangle");

		IsTriangleExist_ = true;
	}

	if (5 < TitleTimeObject::TimeLine_ && 9 > TitleTimeObject::TimeLine_)
	{
		if (true == IsTriangleExist_)
		{
			SetRenderMove(TopTrianglePos_, { 0, 92.5f * GameEngineTime::GetDeltaTime()});
			TopTriangle->SetPivot(TopTrianglePos_);

			SetRenderMove(BotRightTrianglePos_, { -108.0f * GameEngineTime::GetDeltaTime(), -93.0f * GameEngineTime::GetDeltaTime()});
			BotRightTriangle->SetPivot(BotRightTrianglePos_);

			SetRenderMove(BotLeftTrianglePos_, { 108.0f * GameEngineTime::GetDeltaTime(), -93.0f * GameEngineTime::GetDeltaTime() });
			BotLeftTriangle->SetPivot(BotLeftTrianglePos_);
		}
	}

	if (12.5f < TitleTimeObject::TimeLine_)
	{
		if (true == IsTriangleExist_ && false == IsTriangleDeath_)
		{
			TopTriangle->Death();
			BotRightTriangle->Death();
			BotLeftTriangle->Death();
			IsTriangleDeath_ = true;
		}
	}

}
void TitleTriangle::Render()
{

}


