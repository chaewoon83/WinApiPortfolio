#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν :
class PlayMap2F : public GameEngineLevel
{
public:
	// constrcuter destructer
	PlayMap2F();
	~PlayMap2F();

	// delete Function
	PlayMap2F(const PlayMap2F& _Other) = delete;
	PlayMap2F(PlayMap2F&& _Other) noexcept = delete;
	PlayMap2F& operator=(const PlayMap2F& _Other) = delete;
	PlayMap2F& operator=(PlayMap2F&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _NextLevel) override;
private:

};

