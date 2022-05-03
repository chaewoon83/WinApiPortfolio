#include "PlayerLink.h"
#include <windows.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineCollision.h>

#include "Map1F.h"
#include "Boomerang.h"

//링크의 크기 == 64x96
//링크 히트박스의 크키 == 64x64


//FIN
//대각선입력 속력 노말라이즈 하기V
//FSM 대입하기V
//걷기애니메이션 추가V
//TODO
//통로 통과 버그 고치기 ( 키 꾹누르면 state가 변화하지 않음)
//공격 애니메이션, 함수 추가
//피격 함수 추가

//통로 세로 길이 384
//통로 가로 길이 320

//파란색 -> 층이동
//노란색 -> 문이동
//빨간색 -> 닫힌 문 이동

GameEngineImage* PlayerLink::MapColImage_ = nullptr;
GameEngineImage* PlayerLink::MapCarryColImage_ = nullptr;
bool PlayerLink::IsMap1F_2 = false;
bool PlayerLink::IsOnB1F = false;
GameEngineActor* PlayerLink::MainPlayer_ = nullptr;
GameEngineActor* PlayerLink::CarryActor_ = nullptr;
PlayerState PlayerLink::PlayerCurState_ = PlayerState::IdleDown;
PlayerState PlayerLink::PlayerPrevState_ = PlayerState::Max;
//디버그용
//CameraState PlayerLink::CameraState_ = CameraState::Room10;
//CameraState PlayerLink::PrevCameraState_ = CameraState::Room9;
CameraState PlayerLink::CameraState_ = CameraState::Room1;
CameraState PlayerLink::PrevCameraState_ = CameraState::Max;
PlayerStairsState PlayerLink::CurStairs_ = PlayerStairsState::Top;
bool PlayerLink::IsOnStairs_ = false;
bool PlayerLink::IsCarry_ = false;
bool PlayerLink::IsInItemCutScene_ = false;

float PlayerLink::ItemMoveTime_ = 1.0f;
float PlayerLink::CurItemMoveTime_ = 0.0f;

int PlayerLink::CurrentAnimationFrame_ = -1;

PlayerLink::PlayerLink()
	:MapColImage_1_(nullptr)
	, MapColImage_2_(nullptr)
	, BridgeActor_(nullptr)
	, PlayerLowerBodyCollision_(nullptr)
	, HitActor_(nullptr)
	, Speed_(350.0f)
	, KnockBackSpeed_(350.0f)
	, IsCameraAutoMove_(false)
	, IsCharacterAutoMove_(false)
	, AutoMoveDir_(float4::ZERO)
	, PlayerCollision_(nullptr)
	, SwordCollision_(nullptr)
	, AnimationTimer_(0.0f)
	, AnimationIndex_(0)
	, AttackAnimationInterval_(0.04f)
	, IsGetDamaged_(false)
	, IsKnockback_(false)
	, IsBlink_(false)
	, KnockbackTime_(0.2f)
	, CurKnockbackTime_(0.0f)
	, BlinkTime_(1.5f)
	, CurBlinkTime_(0.0f)
	, BlinkFreq_(0.01f)
	, CurBlinkFreq_(0.0f)
	, IsAlphaOn_(true)
	, Hp_(10)
{
}

PlayerLink::~PlayerLink() 
{
}

