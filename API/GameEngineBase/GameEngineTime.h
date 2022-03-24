#pragma once

// Ό³Έν :
class GameEngineTime
{

public:
	float DeltaTime;
	__int64 CurrentCount;
	__int64 SecondCount;
	__int64 PrevCount;
public:
	void Reset();
protected:

private:
	// constrcuter destructer
	GameEngineTime();
	~GameEngineTime();

	// delete Function
	GameEngineTime(const GameEngineTime& _Other) = delete;
	GameEngineTime(GameEngineTime&& _Other) noexcept = delete;
	GameEngineTime& operator=(const GameEngineTime& _Other) = delete;
	GameEngineTime& operator=(GameEngineTime&& _Other) noexcept = delete;
	
};

