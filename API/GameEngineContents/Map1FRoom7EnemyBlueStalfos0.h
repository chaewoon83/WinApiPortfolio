#pragma once
#include <GameEngine/GameEngineActor.h>
#include "GameEngineContentsEnum.h"
// Ό³Έν :
class GameEngineImage;
class Map1FRoom7EnemyBlueStalfos0 : public GameEngineActor
{
public:
	// constrcuter destructer
	Map1FRoom7EnemyBlueStalfos0();
	~Map1FRoom7EnemyBlueStalfos0();

	// delete Function
	Map1FRoom7EnemyBlueStalfos0(const Map1FRoom7EnemyBlueStalfos0& _Other) = delete;
	Map1FRoom7EnemyBlueStalfos0(Map1FRoom7EnemyBlueStalfos0&& _Other) noexcept = delete;
	Map1FRoom7EnemyBlueStalfos0& operator=(const Map1FRoom7EnemyBlueStalfos0& _Other) = delete;
	Map1FRoom7EnemyBlueStalfos0& operator=(Map1FRoom7EnemyBlueStalfos0&& _Other) noexcept = delete;

	bool GetIsDeath()
	{
		return IsDeath_;
	}

protected:
	void Start() override;
	void Update() override;
	void Render() override;

private:
	GameEngineRenderer* BlueStalfosHeadRenderer_;
	GameEngineRenderer* BlueStalfosBodyRenderer_;
	GameEngineRenderer* BlueStalfosShadowRenderer_;
	GameEngineRenderer* DeathEffectRenderer_;

	GameEngineCollision* BlueStalfosCol_;
	GameEngineCollision* BlueStalfosMoveCol_;
	GameEngineCollision* BlueStalfosJumpCol_;
	GameEngineActor* HitActor_;

	float4 BlueStalfosPos_;

	int TimeScale_;

	int Hp_;
	float InvincibleTime_;
	float CurInvincibleTime_;
	bool IsInvincible_;
	bool IsDeath_;
	bool IsRelocated_;

	bool IsGetDamaged_;
	bool IsKnockback_;
	bool IsBlink_;

	float Speed_;
	float JumpSpeed_;
	float MoveTime_;
	float CurMoveTime_;
	float WaitTime_;
	float CurWaitTime_;
	float RestTime_;
	float CurRestTime_;
	float KnockbackTime_;
	float CurKnockbackTime_;
	float BlinkTime_;
	float CurBlinkTime_;
	float BlinkFreq_;
	float CurBlinkFreq_;
	float TimeAfterDeath_;
	float CurTimeAfterDeath_;

	float JumpTime_;
	float CurJumpTime_;
	
	float4 OriginalPivot_;
	float JumpHeight_;
	float JumpVerSpeed_;
	float CurJumpVerSpeed_;

	float4 MoveDir_;
	float4 KnockbackDir_;
	float KnockBackSpeed_;
	bool IsAlphaOn_;

	void MoveDirCheck(int _RandomInt);
	void StopDirCheck();
	void JumpDirCheck(float4 _Dir);
	void JumpCheck();
	void GetDamaged();
	void Action();
	bool MoveFunction();
	bool PosAndColorCheck(int _Color, GameEngineImage* _Image);

	/// ////////FSM
private:
	void BlueStalfosChangeState(BlueStalfosState _State);
	void BlueStalfosStateUpdate();

	BlueStalfosState BlueStalfosCurState_;
	BlueStalfosState BlueStalfosPrevState_;

	void LookAroundRightStart();
	void LookAroundLeftStart();
	void LookAroundUpStart();
	void LookAroundDownStart();
	void WalkRightStart();
	void WalkLeftStart();
	void WalkUpStart();
	void WalkDownStart();
	void JumpRightStart();
	void JumpLeftStart();
	void JumpUpStart();
	void JumpDownStart();
	void KnockbackedStart();
	void DeathStart();

	void LookAroundUpdate();
	void WalkUpdate();
	void JumpUpdate();
	void KnockbackedUpdate();
	void DeathUpdate();

};

