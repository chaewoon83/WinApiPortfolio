#include "Map1F_2.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineTime.h>
#include "PlayerLink.h"
#include "GlobalRandom.h"

#include "EnemyBall.h"
#include "EnemyGargantuanBall.h"

GameEngineRenderer* Map1F_2::Room1TopDoor0_ = nullptr;
GameEngineRenderer* Map1F_2::Room2TopDoor0_ = nullptr;
GameEngineRenderer* Map1F_2::Room2BotDoor0_ = nullptr;
GameEngineRenderer* Map1F_2::Room10RightDoor0_ = nullptr;
GameEngineRenderer* Map1F_2::Room10LeftDoor0_ = nullptr;

GameEngineCollision* Map1F_2::Room1TopDoor0Col_ = nullptr;
GameEngineCollision* Map1F_2::Room2TopDoor0Col_ = nullptr;
GameEngineCollision* Map1F_2::Room2BotDoor0Col_ = nullptr;
GameEngineCollision* Map1F_2::Room10RightDoor0Col_ = nullptr;
GameEngineCollision* Map1F_2::Room10LeftDoor0Col_ = nullptr;

GameEngineCollision* Map1F_2::Room1SwitchCol_ = nullptr;
GameEngineCollision* Map1F_2::Room2SwitchCol_ = nullptr;
GameEngineCollision* Map1F_2::Room10SwitchCol_1_ = nullptr;
GameEngineCollision* Map1F_2::Room10SwitchCol_2_ = nullptr;


Map1F_2::Map1F_2()
	: IsRoom1PlayerOnSwitch_(false)
	, IsRoom1TimeStop_(false)
	, IsRoom1SwitchOn_(false)
	, IsRoom2PlayerOnSwitch_(false)
	, IsRoom2TimeStop_(false)
	, IsRoom2SwitchOn_(false)
	, Room4BallNumbers_(0)
	, Room4BallCreateFreq_(1.0f)
	, Room4CurBallCreateFreq_(0.0f)
	, IsRoom10PlayerOnSwitch_(false)
	, IsRoom10TimeStop_(false)
	, IsRoom10SwitchOn_(false)
	, CurRoomState_(CameraState::Room1)
{
}

Map1F_2::~Map1F_2()
{
}

//맵들의 통로는 오른쪽으로 한 픽셀 지워놓는다 (안그러면 안움직임)

void Map1F_2::Start()
{
	//SetPosition(GameEngineWindow::GetScale().Half()*4);
	//아래부터 넣은 렌더러들이 맨 위부터 나온다
	//CreateRendererToScale("HPBAR.bmp", float4(100.0f, 20.0f), RenderPivot::CENTER, {0, -100});
	GameEngineRenderer* Renderer;
	float4 ImagePos = {};
	Renderer = CreateRenderer("EastPalace1F_2_1F.bmp");
	//렌더러는  0,0 을 기준으로 중앙에 배치된다 ( 그대로 쓰면 이미지 짤림 )
	//이미지, Rect는 0, 0 을 기준으로 오른쪽 아래에 배치된다
	ImagePos.x = (Renderer->GetImage()->GetScale().Half().x);
	ImagePos.y = (Renderer->GetImage()->GetScale().Half().y);
	Renderer->SetPivot(ImagePos);

	DoorAnimationCreate();
	PlaceDoor();


	Room1SwitchCol_ = CreateCollision("Switch", { 48, 40 }, { 3040, 3451 + 4128.0f });
	Room2SwitchCol_ = CreateCollision("Switch", { 56, 40 }, { 3040, 2616 + 4128.0f });
	Room10SwitchCol_1_ = CreateCollision("Switch", { 56, 40 }, { 2244 + 28, 3332 + 20});
	Room10SwitchCol_2_ = CreateCollision("Switch", { 56, 40 }, { 3844 + 28, 2616 + 20 });
}

void Map1F_2::Update()
{
	Room1SwitchCheck();
	Room2SwitchCheck();
	Room4BallGen();
	Room10SwitchCheck();
}
void Map1F_2::Render()
{
	//DebugRectRender();

}

void Map1F_2::PlaceDoor()
{

}