void PlayerLink::Start()
{

	//충돌
	PlayerCollision_ = CreateCollision("PlayerHitBox", {64, 64});
	PlayerLowerBodyCollision_ = CreateCollision("PlayerLowerBodyHitBox", {64, 20} , {0, 22});
	PlayerHigherBodyCollision_ = CreateCollision("PlayerHigherBodyHitBox", { 64, 20 }, { 0, -22 });
	PlayerMoveCollision_ = CreateCollision("PlayerHitBox2", {64, 64}, {0, 12});
	PlayerTopRightCollision_ = CreateCollision("PlayerTopRightHitBox", {20, 20 }, { 22, -10 });
	PlayerTopLeftCollision_ = CreateCollision("PlayerTopLeftHitBox", { 20, 20 }, { -22, -10 });
	PlayerBotRightCollision_ = CreateCollision("PlayerBotRightHitBox", { 20, 20 }, { 22, 34 });
	PlayerBotLeftCollision_ = CreateCollision("PlayerBotLeftHitBox", { 20, 20 }, { -22, 34 });
	PlayerMiddleHorCollision_ = CreateCollision("PlayerBotLeftHitBox", { 64, 24 }, {0, 12});
	PlayerMiddleVerCollision_ = CreateCollision("PlayerBotLeftHitBox", { 24, 64 }, {0, 12});

	SwordCollision_ = CreateCollision("Sword", { 0, 0 });
	SwordCollision_->Off();
	
	//PlayerCollision_->Off();
	//PlayerMoveCollision_->Off();

	//GameEngineRenderer* ExampleRenderer;
	//ExampleRenderer = CreateRenderer();
	//ExampleRenderer->SetImage("Idle.bmp");
	//ExampleRenderer->SetAlpha(100);
	//플레이어가 레벨을 시작할때마다 시작 지점이 다르기 때문에 Level에서 위치를 정해줘야한다
	//SetPosition(GameEngineWindow::GetScale().Half());
	PlayerRenderer_ = CreateRenderer();
	//PlayerRenderer->SetAlpha(50);
	//true 면 루프 false 면 루프아님
	//PlayerRenderer->SetPivot({ 0, -11 });

	PlayerRenderer_->CreateAnimation("Link_Idle_Right.bmp", "Idle_Right", 0, 1, 0.05f, false);
	PlayerRenderer_->CreateAnimation("Link_Idle_Left.bmp", "Idle_Left", 0, 1, 0.05f, false);
	PlayerRenderer_->CreateAnimation("Link_Idle_Up.bmp", "Idle_Up", 0, 1, 0.05f, false);
	PlayerRenderer_->CreateAnimation("Link_Idle_Down.bmp", "Idle_Down", 0, 1, 0.05f, false);

	PlayerRenderer_->CreateAnimation("Link_Walk_Right.bmp", "Walk_Right", 0, 5, 0.05f, true);
	PlayerRenderer_->CreateAnimation("Link_Walk_Left.bmp", "Walk_Left", 0, 5, 0.05f, true);
	PlayerRenderer_->CreateAnimation("Link_Walk_Up.bmp", "Walk_Up", 0, 7, 0.05f, true);
	PlayerRenderer_->CreateAnimation("Link_Walk_Down.bmp", "Walk_Down", 0, 7, 0.05f, true);

	PlayerRenderer_->CreateAnimation("Link_Wield_Right.bmp", "Wield_Right", 0, 4, AttackAnimationInterval_, true);
	PlayerRenderer_->CreateAnimation("Link_Wield_Left.bmp", "Wield_Left", 0, 4, AttackAnimationInterval_, true);
	PlayerRenderer_->CreateAnimation("Link_Wield_Up.bmp", "Wield_Up", 0, 4, AttackAnimationInterval_, true);
	PlayerRenderer_->CreateAnimation("Link_Wield_Down.bmp", "Wield_Down", 0, 5, AttackAnimationInterval_, true);

	PlayerRenderer_->CreateAnimation("Link_Damaged_Right.bmp", "Damaged_Right", 0, 1, 0.05f, false);
	PlayerRenderer_->CreateAnimation("Link_Damaged_Left.bmp", "Damaged_Left", 0, 1, 0.05f, false);
	PlayerRenderer_->CreateAnimation("Link_Damaged_Up.bmp", "Damaged_Up", 0, 1, 0.05f, false);
	PlayerRenderer_->CreateAnimation("Link_Damaged_Down.bmp", "Damaged_Down", 0, 1, 0.05f, false);

	PlayerRenderer_->CreateAnimation("Link_Carry_Start_Right.bmp", "Carry_Start_Right", 0, 2, 0.2f, false);
	PlayerRenderer_->CreateAnimation("Link_Carry_Start_Left.bmp", "Carry_Start_Left", 0, 2, 0.2f, false);
	PlayerRenderer_->CreateAnimation("Link_Carry_Start_Up.bmp", "Carry_Start_Up", 0, 2, 0.2f, false);
	PlayerRenderer_->CreateAnimation("Link_Carry_Start_Down.bmp", "Carry_Start_Down", 0, 2, 0.2f, false);

	PlayerRenderer_->CreateAnimation("Link_Carry_Idle_Right.bmp", "Carry_Idle_Right", 0, 1, 0.25f, true);
	PlayerRenderer_->CreateAnimation("Link_Carry_Idle_Left.bmp", "Carry_Idle_Left", 0, 1, 0.25f, true);
	PlayerRenderer_->CreateAnimation("Link_Carry_Idle_Up.bmp", "Carry_Idle_Up", 0, 1, 0.25f, true);
	PlayerRenderer_->CreateAnimation("Link_Carry_Idle_Down.bmp", "Carry_Idle_Down", 0, 1, 0.25f, true);

	PlayerRenderer_->CreateAnimation("Link_Carry_Move_Right.bmp", "Carry_Move_Right", 0, 1, 0.1f, true);
	PlayerRenderer_->CreateAnimation("Link_Carry_Move_Left.bmp", "Carry_Move_Left", 0, 1, 0.1f, true);
	PlayerRenderer_->CreateAnimation("Link_Carry_Move_Up.bmp", "Carry_Move_Up", 0, 4, 0.1f, true);
	PlayerRenderer_->CreateAnimation("Link_Carry_Move_Down.bmp", "Carry_Move_Down", 0, 4, 0.1f, true);

	int a = PlayerRenderer_->GetOrder();
	PlayerRenderer_->ChangeAnimation("Idle_Down");

	//아래부터 넣은 렌더러들이 맨 위부터 나온다
	//CreateRenderer("LinkStandStill.bmp");
	//CreateRendererToScale("HPBAR.bmp", float4(100.0f, 20.0f), RenderPivot::CENTER, {0, -100});
	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		//이때 대문자여야 한다
		GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("MoveUp", 'W');
		GameEngineInput::GetInst()->CreateKey("MoveDown", 'S');
		GameEngineInput::GetInst()->CreateKey("Attack", 'K');
		GameEngineInput::GetInst()->CreateKey("InterAct", 'L');
		GameEngineInput::GetInst()->CreateKey("Debug", '9');
	}
	MapColImage_1_ = GameEngineImageManager::GetInst()->Find("EastPalace1F_1_1F_ColMap.bmp");

	if (nullptr == MapColImage_1_)
	{
		MsgBoxAssert("충돌용 맵을 찾지 못했습니다");
	}

	MapColImage_2_ = GameEngineImageManager::GetInst()->Find("EastPalace1F_2_1F_ColMap.bmp");

	if (nullptr == MapColImage_2_)
	{
		MsgBoxAssert("충돌용 맵을 찾지 못했습니다");
	}

	MapColImage_ = MapColImage_1_;

	MapCarryColImage_1_ = GameEngineImageManager::GetInst()->Find("EastPalace1F_1_1F_CarryColMap.bmp");

	if (nullptr == MapColImage_1_)
	{
		MsgBoxAssert("충돌용 맵을 찾지 못했습니다");
	}
	MapCarryColImage_2_ = GameEngineImageManager::GetInst()->Find("EastPalace1F_2_1F_CarryColMap.bmp");

	if (nullptr == MapCarryColImage_2_)
	{
		MsgBoxAssert("충돌용 맵을 찾지 못했습니다");
	}

	MapCarryColImage_ = MapCarryColImage_1_;

	MapPasImage_1 = GameEngineImageManager::GetInst()->Find("EastPalace1F_1_1F_PasMap.bmp");

	if (nullptr == MapPasImage_1)
	{
		MsgBoxAssert("통로 맵을 찾지 못했습니다");
	}

	MapPasImage_2 = GameEngineImageManager::GetInst()->Find("EastPalace1F_2_1F_PasMap.bmp");

	if (nullptr == MapPasImage_2)
	{
		MsgBoxAssert("통로 맵을 찾지 못했습니다");
	}
	MapPasImage_ = MapPasImage_1;

	RoomSize_[0] = { 2048, 4063 + 4128 };
	RoomSize_[1] = { 4095, 3088 + 4128 };

	{
		//SetPosition({ 3072.0f, 3800.0f });
		GetLevel()->SetCameraPos({ 3072.0f, 3800.0f });
		RoomSize_[0] = { 0, 3041 };
		RoomSize_[1] = { 1021, 2048 };
		CameraState_ = CameraState::Room8;
		PrevCameraState_ = CameraState::Room7;
	}


}
 
