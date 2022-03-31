#include "Map.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>


Map::Map() 
{
}

Map::~Map() 
{
}

void Map::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());
	SetScale({ 1000, 1000 });
}
 
void Map::Update()
{

}
void Map::Render()
{
	DebugRectRender();

}
