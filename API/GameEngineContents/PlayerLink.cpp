#include "PlayerLink.h"
#include <windows.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>


PlayerLink::PlayerLink() 
{
}

PlayerLink::~PlayerLink() 
{
}

void PlayerLink::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 200, 200 });
	//아래부터 넣은 렌더러들이 맨 위부터 나온다
	CreateRenderer("LinkStandStill.bmp");
	//CreateRendererToScale("HPBAR.bmp", float4(100.0f, 20.0f), RenderPivot::CENTER, {0, -100});
}
 
void PlayerLink::Update()
{

}
//렌더러가 다 돌고 액터들의 랜더함수를 호출한다
void PlayerLink::Render()
{
	//GameEngineImage* FindImage = GameEngineImageManager::GetInst()->Find("Idle.bmp");
	//if (nullptr == FindImage)
	//{
	//	MsgBoxAssert("이미지 렌더링 과정에서 이미지를 찾지 못했습니다");
	//}
	//GameEngine::BackBufferImage()->BitCopyBot(FindImage, GetPosition());

}
