#include "Map1FBridgeBackGround.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>


Map1FBridgeBackGround::Map1FBridgeBackGround() 
{
}

Map1FBridgeBackGround::~Map1FBridgeBackGround() 
{
}

void Map1FBridgeBackGround::Start()
{
	GameEngineRenderer* Renderer;
	float4 ImagePos = {};
	Renderer = CreateRenderer("EastPalace1F_1_1F_BridgeBackground.bmp");
	//렌더러는  0,0 을 기준으로 중앙에 배치된다 ( 그대로 쓰면 이미지 짤림 )
	//이미지, Rect는 0, 0 을 기준으로 오른쪽 아래에 배치된다
	ImagePos.x = (Renderer->GetImage()->GetScale().Half().x);
	ImagePos.y = (Renderer->GetImage()->GetScale().Half().y + + 4128.0f);
	Renderer->SetPivot(ImagePos);
}
 
void Map1FBridgeBackGround::Update()
{

}
void Map1FBridgeBackGround::Render()
{
	DebugRectRender();

}
