#pragma once
#include <GameEngineBase/GameEngineRandom.h>

// Ό³Έν :
class GameEngineRandom;
class GlobalRandom
{
public:
	// constrcuter destructer
	GlobalRandom();
	~GlobalRandom();

	// delete Function
	//GlobalRandom(const GlobalRandom& _Other) = delete;
	//GlobalRandom(GlobalRandom&& _Other) noexcept = delete;
	//GlobalRandom& operator=(const GlobalRandom& _Other) = delete;
	//GlobalRandom& operator=(GlobalRandom&& _Other) noexcept = delete;
	static int RandomIntGenerate(int _Min, int _Max);
	static GameEngineRandom Random;
	static inline GlobalRandom GetInst()
	{
		return Inst_;
	}

protected:

private:
	static GlobalRandom Inst_;
};

