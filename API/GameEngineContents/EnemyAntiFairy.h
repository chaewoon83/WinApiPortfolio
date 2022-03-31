#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class EnemyAntiFairy : public GameEngineActor
{
public:
	// constrcuter destructer
	EnemyAntiFairy();
	~EnemyAntiFairy();

	// delete Function
	EnemyAntiFairy(const EnemyAntiFairy& _Other) = delete;
	EnemyAntiFairy(EnemyAntiFairy&& _Other) noexcept = delete;
	EnemyAntiFairy& operator=(const EnemyAntiFairy& _Other) = delete;
	EnemyAntiFairy& operator=(EnemyAntiFairy&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:

};

