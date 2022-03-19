#include "PlayerLink.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>


PlayerLink::PlayerLink() 
{
}

PlayerLink::~PlayerLink() 
{
}

void PlayerLink::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 500,500 });
}
 
void PlayerLink::Update()
{

}
void PlayerLink::Render()
{
	DebugRectRender();

}
