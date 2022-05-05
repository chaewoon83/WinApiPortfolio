#include "Room3Block0.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>

Room3Block0* Room3Block0::Room3Block_ = nullptr;

Room3Block0::Room3Block0() 
{
}

Room3Block0::~Room3Block0() 
{
}

void Room3Block0::Start()
{
	SetPosition({1536 + 32, 3488 + 32});
	CreateCollision("Block", { 64,64 });
	CreateCollision("Room3Block", { 64,64 });
	CreateRenderer("Block.bmp");
	Room3Block_ = this;
}
 
void Room3Block0::Update()
{

}
void Room3Block0::Render()
{
	DebugRectRender();

}
