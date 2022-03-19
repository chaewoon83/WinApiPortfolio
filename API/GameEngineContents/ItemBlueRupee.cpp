#include "ItemBlueRupee.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>


ItemBlueRupee::ItemBlueRupee() 
{
}

ItemBlueRupee::~ItemBlueRupee() 
{
}

void ItemBlueRupee::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 500,500 });
}
 
void ItemBlueRupee::Update()
{

}
void ItemBlueRupee::Render()
{
	DebugRectRender();

}
