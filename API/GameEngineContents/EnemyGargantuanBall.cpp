#include "EnemyGargantuanBall.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "PlayerLink.h"
#include "GameEngineContentsEnum.h"

EnemyGargantuanBall::EnemyGargantuanBall()
	: DeathTime_(4.0f)
	, CurDeathTime_(0.0f)
	, Renderer_(nullptr)
	, Collision_(nullptr)
{
}

EnemyGargantuanBall::~EnemyGargantuanBall() 
{
}

void EnemyGargantuanBall::Start()
{
	Renderer_ = CreateRenderer();
	Renderer_->CreateAnimationTimeKey("EnemyGargantuanBall.bmp", "Idle", 4, 0, 1, 0.04f, true);
	Renderer_->ChangeAnimation("Idle");
	Collision_ = CreateCollision("MonsterB1FHitBox", { 124, 124 });
}
 
void EnemyGargantuanBall::Update()
{
	SetMove(float4{ 0, 350 } * GameEngineTime::GetDeltaTime(4));

	CurDeathTime_ += GameEngineTime::GetDeltaTime(4);
	if (DeathTime_ < CurDeathTime_)
	{
		Death();
	}
}
void EnemyGargantuanBall::Render()
{
	//DebugRectRender();

}
