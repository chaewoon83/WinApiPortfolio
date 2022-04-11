#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class TitleZeldaZ : public GameEngineActor
{
public:
	// constrcuter destructer
	TitleZeldaZ();
	~TitleZeldaZ();

	// delete Function
	TitleZeldaZ(const TitleZeldaZ& _Other) = delete;
	TitleZeldaZ(TitleZeldaZ&& _Other) noexcept = delete;
	TitleZeldaZ& operator=(const TitleZeldaZ& _Other) = delete;
	TitleZeldaZ& operator=(TitleZeldaZ&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* TitleZeldaZ_;
	bool IsTitleZeldaZExist_;
};