void PlayerLink::Update()
{
	if (GameEngineInput::GetInst()->IsDown("Debug"))
	{
		GetLevel()->IsDebugModeSwitch();
	}

	if (4128 > GetPosition().iy() && false == IsMap1F_2)
	{
		IsMap1F_2 = true;
		MapPasImage_ = MapPasImage_2;
		MapCarryColImage_ = MapCarryColImage_2_;
		if (/*false == IsOnB1F && */PlayerStairsState::Top == CurStairs_)
		{
			//IsOnB1F = true;
			MapColImage_ = MapColImage_2_;
		}

		//if (true == IsOnB1F && PlayerStairsState::Top == CurStairs_)
		//{
		//	IsOnB1F = false;
		//	MapColImage_ = MapColImage_2_;
		//}
	}
	if (4128 <= GetPosition().iy() && true == IsMap1F_2)
	{
		IsMap1F_2 = false;
		MapPasImage_ = MapPasImage_1;
		MapCarryColImage_ = MapCarryColImage_1_;
		if (PlayerStairsState::Top == CurStairs_)
		{
			MapColImage_ = MapColImage_1_;
		}
	}

	PlayerStateUpdate();
	CameraStateUpdate();
	//애니메이셔 프레임 받기
	CurrentAnimationFrame_ = PlayerRenderer_->GetCurrentAnimationFrame();
	BlinkUpdate();
	

}
//렌더러가 다 돌고 액터들의 랜더함수를 호출한다
void PlayerLink::Render()
{

}

