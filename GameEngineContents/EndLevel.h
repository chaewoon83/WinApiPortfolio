#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν :
class EndLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	EndLevel();
	~EndLevel();

	// delete Function
	EndLevel(const EndLevel& _Other) = delete;
	EndLevel(EndLevel&& _Other) noexcept = delete;
	EndLevel& operator=(const EndLevel& _Other) = delete;
	EndLevel& operator=(EndLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
private:

};

