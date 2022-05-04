#pragma once
#include <GameEngine/GameEngineActor.h>
class GameEngineRenderer;
// Ό³Έν :
class BlackScreen : public GameEngineActor
{
public:
	// constrcuter destructer
	BlackScreen();
	~BlackScreen();

	// delete Function
	BlackScreen(const BlackScreen& _Other) = delete;
	BlackScreen(BlackScreen&& _Other) noexcept = delete;
	BlackScreen& operator=(const BlackScreen& _Other) = delete;
	BlackScreen& operator=(BlackScreen&& _Other) noexcept = delete;

	static GameEngineRenderer* Renderer_;
protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
};

