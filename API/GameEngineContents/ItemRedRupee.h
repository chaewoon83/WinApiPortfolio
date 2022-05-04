#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineCollision;
class GmaeEngineRenderer;
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

