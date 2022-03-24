#include "UIMagicMeter.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>


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
		CreateRenderer("UIMagicMeter.bmp", RenderPivot::CENTER, { 0, -i*8 });
	}
}
 
void UIMagicMeter::Update()
{

}
void UIMagicMeter::Render()
{
	//DebugRectRender();

}
