#include "ItemGreenRupee.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>


ItemGreenRupee::ItemGreenRupee() 
{
}

ItemGreenRupee::~ItemGreenRupee() 
{
}

void ItemGreenRupee::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 500,500 });
}
 
void ItemGreenRupee::Update()
{

}
void ItemGreenRupee::Render()
{

}
