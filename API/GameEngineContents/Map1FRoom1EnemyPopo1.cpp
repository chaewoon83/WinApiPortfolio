#include "Map1FRoom1EnemyPopo1.h"
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


Map1FRoom1EnemyPopo1::Map1FRoom1EnemyPopo1()
	:PopoRenderer_(nullptr),
	PopoCol_(nullptr),
	PopoMoveCol_(nullptr),
	PopoPos_({ 3040, 2439 + 4128 }),
	TimeScale_(2),
	IsInvincible_(false),
	IsDeath_(false),
	InvincibleTime_(0.3f),
	CurInvincibleTime_(0.0f),
	Hp_(2),
	IsGetDamaged_(false),
	IsKnockback_(false),
	IsBlink_(false),
	MoveTimes_(0),
	CurMoveTimes_(0),
	MoveFreq_(0.25f),
	CurMoveFreq_(0.0f),
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
	IsAlphaOn_(true),
	KnockbackDir_(float4::ZERO),
	MoveDir_(float4::ZERO),
	KnockBackSpeed_(800.0f),
	PopoCurState_(PopoState::Idle)
{
}


/// 10 times killed Popo, 2 times 1rupee, 1 time 5rupee;
Map1FRoom1EnemyPopo1::~Map1FRoom1EnemyPopo1()
{
}

void Map1FRoom1EnemyPopo1::Start()
{
	SetPosition(PopoPos_);
	PopoRenderer_ = CreateRenderer();
	PopoRenderer_->CreateAnimationTimeKey("EnemyPopo.bmp", "Idle", TimeScale_, 0, 2, 0.15f, true);
	//죽는 애니메이션은 플레이어와 함께한다
	PopoRenderer_->CreateAnimationTimeKey("EnemyDeathEffect.bmp", "DeathEffect", 0, 0, 6, 0.15f, false);
	PopoRenderer_->ChangeAnimation("Idle");

	//DeathEffectRenderer_ = CreateRenderer();
	//DeathEffectRenderer_->CreateAnimation("EnemyDeathEffect.bmp", "DeathEffect", 0, 6, 0.15f, false);

	PopoCol_ = CreateCollision("MonsterHitBox", { 64, 64 });
	PopoMoveCol_ = CreateCollision("MonsterMoveBox", { 64, 64 });

}

void Map1FRoom1EnemyPopo1::Update()
{
	PopoStateUpdate();
	EnemyGlobalFunction::PopoBlinkUpdate(TimeScale_, IsBlink_, IsAlphaOn_, BlinkTime_, CurBlinkTime_, BlinkFreq_, CurBlinkFreq_, PopoCurState_, PopoRenderer_);
}

void Map1FRoom1EnemyPopo1::Render()
{

}

void Map1FRoom1EnemyPopo1::GetDamaged()
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
		if (true == PopoCol_->CollisionResult("Sword", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			Hp_ -= 1;
			IsInvincible_ = true;
			IsBlink_ = true;
			IsKnockback_ = true;
			IsBlink_ = true;
			HitActor_ = ColList[0]->GetActor();
			KnockbackDir_ = GetPosition() - HitActor_->GetPosition();
			KnockbackDir_.Normal2D();
			PopoChangeState(PopoState::Knockbacked);
		}

		if (true == PopoCol_->CollisionResult("PotHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			Hp_ -= 1;
			IsInvincible_ = true;

			IsKnockback_ = true;
			IsBlink_ = true;
			HitActor_ = ColList[0]->GetActor();
			KnockbackDir_ = GetPosition() - HitActor_->GetPosition();
			KnockbackDir_.Normal2D();
			ColList[0]->Off();
			PopoChangeState(PopoState::Knockbacked);
		}

		if (0 >= Hp_)
		{
			IsInvincible_ = true;
			IsDeath_ = true;

			PopoCol_->Death();

			return;
		}
	}

}

void Map1FRoom1EnemyPopo1::IdleStart()
{
	//PopoRenderer_->ChangeAnimation("Idle");
	CurMoveFreq_ = MoveFreq_;
}

void Map1FRoom1EnemyPopo1::KnockbackedStart()
{
}

void Map1FRoom1EnemyPopo1::DeathStart()
{
	PopoMoveCol_->Death();
	PopoRenderer_->SetAlpha(255);
	PopoRenderer_->ChangeAnimation("DeathEffect");
	//DeathEffectRenderer_->ChangeAnimation("DeathEffect");
}

