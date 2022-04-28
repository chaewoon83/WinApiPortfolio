#include "Map1FRoof.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>


Map1FRoof::Map1FRoof()
{
}

Map1FRoof::~Map1FRoof()
{
}

//�ʵ��� ��δ� ���������� �� �ȼ� �������´� (�ȱ׷��� �ȿ�����)

void Map1FRoof::Start()
{
	//SetPosition(GameEngineWindow::GetScale().Half()*4);
	//�Ʒ����� ���� ���������� �� ������ ���´�
	//CreateRendererToScale("HPBAR.bmp", float4(100.0f, 20.0f), RenderPivot::CENTER, {0, -100});
	GameEngineRenderer* Renderer;
	GameEngineRenderer* Renderer2;
	float4 ImagePos = {};
	Renderer = CreateRenderer("EastPalace1F_1_1F_PassageRoof.bmp");
	//��������  0,0 �� �������� �߾ӿ� ��ġ�ȴ� ( �״�� ���� �̹��� ©�� )
	//�̹���, Rect�� 0, 0 �� �������� ������ �Ʒ��� ��ġ�ȴ�
	ImagePos.x = (Renderer->GetImage()->GetScale().Half().x);
	ImagePos.y = (Renderer->GetImage()->GetScale().Half().y + 4128.0f );
	Renderer->SetPivot(ImagePos);

	ImagePos = {};
	Renderer2 = CreateRenderer("EastPalace1F_2_1F_PassageRoof.bmp");
	//��������  0,0 �� �������� �߾ӿ� ��ġ�ȴ� ( �״�� ���� �̹��� ©�� )
	//�̹���, Rect�� 0, 0 �� �������� ������ �Ʒ��� ��ġ�ȴ�
	ImagePos.x = (Renderer2->GetImage()->GetScale().Half().x);
	ImagePos.y = (Renderer2->GetImage()->GetScale().Half().y);
	Renderer2->SetPivot(ImagePos);
}
 
void Map1FRoof::Update()
{

}
void Map1FRoof::Render()
{
	//DebugRectRender();

}
