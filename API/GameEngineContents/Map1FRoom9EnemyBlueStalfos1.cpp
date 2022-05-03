#include "Map1FRoom9EnemyBlueStalfos1.h"
#include "PlayerLink.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "EnemyGlobalFunction.h"
#include "GlobalRandom.h"
#include "ItemGreenRupee.h"
#include "ItemBlueRupee.h"


//TODO
//1. 벽에 부딫혔을때 움찔움찔
//2. 한 방향으로 7-10번씩 움직임


Map1FRoom9EnemyBlueStalfos1::Map1FRoom9EnemyBlueStalfos1()
	:BlueStalfosHeadRenderer_(nullptr),
	 BlueStalfosBodyRenderer_(nullptr),
	 BlueStalfosCol_(nullptr),
	 BlueStalfosMoveCol_(nullptr),
	 BlueStalfosPos_({ 1695, 2980 }),
	 TimeScale_(9),
	 IsInvincible_(false),
	 IsDeath_(false),
	 IsRelocated_(false),
	 InvincibleTime_(0.3f),
	 CurInvincibleTime_(0.0f),
	 Hp_(2),
	 IsGetDamaged_(false),
	 IsKnockback_(false),
	 IsBlink_(false),
	 Speed_(300.0f),
	 JumpSpeed_(300.0f),
	 MoveTime_(0.5f),
	 CurMoveTime_(0.0f),
	 WaitTime_(0.5f),
	 CurWaitTime_(0.0f),
	 RestTime_(3.0f),
	 CurRestTime_(0.0f),
	 KnockbackTime_(0.15f),
	 CurKnockbackTime_(0.0f),
	 BlinkTime_(0.3f),
	 CurBlinkTime_(0.0f),
	 BlinkFreq_(0.02f),
	 CurBlinkFreq_(0.0f),
	 TimeAfterDeath_(2.0f),
	 CurTimeAfterDeath_(0.0f),
	 JumpTime_(0.5f),
	 CurJumpTime_(0.0f),
	 OriginalPivot_({-12,28}),
	 JumpHeight_(0.0f),
	 JumpVerSpeed_(500.0f),
	 CurJumpVerSpeed_(0.0f),
	 IsAlphaOn_(true),
	 KnockbackDir_(float4::ZERO),
	 MoveDir_(float4::ZERO),
	 KnockBackSpeed_(800.0f),
	 BlueStalfosCurState_(BlueStalfosState::LookAroundDown),
	 BlueStalfosPrevState_(BlueStalfosState::Max)
{
}


/// 10 times killed Popo, 2 times 1rupee, 1 time 5rupee;
Map1FRoom9EnemyBlueStalfos1::~Map1FRoom9EnemyBlueStalfos1()
{
}

