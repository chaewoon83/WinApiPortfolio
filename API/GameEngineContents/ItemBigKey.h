#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineCollision;
class GmaeEngineRenderer;
// Ό³Έν :
class ItemBigKey : public GameEngineActor
{
public:
	// constrcuter destructer
	ItemBigKey();
	~ItemBigKey();

	// delete Function
	ItemBigKey(const ItemBigKey& _Other) = delete;
	ItemBigKey(ItemBigKey&& _Other) noexcept = delete;
	ItemBigKey& operator=(const ItemBigKey& _Other) = delete;
	ItemBigKey& operator=(ItemBigKey&& _Other) noexcept = delete;

	void SetRedRupeePosition(float4 _Pos)
	{
		OriginalPos_ = _Pos;
		SetPosition(OriginalPos_);
	}

	void SetRespawnPivot(float _Pivot)
	{
		RespawnPivot_ = _Pivot;
	}

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* ItemRenderer_;
	GameEngineRenderer* ShadowRenderer_;
	GameEngineCollision* ItemCollision_;
	bool IsRendererSet_;
	float4 OriginalPos_;
	float RespawnPivot_;
	float LiveTime_;
	float CurLiveTime_;
	float Speed_;
	float BounceSpeed_;
	float BounceTime_;
	int TimeScale_;

	//blink
	bool IsBlink_;
	bool IsAlphaOn_;
	float CurBlinkTime_;
	float CurBlinkFreq_;
	float BlinkTime_;
	float BlinkFreq_;


};

