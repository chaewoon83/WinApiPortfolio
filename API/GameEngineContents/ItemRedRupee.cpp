#include "ItemRedRupee.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>


ItemRedRupee::ItemRedRupee() 
{
}

ItemRedRupee::~ItemRedRupee() 
{
}

void ItemRedRupee::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 500,500 });
}
 
void ItemRedRupee::Update()
{

}
void ItemRedRupee::Render()
{
	DebugRectRender();

}
