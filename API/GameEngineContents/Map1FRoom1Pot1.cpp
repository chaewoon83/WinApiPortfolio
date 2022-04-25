#include "Map1FRoom1Pot1.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include "PlayerLink.h"

//3016, 3428
//48, 48 (+1, -1)
// �޿� �޸��� (0,-6)


Map1FRoom1Pot1::Map1FRoom1Pot1() 
	:Renderer_(nullptr),
	 BlockCol_(nullptr),
	 PickUpCol_(nullptr),
	 PotHitBox_(nullptr),
	 PotHitBox2_(nullptr),
	 PotPos_({ 3041.0f, 3451.0f }),
	 MoveDir_(float4::ZERO),
	 IsInRoom_(false),
	 Speed_(800.0f),
	 YSpeed_(20.0f),
	 CurYSpeed_(20.0f),
	 AirTime_(0.35f),
	 CurAirTime_(0.0f),
	 CurPotState_(PotState::Idle)
{

}

Map1FRoom1Pot1::~Map1FRoom1Pot1() 
{
}

void Map1FRoom1Pot1::Start()
{
	Renderer_ = CreateRenderer();
	SetPosition(PotPos_);
	BlockCol_ = CreateCollision("Pot", { 48, 48 });
	PickUpCol_ = CreateCollision("PotCarry", { 50, 50 });
	Renderer_->CreateAnimation("Pot_Destroyed.bmp", "Pot_Destroyed", 0, 7, 0.05f, false);
	Renderer_->CreateAnimation("Pot.bmp", "Pot", 0, 0, 0.05f, false);
	Renderer_->ChangeAnimation("Pot");
}
 
void Map1FRoom1Pot1::Update()
{
	Reset();
	PotStateUpdate();
}
void Map1FRoom1Pot1::Render()
{

}

void Map1FRoom1Pot1::IdleStart()
{

}

void Map1FRoom1Pot1::CarriedStart()
{

}

void Map1FRoom1Pot1::InAirStart()
{
	if (nullptr == PotHitBox_)
	{
		PotHitBox_ = CreateCollision("PotHitBox", { 48, 48 });
		PotHitBox2_ = CreateCollision("PotHitBox2", { 48, 48 });
	}
	CurYSpeed_ = YSpeed_;
}

void Map1FRoom1Pot1::DeathAnimationStart()
{
	if (false == PotHitBox2_->IsDeath())
	{
		PotHitBox2_->Death();
	}
	PotHitBox_->Death();
	PotHitBox_ = nullptr;
	CurAirTime_ = 0.0f;
	Renderer_->ChangeAnimationReset("Pot_Destroyed");
}

void Map1FRoom1Pot1::DeathStart()
{
	IsInRoom_ = false;
	Renderer_->Off();
}

void Map1FRoom1Pot1::IdleUpdate()
{
	if (PlayerLink::CarryActor_ == this)
	{
		BlockCol_->Death();
		PickUpCol_->Death();
		BlockCol_ = nullptr;
		PickUpCol_ = nullptr;
		PotStateChange(PotState::Carried);
		return;
	}
}

void Map1FRoom1Pot1::CarriedUpdate()
{
	{
		if (PlayerState::CarryMoveLeft == dynamic_cast<PlayerLink*>(PlayerLink::MainPlayer_)->GetPlayerCurState() &&
			1 == dynamic_cast<PlayerLink*>(PlayerLink::MainPlayer_)->GetCurrentAnimationFrame_())
		{
			SetPosition(PlayerLink::MainPlayer_->GetPosition() + float4{ 2.0f, -53.0f + 4.0f });
		}
		else if (PlayerState::CarryMoveRight == dynamic_cast<PlayerLink*>(PlayerLink::MainPlayer_)->GetPlayerCurState() &&
			1 == dynamic_cast<PlayerLink*>(PlayerLink::MainPlayer_)->GetCurrentAnimationFrame_())
		{
			SetPosition(PlayerLink::MainPlayer_->GetPosition() + float4{ -2.0f, -53.0f + 4.0f });
		}
		else
		{
			SetPosition(PlayerLink::MainPlayer_->GetPosition() + float4{ 0.0f, -53.0f });
		}
	}

	if (GameEngineInput::GetInst()->IsDown("Interact") && true == CheckPickUpEnd())
	{

		if (PlayerState::CarryMoveRight == dynamic_cast<PlayerLink*>(PlayerLink::MainPlayer_)->GetPlayerPrevState() ||
			PlayerState::CarryIdleRight == dynamic_cast<PlayerLink*>(PlayerLink::MainPlayer_)->GetPlayerPrevState())
		{
			MoveDir_ = float4::RIGHT;
			PotStateChange(PotState::InAir);
			return;
		}
		if (PlayerState::CarryMoveLeft == dynamic_cast<PlayerLink*>(PlayerLink::MainPlayer_)->GetPlayerPrevState() ||
			PlayerState::CarryIdleLeft == dynamic_cast<PlayerLink*>(PlayerLink::MainPlayer_)->GetPlayerPrevState())
		{
			MoveDir_ = float4::LEFT;
			PotStateChange(PotState::InAir);
			return;
		}
		if (PlayerState::CarryMoveUp == dynamic_cast<PlayerLink*>(PlayerLink::MainPlayer_)->GetPlayerPrevState() ||
			PlayerState::CarryIdleUp == dynamic_cast<PlayerLink*>(PlayerLink::MainPlayer_)->GetPlayerPrevState())
		{
			MoveDir_ = float4::UP;
			PotStateChange(PotState::InAir);
			return;
		}
		if (PlayerState::CarryMoveDown == dynamic_cast<PlayerLink*>(PlayerLink::MainPlayer_)->GetPlayerPrevState() ||
			PlayerState::CarryIdleDown == dynamic_cast<PlayerLink*>(PlayerLink::MainPlayer_)->GetPlayerPrevState())
		{
			MoveDir_ = float4::DOWN;
			PotStateChange(PotState::InAir);
			return;
		}

	}
}

