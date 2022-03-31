#include "EnemyGreenEyegore.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>


EnemyGreenEyegore::EnemyGreenEyegore() 
{
}

EnemyGreenEyegore::~EnemyGreenEyegore() 
{
}

void EnemyGreenEyegore::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 500,500 });
}
 
void EnemyGreenEyegore::Update()
{

}
void EnemyGreenEyegore::Render()
{
	DebugRectRender();

}
