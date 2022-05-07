#pragma once
#include <GameEngine/GameEngineActor.h>
#include "GameEngineContentsEnum.h"

class GameEngineRenderer;
class GameEngineCollision;
// Ό³Έν :
class BossArmomsKnight : public GameEngineActor
{
public:
	// constrcuter destructer
	BossArmomsKnight();
	~BossArmomsKnight();

	// delete Function
	BossArmomsKnight(const BossArmomsKnight& _Other) = delete;
	BossArmomsKnight(BossArmomsKnight&& _Other) noexcept = delete;
	BossArmomsKnight& operator=(const BossArmomsKnight& _Other) = delete;
	BossArmomsKnight& operator=(BossArmomsKnight&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* BossRenderer_;
	GameEngineRenderer* BossShadowRenderer_;

	//Hit
	GameEngineCollision* BossCol_;
	//Hit by Sword
	GameEngineCollision* BossCol2_;

	int TimeScale_;
	float FollowSpeed_;
	float JumpSpeed_;
	float CurJumpSpeed_;
	float DiveSpeed_;

	///////////////////////FSM
	BossState CurBossState_;
	void BossChangeState(BossState _State);
	void BossUpdate();

	void IdleStart();
	void FollowPlayerStart();
	void JumpStart();
	void DiveStart();
	void KnockbackedStart();
	void DeathStart();

	void IdleUpdate();
	void FollowPlayerUpdate();
	void JumpUpdate();
	void DiveUpdate();
	void KnockbackedUpdate();
	void DeathUpdate();

	//////Idle
	float IdleWaitTime_;
	float CurIdleWaitTime_;

	//////FollowPlayer
	float4 TargetPlayerPos_;
	float4 FollowDir_;
	float DistancebtwPlayer_;

	//Combat
	int Hp_;
	int BossPhase_;
	bool IsInvincible_;
	float InvincibleTime_;
	float CurInvincibleTime_;
	bool IsKnockback_;
	float4 KnockbackDir_;
	float KnockbackSpeed_;
	GameEngineActor* HitActor_;
	static bool IsDeath_;

	void CheckBossPhase();
	void GetDamagedBySword();

	//Jump
	float4 InitialPos_;
	float4 JumpPos_;
	float JumpTime_;
	float CurJumpTime_;
	float JumpHeight_;
	float JumpTargetDistance_;
	
	//Dive
	float DiveTime_;
	float CurDiveTime_;
	float DiveWaitTime_;
	float CurDiveWaitTime_;

	///Movemet
	float BounceSpeed_;
	float BounceTime_;

	void Bounce();

	//Gettter
public:

	static bool GetIsDeath()
	{
		return IsDeath_;
	}
};

