#include "EnemyBall.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include "PlayerLink.h"

EnemyBall::EnemyBall()
	: DeathTime_(4.0f)
	, CurDeathTime_(0.0f)
	, Renderer_(nullptr)
{
}

EnemyBall::~EnemyBall() 
{
}

void EnemyBall::Start()
{
	Renderer_ = CreateRenderer();
	Renderer_->CreateAnimationTimeKey("EnemyBall.bmp", "Idle", 4, 0, 1, 0.04f, true);
	Renderer_->ChangeAnimation("Idle");
	CreateCollision("MonsterBotHitBox", { 60, 60 });
}
 
void EnemyBall::Update()
{
	SetMove(float4{ 0, 350 } * GameEngineTime::GetDeltaTime(4));
	CurDeathTime_ += GameEngineTime::GetDeltaTime(4);
	if (DeathTime_ < CurDeathTime_)
	{
		Death();
	}
}
void EnemyBall::Render()
{
	//DebugRectRender();
}