bool PlayerLink::IsMoveKeyFree()
{
	if (false == GameEngineInput::GetInst()->IsPress("MoveRight") &&
		false == GameEngineInput::GetInst()->IsPress("MoveLeft") &&
		false == GameEngineInput::GetInst()->IsPress("MoveUp") &&
		false == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		return true;
	}

	return false;
}

bool PlayerLink::IsRightMoveKey()
{
	if (true == GameEngineInput::GetInst()->IsDown("MoveRight"))
	{
		return true;
	}

	return false;
}

bool PlayerLink::IsLeftMoveKey()
{
	if (true == GameEngineInput::GetInst()->IsDown("MoveLeft"))
	{
		return true;
	}

	return false;
}

bool PlayerLink::IsUpMoveKey()
{
	if (true == GameEngineInput::GetInst()->IsDown("MoveUp"))
	{
		return true;
	}

	return false;
}

bool PlayerLink::IsDownMoveKey()
{
	if (true == GameEngineInput::GetInst()->IsDown("MoveDown"))
	{
		return true;
	}

	return false;
}

void PlayerLink::CameraUpdate()
{
	{
		GetLevel()->SetCameraPos(GetPosition() - GameEngineWindow::GetInst().GetScale().Half());
		float4 A = GetPosition();
		float4 CurCameraPos = GetLevel()->GetCameraPos();

		if (RoomSize_[0].x > CurCameraPos.x)
		{
			CurCameraPos.x = RoomSize_[0].x;
			GetLevel()->SetCameraPos(CurCameraPos);
		}

		if (RoomSize_[0].y - GameEngineWindow::GetInst().GetScale().y < CurCameraPos.y)
		{
			int a = 0;
			CurCameraPos.y = RoomSize_[0].y - GameEngineWindow::GetInst().GetScale().y;
			GetLevel()->SetCameraPos(CurCameraPos);
		}


		if (RoomSize_[1].x - GameEngineWindow::GetInst().GetScale().x < CurCameraPos.x)
		{
			CurCameraPos.x = RoomSize_[1].x - GameEngineWindow::GetScale().x;
			GetLevel()->SetCameraPos(CurCameraPos);
		}

		if (RoomSize_[1].y > CurCameraPos.y)
		{
			CurCameraPos.y = RoomSize_[1].y;
			GetLevel()->SetCameraPos(CurCameraPos);
		}
	}
}

