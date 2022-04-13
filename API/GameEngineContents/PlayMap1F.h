#pragma once
#include <GameEngine/GameEngineLevel.h>

class Map1FBridge;
// ���� :
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

	void BridgeOn();
	void BridgeOff();
protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart() override;

private:
	Map1FBridge* Bridge_;
};


