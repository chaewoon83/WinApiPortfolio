#include "EnemyPopo.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include "PlayerLink.h"

EnemyPopo::EnemyPopo()
	:PopoRenderer_(nullptr),
	 PopoCol_(nullptr),
	 IsInvincible_(false),
	 IsDeath_(false),
	 InvincibleTime_(0.3f),
	 CurInvincibleTime_(0.0f),
	 Hp_(2),
	 IsGetDamaged_(false),
	 IsKnockback_(false),
	 IsBlink_(false),
	 KnockbackTime_(0.2f),
	 CurKnockbackTime_(0.0f),
	 BlinkTime_(0.3f),
	 CurBlinkTime_(0.0f),
	 BlinkFreq_(0.03f),
	 CurBlinkFreq_(0.0f),
	 IsAlphaOn_(true),
	 KnockbackDir_(float4::ZERO),
	 PopoCurState_(PopoState::Idle)
{
}

EnemyPopo::~EnemyPopo() 
{
}

void EnemyPopo::Start()
{
	SetPosition({3071,3550});
	PopoRenderer_ = CreateRenderer();
	PopoRenderer_->CreateAnimation("EnemyPopo.bmp", "Idle", 0, 2, 0.15f, true);
	PopoRenderer_->CreateAnimation("EnemyDeathEffect.bmp", "DeathEffect", 0, 6, 0.15f, false);
	PopoRenderer_->ChangeAnimation("Idle");

	PopoCol_ = CreateCollision("MonsterHitBox", { 64, 64 });

}
 
void EnemyPopo::Update()
{

	GetDamaged();
	PopoStateUpdate();

}
void EnemyPopo::Render()
{

}

void EnemyPopo::GetDamaged()
{
	std::vector<GameEngineCollision*> ColList;
	if (false == IsDeath_ && true == IsInvincible_)
	{
		CurInvincibleTime_ += GameEngineTime::GetDeltaTime();
		if (InvincibleTime_ < CurInvincibleTime_)
		{
			IsInvincible_ = false;
			CurInvincibleTime_ = 0.0f;
		}
	}
	if (false == IsInvincible_ && false == IsDeath_)
	{
		if (true == PopoCol_->CollisionResult("Sword", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			Hp_ -= 1;
			IsInvincible_ = true;
			IsBlink_ = true;
		}

		if (0 >= Hp_)
		{
			IsBlink_ = false;
			IsDeath_ = true;
			PopoRenderer_->ChangeAnimation("DeathEffect");
			PopoCol_->Death();
			return;
		}

	}
	if (true == IsDeath_ && true == PopoRenderer_->IsEndAnimation())
	{
		Death();
	}
}

void EnemyPopo::BlinkUpdate()
{

	if (true == IsBlink_)
	{
		CurBlinkTime_ += GameEngineTime::GetDeltaTime();
		CurBlinkFreq_ += GameEngineTime::GetDeltaTime();
		if (BlinkFreq_ < CurBlinkFreq_)
		{
			CurBlinkFreq_ = 0.0f;
			if (false == IsAlphaOn_)
			{
				PopoRenderer_->SetAlpha(255);
				IsAlphaOn_ = true;
			}
			else
			{
				PopoRenderer_->SetAlpha(0);
				IsAlphaOn_ = false;
			}
		}

		if (BlinkTime_ < CurBlinkTime_)
		{

			IsBlink_ = false;
			CurBlinkTime_ = 0.0f;
			CurBlinkFreq_ = 0.0f;
			IsAlphaOn_ = true;
			PopoRenderer_->SetAlpha(255);
			return;
		}
	}
	else
	{
		if (IsAlphaOn_ = false)
		{
			PopoRenderer_->SetAlpha(255);
			IsAlphaOn_ = true;
		}
	}
}

void EnemyPopo::IdleStart()
{
	//PopoRenderer_->ChangeAnimation("Idle");
}

void EnemyPopo::DamagedStart()
{
}

void EnemyPopo::IdleUpdate()
{
	DamagedCheck();
}

void EnemyPopo::DamagedUpdate()
{

	CurKnockbackTime_ += GameEngineTime::GetDeltaTime();
	int Black = RGB(0, 0, 0);
	if (true == PosAndColorCheck(Black, MapColImage_))
	{
		SetMove(KnockbackDir_ * KnockBackSpeed_ * GameEngineTime::GetDeltaTime());
	}
	if (KnockbackTime_ < CurKnockbackTime_)
	{
		IsKnockback_ = false;
	}
}

void EnemyPopo::DamagedCheck()
{
	std::vector<GameEngineCollision*> ColList;
	if (true == PopoCol_->CollisionResult("MonsterHitBox", ColList, CollisionType::Rect, CollisionType::Rect) && false == IsKnockback_)
	{
		GetDamaged();
		IsKnockback_ = true;
		IsBlink_ = true;
		HitActor_ = ColList[0]->GetActor();
		KnockbackDir_ = GetPosition() - HitActor_->GetPosition();
		KnockbackDir_.Normal2D();
	}
}




void EnemyPopo::PopoChangeState(PopoState _State)
{
	if (PopoCurState_ != _State)
	{
		switch (_State)
		{
		case PopoState::Idle:
			IdleStart();
			break;
		case PopoState::Damaged:
			DamagedStart();
			break;
		case PopoState::Max:
			break;
		default:
			break;
		}
	}

	PopoCurState_ = _State;
}

void EnemyPopo::PopoStateUpdate()
{
	switch (PopoCurState_)
	{
	case PopoState::Idle:
		IdleUpdate();
		break;
	case PopoState::Damaged:
		DamagedUpdate();
		break;
	case PopoState::Max:
		break;
	default:
		break;
	}