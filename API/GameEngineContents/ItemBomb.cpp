#include "ItemBomb.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>


ItemBomb::ItemBomb() 
{
}

ItemBomb::~ItemBomb() 
{
}

void ItemBomb::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 500,500 });
}
 
void ItemBomb::Update()
{

}
void ItemBomb::Render()
{
	DebugRectRender();

}
