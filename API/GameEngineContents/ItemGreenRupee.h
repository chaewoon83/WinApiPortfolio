#pragma once
#include <GameEngine/GameEngineActor.h>

class GameEngineCollision;
class GmaeEngineRenderer;
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

	void SetGreenRupeePosition(float4 _Pos)
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

