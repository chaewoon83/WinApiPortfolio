#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class ItemBomb : public GameEngineActor
{
public:
	// constrcuter destructer
	ItemBomb();
	~ItemBomb();

	// delete Function
	ItemBomb(const ItemBomb& _Other) = delete;
	ItemBomb(ItemBomb&& _Other) noexcept = delete;
	ItemBomb& operator=(const ItemBomb& _Other) = delete;
	ItemBomb& operator=(ItemBomb&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:

};

