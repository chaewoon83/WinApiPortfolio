#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineRenderer;
class GameEngineCollision;
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
	float Speed_;
	float4 Pos_;
	int TimeScale_;
	float4 MoveDir_;

	bool IsRightBounce_;
	bool IsTopBounce_;

	bool MoveDirCheck();
	bool PixelCollisionCheckX(float4 _Min, float4 _Max);
	bool PixelCollisionCheckY(float4 _Min, float4 _Max);

	GameEngineRenderer* Renderer_;
	GameEngineCollision* Collision_;
};

