#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class ItemRedRupee : public GameEngineActor
{
public:
	// constrcuter destructer
	ItemRedRupee();
	~ItemRedRupee();

	// delete Function
	ItemRedRupee(const ItemRedRupee& _Other) = delete;
	ItemRedRupee(ItemRedRupee&& _Other) noexcept = delete;
	ItemRedRupee& operator=(const ItemRedRupee& _Other) = delete;
	ItemRedRupee& operator=(ItemRedRupee&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:

};