void Map1F_2::DoorAnimationCreate()
{
	Room1TopDoor0_ = CreateRenderer();
	Room1TopDoor0_->SetPivot(float4{ 3072, 3216 + 4128 });
	Room1TopDoor0_->CreateAnimationTimeKey("Top_Door_Idle_Animation.bmp", "Idle_Top", -1, 0, 2, 1.0f, false);
	Room1TopDoor0_->CreateAnimationTimeKey("Top_Door_Open_Animation.bmp", "Open_Top", -1, 0, 2, 0.07f, false);
	Room1TopDoor0_->CreateAnimationTimeKey("Top_Door_Close_Animation.bmp", "Close_Top", -1, 0, 2, 0.07f, false);
	Room1TopDoor0_->ChangeAnimationReset("Idle_Top");
	Room1TopDoor0Col_ = CreateCollision("Block", { 192,96 }, float4{ 3072, 3216 + 4128 });

	Room2TopDoor0_ = CreateRenderer();
	Room2TopDoor0_->SetPivot(float4{ 3072, 2194 + 4128 });
	Room2TopDoor0_->CreateAnimationTimeKey("Top_Door_Idle_Animation.bmp", "Idle_Top", -1, 0, 2, 0.07f, false);
	Room2TopDoor0_->CreateAnimationTimeKey("Top_Door_Open_Animation.bmp", "Open_Top", -1, 0, 2, 0.07f, false);
	Room2TopDoor0_->CreateAnimationTimeKey("Top_Door_Close_Animation.bmp", "Close_Top", -1, 0, 2, 0.07f, false);
	Room2TopDoor0_->ChangeAnimationReset("Idle_Top");
	Room2TopDoor0Col_ = CreateCollision("Block", { 192,96 }, float4{ 3072, 2194 + 4128 });


	Room2BotDoor0_ = CreateRenderer();
	Room2BotDoor0_->SetPivot(float4{ 3072, 2928 + 4128 });
	Room2BotDoor0_->CreateAnimationTimeKey("Bot_Door_Idle_Animation.bmp", "Idle_Bot", -1, 0, 2, 0.07f, false);
	Room2BotDoor0_->CreateAnimationTimeKey("Bot_Door_Open_Animation.bmp", "Open_Bot", -1, 0, 2, 0.07f, false);
	Room2BotDoor0_->CreateAnimationTimeKey("Bot_Door_Close_Animation.bmp", "Close_Bot", -1, 0, 2, 0.07f, false);
	Room2BotDoor0_->ChangeAnimationReset("Idle_Bot");
	Room2BotDoor0Col_ = CreateCollision("Block", { 192,96 }, float4{ 3072, 2928 + 4128 });

	Room10RightDoor0_ = CreateRenderer();
	Room10RightDoor0_->SetPivot(float4{ 2112 + 48, 3040 + 64 });
	Room10RightDoor0_->CreateAnimationTimeKey("Right_Door_Idle_Animation.bmp", "Idle_Right", -1, 0, 2, 0.07f, false);
	Room10RightDoor0_->CreateAnimationTimeKey("Right_Door_Open_Animation.bmp", "Open_Right", -1, 0, 2, 0.07f, false);
	Room10RightDoor0_->CreateAnimationTimeKey("Right_Door_Close_Animation.bmp", "Close_Right", -1, 0, 2, 0.07f, false);
	Room10RightDoor0_->ChangeAnimationReset("Idle_Right");
	Room10RightDoor0Col_ = CreateCollision("Block", { 96, 192 }, float4{ 2112 + 48, 3040 + 64 });
	
	Room10LeftDoor0_ = CreateRenderer();
	Room10LeftDoor0_->SetPivot(float4{ 3936 + 48, 3040 + 64 });
	Room10LeftDoor0_->CreateAnimationTimeKey("Left_Door_Idle_Animation.bmp", "Idle_Left", -1, 0, 2, 0.07f, false);
	Room10LeftDoor0_->CreateAnimationTimeKey("Left_Door_Open_Animation.bmp", "Open_Left", -1, 0, 2, 0.07f, false);
	Room10LeftDoor0_->CreateAnimationTimeKey("Left_Door_Close_Animation.bmp", "Close_Left", -1, 0, 2, 0.07f, false);
	Room10LeftDoor0_->ChangeAnimationReset("Idle_Left");
	Room10LeftDoor0Col_ = CreateCollision("Block", { 96, 192 }, float4{ 3936 + 48, 3040 + 64 });
}

void Map1F_2::Room1SwitchCheck()
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
			Room1TopDoor0Col_->On();
			Room1TopDoor0_->ChangeAnimationReset("Close_Top");
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
			//Room1TopDoor0_->ChangeAnimationReset("Close_Top");
			Room1TopDoor0Col_->On();
		}
	}
}

