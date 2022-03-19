#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class UISelectedItem : public GameEngineActor
{
public:
	// constrcuter destructer
	UISelectedItem();
	~UISelectedItem();

	// delete Function
	UISelectedItem(const UISelectedItem& _Other) = delete;
	UISelectedItem(UISelectedItem&& _Other) noexcept = delete;
	UISelectedItem& operator=(const UISelectedItem& _Other) = delete;
	UISelectedItem& operator=(UISelectedItem&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:

};

