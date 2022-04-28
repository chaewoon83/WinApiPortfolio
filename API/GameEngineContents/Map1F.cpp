#include "Map1F.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineTime.h>
#include "PlayerLink.h"

GameEngineRenderer* Map1F::Room1TopDoor0_ = nullptr;
GameEngineRenderer* Map1F::Room2TopDoor0_ = nullptr;
GameEngineRenderer* Map1F::Room2BotDoor0_ = nullptr;

GameEngineCollision* Map1F::Room1TopDoor0Col_ = nullptr;
GameEngineCollision* Map1F::Room2TopDoor0Col_ = nullptr;
GameEngineCollision* Map1F::Room2BotDoor0Col_ = nullptr;

GameEngineCollision* Map1F::Room1SwitchCol_ = nullptr;
GameEngineCollision* Map1F::Room2SwitchCol_ = nullptr;

Map1F::Map1F()
	: IsRoom1PlayerOnSwitch_(false)
	, IsRoom1TimeStop_(false)
	, IsRoom1SwitchOn_(false)
	, IsRoom2PlayerOnSwitch_(false)
	, IsRoom2TimeStop_(false)
	, IsRoom2SwitchOn_(false)
	, CurRoomState_(CameraState::Room1)
{
}

Map1F::~Map1F()
{
}

//맵들의 통로는 오른쪽으로 한 픽셀 지워놓는다 (안그러면 안움직임)

void Map1F::Start()
{
	//SetPosition(GameEngineWindow::GetScale().Half()*4);
	//아래부터 넣은 렌더러들이 맨 위부터 나온다
	//CreateRendererToScale("HPBAR.bmp", float4(100.0f, 20.0f), RenderPivot::CENTER, {0, -100});
	GameEngineRenderer* Renderer;
	float4 ImagePos = {};
	Renderer = CreateRenderer("EastPalace1F_1_1F.bmp");
	//렌더러는  0,0 을 기준으로 중앙에 배치된다 ( 그대로 쓰면 이미지 짤림 )
	//이미지, Rect는 0, 0 을 기준으로 오른쪽 아래에 배치된다
	ImagePos.x = (Renderer->GetImage()->GetScale().Half().x);
	ImagePos.y = (Renderer->GetImage()->GetScale().Half().y);
	Renderer->SetPivot(ImagePos);

	DoorAnimationCreate();
	PlaceDoor();


	Room1SwitchCol_ = CreateCollision("Switch", { 48, 40 }, { 3040, 3451 });
	Room2SwitchCol_ = CreateCollision("Switch", { 56, 40 }, { 3040, 2616 });
}

void Map1F::Update()
{
	Room1SwitchCheck();
	Room2SwitchCheck();
}
void Map1F::Render()
{
	//DebugRectRender();

}

void Map1F::PlaceDoor()
{

}

void Map1F::DoorAnimationCreate()
{
	Room1TopDoor0_ = CreateRenderer();
	Room1TopDoor0_->SetPivot(float4{ 3072, 3216 });
	Room1TopDoor0_->CreateAnimationTimeKey("Top_Door_Idle_Animation.bmp", "Idle_Top", -1, 0, 2, 1.0f, false);
	Room1TopDoor0_->CreateAnimationTimeKey("Top_Door_Open_Animation.bmp", "Open_Top", -1, 0, 2, 0.07f, false);
	Room1TopDoor0_->CreateAnimationTimeKey("Top_Door_Close_Animation.bmp", "Close_Top", -1, 0, 2, 0.07f, false);
	Room1TopDoor0_->ChangeAnimationReset("Idle_Top");
	Room1TopDoor0Col_ = CreateCollision("Block", { 128,96 }, float4{ 3072, 3216 });

	Room2TopDoor0_ = CreateRenderer();
	Room2TopDoor0_->SetPivot(float4{ 3072, 2194 });
	Room2TopDoor0_->CreateAnimationTimeKey("Top_Door_Idle_Animation.bmp", "Idle_Top", -1, 0, 2, 0.035f, false);
	Room2TopDoor0_->CreateAnimationTimeKey("Top_Door_Open_Animation.bmp", "Open_Top", -1, 0, 2, 0.035f, false);
	Room2TopDoor0_->CreateAnimationTimeKey("Top_Door_Close_Animation.bmp", "Close_Top", -1, 0, 2, 0.035f, false);
	Room2TopDoor0_->ChangeAnimation("Open_Top");
	Room2TopDoor0Col_ = CreateCollision("Block", { 128,96 }, float4{ 3072, 2194 });


	Room2BotDoor0_ = CreateRenderer();
	Room2BotDoor0_->SetPivot(float4{ 3072, 2928 });
	Room2BotDoor0_->CreateAnimationTimeKey("Bot_Door_Idle_Animation.bmp", "Idle_Bot", -1, 0, 2, 0.035f, false);
	Room2BotDoor0_->CreateAnimationTimeKey("Bot_Door_Open_Animation.bmp", "Open_Bot", -1, 0, 2, 0.035f, false);
	Room2BotDoor0_->CreateAnimationTimeKey("Bot_Door_Close_Animation.bmp", "Close_Bot", -1, 0, 2, 0.035f, false);
	Room2BotDoor0_->ChangeAnimation("Open_Bot");
	Room2BotDoor0Col_ = CreateCollision("Block", { 128,96 }, float4{ 3072, 2928 });
}