void Map1FRoom9EnemyBlueStalfos1::Start()
{
	SetPosition(BlueStalfosPos_);
	BlueStalfosShadowRenderer_ = CreateRenderer("EnemyBlueStalfosShadow.bmp");
	BlueStalfosShadowRenderer_->SetPivot({ 0, 48 });

	BlueStalfosBodyRenderer_ = CreateRenderer();
	BlueStalfosBodyRenderer_->SetPivot({ 0, 24 });
	BlueStalfosBodyRenderer_->CreateAnimationTimeKey("EnemyBlueStalfosRightBody.bmp", "Right_Walk", TimeScale_, 0, 1, 0.15f, true);
	BlueStalfosBodyRenderer_->CreateAnimationTimeKey("EnemyBlueStalfosLeftBody.bmp", "Left_Walk", TimeScale_, 0, 1, 0.15f, true);
	BlueStalfosBodyRenderer_->CreateAnimationTimeKey("EnemyBlueStalfosUpBody.bmp", "Up_Walk", TimeScale_, 0, 1, 0.15f, true);
	BlueStalfosBodyRenderer_->CreateAnimationTimeKey("EnemyBlueStalfosDownBody.bmp", "Down_Walk", TimeScale_, 0, 1, 0.15f, true);

	BlueStalfosHeadRenderer_ = CreateRenderer();
	BlueStalfosHeadRenderer_->SetPivot({ 0, -28 });
	BlueStalfosHeadRenderer_->CreateAnimationTimeKey("EnemyBlueStalfosRightHead.bmp", "Right", TimeScale_, 0, 0, 0.15f, false);
	BlueStalfosHeadRenderer_->CreateAnimationTimeKey("EnemyBlueStalfosLeftHead.bmp", "Left", TimeScale_, 0, 0, 0.15f, false);
	BlueStalfosHeadRenderer_->CreateAnimationTimeKey("EnemyBlueStalfosUpHead.bmp", "Up", TimeScale_, 0, 0, 0.15f, false);
	BlueStalfosHeadRenderer_->CreateAnimationTimeKey("EnemyBlueStalfosDownHead.bmp", "Down", TimeScale_, 0, 0, 0.15f, false);
	BlueStalfosHeadRenderer_->ChangeAnimation("Down");





	BlueStalfosBodyRenderer_->CreateAnimationTimeKey("EnemyBlueStalfosRightBodyIdle.bmp", "Right_Idle", TimeScale_, 0, 0, 0.3f, false);
	BlueStalfosBodyRenderer_->CreateAnimationTimeKey("EnemyBlueStalfosLeftBodyIdle.bmp", "Left_Idle", TimeScale_, 0, 0, 0.3f, false);
	BlueStalfosBodyRenderer_->CreateAnimationTimeKey("EnemyBlueStalfosUpBodyIdle.bmp", "Up_Idle", TimeScale_, 0, 0, 0.3f, false);
	BlueStalfosBodyRenderer_->CreateAnimationTimeKey("EnemyBlueStalfosDownBodyIdle.bmp", "Down_Idle", TimeScale_, 0, 0, 0.3f, false);

	BlueStalfosBodyRenderer_->CreateAnimationTimeKey("EnemyBlueStalfosJumpRightBody.bmp", "Right_Jump", TimeScale_, 0, 0, 0.3f, false);
	BlueStalfosBodyRenderer_->CreateAnimationTimeKey("EnemyBlueStalfosJumpLeftBody.bmp", "Left_Jump", TimeScale_, 0, 0, 0.3f, false);
	BlueStalfosBodyRenderer_->CreateAnimationTimeKey("EnemyBlueStalfosJumpUpBody.bmp", "Up_Jump", TimeScale_, 0, 0, 0.3f, false);
	BlueStalfosBodyRenderer_->CreateAnimationTimeKey("EnemyBlueStalfosJumpDownBody.bmp", "Down_Jump", TimeScale_, 0, 0, 0.3f, false);
	BlueStalfosBodyRenderer_->ChangeAnimation("Down_Idle");
	//죽는 애니메이션은 플레이어와 함께한다
	BlueStalfosHeadRenderer_->CreateAnimationTimeKey("EnemyDeathEffect.bmp", "DeathEffect", 0, 0, 6, 0.15f, false);
	BlueStalfosHeadRenderer_->ChangeAnimation("Down");


	//DeathEffectRenderer_ = CreateRenderer();
	//DeathEffectRenderer_->CreateAnimation("EnemyDeathEffect.bmp", "DeathEffect", 0, 6, 0.15f, false);

	BlueStalfosCol_ = CreateCollision("MonsterHitBox", { 48, 56 }, { 0, -14 });
	BlueStalfosMoveCol_ = CreateCollision("MonsterMoveBox", { 64, 78}, { 0, 0 });
	BlueStalfosJumpCol_ = CreateCollision("BlueStalfosJumpBox", { 72, 78 }, { 0, 0 });

	{
		int RandomInt = GlobalRandom::RandomIntGenerate(1, 4);
		MoveDirCheck(RandomInt);
		if (1 == RandomInt)
		{
			BlueStalfosChangeState(BlueStalfosState::LookAroundRight);
			return;
		}
		if (2 == RandomInt)
		{
			BlueStalfosChangeState(BlueStalfosState::LookAroundLeft);
			return;
		}
		if (3 == RandomInt)
		{
			BlueStalfosChangeState(BlueStalfosState::LookAroundUp);
			return;
		}
		if (4 == RandomInt)
		{
			BlueStalfosChangeState(BlueStalfosState::LookAroundDown);
			return;
		}
	}
}

void Map1FRoom9EnemyBlueStalfos1::Update()
{
	BlueStalfosStateUpdate();
	EnemyGlobalFunction::BlueStalfosBlinkUpdate(TimeScale_, IsBlink_, IsAlphaOn_, BlinkTime_, 
		CurBlinkTime_, BlinkFreq_, CurBlinkFreq_, BlueStalfosCurState_, BlueStalfosHeadRenderer_, BlueStalfosBodyRenderer_);
	EnemyGlobalFunction::Relocation(PlayerLink::GetPlayerCurRoomState(), TimeScale_, IsRelocated_, BlueStalfosPos_, this);
}

