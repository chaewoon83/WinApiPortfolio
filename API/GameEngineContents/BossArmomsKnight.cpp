#include "BossArmomsKnight.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineSound.h>
#include "PlayerLink.h"
#include "EnemyGlobalFunction.h"

bool BossArmomsKnight::IsDeath_ = false;
BossArmomsKnight::BossArmomsKnight()
	: BossRenderer_(nullptr)
	, BossShadowRenderer_(nullptr)
	, BossCol_(nullptr)
	, BossCol2_(nullptr)
	, TimeScale_(14)
	, CurBossState_(BossState::Idle)
	, FollowSpeed_(350.0f)
	, JumpSpeed_(150.0f)
	, CurJumpSpeed_(150.0f)
	, DiveSpeed_(500.0f)
	, IdleWaitTime_(0.5f)
	, CurIdleWaitTime_(0.0f)
	, TargetPlayerPos_(float4::ZERO)
	, FollowDir_(float4::ZERO)
	, DistancebtwPlayer_(0.0f)
	, InitialPos_(float4::ZERO)
	, JumpPos_(float4::ZERO)
	, JumpHeight_(150.0f)
	, JumpTime_(0.5f)
	, CurJumpTime_(0.0f)
	, JumpTargetDistance_(0.0f)
	, DiveTime_(0.2f)
	, CurDiveTime_(0.0f)
	, DiveWaitTime_(0.1f)
	, CurDiveWaitTime_(0.0f)
	, Hp_(10)
	, BossPhase_(1)
	, IsInvincible_(false)
	, InvincibleTime_(0.5f)
	, CurInvincibleTime_(0.0f)
	, IsKnockback_(false)
	, KnockbackDir_(float4::ZERO)
	, KnockbackSpeed_(500.0f)
	, HitActor_(nullptr)
	, BounceSpeed_(400.0f)
	, BounceTime_(0.0f)
{
}

BossArmomsKnight::~BossArmomsKnight() 
{
}
//Shadow +12 from Boss
void BossArmomsKnight::Start()
{
	SetPosition({ 3071, 1373 });
	BossRenderer_ = CreateRenderer();
	BossShadowRenderer_ = CreateRenderer("BossShadow.bmp", static_cast<int>(PlayLevelOrder::BELOWMONSTER));
	BossShadowRenderer_->SetPivot({ 0, 48 });
	BossRenderer_->CreateAnimationTimeKey("BossRedIdle.bmp", "Idle", TimeScale_, 0, 0, 1.0f, false);
	BossRenderer_->CreateAnimationTimeKey("BossHit.bmp", "Hit", TimeScale_, 0, 4, 0.05f, true);
	BossRenderer_->CreateAnimationTimeKey("BossDeathEffect.bmp", "Death", TimeScale_, 0, 9, 0.05f, false);
	BossRenderer_->ChangeAnimation("Idle");
	BossCol_ = CreateCollision("MonsterHitBox", { 100, 100 });
	BossCol2_ = CreateCollision("MonsteHitBox2", { 100, 100 });
}
 
void BossArmomsKnight::Update()
{
	CheckBossPhase();
	BossUpdate();
}
void BossArmomsKnight::Render()
{
}

void BossArmomsKnight::IdleStart()
{
	CurIdleWaitTime_ = 0.0f;
	BossRenderer_->ChangeAnimation("Idle");
}

void BossArmomsKnight::IdleUpdate()
{
	CurIdleWaitTime_ += GameEngineTime::GetDeltaTime(TimeScale_);

	if (1 == BossPhase_ && IdleWaitTime_ < CurIdleWaitTime_)
	{
		BossChangeState(BossState::FollowPlayer);
		return;
	}

	if (2 == BossPhase_ && IdleWaitTime_ < CurIdleWaitTime_)
	{
		BossChangeState(BossState::Jump);
		return;
	}
}

