#pragma once
#include <GameEngine/GameEngineActor.h>
#include "GameEngineContentsEnum.h"
// ���� :
class GameEngineImage;
class Map1FRoom2EnemyPopo0 : public GameEngineActor
{
public:
	// constrcuter destructer
	Map1FRoom2EnemyPopo0();
	~Map1FRoom2EnemyPopo0();

	// delete Function
	Map1FRoom2EnemyPopo0(const Map1FRoom2EnemyPopo0& _Other) = delete;
	Map1FRoom2EnemyPopo0(Map1FRoom2EnemyPopo0&& _Other) noexcept = delete;
	Map1FRoom2EnemyPopo0& operator=(const Map1FRoom2EnemyPopo0& _Other) = delete;
	Map1FRoom2EnemyPopo0& operator=(Map1FRoom2EnemyPopo0&& _Other) noexcept = delete;

	void SetPopoPos(float4 _Pos)
	{
		PopoPos_ = _Pos;
		SetPosition(PopoPos_);
	}
protected:
	void Start() override;
	void Update() override;
	void Render() override;

private:
	GameEngineRenderer* PopoRenderer_;
	GameEngineRenderer* DeathEffectRenderer_;

	GameEngineCollision* PopoCol_;
	GameEngineCollision* PopoMoveCol_;
	GameEngineActor* HitActor_;

	float4 PopoPos_;

	int TimeScale_;

	int Hp_;
	float InvincibleTime_;
	float CurInvincibleTime_;
	bool IsInvincible_;
	bool IsDeath_;

	bool IsGetDamaged_;
	bool IsKnockback_;
	bool IsBlink_;

	int MoveTimes_;
	int CurMoveTimes_;
	float MoveFreq_;
	float CurMoveFreq_;
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

	float4 MoveDir_;
	float4 KnockbackDir_;
	float KnockBackSpeed_;
	bool IsAlphaOn_;

	void MoveDirCheck(int _RandomInt);
	void GetDamaged();
	bool PosAndColorCheck(int _Color, GameEngineImage* _Image);

	/// ////////FSM
private:
	void PopoChangeState(PopoState _State);
	void PopoStateUpdate();

	PopoState PopoCurState_;

	void DeathStart();
	void IdleStart();
	void KnockbackedStart();



	void DeathUpdate();
	void IdleUpdate();
	void KnockbackedUpdate();


};

