#include "BossArmomsKnight.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>


BossArmomsKnight::BossArmomsKnight() 
{
}

BossArmomsKnight::~BossArmomsKnight() 
{
}

void BossArmomsKnight::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 500,500 });
}
 
void BossArmomsKnight::Update()
{

}
void BossArmomsKnight::Render()
{
	DebugRectRender();

}