bool PlayerLink::PosOrColorCheck(int _Color, GameEngineImage* _Image)
{
	float4 MyPos = GetPosition();
	float4 Map1f_2_Scale = float4{ 0, -4128 };
	if (false == IsMap1F_2)
	{
		MyPos += Map1f_2_Scale;
	}
	float4 MyPosTopRight = MyPos + float4{ 32.0f, -21.0f };
	float4 MyPosTopLeft = MyPos + float4{ -32.0f, -21.0f };
	float4 MyPosBotRight = MyPos + float4{ 32.0f, 43.0f };
	float4 MyPosBotLeft = MyPos + float4{ -32.0f, 43.0f };
	float4 MyPosRight = MyPos + float4{ 32.0f, 0.0f };
	float4 MyPosLeft = MyPos + float4{ -32.0f, 0.0f };
	float4 MyPosTop = MyPos + float4{ 0.0f, -21.0f };
	float4 MyPosBot = MyPos + float4{ 0.0f, 43.0f };

	int ColorTopRight = _Image->GetImagePixel(MyPosTopRight);
	int ColorTopLeft = _Image->GetImagePixel(MyPosTopLeft);
	int ColorBotRight = _Image->GetImagePixel(MyPosBotRight);
	int ColorBotLeft = _Image->GetImagePixel(MyPosBotLeft);
	int ColorRight = _Image->GetImagePixel(MyPosRight);
	int ColorLeft = _Image->GetImagePixel(MyPosLeft);
	int ColorTop = _Image->GetImagePixel(MyPosTop);
	int ColorBot = _Image->GetImagePixel(MyPosBot);



	if (_Color == ColorTopRight ||
		_Color == ColorTopLeft ||
		_Color == ColorBotRight ||
		_Color == ColorBotLeft ||
		_Color == ColorRight ||
		_Color == ColorLeft ||
		_Color == ColorBot ||
		_Color == ColorTop)
	{
		return true;
	}
	return false;
}

bool PlayerLink::PosAndColorCheck(int _Color, GameEngineImage* _Image)
{
	float4 MyPos = GetPosition();
	float4 Map1f_2_Scale = float4{ 0, -4128 };
	if (false == IsMap1F_2)
	{
		MyPos += Map1f_2_Scale;
	}
	float4 MyPosTopRight = MyPos + float4{ 32.0f, -21.0f };
	float4 MyPosTopLeft = MyPos + float4{ -32.0f, -21.0f };
	float4 MyPosBotRight = MyPos + float4{ 32.0f, 43.0f };
	float4 MyPosBotLeft = MyPos + float4{ -32.0f, 43.0f };
	float4 MyPosRight = MyPos + float4{ 32.0f, 0.0f };
	float4 MyPosLeft = MyPos + float4{ -32.0f, 0.0f };
	float4 MyPosTop = MyPos + float4{ 0.0f, -21.0f };
	float4 MyPosBot = MyPos + float4{ 0.0f, 43.0f };

	int ColorTopRight = _Image->GetImagePixel(MyPosTopRight);
	int ColorTopLeft = _Image->GetImagePixel(MyPosTopLeft);
	int ColorBotRight = _Image->GetImagePixel(MyPosBotRight);
	int ColorBotLeft = _Image->GetImagePixel(MyPosBotLeft);
	int ColorRight = _Image->GetImagePixel(MyPosRight);
	int ColorLeft = _Image->GetImagePixel(MyPosLeft);
	int ColorTop = _Image->GetImagePixel(MyPosTop);
	int ColorBot = _Image->GetImagePixel(MyPosBot);



	if (_Color != ColorTopRight &&
		_Color != ColorTopLeft &&
		_Color != ColorBotRight &&
		_Color != ColorBotLeft &&
		_Color != ColorRight &&
		_Color != ColorLeft &&
		_Color != ColorBot &&
		_Color != ColorTop)
	{
		return true;
	}
	return false;
}

