#include "TitleTimeObject.h"
#include <GameEngineBase/GameEngineTime.h>

float TitleTimeObject::TimeLine_ = 0.0f;

TitleTimeObject::TitleTimeObject() 
{
}

TitleTimeObject::~TitleTimeObject() 
{
}

void TitleTimeObject::Start()
{
}

void TitleTimeObject::Update()
{
	TimeLine_ += GameEngineTime::GetDeltaTime();
}

void TitleTimeObject::Render()
{

}
