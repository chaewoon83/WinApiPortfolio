#include "Map1FRoom1Pot0.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include "PlayerLink.h"

//2536, 3428
//48, 48 (+1, -1)
// ¿Þ¿À ´Þ¸±‹š (0,-6)


Map1FRoom1Pot0::Map1FRoom1Pot0() 
	:Renderer_(nullptr),
	 BlockCol_(nullptr),
	 PickUpCol_(nullptr),
	 PotHitBox_(nullptr),
	 MoveDir_(float4::ZERO),
	 Speed_(1000.0f),
	 YSpeed_(20.0f),
	 AirTime_(0.4f),
	 IsInAir_(false),
	 IsCarried_(false)
{

}

Map1FRoom1Pot0::~Map1FRoom1Pot0() 
{
}

void Map1FRoom1Pot0::Start()
{
	Renderer_ = CreateRenderer("Pot.bmp");
	SetPosition({ 2561.0f, 3451.0f });
	BlockCol_ = CreateCollision("Pot", { 48, 48 });
	PickUpCol_ = CreateCollision("PotCarry", { 50, 50 });
}
 
void Map1FRoom1Pot0::Update()
{
	//hitbox created when thrown
	if (true == IsCarried_ && GameEngineInput::GetInst()->IsDown("Interact") && true == CheckPickUpEnd())
	{
		if (nullptr == PotHitBox_)
		{
			PotHitBox_ = CreateCollision("PotHitBox", { 48, 48 });
			IsInAir_ = true;
			IsCarried_ = false;
		}

		if (PlayerState::CarryMoveRight == dynamic_cast<PlayerLink*>(PlayerLink::MainPlayer_)->GetPlayerPrevState() ||
			PlayerState::CarryIdleRight == dynamic_cast<PlayerLink*>(PlayerLink::MainPlayer_)->GetPlayerPrevState())
		{
			MoveDir_ = float4::RIGHT;
		}
		if (PlayerState::CarryMoveLeft == dynamic_cast<PlayerLink*>(PlayerLink::MainPlayer_)->GetPlayerPrevState() ||
			PlayerState::CarryIdleLeft == dynamic_cast<PlayerLink*>(PlayerLink::MainPlayer_)->GetPlayerPrevState())
		{
			MoveDir_ = float4::LEFT;
		}
		if (PlayerState::CarryMoveUp == dynamic_cast<PlayerLink*>(PlayerLink::MainPlayer_)->GetPlayerPrevState() ||
			PlayerState::CarryIdleUp == dynamic_cast<PlayerLink*>(PlayerLink::MainPlayer_)->GetPlayerPrevState())
		{
			MoveDir_ = float4::UP;
		}
		if (PlayerState::CarryMoveDown == dynamic_cast<PlayerLink*>(PlayerLink::MainPlayer_)->GetPlayerPrevState() ||
			PlayerState::CarryIdleDown == dynamic_cast<PlayerLink*>(PlayerLink::MainPlayer_)->GetPlayerPrevState())
		{
			MoveDir_ = float4::DOWN;
		}

		Death(AirTime_);
	}

	if (nullptr != PotHitBox_ && true == IsInAir_)
	{
		YSpeed_ += 4.5f;
		PlayerState ex = dynamic_cast<PlayerLink*>(PlayerLink::MainPlayer_)->GetPlayerPrevState();
		SetMove(((MoveDir_ * Speed_) + float4{ 0, YSpeed_ })* GameEngineTime::GetDeltaTime());
	}

	if (PlayerLink::CarryActor_ == this && false == IsCarried_ && false == IsInAir_)
	{
		IsCarried_ = true;
		BlockCol_->Death();
		PickUpCol_->Death();
	}
		
	if (true == IsCarried_)
	{
		if (PlayerState::CarryMoveLeft == dynamic_cast<PlayerLink*>(PlayerLink::MainPlayer_)->GetPlayerCurState() &&
			1 == dynamic_cast<PlayerLink*>(PlayerLink::MainPlayer_)->GetCurrentAnimationFrame_())
		{
			SetPosition(PlayerLink::MainPlayer_->GetPosition() + float4{ 2.0f, -53.0f + 4.0f});
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
}
void Map1FRoom1Pot0::Render()
{

}

bool Map1FRoom1Pot0::CheckPickUpEnd()
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
