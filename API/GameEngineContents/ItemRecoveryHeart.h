#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class ItemRecoveryHeart : public GameEngineActor
{
public:
	// constrcuter destructer
	ItemRecoveryHeart();
	~ItemRecoveryHeart();

	// delete Function
	ItemRecoveryHeart(const ItemRecoveryHeart& _Other) = delete;
	ItemRecoveryHeart(ItemRecoveryHeart&& _Other) noexcept = delete;
	ItemRecoveryHeart& operator=(const ItemRecoveryHeart& _Other) = delete;
	ItemRecoveryHeart& operator=(ItemRecoveryHeart&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:

};

