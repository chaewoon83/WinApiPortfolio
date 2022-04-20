#pragma once
#include <GameEngine/GameEngineActor.h>
// ���� :
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

	int Hp_;
	float InvincibleTime_;
	float CurInvincibleTime_;
	bool IsInvincible_;
	bool IsDeath_;

	void GetDamaged();
};

