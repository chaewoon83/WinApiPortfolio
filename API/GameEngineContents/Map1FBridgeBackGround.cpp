#include "Map1FBridgeBackGround.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>

Map1FBridgeBackGround* Map1FBridgeBackGround::Inst_ = nullptr;

Map1FBridgeBackGround::Map1FBridgeBackGround() 
{
}

Map1FBridgeBackGround::~Map1FBridgeBackGround() 
{
}

void Map1FBridgeBackGround::Start()
{

	float4 ImagePos = {};
	Renderer_1_ = CreateRenderer("EastPalace1F_1_1F_BridgeBackground.bmp");
	//��������  0,0 �� �������� �߾ӿ� ��ġ�ȴ� ( �״�� ���� �̹��� ©�� )
	//�̹���, Rect�� 0, 0 �� �������� ������ �Ʒ��� ��ġ�ȴ�
	ImagePos.x = (Renderer_1_->GetImage()->GetScale().Half().x);
	ImagePos.y = (Renderer_1_->GetImage()->GetScale().Half().y + + 4128.0f);
	Renderer_1_->SetPivot(ImagePos);
	Inst_ = this;
}
 
void Map1FBridgeBackGround::Update()
{

}
void Map1FBridgeBackGround::Render()
{
	DebugRectRender();

}
