#include "Map1F_2.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineSound.h>
#include "PlayerLink.h"
#include "GlobalRandom.h"

#include "EnemyBall.h"
#include "EnemyGargantuanBall.h"

#include "Map1FRoom4TreasureBox.h"
#include "Map1FRoom8TreasureBox.h"
#include "Map1FRoom3TreasureBox.h"

#include "Map1FRoom7EnemyBlueStalfos0.h"

GameEngineRenderer* Map1F_2::Room1TopDoor0_ = nullptr;
GameEngineRenderer* Map1F_2::Room2TopDoor0_ = nullptr;
GameEngineRenderer* Map1F_2::Room2BotDoor0_ = nullptr;
GameEngineRenderer* Map1F_2::Room10RightDoor0_ = nullptr;
GameEngineRenderer* Map1F_2::Room10LeftDoor0_ = nullptr;
GameEngineRenderer* Map1F_2::Room7RightDoor0_ = nullptr;
GameEngineRenderer* Map1F_2::Room7TopDoor0_ = nullptr;
GameEngineRenderer* Map1F_2::Room5RightDoor0_ = nullptr;
GameEngineRenderer* Map1F_2::Room5LeftKeyDoor0_ = nullptr;
GameEngineRenderer* Map1F_2::Room4RightKeyDoor0_ = nullptr;
GameEngineRenderer* Map1F_2::Room3TopBigKeyDoor0_ = nullptr;

GameEngineCollision* Map1F_2::Room1TopDoor0Col_ = nullptr;
GameEngineCollision* Map1F_2::Room2TopDoor0Col_ = nullptr;
GameEngineCollision* Map1F_2::Room2BotDoor0Col_ = nullptr;
GameEngineCollision* Map1F_2::Room10RightDoor0Col_ = nullptr;
GameEngineCollision* Map1F_2::Room10LeftDoor0Col_ = nullptr;
GameEngineCollision* Map1F_2::Room7RightDoor0Col_ = nullptr;
GameEngineCollision* Map1F_2::Room7TopDoor0Col_ = nullptr;
GameEngineCollision* Map1F_2::Room5RightDoor0Col_ = nullptr;
GameEngineCollision* Map1F_2::Room5LeftKeyDoor0Col_ = nullptr;
GameEngineCollision* Map1F_2::Room5LeftKeyDoor0Col2_ = nullptr;
GameEngineCollision* Map1F_2::Room3TopBigKeyDoor0Col_ = nullptr;
GameEngineCollision* Map1F_2::Room3TopBigKeyDoor0Col2_ = nullptr;

GameEngineCollision* Map1F_2::Room4TreasureBoxCol_ = nullptr;
GameEngineCollision* Map1F_2::Room8TreasureBoxCol_ = nullptr;
GameEngineCollision* Map1F_2::Room3TreasureBoxCol_ = nullptr;

GameEngineCollision* Map1F_2::Room1SwitchCol_ = nullptr;
GameEngineCollision* Map1F_2::Room2SwitchCol_ = nullptr;
GameEngineCollision* Map1F_2::Room10SwitchCol_1_ = nullptr;
GameEngineCollision* Map1F_2::Room10SwitchCol_2_ = nullptr;
GameEngineCollision* Map1F_2::Room5SwitchCol_ = nullptr;
GameEngineCollision* Map1F_2::Room3SwitchCol_ = nullptr;

GameEngineActor* Map1F_2::Room4TreasureBox_ = nullptr;
GameEngineActor* Map1F_2::Room8TreasureBox_ = nullptr;
GameEngineActor* Map1F_2::Room3TreasureBox_ = nullptr;

GameEngineRenderer* Map1F_2::Room4ItemRenderer_ = nullptr;
GameEngineRenderer* Map1F_2::Room8ItemRenderer_ = nullptr;
GameEngineRenderer* Map1F_2::Room3ItemRenderer_ = nullptr;


