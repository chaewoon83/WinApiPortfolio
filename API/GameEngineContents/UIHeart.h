#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class UIHeart : public GameEngineActor
{
public:
	// constrcuter destructer
	UIHeart();
	~UIHeart();

	// delete Function
	UIHeart(const UIHeart& _Other) = delete;
	UIHeart(UIHeart&& _Other) noexcept = delete;
	UIHeart& operator=(const UIHeart& _Other) = delete;
	UIHeart& operator=(UIHeart&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	std::list<GameEngineRenderer*> AllHearts;
};

