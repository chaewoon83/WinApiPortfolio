#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class ItemBlueRupee : public GameEngineActor
{
public:
	// constrcuter destructer
	ItemBlueRupee();
	~ItemBlueRupee();

	// delete Function
	ItemBlueRupee(const ItemBlueRupee& _Other) = delete;
	ItemBlueRupee(ItemBlueRupee&& _Other) noexcept = delete;
	ItemBlueRupee& operator=(const ItemBlueRupee& _Other) = delete;
	ItemBlueRupee& operator=(ItemBlueRupee&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:

};