void Map1FRoom1EnemyPopo1::IdleUpdate()
{
	GetDamaged();
	CurRestTime_ += GameEngineTime::GetDeltaTime(TimeScale_);
	if (MoveTimes_ == CurMoveTimes_)
	{
		CurMoveTimes_ = 0;
		int RandomInt = GlobalRandom::RandomIntGenerate(7, 9);
		MoveTimes_ = RandomInt;
		RandomInt = GlobalRandom::RandomIntGenerate(1, 8);
		MoveDirCheck(RandomInt);
		CurRestTime_ = 0;
	}
	if (RestTime_ < CurRestTime_)
	{
		CurMoveFreq_ += GameEngineTime::GetDeltaTime(TimeScale_);
		if (MoveFreq_ < CurMoveFreq_)
		{
			CurMoveTimes_ += 1;
			CurMoveFreq_ = 0.0f;
			float4 NextPosition = GetPosition() + (MoveDir_ * 10);
			int White = RGB(255, 255, 255);
			if (true == PosAndColorCheck(White, PlayerLink::MapColImage_))
			{
				SetPosition(GetPosition() + (MoveDir_ * 10));
			}
		}
	}
}

void Map1FRoom1EnemyPopo1::KnockbackedUpdate()
{
	CurKnockbackTime_ += GameEngineTime::GetDeltaTime(TimeScale_);
	int White = RGB(255, 255, 255);
	if (true == PosAndColorCheck(White, PlayerLink::MapColImage_))
	{
		EnemyGlobalFunction::KnockBackMoveFunction(TimeScale_, KnockBackSpeed_, KnockbackDir_, PopoMoveCol_, this);
	}
	if (KnockbackTime_ < CurKnockbackTime_)
	{
		IsKnockback_ = false;
	}
	if (true == IsDeath_ && true == IsInvincible_ && KnockbackTime_ * 0.3f < CurKnockbackTime_)
	{
		PopoChangeState(PopoState::Death);
		return;
	}
	if (false == IsKnockback_)
	{
		CurKnockbackTime_ = 0.0f;
		PopoChangeState(PopoState::Idle);
		return;
	}
}

void Map1FRoom1EnemyPopo1::DeathUpdate()
{
	if (true == IsDeath_ && true == PopoRenderer_->IsEndAnimation())
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




void Map1FRoom1EnemyPopo1::PopoChangeState(PopoState _State)
{
	if (PopoCurState_ != _State)
	{
		switch (_State)
		{
		case PopoState::Idle:
			IdleStart();
			break;
		case PopoState::Knockbacked:
			KnockbackedStart();
			break;
		case PopoState::Death:
			DeathStart();
			break;
		case PopoState::Max:
			break;
		default:
			break;
		}
	}

	PopoCurState_ = _State;
}

void Map1FRoom1EnemyPopo1::PopoStateUpdate()
{
	switch (PopoCurState_)
	{
	case PopoState::Idle:
		IdleUpdate();
		break;
	case PopoState::Knockbacked:
		KnockbackedUpdate();
		break;
	case PopoState::Death:
		DeathUpdate();
		break;
	case PopoState::Max:
		break;
	default:
		break;
	}
}

bool Map1FRoom1EnemyPopo1::PosAndColorCheck(int _Color, GameEngineImage* _Image)
{
	float4 MyPos = GetPosition();
	float4 Map1f_2_Scale = float4{ 0, -4128 };
	if (false == dynamic_cast<PlayerLink*>(PlayerLink::MainPlayer_)->GetIsMap1F_2())
	{
		MyPos += Map1f_2_Scale;
	}
	float4 MyPosTopRight = MyPos + float4{ 32.0f, -32.0f };
	float4 MyPosTopLeft = MyPos + float4{ -32.0f, -32.0f };
	float4 MyPosBotRight = MyPos + float4{ 32.0f, 32.0f };
	float4 MyPosBotLeft = MyPos + float4{ -32.0f, 32.0f };
	float4 MyPosRight = MyPos + float4{ 32.0f, 0.0f };
	float4 MyPosLeft = MyPos + float4{ -32.0f, 0.0f };
	float4 MyPosTop = MyPos + float4{ 0.0f, -32.0f };
	float4 MyPosBot = MyPos + float4{ 0.0f, 32.0f };

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

void Map1FRoom1EnemyPopo1::MoveDirCheck(int _RandomInt)
{
	if (1 == _RandomInt)
	{
		MoveDir_ = float4{ 0, 1 };
	}
	if (2 == _RandomInt)
	{
		MoveDir_ = float4{ 1, 1 };
	}
	if (3 == _RandomInt)
	{
		MoveDir_ = float4{ 1, 0 };
	}
	if (4 == _RandomInt)
	{
		MoveDir_ = float4{ 1, -1 };
	}
	if (5 == _RandomInt)
	{
		MoveDir_ = float4{ 0, -1 };
	}
	if (6 == _RandomInt)
	{
		MoveDir_ = float4{ -1, -1 };
	}
	if (7 == _RandomInt)
	{
		MoveDir_ = float4{ -1,0 };
	}
	if (8 == _RandomInt)
	{
		MoveDir_ = float4{ -1, 1 };
	}
}


