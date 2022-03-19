#include "ItemMagicJar_Large_.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>


ItemMagicJar_Large_::ItemMagicJar_Large_() 
{
}

ItemMagicJar_Large_::~ItemMagicJar_Large_() 
{
}

void ItemMagicJar_Large_::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 500,500 });
}
 
void ItemMagicJar_Large_::Update()
{

}
void ItemMagicJar_Large_::Render()
{
	DebugRectRender();

}
