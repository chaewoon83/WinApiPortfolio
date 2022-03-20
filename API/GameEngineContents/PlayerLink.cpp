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
	SetScale({ 200, 200 });
}
 
void PlayerLink::Update()
{

}
void PlayerLink::Render()
{
	DebugRectRender();

}
