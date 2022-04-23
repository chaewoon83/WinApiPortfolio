#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
enum class PopoState
{
	Idle,
	Knockbacked,
	Death,
	Max,
};
class GameEngineImage;
class EnemyPopo : public GameEngineActor
{
public:
	// constrcuter destructer
	EnemyPopo();
	~EnemyPopo();

	// delete Function
	EnemyPopo(const EnemyPopo& _Other) = delete;
	EnemyPopo(EnemyPopo&& _Other) noexcept = delete;
	EnemyPopo& operator=(const EnemyPopo& _Other) = delete;
	EnemyPopo& operator=(EnemyPopo&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;

private:
	GameEngineRenderer* PopoRenderer_;
	GameEngineCollision* PopoCol_;
	GameEngineActor* HitActor_;

	int Hp_;
	float InvincibleTime_;
	float CurInvincibleTime_;
	bool IsInvincible_;
	bool IsDeath_;

	bool IsGetDamaged_;
	bool IsKnockback_;
	bool IsBlink_;

	float KnockbackTime_;
	float CurKnockbackTime_;
	float BlinkTime_;
	float CurBlinkTime_;
	float BlinkFreq_;
	float CurBlinkFreq_;

	float4 KnockbackDir_;
	float KnockBackSpeed_;
	bool IsAlphaOn_;

	void GetDamaged();
	void BlinkUpdate();
	void KnockbackedCheck();
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