void PlayerLink::CameraAutoMove()
{
	if (AutoMoveDir_.CompareInt2D(float4::RIGHT))
	{
		float4 CurCameraPos = GetLevel()->GetCameraPos();

		GetLevel()->SetCameraPos(CurCameraPos + AutoMoveDir_ * GameEngineTime::GetDeltaTime() * 800);

		float Time = GameEngineTime::GetDeltaTime();


		if (RoomSize_[0].x < GetLevel()->GetCameraPos().x)
		{
			IsCameraAutoMove_ = false;
		}
	}

	if (AutoMoveDir_.CompareInt2D(float4::LEFT))
	{
		float4 CurCameraPos = GetLevel()->GetCameraPos();

		GetLevel()->SetCameraPos(CurCameraPos + AutoMoveDir_ * GameEngineTime::GetDeltaTime() * 800);

		float Time = GameEngineTime::GetDeltaTime();


		if (RoomSize_[1].x - GameEngineWindow::GetInst().GetScale().x > GetLevel()->GetCameraPos().x)
		{
			IsCameraAutoMove_ = false;
		}
	}
	if (AutoMoveDir_.CompareInt2D(float4::UP))
	{
		float4 CurCameraPos = GetLevel()->GetCameraPos();

		GetLevel()->SetCameraPos(CurCameraPos + AutoMoveDir_ * GameEngineTime::GetDeltaTime() * 800);

		float Time = GameEngineTime::GetDeltaTime();


		if (RoomSize_[0].y - GameEngineWindow::GetInst().GetScale().y > GetLevel()->GetCameraPos().y)
		{
			IsCameraAutoMove_ = false;
		}
	}

	if (AutoMoveDir_.CompareInt2D(float4::DOWN))
	{
		float4 CurCameraPos = GetLevel()->GetCameraPos();

		GetLevel()->SetCameraPos(CurCameraPos + AutoMoveDir_ * GameEngineTime::GetDeltaTime() * 800);

		float Time = GameEngineTime::GetDeltaTime();


		if (RoomSize_[1].y < GetLevel()->GetCameraPos().y)
		{
			IsCameraAutoMove_ = false;
		}
	}


}

bool PlayerLink::IsPlayerMoveState()
{
	if (PlayerState::MoveRight == PlayerCurState_ ||
		PlayerState::MoveLeft == PlayerCurState_ || 
		PlayerState::MoveUp == PlayerCurState_ || 
		PlayerState::MoveDown == PlayerCurState_)
	{
		return true;
	}
	return false;
}

void PlayerLink::PlayerSetIdle()
{

}

