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

//�� ���� 128, ��ĭ�� ���� 8
//16������ �װ� �����Ѵ�

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
