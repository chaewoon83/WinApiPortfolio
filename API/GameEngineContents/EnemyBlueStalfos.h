//#pragma once
//#include <GameEngine/GameEngineActor.h>
//#include "GameEngineContentsEnum.h"
//// Ό³Έν :
//class GameEngineImage;
//class EnemyBlueStalfos : public GameEngineActor
//{
//public:
//	// constrcuter destructer
//	EnemyBlueStalfos();
//	~EnemyBlueStalfos();
//
//	// delete Function
//	EnemyBlueStalfos(const EnemyBlueStalfos& _Other) = delete;
//	EnemyBlueStalfos(EnemyBlueStalfos&& _Other) noexcept = delete;
//	EnemyBlueStalfos& operator=(const EnemyBlueStalfos& _Other) = delete;
//	EnemyBlueStalfos& operator=(EnemyBlueStalfos&& _Other) noexcept = delete;
//
//protected:
//	void Start() override;
//	void Update() override;
//	void Render() override;
//
//private:
//	GameEngineRenderer* BlueStalfosHeadRenderer_;
//	GameEngineRenderer* BlueStalfosBodyRenderer_;
//	GameEngineRenderer* DeathEffectRenderer_;
//
//	GameEngineCollision* BlueStalfosCol_;
//	GameEngineCollision* BlueStalfosMoveCol_;
//	GameEngineActor* HitActor_;
//
//	float4 BlueStalfosPos_;
//
//	int TimeScale_;
//
//	int Hp_;
//	float InvincibleTime_;
//	float CurInvincibleTime_;
//	bool IsInvincible_;
//	bool IsDeath_;
//
//	bool IsGetDamaged_;
//	bool IsKnockback_;
//	bool IsBlink_;
//
//	int MoveTimes_;
//	int CurMoveTimes_;
//	float MoveFreq_;
//	float CurMoveFreq_;
//	float RestTime_;
//	float CurRestTime_;
//	float KnockbackTime_;
//	float CurKnockbackTime_;
//	float BlinkTime_;
//	float CurBlinkTime_;
//	float BlinkFreq_;
//	float CurBlinkFreq_;
//	float TimeAfterDeath_;
//	float CurTimeAfterDeath_;
//
//	float4 MoveDir_;
//	float4 KnockbackDir_;
//	float KnockBackSpeed_;
//	bool IsAlphaOn_;
//
//	void MoveDirCheck(int _RandomInt);
//	void GetDamaged();
//	bool PosAndColorCheck(int _Color, GameEngineImage* _Image);
//
//	/// ////////FSM
//private:
//	void BlueStalfosChangeState(BlueStalfosState _State);
//	void BlueStalfosStateUpdate();
//
//	BlueStalfosState BlueStalfosCurState_;
//
//	void LookAroundStart();
//	void WalkStart();
//	void JumpStart();
//	void KnockbackedStart();
//	void DeathStart();
//
//	void LookAroundUpdate();
//	void WalkUpdate();
//	void JumpUpdate();
//	void KnockbackedUpdate();
//	void DeathUpdate();
//
//};
//
