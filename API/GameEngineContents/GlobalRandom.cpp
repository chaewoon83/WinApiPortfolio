#include "GlobalRandom.h"

GlobalRandom::GlobalRandom() 
{
}

GlobalRandom::~GlobalRandom() 
{
}
GameEngineRandom GlobalRandom::Random = GameEngineRandom();

int GlobalRandom::RandomIntGenerate(int _Min, int _Max)
{
	return Random.RandomInt(_Min, _Max);
}
