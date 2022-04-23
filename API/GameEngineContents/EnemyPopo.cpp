#include "EnemyPopo.h"
#include "PlayerLink.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineRandom.h>
#include "GameEngineContentsEnum.h"
#include "ItemGreenRupee.h"
#include "ItemBlueRupee.h"


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
	 KnockBackSpeed_(500.0f),
	 PopoCurState_(PopoState::Idle)
{
}


/// 10 times killed Popo, 2 times 1rupee, 1 time 5rupee;
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
	BlinkUpdate();
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
			PopoChangeState(PopoState::Death);
			return;
		}
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

void EnemyPopo::KnockbackedStart()
{
}

void EnemyPopo::DeathStart()
{
}

void EnemyPopo::IdleUpdate()
{
	KnockbackedCheck();
}

void EnemyPopo::KnockbackedUpdate()
{
	CurKnockbackTime_ += GameEngineTime::GetDeltaTime();
	int White = RGB(255, 255, 255);
	if (true == PosAndColorCheck(White, PlayerLink::MapColImage_))
	{
		SetMove(KnockbackDir_ * KnockBackSpeed_ * GameEngineTime::GetDeltaTime());
	}
	if (KnockbackTime_ < CurKnockbackTime_)
	{
		IsKnockback_ = false;
	}
	if (false == IsKnockback_)
	{
		PopoChangeState(PopoState::Idle);
	}
	if (nullptr == GetLevel())
	{
		return;
	}
}

void EnemyPopo::DeathUpdate()
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

void EnemyPopo::KnockbackedCheck()
{
	std::vector<GameEngineCollision*> ColList;

	if (true == PopoCol_->CollisionResult("Sword", ColList, CollisionType::Rect, CollisionType::Rect) && false == IsKnockback_)
	{
		PopoChangeState(PopoState::Knockbacked);
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

void EnemyPopo::PopoStateUpdate()
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

bool EnemyPopo::PosAndColorCheck(int _Color, GameEngineImage* _Image)
{
	float4 MyPos = GetPosition();
	float4 MyPosTopRight = MyPos + float4{ 32.0f, -21.0f };
	float4 MyPosTopLeft = MyPos + float4{ -32.0f, -21.0f };
	float4 MyPosBotRight = MyPos + float4{ 32.0f, 43.0f };
	float4 MyPosBotLeft = MyPos + float4{ -32.0f, 43.0f };
	float4 MyPosRight = MyPos + float4{ +32.0f,  0.0f };
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