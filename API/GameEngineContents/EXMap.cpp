#include "EXMap.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>


EXMap::EXMap() 
{
}

EXMap::~EXMap() 
{
}
 // y 7200

void EXMap::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	//SetScale(GameEngineWindow::GetScale());
	GameEngineRenderer* Renderer;
	//SetScale({ 600, 600 });
	float4 ImagePos = {};
	Renderer = CreateRenderer("ExMapColMap.bmp");
	//렌더러는  0,0 을 기준으로 중앙에 배치된다 ( 그대로 쓰면 이미지 짤림 )
	//이미지, Rect는 0, 0 을 기준으로 오른쪽 아래에 배치된다
	ImagePos.x = (Renderer->GetImage()->GetScale().Half().x - GameEngineWindow::GetScale().Half().x);
	ImagePos.y = (Renderer->GetImage()->GetScale().Half().y - GameEngineWindow::GetScale().Half().y);
	Renderer->SetPivot(ImagePos);
}
 
void EXMap::Update()
{

}
void EXMap::Render()
{
	//DebugRectRender();

}