void PlayerLink::PlayerAutoMove()
{
	CheckDirection();
	SetMove(AutoMoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
	int Red = RGB(255, 0, 0);
	if (PosAndColorCheck(Red, MapPasImage_))
	{
		IsCharacterAutoMove_ = false;
	}
}

void PlayerLink::PlayerAutoMove(float _Speed)
{
	CheckDirection();
	SetMove(AutoMoveDir_ * GameEngineTime::GetDeltaTime() * _Speed);
	int Red = RGB(255, 0, 0);
	if (PosAndColorCheck(Red, MapPasImage_))
	{
		IsCharacterAutoMove_ = false;
	}
}

void PlayerLink::CheckDirection()
{
	if (PlayerState::MoveRight == PlayerCurState_)
	{
		AutoMoveDir_ = float4::RIGHT;
	}
	if (PlayerState::MoveLeft == PlayerCurState_)
	{
		AutoMoveDir_ = float4::LEFT;
	}
	if (PlayerState::MoveUp == PlayerCurState_)
	{
		AutoMoveDir_ = float4::UP;
	}
	if (PlayerState::MoveDown == PlayerCurState_)
	{
		AutoMoveDir_ = float4::DOWN;
	}
}

/////////////////////////////////////////////////////////////////////Combat

void PlayerLink::GetDamaged()
{
	Hp_ -= 1;
}

void PlayerLink::BlinkUpdate()
{

	if (true == IsBlink_)
	{
		CurBlinkTime_  += GameEngineTime::GetDeltaTime();
		CurBlinkFreq_ += GameEngineTime::GetDeltaTime();
		if (BlinkFreq_ < CurBlinkFreq_)
		{
			CurBlinkFreq_ = 0.0f;
			if (false == IsAlphaOn_)
			{
				PlayerRenderer_->SetAlpha(255);
				IsAlphaOn_ = true;
			}
			else
			{
				PlayerRenderer_->SetAlpha(0);
				IsAlphaOn_ = false;
			}
		}

		if (BlinkTime_ < CurBlinkTime_)
		{

			IsBlink_ = false;
			CurBlinkTime_ = 0.0f;
			CurBlinkFreq_ = 0.0f;
			IsAlphaOn_ = true;
			PlayerRenderer_->SetAlpha(255);
		}
	}

}


/// //////////////////////////// State Change, Update
 
void PlayerLink::PlayerChangeState(PlayerState _State)
{
	if (PlayerCurState_ != _State)
	{
		switch (_State)
		{
		case PlayerState::IdleRight:
			IdleRightStart();
			break;
		case PlayerState::IdleLeft:
			IdleLeftStart();
			break;
		case PlayerState::IdleUp:
			IdleUpStart();
			break;
		case PlayerState::IdleDown:
			IdleDownStart();
			break;
		case PlayerState::MoveRight:
			MoveRightStart();
			break;
		case PlayerState::MoveLeft:
			MoveLeftStart();
			break;
		case PlayerState::MoveUp:
			MoveUpStart();
			break;
		case PlayerState::MoveDown:
			MoveDownStart();
			break;
		case PlayerState::WieldRight:
			WieldRightStart();
			break;
		case PlayerState::WieldLeft:
			WieldLeftStart();
			break;
		case PlayerState::WieldUp:
			WieldUpStart();
			break;
		case PlayerState::WieldDown:
			WieldDownStart();
			break;
		case PlayerState::WieldRight_1:
			WieldRightStart();
			break;
		case PlayerState::WieldLeft_1:
			WieldLeftStart();
			break;
		case PlayerState::WieldUp_1:
			WieldUpStart();
			break;
		case PlayerState::WieldDown_1:
			WieldDownStart();
			break;
		case PlayerState::DamagedRight:
			DamagedRightStart();
			break;
		case PlayerState::DamagedLeft:
			DamagedLeftStart();
			break;
		case PlayerState::DamagedUp:
			DamagedUpStart();
			break;
		case PlayerState::DamagedDown:
			DamagedDownStart();
			break;
		case PlayerState::CarryStartRight:
			CarryStartRightStart();
			break;
		case PlayerState::CarryStartLeft:
			CarryStartLeftStart();
			break;
		case PlayerState::CarryStartUp:
			CarryStartUpStart();
			break;
		case PlayerState::CarryStartDown:
			CarryStartDownStart();
			break;
		case PlayerState::CarryIdleRight:
			CarryIdleRightStart();
			break;
		case PlayerState::CarryIdleLeft:
			CarryIdleLeftStart();
			break;
		case PlayerState::CarryIdleUp:
			CarryIdleUpStart();
			break;
		case PlayerState::CarryIdleDown:
			CarryIdleDownStart();
			break;
		case PlayerState::CarryMoveRight:
			CarryMoveRightStart();
			break;
		case PlayerState::CarryMoveLeft:
			CarryMoveLeftStart();
			break;
		case PlayerState::CarryMoveUp:
			CarryMoveUpStart();
			break;
		case PlayerState::CarryMoveDown:
			CarryMoveDownStart();
			break;
		case PlayerState::Max:
			break;
		default:
			break;
		}
	}

	PlayerCurState_ = _State;
}

void PlayerLink::PlayerStateUpdate()
{
	switch (PlayerCurState_)
	{
	case PlayerState::IdleRight:
	case PlayerState::IdleLeft:
	case PlayerState::IdleUp:
	case PlayerState::IdleDown:
		IdleUpdate();
		break;
	case PlayerState::MoveRight:
	case PlayerState::MoveLeft:
	case PlayerState::MoveUp:
	case PlayerState::MoveDown:
		MoveUpdate();
		break;
	case PlayerState::WieldRight:
	case PlayerState::WieldLeft:
	case PlayerState::WieldUp:
	case PlayerState::WieldDown:
	case PlayerState::WieldRight_1:
	case PlayerState::WieldLeft_1:
	case PlayerState::WieldUp_1:
	case PlayerState::WieldDown_1:
		WieldUpdate();
		break;
	case PlayerState::DamagedRight:
	case PlayerState::DamagedLeft:
	case PlayerState::DamagedUp:
	case PlayerState::DamagedDown:
		DamagedUpdate();
		break;
	case PlayerState::CarryStartRight:
	case PlayerState::CarryStartLeft:
	case PlayerState::CarryStartUp:
	case PlayerState::CarryStartDown:
		CarryStartUpdate();
		break;
	case PlayerState::CarryIdleRight:
	case PlayerState::CarryIdleLeft:
	case PlayerState::CarryIdleUp:
	case PlayerState::CarryIdleDown:
		CarryIdleUpdate();
		break;
	case PlayerState::CarryMoveRight:
	case PlayerState::CarryMoveLeft:
	case PlayerState::CarryMoveUp:
	case PlayerState::CarryMoveDown:
		CarryMoveUpdate();
		break;
	case PlayerState::Max:
		break;
	default:
		break;
	}
}