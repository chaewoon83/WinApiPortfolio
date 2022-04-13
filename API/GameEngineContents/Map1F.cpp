#include "Map1F.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>

GameEngineRenderer* Map1F::TopDoor1 = nullptr;
GameEngineRenderer* Map1F::TopDoor2 = nullptr;
GameEngineRenderer* Map1F::TopDoor3 = nullptr;
GameEngineRenderer* Map1F::BotDoor1 = nullptr;
GameEngineRenderer* Map1F::RightDoor1 = nullptr;

Map1F::Map1F() 
{
}

Map1F::~Map1F() 
{
}

//맵들의 통로는 오른쪽으로 한 픽셀 지워놓는다 (안그러면 안움직임)

void Map1F::Start()
{
	//SetPosition(GameEngineWindow::GetScale().Half()*4);
	//아래부터 넣은 렌더러들이 맨 위부터 나온다
	//CreateRendererToScale("HPBAR.bmp", float4(100.0f, 20.0f), RenderPivot::CENTER, {0, -100});
	GameEngineRenderer* Renderer;
	float4 ImagePos = {};
	Renderer = CreateRenderer("EastPalace1F_1_1F.bmp");
	//렌더러는  0,0 을 기준으로 중앙에 배치된다 ( 그대로 쓰면 이미지 짤림 )
	//이미지, Rect는 0, 0 을 기준으로 오른쪽 아래에 배치된다
	ImagePos.x = (Renderer->GetImage()->GetScale().Half().x);
	ImagePos.y = (Renderer->GetImage()->GetScale().Half().y);
	Renderer->SetPivot(ImagePos);

	DoorAnimationCreate();
	PlaceDoor();

	CreateCollision("Switch", { 48, 40 }, { 3040, 3451 });
}
 
void Map1F::Update()
{

}
void Map1F::Render()
{
	//DebugRectRender();

}

void Map1F::PlaceDoor()
{
	//3008+64, 3200+48 
	//128,96
	TopDoor1->SetPivot(float4{3072, 3216});
	//CreateCollision("Door", { 128,96 }, { 3072, 3248 });
	TopDoor2->SetPivot({ 0, -11 });
	//CreateCollision("Door", { 128,96 }, { 3072, 2848 });
	TopDoor3->SetPivot({ 0, -11 });
	BotDoor1->SetPivot({ 0, -11 });
	RightDoor1->SetPivot({ 0, -11 });
}

void Map1F::DoorAnimationCreate()
{

	TopDoor1 = CreateRenderer();
	TopDoor1->CreateAnimation("Top_Door_Idle_Animation.bmp", "Idle_Top", 0, 2, 1.0f, false);
	TopDoor1->CreateAnimation("Top_Door_Animation.bmp", "Top", 0, 2, 0.07f, false);
	TopDoor1->ChangeAnimation("Idle_Top");

	TopDoor2 = CreateRenderer();
	TopDoor2->CreateAnimation("Top_Door_Idle_Animation.bmp", "Idle_Top", 0, 2, 0.035f, false);
	TopDoor2->CreateAnimation("Top_Door_Animation.bmp", "Top", 0, 2, 0.035f, false);
	TopDoor2->ChangeAnimation("Idle_Top");

	TopDoor3 = CreateRenderer();
	TopDoor3->CreateAnimation("Top_Door_Idle_Animation.bmp", "Idle_Top", 0, 2, 0.035f, false);
	TopDoor3->CreateAnimation("Top_Door_Animation.bmp", "Top", 0, 2, 0.035f, false);
	TopDoor3->ChangeAnimation("Idle_Top");

	BotDoor1 = CreateRenderer();
	BotDoor1->CreateAnimation("Bot_Door_Idle_Animation.bmp", "Idle_Bot", 0, 2, 0.035f, false);
	BotDoor1->CreateAnimation("Bot_Door_Animation.bmp", "Bot", 0, 2, 0.035f, false);
	BotDoor1->ChangeAnimation("Idle_Bot");

	RightDoor1 = CreateRenderer();
	RightDoor1->CreateAnimation("Right_Door_Idle_Animation.bmp", "Idle_Right", 0, 2, 0.035f, false);
	RightDoor1->CreateAnimation("Right_Door_Animation.bmp", "Down", 0, 2, 0.035f, false);
	RightDoor1->ChangeAnimation("Idle_Right");


}