Map1F_2::Map1F_2()
	: IsRoom1PlayerOnSwitch_(false)
	, IsRoom1TimeStop_(false)
	, IsRoom1SwitchOn_(false)
	, IsRoom2PlayerOnSwitch_(false)
	, IsRoom2TimeStop_(false)
	, IsRoom2SwitchOn_(false)
	, IsRoom4CreateItemRenderer_(false)
	, Room4ItemRendererPivot_(float4{ 3650 + 30 ,1116 + 30 + 4128 })
	, Room4ItemMoveTime_(1.0f)
	, CurRoom4ItemMoveTime_(0.0f)
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
	, IsRoom8CreateItemRenderer_(false)
	, Room8ItemRendererPivot_(float4{ 420 + 28 ,2324 + 30 })
	, Room8ItemMoveTime_(1.0f)
	, CurRoom8ItemMoveTime_(0.0f)
	, IsRoom5TimeStop_(false)
	, IsRoom5PlayerOnSwitch_(false)
	, IsRoom5SwitchOn_(false)
	, IsRoom5KeyDoorOpened_(false)
	, IsRoom3SwitchOn_(false)
	, IsRoom3CreateItemRenderer_(false)
	, Room3ItemRendererPivot_(float4{ 1540 + 28 , 468 + 32 })
	, Room3ItemMoveTime_(1.0f)
	, CurRoom3ItemMoveTime_(0.0f)

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
	Room5SwitchCol_ = CreateCollision("Switch", { 56, 40 }, { 4868 + 28, 612 + 20 + 4128});
	Room3SwitchCol_ = CreateCollision("Switch", { 40, 40 }, { 1548 + 20, 808 + 20 + 4128});

	Room4TreasureBoxCol_ = CreateCollision("TreasureBox", { 16, 1 }, { 3672 + 8, 1184 + 4128 });
	Room8TreasureBoxCol_ = CreateCollision("TreasureBox", { 16, 1 }, { 440 + 8, 2400 });
	Room8TreasureBoxCol_ = CreateCollision("TreasureBox", { 16, 2 }, { 1560 + 8, 544 + 4128});

	Room4TreasureBox_ = GetLevel()->CreateActor<Map1FRoom4TreasureBox>(static_cast<int>(PlayLevelOrder::BELOWPLAYER));
	Room8TreasureBox_ = GetLevel()->CreateActor<Map1FRoom8TreasureBox>(static_cast<int>(PlayLevelOrder::BELOWPLAYER));


}

void Map1F_2::Update()
{
	Room1SwitchCheck();
	Room2SwitchCheck();
	Room4CheckTreasureBox();
	Room4BallGen();
	Room10SwitchCheck();
	Room9CheckStatus();
	Room7SummonEnemies();
	Room7DoorCheck();
	Room8CheckTreasureBox();
	Room5SwitchCheck();
	Room3SwitchCheck();
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

	Room5RightDoor0_ = CreateRenderer();
	Room5RightDoor0_->SetPivot(float4{ 4960 + 48, 448 + 64 + 4128 });
	Room5RightDoor0_->CreateAnimationTimeKey("Left_Door_Idle_Animation.bmp", "Idle_Right", -1, 0, 2, 0.07f, false);
	Room5RightDoor0_->CreateAnimationTimeKey("Left_Door_Open_Animation.bmp", "Open_Right", -1, 0, 2, 0.07f, false);
	Room5RightDoor0_->CreateAnimationTimeKey("Left_Door_Close_Animation.bmp", "Close_Right", -1, 0, 2, 0.07f, false);
	Room5RightDoor0_->ChangeAnimationReset("Open_Right");
	Room5RightDoor0Col_ = CreateCollision("Block", { 96, 192 }, float4{ 4960 + 48, 448 + 64 + 4128 });

	Room5LeftKeyDoor0_ = CreateRenderer("Left_Locked_Door_Idle.bmp");
	Room5LeftKeyDoor0_->SetPivot(float4{ 4192 + 32, 448 + 64 + 4128 });
	Room4RightKeyDoor0_ = CreateRenderer("Right_Locked_Door_Idle.bmp");
	Room4RightKeyDoor0_->SetPivot(float4{ 3396 + 32, 448 + 64 + 4128 });
	Room5LeftKeyDoor0Col_ = CreateCollision("Block", { 64, 128 }, float4{ 4192 + 32, 448 + 64 + 4128 });
	Room5LeftKeyDoor0Col2_ = CreateCollision("LockedDoor", { 4, 64 }, float4{ 4256, 480 + 32 + 4128 });

	Room3TopBigKeyDoor0_ = CreateRenderer("Top_BigLocked_Door_Idle.bmp");
	Room3TopBigKeyDoor0_->SetPivot(float4{ 1472 + 64, 96 + 48 + 4128 });
	Room3TopBigKeyDoor0Col_ = CreateCollision("Block", { 128, 96 }, float4{ 1472 + 64, 96 + 48 + 4128 });
	Room3TopBigKeyDoor0Col2_ = CreateCollision("LockedDoor", { 62, 2 }, float4{ 1504 + 32, 193 + 4128 });


}

