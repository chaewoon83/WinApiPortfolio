#include "EnemyBall.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>


EnemyBall::EnemyBall() 
{
}

EnemyBall::~EnemyBall() 
{
}

void EnemyBall::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 500,500 });
}
 
void EnemyBall::Update()
{

}
void EnemyBall::Render()
{
	DebugRectRender();

}
