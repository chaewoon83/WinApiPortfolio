#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class ItemGreenRupee : public GameEngineActor
{
public:
	// constrcuter destructer
	ItemGreenRupee();
	~ItemGreenRupee();

	// delete Function
	ItemGreenRupee(const ItemGreenRupee& _Other) = delete;
	ItemGreenRupee(ItemGreenRupee&& _Other) noexcept = delete;
	ItemGreenRupee& operator=(const ItemGreenRupee& _Other) = delete;
	ItemGreenRupee& operator=(ItemGreenRupee&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:

};

