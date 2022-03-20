#pragma once
#include <GameEngine/GameEngineLevel.h>

// ���� :
class MapLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	MapLevel();
	~MapLevel();

	// delete Function
	MapLevel(const MapLevel& _Other) = delete;
	MapLevel(MapLevel&& _Other) noexcept = delete;
	MapLevel& operator=(const MapLevel& _Other) = delete;
	MapLevel& operator=(MapLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
private:

};