void Map1F_2::Room1SwitchCheck()
{

	std::vector<GameEngineCollision*> ColList;

	if (true == Room1SwitchCol_->CollisionResult("PlayerLowerBodyHitBox", ColList, CollisionType::Rect, CollisionType::Rect) && false == IsRoom1PlayerOnSwitch_)
	{
		if (false == IsRoom1SwitchOn_)
		{
			GameEngineSound::SoundPlayOneShot("button.mp3");
			GameEngineSound::SoundPlayOneShot("dooropen.mp3");
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
			GameEngineSound::SoundPlayOneShot("button.mp3");
			Room1TopDoor0Col_->On();
			GameEngineSound::SoundPlayOneShot("doorclose.mp3");
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
			GameEngineSound::SoundPlayOneShot("doorclose.mp3");
			CurRoomState_ = PlayerLink::GetPlayerCurRoomState();
			Room1TopDoor0_->ChangeAnimationReset("Close_Top");
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
			GameEngineSound::SoundPlayOneShot("button.mp3");
			GameEngineSound::SoundPlayOneShot("dooropen.mp3");
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
			GameEngineSound::SoundPlayOneShot("button.mp3");
			GameEngineSound::SoundPlayOneShot("doorclose.mp3");
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
			GameEngineSound::SoundPlayOneShot("doorclose.mp3");
			Room2TopDoor0_->ChangeAnimationReset("Close_Top");
			Room2BotDoor0_->ChangeAnimationReset("Close_Bot");
			Room2TopDoor0Col_->On();
			Room2BotDoor0Col_->On();
		}
	}
}

