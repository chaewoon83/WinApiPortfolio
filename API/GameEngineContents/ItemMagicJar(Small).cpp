#include "ItemMagicJar_Small_.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>


ItemMagicJar_Small_::ItemMagicJar_Small_() 
{
}

ItemMagicJar_Small_::~ItemMagicJar_Small_() 
{
}

void ItemMagicJar_Small_::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 500,500 });
}
 
void ItemMagicJar_Small_::Update()
{

}
void ItemMagicJar_Small_::Render()
{
	DebugRectRender();

}
