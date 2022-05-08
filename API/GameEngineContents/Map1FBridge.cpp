#include "Map1FBridge.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>

Map1FBridge* Map1FBridge::Inst_ = nullptr;

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
	float4 ImagePos = {};
	Renderer_1_ = CreateRenderer("EastPalace1F_2_1F_Bridge.bmp");
	//��������  0,0 �� �������� �߾ӿ� ��ġ�ȴ� ( �״�� ���� �̹��� ©�� )
	//�̹���, Rect�� 0, 0 �� �������� ������ �Ʒ��� ��ġ�ȴ�
	ImagePos.x = (Renderer_1_->GetImage()->GetScale().Half().x);
	ImagePos.y = (Renderer_1_->GetImage()->GetScale().Half().y);
	Renderer_1_->SetPivot(ImagePos);

	ImagePos = {};
	Renderer_2_ = CreateRenderer("EastPalace1F_1_1F_Bridge.bmp");
	//��������  0,0 �� �������� �߾ӿ� ��ġ�ȴ� ( �״�� ���� �̹��� ©�� )
	//�̹���, Rect�� 0, 0 �� �������� ������ �Ʒ��� ��ġ�ȴ�
	ImagePos.x = (Renderer_2_->GetImage()->GetScale().Half().x);
	ImagePos.y = (Renderer_2_->GetImage()->GetScale().Half().y + 4129.0f);
	Renderer_2_->SetPivot(ImagePos);
	Inst_ = this;
}
 
void Map1FBridge::Update()
{
}
void Map1FBridge::Render()
{
	//DebugRectRender();

}
