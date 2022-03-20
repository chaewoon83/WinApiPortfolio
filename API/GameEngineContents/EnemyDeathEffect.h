#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class EnemyDeathEffect : public GameEngineActor
{
public:
	// constrcuter destructer
	EnemyDeathEffect();
	~EnemyDeathEffect();

	// delete Function
	EnemyDeathEffect(const EnemyDeathEffect& _Other) = delete;
	EnemyDeathEffect(EnemyDeathEffect&& _Other) noexcept = delete;
	EnemyDeathEffect& operator=(const EnemyDeathEffect& _Other) = delete;
	EnemyDeathEffect& operator=(EnemyDeathEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:

};

