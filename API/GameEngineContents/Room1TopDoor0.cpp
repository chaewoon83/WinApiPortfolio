#include "Room1TopDoor0.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "PlayerLink.h"

GameEngineRenderer* Room1TopDoor0::Room1TopDoor0_ = nullptr;
GameEngineCollision* Room1TopDoor0::Room1Door0Col_ = nullptr;
Room1TopDoor0::Room1TopDoor0() 
	:DoorPos_(float4{ 3072, 3216})
{
}

Room1TopDoor0::~Room1TopDoor0() 
{
}

void Room1TopDoor0::Start()
{
	SetPosition(DoorPos_);
	Room1TopDoor0_ = CreateRenderer();
	Room1TopDoor0_->CreateAnimation("Top_Door_Idle_Animation.bmp", "Idle_Top", 0, 2, 1.0f, false);
	Room1TopDoor0_->CreateAnimation("Top_Door_Open_Animation.bmp", "Open_Top", 0, 2, 0.07f, false);
	Room1TopDoor0_->CreateAnimation("Top_Door_Close_Animation.bmp", "Close_Top", 0, 2, 0.07f, false);
	Room1TopDoor0_->ChangeAnimation("Idle_Top");
	Room1Door0Col_ = CreateCollision("Block", { 128,96 });
}
 
void Room1TopDoor0::Update()
{
	//if (CameraState::Room1 == PlayerLink::GetPlayerCurRoomState())
	//{
	//	if (true == Room1Door0Col_->IsDeath())
	//	{
	//		Room1Door0Col_ = CreateCollision("Block", { 128,96 });
	//	}
	//}
}
void Room1TopDoor0::Render()
{
	//DebugRectRender();

}
