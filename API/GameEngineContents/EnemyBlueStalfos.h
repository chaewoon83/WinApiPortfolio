#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class EnemyBlueStalfos : public GameEngineActor
{
public:
	// constrcuter destructer
	EnemyBlueStalfos();
	~EnemyBlueStalfos();

	// delete Function
	EnemyBlueStalfos(const EnemyBlueStalfos& _Other) = delete;
	EnemyBlueStalfos(EnemyBlueStalfos&& _Other) noexcept = delete;
	EnemyBlueStalfos& operator=(const EnemyBlueStalfos& _Other) = delete;
	EnemyBlueStalfos& operator=(EnemyBlueStalfos&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:

};

