#include "Map1FBridge.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>

Map1FBridge* Map1FBridge::Inst_ = nullptr;

Map1FBridge::Map1FBridge() 
{
}

Map1FBridge::~Map1FBridge() 
{
}

//맵들의 통로는 오른쪽으로 한 픽셀 지워놓는다 (안그러면 안움직임)

void Map1FBridge::Start()
{

	//SetPosition(GameEngineWindow::GetScale().Half()*4);
	//아래부터 넣은 렌더러들이 맨 위부터 나온다
	//CreateRendererToScale("HPBAR.bmp", float4(100.0f, 20.0f), RenderPivot::CENTER, {0, -100});
	float4 ImagePos = {};
	Renderer_1_ = CreateRenderer("EastPalace1F_2_1F_Bridge.bmp");
	//렌더러는  0,0 을 기준으로 중앙에 배치된다 ( 그대로 쓰면 이미지 짤림 )
	//이미지, Rect는 0, 0 을 기준으로 오른쪽 아래에 배치된다
	ImagePos.x = (Renderer_1_->GetImage()->GetScale().Half().x);
	ImagePos.y = (Renderer_1_->GetImage()->GetScale().Half().y);
	Renderer_1_->SetPivot(ImagePos);

	ImagePos = {};
	Renderer_2_ = CreateRenderer("EastPalace1F_1_1F_Bridge.bmp");
	//렌더러는  0,0 을 기준으로 중앙에 배치된다 ( 그대로 쓰면 이미지 짤림 )
	//이미지, Rect는 0, 0 을 기준으로 오른쪽 아래에 배치된다
	ImagePos.x = (Renderer_2_->GetImage()->GetScale().Half().x);
	ImagePos.y = (Renderer_2_->GetImage()->GetScale().Half().y + 4129.0f);
	Renderer_2_->SetPivot(ImagePos);
	Inst_ = this;
}
 
void Map1FBridge::Update()
{
}
void Map1FBridge::Render()
{
	//DebugRectRender();

}
