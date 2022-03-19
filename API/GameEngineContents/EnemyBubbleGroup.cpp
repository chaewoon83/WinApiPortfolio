#include "EnemyBubbleGroup.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>


EnemyBubbleGroup::EnemyBubbleGroup() 
{
}

EnemyBubbleGroup::~EnemyBubbleGroup() 
{
}

void EnemyBubbleGroup::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 500,500 });
}
 
void EnemyBubbleGroup::Update()
{

}
void EnemyBubbleGroup::Render()
{
	DebugRectRender();

}