void BossArmomsKnight::FollowPlayerStart()
{
	BossRenderer_->ChangeAnimation("Idle");
}

void BossArmomsKnight::FollowPlayerUpdate()
{
	GetDamagedBySword();
	if (true == IsInvincible_)
	{
		return;
	}
	TargetPlayerPos_ = PlayerLink::MainPlayer_->GetPosition();
	FollowDir_ = PlayerLink::MainPlayer_->GetPosition() - GetPosition();
	DistancebtwPlayer_ = FollowDir_.Len2D();
	FollowDir_.Normal2D();
	if (70.0f > DistancebtwPlayer_)
	{
		BossChangeState(BossState::Idle);
	}

	SetMove(FollowDir_ * GameEngineTime::GetDeltaTime(TimeScale_) * FollowSpeed_);


}

void BossArmomsKnight::JumpStart()
{
	GameEngineSound::SoundPlayOneShot("fall.mp3");
	TargetPlayerPos_ = PlayerLink::MainPlayer_->GetPosition();
	InitialPos_ = GetPosition();
	JumpPos_ = TargetPlayerPos_ + float4{ 0, -JumpHeight_ };
	//FollowDir_ = JumpPos_ - GetPosition();
	//FollowDir_.Normal2D();
	//JumpTargetDistance_ = FollowDir_.Len2D();
	//JumpSpeed_ = JumpTargetDistance_;
	BossCol_->Off();
	BossCol2_->Off();
}

void BossArmomsKnight::JumpUpdate()
{
	CurJumpTime_ += GameEngineTime::GetDeltaTime(TimeScale_);
	if (JumpTime_ < CurJumpTime_)
	{
		CurJumpTime_ = 0.0f;
		BossChangeState(BossState::Dive);
		return;
	}
	float4 ActorPos = float4::Lerp(InitialPos_, TargetPlayerPos_, CurJumpTime_ / JumpTime_);
	float4 RendererPos = float4::Lerp(InitialPos_, JumpPos_, CurJumpTime_ / JumpTime_);

	SetPosition(ActorPos);

	BossRenderer_->SetPivot({0, (RendererPos - ActorPos).y});
}

void BossArmomsKnight::DiveStart()
{
	CurDiveWaitTime_ = 0.0f;
}

void BossArmomsKnight::DiveUpdate()
{
	CurDiveWaitTime_ += GameEngineTime::GetDeltaTime(TimeScale_);
	if (DiveWaitTime_ < CurDiveWaitTime_)
	{
		if (DiveTime_ * 0.5f < CurDiveTime_)
		{
			BossCol2_->On();
		}
		if (DiveTime_ * 0.7f < CurDiveTime_)
		{
			BossCol_->On();
		}
		GetDamagedBySword();
		if (true == IsInvincible_)
		{
			CurDiveTime_ = 0.0f;
			return;
		}
		CurDiveTime_ += GameEngineTime::GetDeltaTime(TimeScale_);
		if (DiveTime_ < CurDiveTime_)
		{
			GameEngineSound::SoundPlayOneShot("bombexplode.mp3");
			CurDiveTime_ = 0.0f;
			BossChangeState(BossState::Idle);
			return;
		}

		float4 RendererPos = float4::Lerp(JumpPos_, TargetPlayerPos_, CurDiveTime_ / DiveTime_);
		float RendererPivot = (RendererPos - TargetPlayerPos_).y;
		BossRenderer_->SetPivot({ 0, RendererPivot });
	}
}

void BossArmomsKnight::KnockbackedStart()
{
	BossRenderer_->SetPivot(float4::ZERO);
	BossRenderer_->ChangeAnimationReset("Hit");
}

void BossArmomsKnight::KnockbackedUpdate()
{
	EnemyGlobalFunction::KnockBackMoveFunction(TimeScale_, KnockbackSpeed_, KnockbackDir_, BossCol_, this, PlayerLink::MapCarryColImage_2_, 64.0f, 64.0f, 64.0f);

	if (true == BossRenderer_->IsEndAnimation())
	{
		IsInvincible_ = false;
		BossChangeState(BossState::Idle);
	}
}

