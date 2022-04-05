#include "Map1F.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>


Map1F::Map1F() 
{
}

Map1F::~Map1F() 
{
}

//�ʵ��� ��δ� ���������� �� �ȼ� �������´� (�ȱ׷��� �ȿ�����)

void Map1F::Start()
{
	//SetPosition(GameEngineWindow::GetScale().Half()*4);
	//�Ʒ����� ���� ���������� �� ������ ���´�
	//CreateRendererToScale("HPBAR.bmp", float4(100.0f, 20.0f), RenderPivot::CENTER, {0, -100});
	GameEngineRenderer* Renderer;
	float4 ImagePos = {};
	Renderer = CreateRenderer("EastPalace1F_1_1F.bmp");
	//��������  0,0 �� �������� �߾ӿ� ��ġ�ȴ� ( �״�� ���� �̹��� ©�� )
	//�̹���, Rect�� 0, 0 �� �������� ������ �Ʒ��� ��ġ�ȴ�
	ImagePos.x = (Renderer->GetImage()->GetScale().Half().x);
	ImagePos.y = (Renderer->GetImage()->GetScale().Half().y);
	Renderer->SetPivot(ImagePos);

	DoorAnimationCreate();
	PlaceDoor();
}
 
void Map1F::Update()
{

}
void Map1F::Render()
{
	DebugRectRender();

}

void Map1F::PlaceDoor()
{
	//3008+64, 3200+48 
	//128,96
	UpDoor1->SetPivot(float4{3072, 3248});
	UpDoor2->SetPivot({ 0, -11 });
	UpDoor3->SetPivot({ 0, -11 });
	BotDoor1->SetPivot({ 0, -11 });
	RightDoor1->SetPivot({ 0, -11 });
}

void Map1F::DoorAnimationCreate()
{

	UpDoor1 = CreateRenderer();
	UpDoor1->CreateAnimation("Top_Door_Idle_Animation.bmp", "Idle_Top", 0, 2, 0.035f, false);
	UpDoor1->CreateAnimation("Top_Door_Animation.bmp", "Top", 0, 2, 0.035f, false);
	UpDoor1->ChangeAnimation("Top");

	UpDoor2 = CreateRenderer();
	UpDoor2->CreateAnimation("Top_Door_Idle_Animation.bmp", "Idle_Top", 0, 2, 0.035f, false);
	UpDoor2->CreateAnimation("Top_Door_Animation.bmp", "Top", 0, 2, 0.035f, false);
	UpDoor2->ChangeAnimation("Idle_Top");

	UpDoor3 = CreateRenderer();
	UpDoor3->CreateAnimation("Top_Door_Idle_Animation.bmp", "Idle_Top", 0, 2, 0.035f, false);
	UpDoor3->CreateAnimation("Top_Door_Animation.bmp", "Top", 0, 2, 0.035f, false);
	UpDoor3->ChangeAnimation("Idle_Top");

	BotDoor1 = CreateRenderer();
	BotDoor1->CreateAnimation("Bot_Door_Idle_Animation.bmp", "Idle_Bot", 0, 2, 0.035f, false);
	BotDoor1->CreateAnimation("Bot_Door_Animation.bmp", "Bot", 0, 2, 0.035f, false);
	BotDoor1->ChangeAnimation("Idle_Bot");

	RightDoor1 = CreateRenderer();
	RightDoor1->CreateAnimation("Right_Door_Idle_Animation.bmp", "Idle_Right", 0, 2, 0.035f, false);
	RightDoor1->CreateAnimation("Right_Door_Animation.bmp", "Down", 0, 2, 0.035f, false);
	RightDoor1->ChangeAnimation("Idle_Right");


}