void Map1FRoom9EnemyBlueStalfos1::Render()
{

}

void Map1FRoom9EnemyBlueStalfos1::LookAroundRightStart()
{
	StopDirCheck();
	BlueStalfosHeadRenderer_->SetPivot({ 0, -28 });
	BlueStalfosBodyRenderer_->SetPivot({ 0, 24 });
	BlueStalfosHeadRenderer_->ChangeAnimation("Right");
}
void Map1FRoom9EnemyBlueStalfos1::LookAroundLeftStart()
{
	StopDirCheck();
	BlueStalfosHeadRenderer_->SetPivot({ 0, -28 });
	BlueStalfosBodyRenderer_->SetPivot({ 0, 24 });
	BlueStalfosHeadRenderer_->ChangeAnimation("Left");
}
void Map1FRoom9EnemyBlueStalfos1::LookAroundUpStart()
{
	StopDirCheck();
	BlueStalfosHeadRenderer_->SetPivot({ 0, -28 });
	BlueStalfosBodyRenderer_->SetPivot({ 0, 24 });
	BlueStalfosHeadRenderer_->ChangeAnimation("Up");
}
void Map1FRoom9EnemyBlueStalfos1::LookAroundDownStart()
{
	StopDirCheck();
	BlueStalfosHeadRenderer_->SetPivot({ 0, -28 });
	BlueStalfosBodyRenderer_->SetPivot({ 0, 24 });
	BlueStalfosHeadRenderer_->ChangeAnimation("Down");
}
void Map1FRoom9EnemyBlueStalfos1::WalkRightStart()
{
	BlueStalfosHeadRenderer_->SetPivot({ 0, -28 });
	BlueStalfosBodyRenderer_->SetPivot({ 0, 24 });
	BlueStalfosBodyRenderer_->ChangeAnimation("Right_Walk");
}
void Map1FRoom9EnemyBlueStalfos1::WalkLeftStart()
{
	BlueStalfosHeadRenderer_->SetPivot({ 0, -28 });
	BlueStalfosBodyRenderer_->SetPivot({ 0, 24 });
	BlueStalfosBodyRenderer_->ChangeAnimation("Left_Walk");
}
void Map1FRoom9EnemyBlueStalfos1::WalkUpStart()
{
	BlueStalfosHeadRenderer_->SetPivot({ 0, -28 });
	BlueStalfosBodyRenderer_->SetPivot({ 0, 24 });
	BlueStalfosBodyRenderer_->ChangeAnimation("Up_Walk");
}
void Map1FRoom9EnemyBlueStalfos1::WalkDownStart()
{
	BlueStalfosHeadRenderer_->SetPivot({ 0, -28 });
	BlueStalfosBodyRenderer_->SetPivot({ 0, 24 });
	BlueStalfosBodyRenderer_->ChangeAnimation("Down_Walk");
}

void Map1FRoom9EnemyBlueStalfos1::JumpRightStart()
{
	CurJumpVerSpeed_ = 0.0f;
	BlueStalfosHeadRenderer_->ChangeAnimation("Left");
	BlueStalfosBodyRenderer_->ChangeAnimation("Right_Jump");
}
void Map1FRoom9EnemyBlueStalfos1::JumpLeftStart()
{
	CurJumpVerSpeed_ = 0.0f;
	BlueStalfosHeadRenderer_->ChangeAnimation("Right");
	BlueStalfosBodyRenderer_->ChangeAnimation("Left_Jump");
}
void Map1FRoom9EnemyBlueStalfos1::JumpUpStart()
{
	CurJumpVerSpeed_ = 0.0f;
	BlueStalfosHeadRenderer_->ChangeAnimation("Down");
	BlueStalfosBodyRenderer_->ChangeAnimation("Up_Jump");
}
void Map1FRoom9EnemyBlueStalfos1::JumpDownStart()
{
	CurJumpVerSpeed_ = 0.0f;
	BlueStalfosHeadRenderer_->ChangeAnimation("Up");
	BlueStalfosBodyRenderer_->ChangeAnimation("Down_Jump");
}

void Map1FRoom9EnemyBlueStalfos1::KnockbackedStart()
{
}

