#include "UIMagicMeter.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>


UIMagicMeter::UIMagicMeter() 
{
}

UIMagicMeter::~UIMagicMeter() 
{
}

void UIMagicMeter::Start()
{
	SetPosition({200, 100});
	SetScale({ 50, 100 });
}
 
void UIMagicMeter::Update()
{

}
void UIMagicMeter::Render()
{
	DebugRectRender();

}
