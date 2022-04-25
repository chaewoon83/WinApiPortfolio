#include "Map1F.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineCollision.h>
#include "PlayerLink.h"
#include "Room1TopDoor0.h"

GameEngineRenderer* Map1F::Room1TopDoor0_ = nullptr;
GameEngineRenderer* Map1F::Room2TopDoor0 = nullptr;
GameEngineRenderer* Map1F::Room2BotDoor0 = nullptr;

GameEngineCollision* Map1F::Room1Door0Col_ = nullptr;
GameEngineCollision* Map1F::SwitchCol_ = nullptr;

Map1F::Map1F()
	:IsRoom1TopDoor0On_(true)
	,CurRoomState_(CameraState::Room1)
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


	SwitchCol_ = CreateCollision("Switch", { 48, 40 }, { 3040, 3451 });
}
 
void Map1F::Update()
{

	{
		std::vector<GameEngineCollision*> ColList;

		if (true == SwitchCol_->CollisionResult("PlayerHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			Room1TopDoor0::Room1TopDoor0_->ChangeAnimation("Open_Top");
			Room1TopDoor0::Room1Door0Col_->Death();
		}
	}


	if (CameraState::Room1 == PlayerLink::GetPlayerCurRoomState())
	{
		if (CameraState::Room1 != CurRoomState_)
		{
			CurRoomState_ = PlayerLink::GetPlayerCurRoomState();
			Room1TopDoor0::Room1Door0Col_ = CreateCollision("Block", { 128,70 });
		}
	}
}
void Map1F::Render()
{
	//DebugRectRender();

}

void Map1F::PlaceDoor()
{

}

void Map1F::DoorAnimationCreate()
{
	//Room1TopDoor0_ = CreateRenderer();
	//Room1TopDoor0_->CreateAnimation("Top_Door_Idle_Animation.bmp", "Idle_Top", 0, 2, 1.0f, false);
	//Room1TopDoor0_->CreateAnimation("Top_Door_Open_Animation.bmp", "Open_Top", 0, 2, 0.07f, false);
	//Room1TopDoor0_->CreateAnimation("Top_Door_Close_Animation.bmp", "Close_Top", 0, 2, 0.07f, false);
	//Room1TopDoor0_->ChangeAnimation("Idle_Top");
	//Room1Door0Col_ = CreateCollision("Block", { 128,96 }, float4{ 3072, 3216 });

	Room2TopDoor0 = CreateRenderer();
	Room2TopDoor0->CreateAnimation("Top_Door_Idle_Animation.bmp", "Idle_Top", 0, 2, 0.035f, false);
	Room2TopDoor0->CreateAnimation("Top_Door_Open_Animation.bmp", "Open_Top", 0, 2, 0.035f, false);
	Room2TopDoor0->CreateAnimation("Top_Door_Close_Animation.bmp", "Close_Top", 0, 2, 0.035f, false);
	Room2TopDoor0->ChangeAnimation("Open_Top");

	Room2BotDoor0 = CreateRenderer();
	Room2BotDoor0->CreateAnimation("Bot_Door_Idle_Animation.bmp", "Idle_Bot", 0, 2, 0.035f, false);
	Room2BotDoor0->CreateAnimation("Bot_Door_Open_Animation.bmp", "Open_Bot", 0, 2, 0.035f, false);
	Room2BotDoor0->CreateAnimation("Bot_Door_Close_Animation.bmp", "Close_Bot", 0, 2, 0.035f, false);
	Room2BotDoor0->ChangeAnimation("Open_Bot");


}