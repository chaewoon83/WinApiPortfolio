#include "EnemyDeathEffect.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>


EnemyDeathEffect::EnemyDeathEffect() 
{
}

EnemyDeathEffect::~EnemyDeathEffect() 
{
}

void EnemyDeathEffect::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 500,500 });
}
 
void EnemyDeathEffect::Update()
{

}
void EnemyDeathEffect::Render()
{
	DebugRectRender();

}
