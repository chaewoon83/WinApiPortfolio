#include "EnemyPopo.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>


EnemyPopo::EnemyPopo() 
{
}

EnemyPopo::~EnemyPopo() 
{
}

void EnemyPopo::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 500,500 });
}
 
void EnemyPopo::Update()
{

}
void EnemyPopo::Render()
{
	DebugRectRender();

}