void Map1F_2::Room4CheckTreasureBox()
{

	if (CameraState::Room4 == PlayerLink::GetPlayerCurRoomState())
	{
		if (CameraState::Room4 != CurRoomState_)
		{
			CurRoomState_ = PlayerLink::GetPlayerCurRoomState();
		}

		if (true == PlayerLink::GetIsInItemCutScene())
		{
			if (false == IsRoom4CreateItemRenderer_)
			{
				IsRoom4CreateItemRenderer_ = true;
				Room4ItemRenderer_ = CreateRenderer("Item50Rupee.bmp");
				Room4ItemRenderer_->SetPivot(Room4ItemRendererPivot_);
			}
			if (true == IsRoom4CreateItemRenderer_)
			{
				if (Room4ItemMoveTime_ > CurRoom4ItemMoveTime_)
				{
					CurRoom4ItemMoveTime_ += GameEngineTime::GetDeltaTime();
					Room4ItemRendererPivot_ = { Room4ItemRendererPivot_.x ,Room4ItemRendererPivot_.y - 50.0f * GameEngineTime::GetDeltaTime() };
					Room4ItemRenderer_->SetPivot(Room4ItemRendererPivot_);
				}
			}
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
				GameEngineSound::SoundPlayOneShot("cannonballs.mp3");
				Room4BallNumbers_ = 0;
				GetLevel()->CreateActor<EnemyGargantuanBall>()->SetPosition(float4{ 3104 + 64, 320 - 32 + 4128 });
			}
			else
			{
				GameEngineSound::SoundPlayOneShot("cannonballs.mp3");
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
				GameEngineSound::SoundPlayOneShot("button.mp3");
				GameEngineSound::SoundPlayOneShot("dooropen.mp3");
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
				GameEngineSound::SoundPlayOneShot("button.mp3");
				GameEngineSound::SoundPlayOneShot("doorclose.mp3");
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
			GameEngineSound::SoundPlayOneShot("doorclose.mp3");
			IsRoom10SwitchOn_ = false;
			CurRoomState_ = PlayerLink::GetPlayerCurRoomState();
			Room10RightDoor0_->ChangeAnimationReset("Close_Right");
			Room10LeftDoor0_->ChangeAnimationReset("Close_Left");
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
			GameEngineSound::SoundPlayOneShot("flap.mp3");
			BlueStalfos0 = GetLevel()->CreateActor<Map1FRoom7EnemyBlueStalfos0>(static_cast<int>(PlayLevelOrder::MONSTER));
			BlueStalfos0->SetBlueStalfosPos({ 639, 3471 });
			SummonEffect_->SetPivot({ 639, 3855 });
			SummonIndex_ = 1;
		}

		else if (1 == SummonIndex_ && true == SummonEffect_->IsEndAnimation())
		{
			GameEngineSound::SoundPlayOneShot("flap.mp3");
			SummonEffect_->ChangeAnimationReset("Idle");
			BlueStalfos1 = GetLevel()->CreateActor<Map1FRoom7EnemyBlueStalfos0>(static_cast<int>(PlayLevelOrder::MONSTER));
			BlueStalfos1->SetBlueStalfosPos({ 639, 3855 });
			SummonEffect_->SetPivot({ 447, 3663 });
			SummonIndex_ = 2;
		}

		else if (2 == SummonIndex_ && true == SummonEffect_->IsEndAnimation())
		{
			GameEngineSound::SoundPlayOneShot("flap.mp3");
			SummonEffect_->ChangeAnimationReset("Idle");
			BlueStalfos2 = GetLevel()->CreateActor<Map1FRoom7EnemyBlueStalfos0>(static_cast<int>(PlayLevelOrder::MONSTER));
			BlueStalfos2->SetBlueStalfosPos({ 447, 3663 });
			SummonEffect_->SetPivot({ 767, 3663 });
			SummonIndex_ = 3;
		}

		else if (3 == SummonIndex_ && true == SummonEffect_->IsEndAnimation())
		{
			GameEngineSound::SoundPlayOneShot("flap.mp3");
			BlueStalfos3 = GetLevel()->CreateActor<Map1FRoom7EnemyBlueStalfos0>(static_cast<int>(PlayLevelOrder::MONSTER));
			BlueStalfos3->SetBlueStalfosPos({ 767, 3663 });
			SummonEffect_->Death();
			IsRoom7Summoning_ = false;
			IsRoom7InFight_ = true;
		}
	}
	if (true == IsRoom7InFight_)
	{
		if (true == BlueStalfos0->GetIsDeath() /*&&
			true == BlueStalfos1->GetIsDeath() &&
			true == BlueStalfos2->GetIsDeath() &&
			true == BlueStalfos3->GetIsDeath()*/)
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
			GameEngineSound::SoundPlayOneShot("dooropen.mp3");
			GameEngineSound::SoundPlayOneShot("secret.mp3");
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
			GameEngineSound::SoundPlayOneShot("doorclose.mp3");
			IsRoom7DoorOpened_ = false;
			CurRoomState_ = PlayerLink::GetPlayerCurRoomState();
			Room7RightDoor0_->ChangeAnimationReset("Close_Right");
			Room7TopDoor0_->ChangeAnimationReset("Close_Top");
			Room7RightDoor0Col_->On();
			Room7TopDoor0Col_->On();
		}
	}
}

