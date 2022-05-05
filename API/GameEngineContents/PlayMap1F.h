#pragma once
#include <GameEngine/GameEngineLevel.h>
class PlayerLink;
class Map1FBridge;
// Ό³Έν :
class PlayMap1F : public GameEngineLevel
{
public:
	// constrcuter destructer
	PlayMap1F();
	~PlayMap1F();

	// delete Function
	PlayMap1F(const PlayMap1F& _Other) = delete;
	PlayMap1F(PlayMap1F&& _Other) noexcept = delete;
	PlayMap1F& operator=(const PlayMap1F& _Other) = delete;
	PlayMap1F& operator=(PlayMap1F&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _NextLevel) override;
	void LevelChangeEnd(GameEngineLevel* _PrevLevel) override;

private:
	GameEngineSoundPlayer BGMSoundPlayer_;
	PlayerLink* Player_;
	void ResetTimeScale();
	void CreatePot();
};


