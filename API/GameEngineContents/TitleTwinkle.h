#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class TitleTwinkle : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleTwinkle();
	~TitleTwinkle();

	// delete Function
	TitleTwinkle(const TitleTwinkle& _Other) = delete;
	TitleTwinkle(TitleTwinkle&& _Other) noexcept = delete;
	TitleTwinkle& operator=(const TitleTwinkle& _Other) = delete;
	TitleTwinkle& operator=(TitleTwinkle&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* Twinkle1_;
	bool IsTwinkleExist_;
	float4 TwinklePos_;
	float4 TwinklePos1_;
	float4 TwinklePos2_;
	float4 TwinklePos3_;
	float4 TwinklePos4_;
	int CurrentTwinkle_;
	bool IsAnimationEnd_;
};

