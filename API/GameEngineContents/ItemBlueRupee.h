#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineCollision;
class GmaeEngineRenderer;
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
	
	void SetBlueRupeePosition(float4 _Pos)
	{
		OriginalPos_ = _Pos;
		SetPosition(OriginalPos_);
		IsRendererSet_ = true;
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