void Map1FRoom1Pot1::InAirUpdate()
{
	CurAirTime_ += GameEngineTime::GetDeltaTime();
	if (AirTime_ < CurAirTime_)
	{
		PotStateChange(PotState::DeathAnimation);
		return;
	}
	CurYSpeed_ += 1000.0f * GameEngineTime::GetDeltaTime();
	SetMove(((MoveDir_ * Speed_) + float4{ 0, CurYSpeed_ }) * GameEngineTime::GetDeltaTime());

	std::vector<GameEngineCollision*> ColList;
	if (true == PotHitBox_->CollisionResult("MonsterHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		PotStateChange(PotState::DeathAnimation);
		return;
	}
}

void Map1FRoom1Pot1::DeathAnimationUpdate()
{
	if (true == Renderer_->IsEndAnimation())
	{
		PlayerLink::CarryActor_ = nullptr;
		PotStateChange(PotState::Death);
		return;
	}
}

void Map1FRoom1Pot1::DeathUpdate()
{

}

void Map1FRoom1Pot1::PotStateChange(PotState _State)
{
	if (CurPotState_ != _State)
	{
		switch (_State)
		{
		case PotState::Idle:
			IdleStart();
			break;
		case PotState::Carried:
			CarriedStart();
			break;
		case PotState::InAir:
			InAirStart();
			break;
		case PotState::DeathAnimation:
			DeathAnimationStart();
			break;
		case PotState::Death:
			DeathStart();
			break;
		case PotState::Max:
			break;
		default:
			break;
		}
		CurPotState_ = _State;
	}

}

void Map1FRoom1Pot1::PotStateUpdate()
{
	switch (CurPotState_)
	{
	case PotState::Idle:
		IdleUpdate();
		break;
	case PotState::Carried:
		CarriedUpdate();
		break;
	case PotState::InAir:
		InAirUpdate();
		break;
	case PotState::DeathAnimation:
		DeathAnimationUpdate();
		break;
	case PotState::Death:
		DeathUpdate();
		break;
	case PotState::Max:
		break;
	default:
		break;
	}
}


bool Map1FRoom1Pot1::CheckPickUpEnd()
{
	if (PlayerState::CarryStartRight == dynamic_cast<PlayerLink*>(PlayerLink::MainPlayer_)->GetPlayerCurState() ||
		PlayerState::CarryStartLeft == dynamic_cast<PlayerLink*>(PlayerLink::MainPlayer_)->GetPlayerCurState() ||
		PlayerState::CarryStartUp == dynamic_cast<PlayerLink*>(PlayerLink::MainPlayer_)->GetPlayerCurState() ||
		PlayerState::CarryStartDown == dynamic_cast<PlayerLink*>(PlayerLink::MainPlayer_)->GetPlayerCurState())
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Map1FRoom1Pot1::Reset()
{
	if (CameraState::Room3 == PlayerLink::GetPlayerPrevRoomState() &&  false == IsInRoom_ && PotState::Death == CurPotState_)
	{
		IsInRoom_ = true;
		CurYSpeed_ = 0;
		SetPosition(PotPos_);
		BlockCol_ = CreateCollision("Pot", { 48, 48 });
		PickUpCol_ = CreateCollision("PotCarry", { 50, 50 });
		Renderer_->ChangeAnimation("Pot");
		PotStateChange(PotState::Idle);
		Renderer_->On();
	}
}