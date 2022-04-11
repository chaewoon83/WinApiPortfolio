#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class TitleNintenPresents : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleNintenPresents();
	~TitleNintenPresents();

	// delete Function
	TitleNintenPresents(const TitleNintenPresents& _Other) = delete;
	TitleNintenPresents(TitleNintenPresents&& _Other) noexcept = delete;
	TitleNintenPresents& operator=(const TitleNintenPresents& _Other) = delete;
	TitleNintenPresents& operator=(TitleNintenPresents&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* NintendoPresents_;
	bool IsNintendoPresentsExist_;
	bool IsNintendoPresentsDeath_;
};

