#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineRenderer;
class GameEngineCollision;
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
	float DeathTime_;
	float CurDeathTime_;

	GameEngineRenderer* Renderer_;
	GameEngineCollision* Collision_;
};

