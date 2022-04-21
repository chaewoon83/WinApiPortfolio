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
	 Hp_(2)
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
	if (false == IsInvincible_  && false == IsDeath_)
	{
		if (true == PopoCol_->CollisionResult("Sword", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			Hp_ -= 1;
			IsInvincible_ = true;
		}

		if (0 >= Hp_)
		{
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
