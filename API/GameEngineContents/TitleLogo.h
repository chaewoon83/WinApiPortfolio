#pragma once
#include <GameEngine/GameEngineActor.h>
// ���� :
class TitleLogo : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleLogo();
	~TitleLogo();

	// delete Function
	TitleLogo(const TitleLogo& _Other) = delete;
	TitleLogo(TitleLogo&& _Other) noexcept = delete;
	TitleLogo& operator=(const TitleLogo& _Other) = delete;
	TitleLogo& operator=(TitleLogo&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* TitleLogo_;
	bool IsTitleLogoExist_;
};

