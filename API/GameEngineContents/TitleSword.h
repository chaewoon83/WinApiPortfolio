#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class TitleSword : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleSword();
	~TitleSword();

	// delete Function
	TitleSword(const TitleSword& _Other) = delete;
	TitleSword(TitleSword&& _Other) noexcept = delete;
	TitleSword& operator=(const TitleSword& _Other) = delete;
	TitleSword& operator=(TitleSword&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	float4 SwordPos_;
	bool IsSwordExist_;
	bool IsSwordStop_;
	GameEngineRenderer* Sword_;

};

