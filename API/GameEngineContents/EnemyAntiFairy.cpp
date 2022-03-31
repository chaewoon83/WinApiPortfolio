#include "EnemyAntiFairy.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>


EnemyAntiFairy::EnemyAntiFairy() 
{
}

EnemyAntiFairy::~EnemyAntiFairy() 
{
}

void EnemyAntiFairy::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 500,500 });
}
 
void EnemyAntiFairy::Update()
{

}
void EnemyAntiFairy::Render()
{
	DebugRectRender();

}
