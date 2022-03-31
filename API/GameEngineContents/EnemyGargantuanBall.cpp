#include "EnemyGargantuanBall.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>


EnemyGargantuanBall::EnemyGargantuanBall() 
{
}

EnemyGargantuanBall::~EnemyGargantuanBall() 
{
}

void EnemyGargantuanBall::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 500,500 });
}
 
void EnemyGargantuanBall::Update()
{

}
void EnemyGargantuanBall::Render()
{
	DebugRectRender();

}
