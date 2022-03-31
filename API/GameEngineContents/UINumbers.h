#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class UINumbers : public GameEngineActor
{
public:
	// constrcuter destructer
	UINumbers();
	~UINumbers();

	// delete Function
	UINumbers(const UINumbers& _Other) = delete;
	UINumbers(UINumbers&& _Other) noexcept = delete;
	UINumbers& operator=(const UINumbers& _Other) = delete;
	UINumbers& operator=(UINumbers&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:

};

