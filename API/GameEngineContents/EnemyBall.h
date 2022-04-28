#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineRenderer;
// Ό³Έν :
class EnemyBall : public GameEngineActor
{
public:
	// constrcuter destructer
	EnemyBall();
	~EnemyBall();

	// delete Function
	EnemyBall(const EnemyBall& _Other) = delete;
	EnemyBall(EnemyBall&& _Other) noexcept = delete;
	EnemyBall& operator=(const EnemyBall& _Other) = delete;
	EnemyBall& operator=(EnemyBall&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	float DeathTime_;
	float CurDeathTime_;

	GameEngineRenderer* Renderer_;

};

