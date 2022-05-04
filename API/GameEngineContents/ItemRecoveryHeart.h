#pragma once
#include <GameEngine/GameEngineActor.h>
class GameEngineCollision;
class GmaeEngineRenderer;
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
	GameEngineRenderer* ItemRenderer_;
	GameEngineRenderer* ShadowRenderer_;
	GameEngineCollision* ItemCollision_;
	float LiveTime_;
	float CurLiveTime_;
	bool IsBlink_;
	bool IsAlphaOn_;
	float CurBlinkTime_;
	float CurBlinkFreq_;
	float BlinkTime_;
	float BlinkFreq_;
};

