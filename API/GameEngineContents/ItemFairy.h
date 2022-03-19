#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class ItemFairy : public GameEngineActor
{
public:
	// constrcuter destructer
	ItemFairy();
	~ItemFairy();

	// delete Function
	ItemFairy(const ItemFairy& _Other) = delete;
	ItemFairy(ItemFairy&& _Other) noexcept = delete;
	ItemFairy& operator=(const ItemFairy& _Other) = delete;
	ItemFairy& operator=(ItemFairy&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:

};

