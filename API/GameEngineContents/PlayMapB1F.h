#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν :
class PlayMapB1F : public GameEngineLevel
{
public:
	// constrcuter destructer
	PlayMapB1F();
	~PlayMapB1F();

	// delete Function
	PlayMapB1F(const PlayMapB1F& _Other) = delete;
	PlayMapB1F(PlayMapB1F&& _Other) noexcept = delete;
	PlayMapB1F& operator=(const PlayMapB1F& _Other) = delete;
	PlayMapB1F& operator=(PlayMapB1F&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;
private:

};

