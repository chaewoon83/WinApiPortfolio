#include "Map1FBridge.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>


Map1FBridge::Map1FBridge() 
{
}

Map1FBridge::~Map1FBridge() 
{
}

//�ʵ��� ��δ� ���������� �� �ȼ� �������´� (�ȱ׷��� �ȿ�����)

void Map1FBridge::Start()
{
	//SetPosition(GameEngineWindow::GetScale().Half()*4);
	//�Ʒ����� ���� ���������� �� ������ ���´�
	//CreateRendererToScale("HPBAR.bmp", float4(100.0f, 20.0f), RenderPivot::CENTER, {0, -100});
	GameEngineRenderer* Renderer;
	GameEngineRenderer* Renderer2;
	float4 ImagePos = {};
	Renderer = CreateRenderer("EastPalace1F_2_1F_Bridge.bmp");
	//��������  0,0 �� �������� �߾ӿ� ��ġ�ȴ� ( �״�� ���� �̹��� ©�� )
	//�̹���, Rect�� 0, 0 �� �������� ������ �Ʒ��� ��ġ�ȴ�
	ImagePos.x = (Renderer->GetImage()->GetScale().Half().x);
	ImagePos.y = (Renderer->GetImage()->GetScale().Half().y);
	Renderer->SetPivot(ImagePos);

	ImagePos = {};
	Renderer2 = CreateRenderer("EastPalace1F_1_1F_Bridge.bmp");
	//��������  0,0 �� �������� �߾ӿ� ��ġ�ȴ� ( �״�� ���� �̹��� ©�� )
	//�̹���, Rect�� 0, 0 �� �������� ������ �Ʒ��� ��ġ�ȴ�
	ImagePos.x = (Renderer2->GetImage()->GetScale().Half().x);
	ImagePos.y = (Renderer2->GetImage()->GetScale().Half().y + 4129.0f);
	Renderer2->SetPivot(ImagePos);

}
 
void Map1FBridge::Update()
{
}
void Map1FBridge::Render()
{
	//DebugRectRender();

}