void Map1F_2::Room8CheckTreasureBox()
{

	if (CameraState::Room8 == PlayerLink::GetPlayerCurRoomState())
	{
		if (CameraState::Room8 != CurRoomState_)
		{
			CurRoomState_ = PlayerLink::GetPlayerCurRoomState();
		}

		if (true == PlayerLink::GetIsInItemCutScene())
		{
			if (false == IsRoom8CreateItemRenderer_)
			{
				IsRoom8CreateItemRenderer_ = true;
				Room8ItemRenderer_ = CreateRenderer("ItemCompass.bmp");
				Room8ItemRenderer_->SetPivot(Room8ItemRendererPivot_);
			}
			if (true == IsRoom8CreateItemRenderer_)
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

void Map1F_2::Room5SwitchCheck()
{

	std::vector<GameEngineCollision*> ColList;

	if (true == Room5SwitchCol_->CollisionResult("PlayerLowerBodyHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		if (false == IsRoom5PlayerOnSwitch_)
		{
			if (false == IsRoom5SwitchOn_)
			{
				GameEngineSound::SoundPlayOneShot("button.mp3");
				GameEngineSound::SoundPlayOneShot("dooropen.mp3");
				Room5RightDoor0_->ChangeAnimationReset("Open_Right");
				Room5RightDoor0Col_->Off();
				IsRoom5SwitchOn_ = true;
				IsRoom5PlayerOnSwitch_ = true;
				IsRoom5TimeStop_ = true;
				GameEngineTime::GetInst()->SetTimeScale(0, 0.0f);
				GameEngineTime::GetInst()->SetTimeScale(5, 0.0f);
			}
			else
			{
				GameEngineSound::SoundPlayOneShot("button.mp3");
				GameEngineSound::SoundPlayOneShot("doorclose.mp3");
				Room5RightDoor0_->ChangeAnimationReset("Close_Right");
				Room5RightDoor0Col_->On();
				IsRoom5SwitchOn_ = false;
				IsRoom5PlayerOnSwitch_ = true;
				IsRoom5TimeStop_ = true;
				GameEngineTime::GetInst()->SetTimeScale(0, 0.0f);
				GameEngineTime::GetInst()->SetTimeScale(5, 0.0f);
			}
		}

	}
	else if (false == Room5SwitchCol_->CollisionResult("PlayerLowerBodyHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		IsRoom5PlayerOnSwitch_ = false;
	}

	if (true == IsRoom5TimeStop_ && true == Room5RightDoor0_->IsEndAnimation())
	{
		IsRoom5TimeStop_ = false;
		GameEngineTime::GetInst()->SetTimeScale(0, 1.0f);
		GameEngineTime::GetInst()->SetTimeScale(5, 1.0f);
	}

	if (false == IsRoom5KeyDoorOpened_)
	{
		if (true == Room5LeftKeyDoor0Col2_->CollisionResult("PlayerHitBox", ColList) && 1 <= PlayerLink::GetPlayerKey())
		{
			GameEngineSound::SoundPlayOneShot("chestopen.mp3");
			GameEngineSound::SoundPlayOneShot("dooropen.mp3");
			Room5LeftKeyDoor0_->Death();
			Room5LeftKeyDoor0Col_->Death();
			Room5LeftKeyDoor0Col2_->Death();
			Room4RightKeyDoor0_->Death();
			IsRoom5KeyDoorOpened_ = true;
			PlayerLink::UseKey();
		}
	}



	if (CameraState::Room5 == PlayerLink::GetPlayerCurRoomState())
	{
		if (CameraState::Room5 != CurRoomState_)
		{
			GameEngineSound::SoundPlayOneShot("doorclose.mp3");
			IsRoom5SwitchOn_ = false;
			CurRoomState_ = PlayerLink::GetPlayerCurRoomState();
			Room5RightDoor0_->ChangeAnimationReset("Close_Right");
			Room5RightDoor0Col_->On();
		}
	}

}

void Map1F_2::Room3SwitchCheck()
{
	if (false == IsRoom3SwitchOn_)
	{
		if (true == Room3SwitchCol_->CollisionCheck("PlayerLowerBodyHitBox", CollisionType::Rect, CollisionType::Rect))
		{
			GameEngineSound::SoundPlayOneShot("chestappears.mp3");
			IsRoom3SwitchOn_ = true;
			Room3TreasureBox_ = GetLevel()->CreateActor<Map1FRoom3TreasureBox>(static_cast<int>(PlayLevelOrder::BELOWPLAYER));
			Room5SwitchCol_->Off();
		}
	}
}