void BossArmomsKnight::DeathStart()
{
	BossCol_->Off();
	BossCol2_->Off();

	BossRenderer_->ChangeAnimationReset("Death");
}

void BossArmomsKnight::DeathUpdate()
{
	if (true == BossRenderer_->IsEndAnimation())
	{
		BossRenderer_->Off();
		BossShadowRenderer_->Off();
	}
}

void BossArmomsKnight::CheckBossPhase()
{
	if (1 == BossPhase_ && 5 >= Hp_)
	{
		BossPhase_ = 2;
	}
	if (true == IsDeath_)
	{
		return;
	}
	if (1 == BossPhase_)
	{
		Bounce();
	}
}

void BossArmomsKnight::Bounce()
{
	float BounceHeight = 0.0f;
	BounceTime_ += GameEngineTime::GetDeltaTime(TimeScale_);
	BounceHeight = BounceSpeed_ * BounceTime_ - 2000.0f * 0.5f * BounceTime_ * BounceTime_;

	if (0 > BounceHeight)
	{
		GameEngineSound::SoundPlayOneShot("doorclose.mp3");
		BounceHeight = 0.0f;
		BounceTime_ = 0.0f;
	}
	BossRenderer_->SetPivot({ 0, -BounceHeight });
}

void BossArmomsKnight::GetDamagedBySword()
{
	if (true == IsInvincible_)
	{
		CurInvincibleTime_ += GameEngineTime::GetDeltaTime(TimeScale_);
		if (InvincibleTime_ < CurInvincibleTime_)
		{
			IsInvincible_ = false;
			CurInvincibleTime_ = 0.0f;
		}
	}
	if (false == IsInvincible_)
	{
		std::vector<GameEngineCollision*> ColList;
		if (true == BossCol2_->CollisionResult("Sword", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			GameEngineSound::SoundPlayOneShot("bosshit.mp3");
			Hp_ -= 1;
			IsInvincible_ = true;
			IsKnockback_ = true;
			HitActor_ = ColList[0]->GetActor();
			KnockbackDir_ = GetPosition() - HitActor_->GetPosition();
			KnockbackDir_.Normal2D();
			dynamic_cast<PlayerLink*>(ColList[0]->GetActor())->SetIsInChargingStateOff();
			BossChangeState(BossState::Knockbacked);
		}
		if (0 >= Hp_)
		{
			IsDeath_ = true;
			IsInvincible_ = true;
			BossChangeState(BossState::Death);
			BossCol_->Death();
			return;
		}
	}

}

void BossArmomsKnight::BossChangeState(BossState _State)
{
	if (CurBossState_ != _State)
	{
		switch (_State)
		{
		case BossState::Idle:
			IdleStart();
			break;
		case BossState::FollowPlayer:
			FollowPlayerStart();
			break;
		case BossState::Jump:
			JumpStart();
			break;
		case BossState::Dive:
			DiveStart();
			break;
		case BossState::Knockbacked:
			KnockbackedStart();
			break;
		case BossState::Death:
			DeathStart();
			break;
		default:
			break;
		}
	}
	CurBossState_ = _State;
}


void BossArmomsKnight::BossUpdate()
{
	switch (CurBossState_)
	{
	case BossState::Idle:
		IdleUpdate();
		break;
	case BossState::FollowPlayer:
		FollowPlayerUpdate();
		break;
	case BossState::Jump:
		JumpUpdate();
		break;
	case BossState::Dive:
		DiveUpdate();
		break;
	case BossState::Knockbacked:
		KnockbackedUpdate();
		break;
	case BossState::Death:
		DeathUpdate();
		break;
	default:
		break;
	}
}
