#include "EnemyBlueStalfos.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>


EnemyBlueStalfos::EnemyBlueStalfos() 
{
}

EnemyBlueStalfos::~EnemyBlueStalfos() 
{
}

void EnemyBlueStalfos::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	//SetScale({ 500,500 });
}
 
void EnemyBlueStalfos::Update()
{

}
void EnemyBlueStalfos::Render()
{
	//DebugRectRender();

}
