#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class UILayout : public GameEngineActor
{
public:
	// constrcuter destructer
	UILayout();
	~UILayout();

	// delete Function
	UILayout(const UILayout& _Other) = delete;
	UILayout(UILayout&& _Other) noexcept = delete;
	UILayout& operator=(const UILayout& _Other) = delete;
	UILayout& operator=(UILayout&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:

};

