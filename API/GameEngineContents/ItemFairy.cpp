#include "ItemFairy.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>


ItemFairy::ItemFairy() 
{
}

ItemFairy::~ItemFairy() 
{
}

void ItemFairy::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 500,500 });
}
 
void ItemFairy::Update()
{

}
void ItemFairy::Render()
{
	DebugRectRender();

}
