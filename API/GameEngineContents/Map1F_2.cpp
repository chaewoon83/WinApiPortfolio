#include "Map1F_2.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineInput.h>
#include "PlayerLink.h"
#include "GlobalRandom.h"

#include "EnemyBall.h"
#include "EnemyGargantuanBall.h"

#include "Map1FRoom8TreasureBox.h"

#include "Map1FRoom7EnemyBlueStalfos0.h"
#include "Map1FRoom7EnemyBlueStalfos1.h"
#include "Map1FRoom7EnemyBlueStalfos2.h"
#include "Map1FRoom7EnemyBlueStalfos3.h"

GameEngineRenderer* Map1F_2::Room1TopDoor0_ = nullptr;
GameEngineRenderer* Map1F_2::Room2TopDoor0_ = nullptr;
GameEngineRenderer* Map1F_2::Room2BotDoor0_ = nullptr;
GameEngineRenderer* Map1F_2::Room10RightDoor0_ = nullptr;
GameEngineRenderer* Map1F_2::Room10LeftDoor0_ = nullptr;
GameEngineRenderer* Map1F_2::Room7RightDoor0_ = nullptr;
GameEngineRenderer* Map1F_2::Room7TopDoor0_ = nullptr;

GameEngineCollision* Map1F_2::Room1TopDoor0Col_ = nullptr;
GameEngineCollision* Map1F_2::Room2TopDoor0Col_ = nullptr;
GameEngineCollision* Map1F_2::Room2BotDoor0Col_ = nullptr;
GameEngineCollision* Map1F_2::Room10RightDoor0Col_ = nullptr;
GameEngineCollision* Map1F_2::Room10LeftDoor0Col_ = nullptr;
GameEngineCollision* Map1F_2::Room7RightDoor0Col_ = nullptr;
GameEngineCollision* Map1F_2::Room7TopDoor0Col_ = nullptr;
GameEngineCollision* Map1F_2::Room8TreasureBoxCol_ = nullptr;

GameEngineCollision* Map1F_2::Room1SwitchCol_ = nullptr;
GameEngineCollision* Map1F_2::Room2SwitchCol_ = nullptr;
GameEngineCollision* Map1F_2::Room10SwitchCol_1_ = nullptr;
GameEngineCollision* Map1F_2::Room10SwitchCol_2_ = nullptr;

GameEngineActor* Map1F_2::Room8TreasureBox_ = nullptr;
GameEngineRenderer* Map1F_2::Room8ItemRenderer_ = nullptr;


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
	, IsRoom7First_(false)
	, IsRoom7Summoning_(false)
	, IsRoom7InFight_(false)
	, IsRoom7Clear_(false)
	, IsRoom7DoorOpened_(false)
	, SummonIndex_(0)
	, SummonEffect_(nullptr)
	, IsCreateItemRenderer_(false)
	, Room8ItemRendererPivot_(float4{ 420 + 28 ,2324 + 30 })
	, Room8ItemMoveTime_(1.0f)
	, CurRoom8ItemMoveTime_(0.0f)
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
	Room8TreasureBoxCol_ = CreateCollision("TreasureBox", { 16, 1 }, { 440 + 8, 2400 });

	Room8TreasureBox_ = GetLevel()->CreateActor<Map1FRoom8TreasureBox>(static_cast<int>(PlayLevelOrder::BELOWPLAYER));

}