void Map1FRoom9EnemyBlueStalfos1::DeathStart()
{
	BlueStalfosMoveCol_->Death();
	BlueStalfosHeadRenderer_->SetAlpha(255);
	BlueStalfosBodyRenderer_->SetAlpha(255);
	BlueStalfosHeadRenderer_->ChangeAnimation("DeathEffect");
	BlueStalfosBodyRenderer_->Death();
	BlueStalfosShadowRenderer_->Death();
	//DeathEffectRenderer_->ChangeAnimation("DeathEffect");
}

void Map1FRoom9EnemyBlueStalfos1::LookAroundUpdate()
{
	std::vector<GameEngineCollision*> ColList;
	if (true == BlueStalfosJumpCol_->CollisionResult("Sword", ColList, CollisionType::Rect, CollisionType::Rect) ||
		true == BlueStalfosJumpCol_->CollisionResult("PotHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		HitActor_ = ColList[0]->GetActor();
		KnockbackDir_ = GetPosition() - HitActor_->GetPosition();
		KnockbackDir_.Normal2D();
		JumpDirCheck(KnockbackDir_);
		return;
	}

	CurWaitTime_ += GameEngineTime::GetDeltaTime(TimeScale_);
	if (WaitTime_ < CurWaitTime_)
	{
		CurWaitTime_ = 0.0f;
		if (BlueStalfosState::LookAroundRight == BlueStalfosCurState_)
		{
			BlueStalfosChangeState(BlueStalfosState::WalkRight);
			return;
		}
		if (BlueStalfosState::LookAroundLeft == BlueStalfosCurState_)
		{
			BlueStalfosChangeState(BlueStalfosState::WalkLeft);
			return;
		}
		if (BlueStalfosState::LookAroundUp == BlueStalfosCurState_)
		{
			BlueStalfosChangeState(BlueStalfosState::WalkUp);
			return;
		}
		if (BlueStalfosState::LookAroundDown == BlueStalfosCurState_)
		{
			BlueStalfosChangeState(BlueStalfosState::WalkDown);
			return;
		}
	}
}

void Map1FRoom9EnemyBlueStalfos1::WalkUpdate()
{
	std::vector<GameEngineCollision*> ColList;
	if (true == BlueStalfosJumpCol_->CollisionResult("Sword", ColList, CollisionType::Rect, CollisionType::Rect) ||
		true == BlueStalfosJumpCol_->CollisionResult("PotHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		HitActor_ = ColList[0]->GetActor();
		KnockbackDir_ = GetPosition() - HitActor_->GetPosition();
		KnockbackDir_.Normal2D();
		JumpDirCheck(KnockbackDir_);
		return;
	}

	CurMoveTime_ += GameEngineTime::GetDeltaTime(TimeScale_);

	if (MoveTime_ < CurMoveTime_ || false == MoveFunction())
	{
		BlueStalfosPrevState_ = BlueStalfosCurState_;
		CurMoveTime_ = 0.0f;
		int RandomInt = GlobalRandom::RandomIntGenerate(1, 4);
		MoveDirCheck(RandomInt);
		if (1 == RandomInt)
		{
			BlueStalfosChangeState(BlueStalfosState::LookAroundRight);
			return;
		}
		if (2 == RandomInt)
		{
			BlueStalfosChangeState(BlueStalfosState::LookAroundLeft);
			return;
		}
		if (3 == RandomInt)
		{
			BlueStalfosChangeState(BlueStalfosState::LookAroundUp);
			return;
		}
		if (4 == RandomInt)
		{
			BlueStalfosChangeState(BlueStalfosState::LookAroundDown);
			return;
		}
	}
}

void Map1FRoom9EnemyBlueStalfos1::Action()
{

}

void Map1FRoom9EnemyBlueStalfos1::JumpUpdate()
{
	CurJumpTime_ += GameEngineTime::GetDeltaTime(TimeScale_);

	JumpHeight_ = 500.0f * CurJumpTime_ - 2000.0f * 0.5f * static_cast<float>(pow(CurJumpTime_, 2));

	BlueStalfosHeadRenderer_->SetPivot({ 0, OriginalPivot_.x - JumpHeight_ });
	BlueStalfosBodyRenderer_->SetPivot({ 0, OriginalPivot_.y - JumpHeight_ });


	EnemyGlobalFunction::KnockBackMoveFunction(TimeScale_, JumpSpeed_, KnockbackDir_, BlueStalfosMoveCol_, this, 32.0f, 14.0f, 64.0f);

	if (0.1f * JumpTime_ < CurJumpTime_ && 0.3f * JumpTime_ > CurJumpTime_)
	{
		GetDamaged();
		if (true == IsKnockback_)
		{
			return;
		}
	}

	if (0.7f * JumpTime_ < CurJumpTime_)
	{
		GetDamaged();
		if (true == IsKnockback_)
		{
			return;
		}
	}

	if (JumpTime_ < CurJumpTime_)
	{
		JumpHeight_ = 0.0f;
		CurJumpTime_ = 0.0f;
		int RandomInt = GlobalRandom::RandomIntGenerate(1, 4);
		MoveDirCheck(RandomInt);
		if (1 == RandomInt)
		{
			BlueStalfosChangeState(BlueStalfosState::LookAroundRight);
			return;
		}
		if (2 == RandomInt)
		{
			BlueStalfosChangeState(BlueStalfosState::LookAroundLeft);
			return;
		}
		if (3 == RandomInt)
		{
			BlueStalfosChangeState(BlueStalfosState::LookAroundUp);
			return;
		}
		if (4 == RandomInt)
		{
			BlueStalfosChangeState(BlueStalfosState::LookAroundDown);
			return;
		}
	}
}

void Map1FRoom9EnemyBlueStalfos1::KnockbackedUpdate()
{
	GetDamaged();
	CurKnockbackTime_ += GameEngineTime::GetDeltaTime(TimeScale_);
	int White = RGB(255, 255, 255);

	if (true == PosAndColorCheck(White, PlayerLink::MapColImage_))
	{
		EnemyGlobalFunction::KnockBackMoveFunction(TimeScale_, KnockBackSpeed_, KnockbackDir_, BlueStalfosMoveCol_, this, 32.0f, 14.0f, 64.0f);
	}
	if (KnockbackTime_ < CurKnockbackTime_)
	{
		IsKnockback_ = false;
	}
	if (true == IsDeath_ && true == IsInvincible_ && KnockbackTime_ * 0.3f < CurKnockbackTime_)
	{
		BlueStalfosChangeState(BlueStalfosState::Death);
		return;
	}
	if (false == IsKnockback_)
	{
		CurKnockbackTime_ = 0.0f;
		{
			int RandomInt = GlobalRandom::RandomIntGenerate(1, 4);
			MoveDirCheck(RandomInt);
			if (1 == RandomInt)
			{
				BlueStalfosChangeState(BlueStalfosState::LookAroundRight);
				return;
			}
			if (2 == RandomInt)
			{
				BlueStalfosChangeState(BlueStalfosState::LookAroundLeft);
				return;
			}
			if (3 == RandomInt)
			{
				BlueStalfosChangeState(BlueStalfosState::LookAroundUp);
				return;
			}
			if (4 == RandomInt)
			{
				BlueStalfosChangeState(BlueStalfosState::LookAroundDown);
				return;
			}
		}
	}
}

void Map1FRoom9EnemyBlueStalfos1::DeathUpdate()
{
	if (true == IsDeath_ && true == BlueStalfosHeadRenderer_->IsEndAnimation())
	{
		GameEngineRandom Random;
		//Max 10
		int RandomInt = Random.RandomInt(1, 10);
		//if (2 >= RandomInt)
		//{
		//	ItemGreenRupee* Ptr = GetLevel()->CreateActor<ItemGreenRupee>((int)PlayLevelOrder::PLAYER);
		//	Ptr->SetPosition(GetPosition());
		//}

		//if (2 <= RandomInt && 3 >= RandomInt)
		//{
		//	ItemGreenRupee* Ptr = GetLevel()->CreateActor<ItemGreenRupee>((int)PlayLevelOrder::PLAYER);
		//	Ptr->SetPosition(GetPosition());
		//}

		{
			ItemBlueRupee* Ptr = GetLevel()->CreateActor<ItemBlueRupee>((int)PlayLevelOrder::PLAYER);
			Ptr->SetPosition(GetPosition());
		}

		Death();
	}
}

void Map1FRoom9EnemyBlueStalfos1::BlueStalfosChangeState(BlueStalfosState _State)
{
	if (BlueStalfosCurState_ != _State)
	{
		switch (_State)
		{
		case BlueStalfosState::LookAroundRight:
			LookAroundRightStart();
			break;
		case BlueStalfosState::LookAroundLeft:
			LookAroundLeftStart();
			break;
		case BlueStalfosState::LookAroundUp:
			LookAroundUpStart();
			break;
		case BlueStalfosState::LookAroundDown:
			LookAroundDownStart();
			break;
		case BlueStalfosState::WalkRight:
			WalkRightStart();
			break;
		case BlueStalfosState::WalkLeft:
			WalkLeftStart();
			break;
		case BlueStalfosState::WalkUp:
			WalkUpStart();
			break;
		case BlueStalfosState::WalkDown:
			WalkDownStart();
			break;
		case BlueStalfosState::JumpRight:
			JumpRightStart();
			break;
		case BlueStalfosState::JumpLeft:
			JumpLeftStart();
			break;
		case BlueStalfosState::JumpUp:
			JumpUpStart();
			break;
		case BlueStalfosState::JumpDown:
			JumpDownStart();
			break;
		case BlueStalfosState::Knockbacked:
			KnockbackedStart();
			break;
		case BlueStalfosState::Death:
			DeathStart();
			break;
		case BlueStalfosState::Max:
			break;
		default:
			break;
		}
	}
	BlueStalfosCurState_ = _State;
}

void Map1FRoom9EnemyBlueStalfos1::BlueStalfosStateUpdate()
{
	switch (BlueStalfosCurState_)
	{
	case BlueStalfosState::LookAroundRight:
	case BlueStalfosState::LookAroundLeft:
	case BlueStalfosState::LookAroundUp:
	case BlueStalfosState::LookAroundDown:
		LookAroundUpdate();
		break;
	case BlueStalfosState::WalkRight:
	case BlueStalfosState::WalkLeft:
	case BlueStalfosState::WalkUp:
	case BlueStalfosState::WalkDown:
		WalkUpdate();
		break;
	case BlueStalfosState::JumpRight:
	case BlueStalfosState::JumpLeft:
	case BlueStalfosState::JumpUp:
	case BlueStalfosState::JumpDown:
		JumpUpdate();
		break;
	case BlueStalfosState::Knockbacked:
		KnockbackedUpdate();
		break;
	case BlueStalfosState::Death:
		DeathUpdate();
		break;
	case BlueStalfosState::Max:
		break;
	default:
		break;
	}
}


void Map1FRoom9EnemyBlueStalfos1::MoveDirCheck(int _RandomInt)
{
	if (1 == _RandomInt)
	{
		MoveDir_ = float4{ 1, 0 };
	}
	if (2 == _RandomInt)
	{
		MoveDir_ = float4{ -1, 0 };
	}
	if (3 == _RandomInt)
	{
		MoveDir_ = float4{ 0, -1 };
	}
	if (4 == _RandomInt)
	{
		MoveDir_ = float4{ 0, 1 };
	}
}

void Map1FRoom9EnemyBlueStalfos1::StopDirCheck()
{
	if (BlueStalfosState::JumpRight == BlueStalfosPrevState_ ||
		BlueStalfosState::WalkRight == BlueStalfosPrevState_)
	{
		BlueStalfosBodyRenderer_->ChangeAnimation("Right_Idle");
	}
	if (BlueStalfosState::JumpLeft == BlueStalfosPrevState_ ||
		BlueStalfosState::WalkLeft == BlueStalfosPrevState_)
	{
		BlueStalfosBodyRenderer_->ChangeAnimation("Left_Idle");
	}
	if (BlueStalfosState::JumpUp== BlueStalfosPrevState_ ||
		BlueStalfosState::WalkUp == BlueStalfosPrevState_)
	{
		BlueStalfosBodyRenderer_->ChangeAnimation("Up_Idle");
	}
	if (BlueStalfosState::JumpDown == BlueStalfosPrevState_ ||
		BlueStalfosState::WalkDown == BlueStalfosPrevState_)
	{
		BlueStalfosBodyRenderer_->ChangeAnimation("Down_Idle");
	}
}

void Map1FRoom9EnemyBlueStalfos1::JumpCheck()
{
}

void Map1FRoom9EnemyBlueStalfos1::GetDamaged()
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
	if (false == IsInvincible_ && false == IsDeath_)
	{
		std::vector<GameEngineCollision*> ColList;
		if (true == BlueStalfosCol_->CollisionResult("Sword", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			Hp_ -= 1;
			IsInvincible_ = true;
			IsBlink_ = true;
			IsKnockback_ = true;
			IsBlink_ = true;
			HitActor_ = ColList[0]->GetActor();
			KnockbackDir_ = GetPosition() - HitActor_->GetPosition();
			KnockbackDir_.Normal2D();
			BlueStalfosChangeState(BlueStalfosState::Knockbacked);
		}

		if (true == BlueStalfosCol_->CollisionResult("PotHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			Hp_ -= 1;
			IsInvincible_ = true;

			IsKnockback_ = true;
			IsBlink_ = true;
			HitActor_ = ColList[0]->GetActor();
			KnockbackDir_ = GetPosition() - HitActor_->GetPosition();
			KnockbackDir_.Normal2D();
			ColList[0]->Off();
			BlueStalfosChangeState(BlueStalfosState::Knockbacked);
		}

		if (0 >= Hp_)
		{
			IsInvincible_ = true;
			IsDeath_ = true;

			BlueStalfosCol_->Death();

			return;
		}
	}

}

void Map1FRoom9EnemyBlueStalfos1::JumpDirCheck(float4 _Dir)
{
	if (abs(_Dir.x) > abs(_Dir.y))
	{
		if (0.0f < _Dir.x)
		{
			BlueStalfosChangeState(BlueStalfosState::JumpRight);
			return;
		}
		else
		{
			BlueStalfosChangeState(BlueStalfosState::JumpLeft);
			return;
		}
	}
	else
	{
		if (0.0f < _Dir.y)
		{
			BlueStalfosChangeState(BlueStalfosState::JumpDown);
			return;
		}
		else
		{
			BlueStalfosChangeState(BlueStalfosState::JumpUp);
			return;
		}
	}
}

bool Map1FRoom9EnemyBlueStalfos1::PosAndColorCheck(int _Color, GameEngineImage* _Image)
{
	float4 MyPos = GetPosition();
	float4 Map1f_2_Scale = float4{ 0, -4128 };
	if (false == dynamic_cast<PlayerLink*>(PlayerLink::MainPlayer_)->GetIsMap1F_2())
	{
		MyPos += Map1f_2_Scale;
	}
	float4 MyPosTopRight = MyPos + float4{ 32.0f, -14.0f };
	float4 MyPosTopLeft = MyPos + float4{ -32.0f, -14.0f };
	float4 MyPosBotRight = MyPos + float4{ 32.0f, 64.0f };
	float4 MyPosBotLeft = MyPos + float4{ -32.0f, 64.0f };
	float4 MyPosRight = MyPos + float4{ 32.0f, 0.0f };
	float4 MyPosLeft = MyPos + float4{ -32.0f, 0.0f };
	float4 MyPosTop = MyPos + float4{ 0.0f, -14.0f };
	float4 MyPosBot = MyPos + float4{ 0.0f, 64.0f };

	int ColorTopRight = _Image->GetImagePixel(MyPosTopRight);
	int ColorTopLeft = _Image->GetImagePixel(MyPosTopLeft);
	int ColorBotRight = _Image->GetImagePixel(MyPosBotRight);
	int ColorBotLeft = _Image->GetImagePixel(MyPosBotLeft);
	int ColorRight = _Image->GetImagePixel(MyPosRight);
	int ColorLeft = _Image->GetImagePixel(MyPosLeft);
	int ColorTop = _Image->GetImagePixel(MyPosTop);
	int ColorBot = _Image->GetImagePixel(MyPosBot);



	if (_Color == ColorTopRight &&
		_Color == ColorTopLeft &&
		_Color == ColorBotRight &&
		_Color == ColorBotLeft &&
		_Color == ColorRight &&
		_Color == ColorLeft &&
		_Color == ColorBot &&
		_Color == ColorTop)
	{
		return true;
	}
	return false;
}

bool Map1FRoom9EnemyBlueStalfos1::MoveFunction()
{
	float4 CheckPos;
	//맵 이미지와 캐릭터의 이미지의 픽셀 위치를 동일하게 맞춰놔야한다
	bool MoveLeft = false;
	bool MoveRight = false;
	bool MoveUp = false;
	bool MoveDown = false;
	EnemyGlobalFunction::MoveDirBoolCheck(MoveRight, MoveLeft, MoveUp, MoveDown, MoveDir_);
	float4 Map1f_2_Scale = float4{ 0, -4128 };
	//SetMove(MoveDir * GameEngineTime::GetDeltaTime(0) * Speed_);
	{
		int Black = RGB(0, 0, 0);
		float4 MyPos = GetPosition();
		if (false == PlayerLink::GetIsMap1F_2())
		{
			MyPos += Map1f_2_Scale;
		}
		float4 MyPosTopRight = MyPos + float4{ 32.0f, -14.0f };
		float4 MyPosTopLeft = MyPos + float4{ -32.0f, -14.0f };
		float4 MyPosBotRight = MyPos + float4{ 32.0f, 64.0f };
		float4 MyPosBotLeft = MyPos + float4{ -32.0f, 64.0f };
		float4 MyPosRight = MyPos + float4{ 32.0f, 0.0f };
		float4 MyPosLeft = MyPos + float4{ -32.0f, 0.0f };
		float4 MyPosTop = MyPos + float4{ 0.0f, -14.0f };
		float4 MyPosBot = MyPos + float4{ 0.0f, 64.0f };
		float4 NextPos = MyPos + (MoveDir_ * GameEngineTime::GetDeltaTime(TimeScale_) * Speed_);
		float4 NextRealPos = MyPos + (MoveDir_ * GameEngineTime::GetDeltaTime(TimeScale_) * Speed_);
		float4 CheckPosTopRight = NextPos + float4{ 32.0f, -14.0f };
		float4 CheckPosTopLeft = NextPos + float4{ -32.0f, -14.0f };
		float4 CheckPosBotRight = NextPos + float4{ 32.0f, 64.0f };
		float4 CheckPosBotLeft = NextPos + float4{ -32.0f, 64.0f };
		float4 CheckPosRight = NextPos + float4{ 32.0f, 0.0f };
		float4 CheckPosLeft = NextPos + float4{ -32.0f, 0.0f };
		float4 CheckPosTop = NextPos + float4{ 0.0f, -14.0f };
		float4 CheckPosBot = NextPos + float4{ 0.0f, 64.0f };

		int ColorNextTopRight = PlayerLink::MapCarryColImage_->GetImagePixel(CheckPosTopRight);
		int ColorNextTopLeft = PlayerLink::MapCarryColImage_->GetImagePixel(CheckPosTopLeft);
		int ColorNextBotRight = PlayerLink::MapCarryColImage_->GetImagePixel(CheckPosBotRight);
		int ColorNextBotLeft = PlayerLink::MapCarryColImage_->GetImagePixel(CheckPosBotLeft);
		int ColorNextRight = PlayerLink::MapCarryColImage_->GetImagePixel(CheckPosRight);
		int ColorNextLeft = PlayerLink::MapCarryColImage_->GetImagePixel(CheckPosLeft);
		int ColorNextTop = PlayerLink::MapCarryColImage_->GetImagePixel(CheckPosTop);
		int ColorNextBot = PlayerLink::MapCarryColImage_->GetImagePixel(CheckPosBot);

		if (Black != ColorNextTopRight &&
			Black != ColorNextTopLeft &&
			Black != ColorNextBotRight &&
			Black != ColorNextBotLeft &&
			Black != ColorNextRight &&
			Black != ColorNextLeft &&
			Black != ColorNextTop &&
			Black != ColorNextBot)
		{
			if (false == BlueStalfosCol_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
			{
				SetMove(MoveDir_ * GameEngineTime::GetDeltaTime(TimeScale_) * Speed_);
				return true;
			}
			else
			{
				if (true == MoveRight)
				{
					if (false == BlueStalfosCol_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime(TimeScale_) * Speed_);
					}
				}

				if (true == MoveLeft)
				{
					if (false == BlueStalfosCol_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						SetMove(float4::LEFT * GameEngineTime::GetDeltaTime(TimeScale_) * Speed_);
					}
				}
				if (true == MoveUp)
				{
					if (false == BlueStalfosCol_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						SetMove(float4::UP * GameEngineTime::GetDeltaTime(TimeScale_) * Speed_);
					}

				}
				if (true == MoveDown)
				{
					if (false == BlueStalfosCol_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						SetMove(float4::DOWN * GameEngineTime::GetDeltaTime(TimeScale_) * Speed_);
					}

				}
				return true;
			}
		}

		return false;
	}
}

