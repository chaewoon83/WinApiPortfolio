#include "TitleTriangle.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>


TitleTriangle::TitleTriangle() 
{
}

TitleTriangle::~TitleTriangle() 
{
}

//64*64크기 
//위 패딩 44
//아래패딩 48
//좌우 패딩 8

void TitleTriangle::Start()
{
	SetPosition({ 0,0 });
	GameEngineRenderer* TopTriangle = CreateRenderer();
	TopTriangle->SetPivot(GameEngineWindow::GetScale().Half() + float4{0, ( - 32 * 2) - 22 + 8});
	TopTriangle->CreateAnimation("trianglebmp.bmp", "TopTriangle", 0, 169, 0.035f, false);
	TopTriangle->ChangeAnimation("TopTriangle");

	GameEngineRenderer* BotLeftTriangle = CreateRenderer();
	BotLeftTriangle->SetPivot(GameEngineWindow::GetScale().Half() + float4{ ( - 32 * 2 )- 16, (+ 32 * 2) + 22});
	BotLeftTriangle->CreateAnimation("trianglebmp.bmp", "BotTriangle1", 0, 169, 0.035f, false);
	BotLeftTriangle->ChangeAnimation("BotTriangle1");

	GameEngineRenderer* BotRightTriangle = CreateRenderer();
	BotRightTriangle->SetPivot(GameEngineWindow::GetScale().Half() + float4{ ( + 32 * 2) + 16, ( + 32 * 2) + 22});
	BotRightTriangle->CreateAnimation("trianglebmp.bmp", "BotTriangle1", 0, 169, 0.035f, false);
	BotRightTriangle->ChangeAnimation("BotTriangle1");

}
 
void TitleTriangle::Update()
{

}
void TitleTriangle::Render()
{

}
