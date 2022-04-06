#include "UIMagicMeter.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

UIMagicMeter::UIMagicMeter() 
{
}

UIMagicMeter::~UIMagicMeter() 
{
}

//총 높이 128, 한칸의 높이 8
//16개까지 쌓고 시작한다

void UIMagicMeter::Start()
{
	SetPosition({ 112, 216});
	SetScale({ 32, 8 });
	for (float i = 0; i < 16; i++)
	{
		AllMagicMeters.push_back(CreateRenderer("UIMagicMeter.bmp", static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot::CENTER, { 0, -i * 8.0f }));
	}

	std::list<GameEngineRenderer*>::iterator Iter = AllMagicMeters.begin();
	for (; Iter != AllMagicMeters.end(); ++Iter)
	{
		(*Iter)->CameraEffectOff();
	}
}
 
void UIMagicMeter::Update()
{

}
void UIMagicMeter::Render()
{
	//DebugRectRender();

}