void Map1F_2::Update()
{
	Room1SwitchCheck();
	Room2SwitchCheck();
	Room4BallGen();
	Room10SwitchCheck();
	Room9CheckStatus();
	Room7SummonEnemies();
	Room7DoorCheck();
	Room8CheckItemBox();
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

	Room7RightDoor0_ = CreateRenderer();
	Room7RightDoor0_->SetPivot(float4{ 864 + 48, 3552 + 64 });
	Room7RightDoor0_->CreateAnimationTimeKey("Left_Door_Idle_Animation.bmp", "Idle_Right", -1, 0, 2, 0.07f, false);
	Room7RightDoor0_->CreateAnimationTimeKey("Left_Door_Open_Animation.bmp", "Open_Right", -1, 0, 2, 0.07f, false);
	Room7RightDoor0_->CreateAnimationTimeKey("Left_Door_Close_Animation.bmp", "Close_Right", -1, 0, 2, 0.07f, false);
	Room7RightDoor0_->ChangeAnimationReset("Open_Right");
	Room7RightDoor0Col_ = CreateCollision("Block", { 96, 192 }, float4{ 864 + 48, 3552 + 64 });

	Room7TopDoor0_ = CreateRenderer();
	Room7TopDoor0_->SetPivot(float4{ 448 + 64, 3200 + 48 });
	Room7TopDoor0_->CreateAnimationTimeKey("Top_Door_Idle_Animation.bmp", "Idle_Top", -1, 0, 2, 0.07f, false);
	Room7TopDoor0_->CreateAnimationTimeKey("Top_Door_Open_Animation.bmp", "Open_Top", -1, 0, 2, 0.07f, false);
	Room7TopDoor0_->CreateAnimationTimeKey("Top_Door_Close_Animation.bmp", "Close_Top", -1, 0, 2, 0.07f, false);
	Room7TopDoor0_->ChangeAnimationReset("Open_Top");
	Room7TopDoor0Col_ = CreateCollision("Block", { 192,96 }, float4{ 444 + 64, 3200 + 48 });
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

void Map1F_2::Room9CheckStatus()
{
	if (CameraState::Room9 == PlayerLink::GetPlayerCurRoomState())
	{
		if (CameraState::Room9 != CurRoomState_)
		{
			CurRoomState_ = PlayerLink::GetPlayerCurRoomState();
		}
	}
}
void Map1F_2::Room7SummonEnemies()
{
	if (639.0f > PlayerLink::MainPlayer_->GetPosition().x &&
		3296.0f < PlayerLink::MainPlayer_->GetPosition().y &&
		3951.0f > PlayerLink::MainPlayer_->GetPosition().y &&
		CameraState::Room7 == PlayerLink::GetPlayerCurRoomState())
	{
		if (false == IsRoom7First_)
		{
			SummonEffect_ = CreateRenderer();
			SummonEffect_->CreateAnimationTimeKey("EnemySummonEffect.bmp", "Idle", 7, 0, 1, 0.2f, false);
			SummonEffect_->SetPivot({ 639, 3471 });
			SummonEffect_->ChangeAnimationReset("Idle");
			IsRoom7First_ = true;
			IsRoom7Summoning_ = true;
		}
	}

	if (true == IsRoom7Summoning_)
	{
		if (0 == SummonIndex_ && true == SummonEffect_->IsEndAnimation())
		{
			BlueStalfos0 = GetLevel()->CreateActor<Map1FRoom7EnemyBlueStalfos0>(static_cast<int>(PlayLevelOrder::MONSTER));
			SummonEffect_->SetPivot({ 639, 3855 });
			SummonIndex_ = 1;
		}

		else if (1 == SummonIndex_ && true == SummonEffect_->IsEndAnimation())
		{
			SummonEffect_->ChangeAnimationReset("Idle");
			BlueStalfos1 = GetLevel()->CreateActor<Map1FRoom7EnemyBlueStalfos1>(static_cast<int>(PlayLevelOrder::MONSTER));
			SummonEffect_->SetPivot({ 447, 3663 });
			SummonIndex_ = 2;
		}

		else if (2 == SummonIndex_ && true == SummonEffect_->IsEndAnimation())
		{
			SummonEffect_->ChangeAnimationReset("Idle");
			BlueStalfos2 = GetLevel()->CreateActor<Map1FRoom7EnemyBlueStalfos2>(static_cast<int>(PlayLevelOrder::MONSTER));
			SummonEffect_->SetPivot({ 767, 3663 });
			SummonIndex_ = 3;
		}

		else if (3 == SummonIndex_ && true == SummonEffect_->IsEndAnimation())
		{
			BlueStalfos3 = GetLevel()->CreateActor<Map1FRoom7EnemyBlueStalfos3>(static_cast<int>(PlayLevelOrder::MONSTER));
			SummonEffect_->Death();
			IsRoom7Summoning_ = false;
			IsRoom7InFight_ = true;
		}
	}
	if (true == IsRoom7InFight_)
	{
		if (true == dynamic_cast<Map1FRoom7EnemyBlueStalfos0*>(BlueStalfos0)->GetIsDeath() /*&&
			true == dynamic_cast<Map1FRoom7EnemyBlueStalfos1*>(BlueStalfos1)->GetIsDeath() &&
			true == dynamic_cast<Map1FRoom7EnemyBlueStalfos2*>(BlueStalfos2)->GetIsDeath() &&
			true == dynamic_cast<Map1FRoom7EnemyBlueStalfos3*>(BlueStalfos3)->GetIsDeath()*/)
		{
			IsRoom7Clear_ = true;
		}
	}
}

void Map1F_2::Room7DoorCheck()
{
	if (true == IsRoom7Clear_)
	{
		if (CameraState::Room7 == CurRoomState_ && false == IsRoom7DoorOpened_)
		{
			IsRoom7DoorOpened_ = true;
			Room7RightDoor0_->ChangeAnimationReset("Open_Right");
			Room7RightDoor0Col_->Off();
			Room7TopDoor0_->ChangeAnimationReset("Open_Top");
			Room7TopDoor0Col_->Off();
		}
	}

	if (CameraState::Room7 == PlayerLink::GetPlayerCurRoomState())
	{
		if (CameraState::Room7 != CurRoomState_)
		{
			IsRoom7DoorOpened_ = false;
			CurRoomState_ = PlayerLink::GetPlayerCurRoomState();
			Room7RightDoor0_->ChangeAnimationReset("Close_Right");
			Room7TopDoor0_->ChangeAnimationReset("Close_Top");
			Room7RightDoor0Col_->On();
			Room7TopDoor0Col_->On();
		}
	}
}

void Map1F_2::Room8CheckItemBox()
{

	if (CameraState::Room8 == PlayerLink::GetPlayerCurRoomState())
	{
		if (CameraState::Room8 != CurRoomState_)
		{
			CurRoomState_ = PlayerLink::GetPlayerCurRoomState();
		}

		if (true == PlayerLink::GetIsInItemCutScene())
		{
			if (false == IsCreateItemRenderer_)
			{
				IsCreateItemRenderer_ = true;
				Room8ItemRenderer_ = CreateRenderer("ItemCompass.bmp");
				Room8ItemRenderer_->SetPivot(Room8ItemRendererPivot_);
			}
			if (true == IsCreateItemRenderer_)
			{
				if (Room8ItemMoveTime_ > CurRoom8ItemMoveTime_)
				{
					CurRoom8ItemMoveTime_ += GameEngineTime::GetDeltaTime();
					Room8ItemRendererPivot_ = { Room8ItemRendererPivot_.x ,Room8ItemRendererPivot_.y - 50.0f * GameEngineTime::GetDeltaTime() };
					Room8ItemRenderer_->SetPivot(Room8ItemRendererPivot_);
				}
			}
		}
	}

}