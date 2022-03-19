#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class EnemyStalfos : public GameEngineActor
{
public:
	// constrcuter destructer
	EnemyStalfos();
	~EnemyStalfos();

	// delete Function
	EnemyStalfos(const EnemyStalfos& _Other) = delete;
	EnemyStalfos(EnemyStalfos&& _Other) noexcept = delete;
	EnemyStalfos& operator=(const EnemyStalfos& _Other) = delete;
	EnemyStalfos& operator=(EnemyStalfos&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:

};

