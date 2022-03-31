#include "ItemRecoveryHeart.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>


ItemRecoveryHeart::ItemRecoveryHeart() 
{
}

ItemRecoveryHeart::~ItemRecoveryHeart() 
{
}

void ItemRecoveryHeart::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 500,500 });
}
 
void ItemRecoveryHeart::Update()
{

}
void ItemRecoveryHeart::Render()
{
	DebugRectRender();

}
