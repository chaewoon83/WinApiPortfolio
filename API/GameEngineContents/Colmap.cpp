#include "Colmap.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineInput.h>
#include "PlayerLink.h"
#include "Map1FRoof.h"
#include "Map1FBridge.h"
#include "Map1FBridgeBackGround.h"


Colmap::Colmap()
	: IsDeugModeOn_(false)
	, IsIn1F_(true)
{
}

Colmap::~Colmap() 
{
}

void Colmap::Start()
{
	Map1F_1_Renderer_ = CreateRenderer();
	Map1F_1_Renderer_->CreateAnimation("EastPalace1F_1_1F_ColMap.bmp", "1F", 0, 0, 1.0f, false);
	Map1F_1_Renderer_->CreateAnimation("EastPalace1F_1_B1F_ColMap.bmp", "B1F", 0, 0, 1.0f, false);
	Map1F_1_Renderer_->ChangeAnimation("1F");
	Map1F_1_Renderer_->Off();
	float4 ImagePos = {};
	float4 Map1FSize = float4{ 6144, 4064 };
	//렌더러는  0,0 을 기준으로 중앙에 배치된다 ( 그대로 쓰면 이미지 짤림 )
	//이미지, Rect는 0, 0 을 기준으로 오른쪽 아래에 배치된다
	ImagePos.x = (Map1FSize.Half().x);
	ImagePos.y = (Map1FSize.Half().y + 4128.0f);
	Map1F_1_Renderer_->SetPivot(ImagePos);

	float4 Map1F_2Size = { 6144, 4128 };
	Map1F_2_Renderer_ = CreateRenderer();
	Map1F_2_Renderer_->CreateAnimation("EastPalace1F_2_1F_ColMap.bmp", "1F", 0, 0, 1.0f, false);
	Map1F_2_Renderer_->CreateAnimation("EastPalace1F_2_B1F_ColMap.bmp", "B1F", 0, 0, 1.0f, false);
	Map1F_2_Renderer_->ChangeAnimation("1F");
	Map1F_2_Renderer_->Off();
	ImagePos = {};
	ImagePos.x = (Map1F_2Size.Half().x);
	ImagePos.y = (Map1F_2Size.Half().y);
	Map1F_2_Renderer_->SetPivot(ImagePos);

	GameEngineInput::GetInst()->CreateKey("DebugMode", '8');
}
 
void Colmap::Update()
{
	if (GameEngineInput::GetInst()->IsDown("DebugMode"))
	{
		if (false == IsDeugModeOn_)
		{
			IsDeugModeOn_ = true;
			Map1F_1_Renderer_->On();
			Map1F_2_Renderer_->On();
			Map1FRoof::GetInst()->Off();
			//Map1FBridge::GetInst()->Off();
			Map1FBridgeBackGround::GetInst()->Off();
		}
		else
		{
			IsDeugModeOn_ = false;
			Map1F_1_Renderer_->Off();
			Map1F_2_Renderer_->Off();
			Map1FRoof::GetInst()->On();
			//Map1FBridge::GetInst()->On();
			Map1FBridgeBackGround::GetInst()->On();
		}
	}

	if (PlayerStairsState::Top == PlayerLink::GetPlayerStairsState())
	{
		Map1F_1_Renderer_->ChangeAnimation("1F");
		Map1F_2_Renderer_->ChangeAnimation("1F");
		//Map1FBridge::GetInst()->On();

	}
	else if (PlayerStairsState::Bot == PlayerLink::GetPlayerStairsState())
	{
		Map1F_1_Renderer_->ChangeAnimation("B1F");
		Map1F_2_Renderer_->ChangeAnimation("B1F");
		//Map1FBridge::GetInst()->Off();
	}

}
void Colmap::Render()
{
	//DebugRectRender();

}
