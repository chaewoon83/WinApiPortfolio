#include "Boomerang.h"
#include <GameEngineBase/GameEngineTime.h>


Boomerang::Boomerang() 
{
}

Boomerang::~Boomerang() 
{
}

void Boomerang::Start()
{
	CreateRenderer("Boomerang.bmp");
	Death(2.0f);
}

void Boomerang::Update()
{
	Time -= GameEngineTime::GetDeltaTime();

	SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * 200.0f);
}
