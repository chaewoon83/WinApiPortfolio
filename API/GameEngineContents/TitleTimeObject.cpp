#include "TitleTimeObject.h"
#include <GameEngineBase/GameEngineTime.h>

float TitleTimeObject::TimeLine_ = -0.7f;

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