void Map1F::Room1SwitchCheck()
{

	std::vector<GameEngineCollision*> ColList;

	if (true == Room1SwitchCol_->CollisionResult("PlayerLowerBodyHitBox", ColList, CollisionType::Rect, CollisionType::Rect) && false == IsRoom1PlayerOnSwitch_)
	{
		if (false == IsRoom1SwitchOn_)
		{
			Room1TopDoor0_->ChangeAnimationReset("Open_Top");
			Room1TopDoor0Col_->Off();
			IsRoom1SwitchOn_ = true;
			IsRoom1PlayerOnSwitch_ = true;
			IsRoom1TimeStop_ = true;
			GameEngineTime::GetInst()->SetTimeScale(0, 0.0f);
			GameEngineTime::GetInst()->SetTimeScale(1, 0.0f);
		}
		else
		{
			Room1TopDoor0_->ChangeAnimationReset("Close_Top");
			Room1TopDoor0Col_->On();
			IsRoom1SwitchOn_ = false;
			IsRoom1PlayerOnSwitch_ = true;
			IsRoom1TimeStop_ = true;
			GameEngineTime::GetInst()->SetTimeScale(0, 0.0f);
			GameEngineTime::GetInst()->SetTimeScale(1, 0.0f);
		}
	}
	else if (false == Room1SwitchCol_->CollisionResult("PlayerLowerBodyHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		IsRoom1PlayerOnSwitch_ = false;
	}

	if (true == IsRoom1TimeStop_ && true == Room1TopDoor0_->IsEndAnimation())
	{
		IsRoom1TimeStop_ = false;
		GameEngineTime::GetInst()->SetTimeScale(0, 1.0f);
		GameEngineTime::GetInst()->SetTimeScale(1, 1.0f);
	}


	if (CameraState::Room1 == PlayerLink::GetPlayerCurRoomState())
	{
		if (CameraState::Room1 != CurRoomState_)
		{
			IsRoom1SwitchOn_ = false;
			CurRoomState_ = PlayerLink::GetPlayerCurRoomState();
			Room1TopDoor0_->ChangeAnimationReset("Close_Top");
			Room1TopDoor0Col_->On();
		}
	}
}

void Map1F::Room2SwitchCheck()
{

	std::vector<GameEngineCollision*> ColList;

	if (true == Room2SwitchCol_->CollisionResult("PlayerLowerBodyHitBox", ColList, CollisionType::Rect, CollisionType::Rect) && false == IsRoom2PlayerOnSwitch_)
	{
		if (false == IsRoom2SwitchOn_)
		{
			Room2TopDoor0_->ChangeAnimationReset("Open_Top");
			Room2TopDoor0Col_->Off();
			Room2BotDoor0_->ChangeAnimationReset("Open_Bot");
			Room2BotDoor0Col_->Off();
			IsRoom2SwitchOn_ = true;
			IsRoom2PlayerOnSwitch_ = true;
			IsRoom2TimeStop_ = true;
			GameEngineTime::GetInst()->SetTimeScale(0, 0.0f);
			GameEngineTime::GetInst()->SetTimeScale(2, 0.0f);
		}
		else
		{
			Room2TopDoor0_->ChangeAnimationReset("Close_Top");
			Room2TopDoor0Col_->On();
			Room2BotDoor0_->ChangeAnimationReset("Close_Bot");
			Room2BotDoor0Col_->On();
			IsRoom2SwitchOn_ = false;
			IsRoom2PlayerOnSwitch_ = true;
			IsRoom2TimeStop_ = true;
			GameEngineTime::GetInst()->SetTimeScale(0, 0.0f);
			GameEngineTime::GetInst()->SetTimeScale(2, 0.0f);
		}
	}
	else if (false == Room2SwitchCol_->CollisionResult("PlayerLowerBodyHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		IsRoom2PlayerOnSwitch_ = false;
	}

	if (true == IsRoom2TimeStop_ && true == Room2TopDoor0_->IsEndAnimation())
	{
		IsRoom2TimeStop_ = false;
		GameEngineTime::GetInst()->SetTimeScale(0, 1.0f);
		GameEngineTime::GetInst()->SetTimeScale(2, 1.0f);
	}


	if (CameraState::Room2 == PlayerLink::GetPlayerCurRoomState())
	{
		if (CameraState::Room2 != CurRoomState_)
		{
			IsRoom2SwitchOn_ = false;
			CurRoomState_ = PlayerLink::GetPlayerCurRoomState();
			Room2TopDoor0_->ChangeAnimationReset("Close_Top");
			Room2BotDoor0_->ChangeAnimationReset("Close_Bot");
			Room2TopDoor0Col_->On();
			Room2BotDoor0Col_->On();
		}
	}
}