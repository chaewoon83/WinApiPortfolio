#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class EnemyGargantuanBall : public GameEngineActor
{
public:
	// constrcuter destructer
	EnemyGargantuanBall();
	~EnemyGargantuanBall();

	// delete Function
	EnemyGargantuanBall(const EnemyGargantuanBall& _Other) = delete;
	EnemyGargantuanBall(EnemyGargantuanBall&& _Other) noexcept = delete;
	EnemyGargantuanBall& operator=(const EnemyGargantuanBall& _Other) = delete;
	EnemyGargantuanBall& operator=(EnemyGargantuanBall&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:

};

