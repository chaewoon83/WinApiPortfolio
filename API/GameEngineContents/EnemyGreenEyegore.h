#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class EnemyGreenEyegore : public GameEngineActor
{
public:
	// constrcuter destructer
	EnemyGreenEyegore();
	~EnemyGreenEyegore();

	// delete Function
	EnemyGreenEyegore(const EnemyGreenEyegore& _Other) = delete;
	EnemyGreenEyegore(EnemyGreenEyegore&& _Other) noexcept = delete;
	EnemyGreenEyegore& operator=(const EnemyGreenEyegore& _Other) = delete;
	EnemyGreenEyegore& operator=(EnemyGreenEyegore&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:

};

