#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class EnemyBubbleGroup : public GameEngineActor
{
public:
	// constrcuter destructer
	EnemyBubbleGroup();
	~EnemyBubbleGroup();

	// delete Function
	EnemyBubbleGroup(const EnemyBubbleGroup& _Other) = delete;
	EnemyBubbleGroup(EnemyBubbleGroup&& _Other) noexcept = delete;
	EnemyBubbleGroup& operator=(const EnemyBubbleGroup& _Other) = delete;
	EnemyBubbleGroup& operator=(EnemyBubbleGroup&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:

};