void Map1F_2::Room2SwitchCheck()
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
			Room2TopDoor0Col_->On();
			Room2TopDoor0_->ChangeAnimationReset("Close_Top");
			Room2BotDoor0Col_->On();
			Room2BotDoor0_->ChangeAnimationReset("Close_Bot");
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
			//Room2TopDoor0_->ChangeAnimationReset("Close_Top");
			//Room2BotDoor0_->ChangeAnimationReset("Close_Bot");
			Room2TopDoor0Col_->On();
			Room2BotDoor0Col_->On();
		}
	}
}

void Map1F_2::Room4BallGen()
{
	if (CameraState::Room4 == PlayerLink::GetPlayerCurRoomState())
	{
		Room4CurBallCreateFreq_ += GameEngineTime::GetDeltaTime(4);

		if (Room4BallCreateFreq_ < Room4CurBallCreateFreq_)
		{
			Room4CurBallCreateFreq_ = 0;
			if (6 <= Room4BallNumbers_)
			{
				Room4BallNumbers_ = 0;
				GetLevel()->CreateActor<EnemyGargantuanBall>()->SetPosition(float4{ 3104 + 64, 320 - 32 + 4128 });
			}
			else
			{
				Room4BallNumbers_ += 1;
				int RandomInt = GlobalRandom::RandomIntGenerate(0, 1);
				if (0 == RandomInt)
				{
					GetLevel()->CreateActor<EnemyBall>()->SetPosition(float4{ 3104 + 32, 320 + 32 + 4128 });
				}
				else
				{
					GetLevel()->CreateActor<EnemyBall>()->SetPosition(float4{ 3168 + 32, 320 + 32 + 4128 });
				}
			}
		}
		if (CameraState::Room4 != CurRoomState_)
		{
			IsRoom2SwitchOn_ = false;
			CurRoomState_ = PlayerLink::GetPlayerCurRoomState();
		}
	}
}

void Map1F_2::Room10SwitchCheck()
{

	std::vector<GameEngineCollision*> ColList;

	if (true == Room10SwitchCol_1_->CollisionResult("PlayerLowerBodyHitBox", ColList, CollisionType::Rect, CollisionType::Rect) || 
		true == Room10SwitchCol_2_->CollisionResult("PlayerLowerBodyHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		if (false == IsRoom10PlayerOnSwitch_)
		{
			if (false == IsRoom10SwitchOn_)
			{
				Room10RightDoor0_->ChangeAnimationReset("Open_Right");
				Room10RightDoor0Col_->Off();
				Room10LeftDoor0_->ChangeAnimationReset("Open_Left");
				Room10LeftDoor0Col_->Off();
				IsRoom10SwitchOn_ = true;
				IsRoom10PlayerOnSwitch_ = true;
				IsRoom10TimeStop_ = true;
				GameEngineTime::GetInst()->SetTimeScale(0, 0.0f);
				GameEngineTime::GetInst()->SetTimeScale(10, 0.0f);
			}
			else
			{
				Room10RightDoor0Col_->On();
				Room10RightDoor0_->ChangeAnimationReset("Close_Right");
				Room10LeftDoor0Col_->On();
				Room10LeftDoor0_->ChangeAnimationReset("Close_Left");
				IsRoom10SwitchOn_ = false;
				IsRoom10PlayerOnSwitch_ = true;
				IsRoom10TimeStop_ = true;
				GameEngineTime::GetInst()->SetTimeScale(0, 0.0f);
				GameEngineTime::GetInst()->SetTimeScale(10, 0.0f);
			}
		}

	}
	else if (false == Room10SwitchCol_1_->CollisionResult("PlayerLowerBodyHitBox", ColList, CollisionType::Rect, CollisionType::Rect) &&
		false == Room10SwitchCol_2_->CollisionResult("PlayerLowerBodyHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		IsRoom10PlayerOnSwitch_ = false;
	}

	if (true == IsRoom10TimeStop_ && true == Room10RightDoor0_->IsEndAnimation())
	{
		IsRoom10TimeStop_ = false;
		GameEngineTime::GetInst()->SetTimeScale(0, 1.0f);
		GameEngineTime::GetInst()->SetTimeScale(10, 1.0f);
	}


	if (CameraState::Room10 == PlayerLink::GetPlayerCurRoomState())
	{
		if (CameraState::Room10 != CurRoomState_)
		{
			IsRoom10SwitchOn_ = false;
			CurRoomState_ = PlayerLink::GetPlayerCurRoomState();
			//Room10TopDoor0_->ChangeAnimationReset("Close_Top");
			//Room2BotDoor0_->ChangeAnimationReset("Close_Bot");
			Room10RightDoor0Col_->On();
			Room10LeftDoor0Col_->On();
		}
	}
}