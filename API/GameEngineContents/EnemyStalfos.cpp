#include "EnemyStalfos.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>


EnemyStalfos::EnemyStalfos() 
{
}

EnemyStalfos::~EnemyStalfos() 
{
}

void EnemyStalfos::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 500,500 });
}
 
void EnemyStalfos::Update()
{

}
void EnemyStalfos::Render()
{
	DebugRectRender();

}
