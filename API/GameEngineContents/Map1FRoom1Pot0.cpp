#include "Map1FRoom1Pot0.h"
#include <windows.h>
#include <GameEngineBase/GameEngineWindow.h>

//2536, 3428
//48, 48 (+1, -1)
Map1FRoom1Pot0::Map1FRoom1Pot0() 
{
}

Map1FRoom1Pot0::~Map1FRoom1Pot0() 
{
}

void Map1FRoom1Pot0::Start()
{
	CreateRenderer("Pot.bmp");
	SetPosition({ 2561.0f, 3451.0f });
	CreateCollision("Pot", { 48, 48 });
	CreateCollision("PotCarry", { 50, 50 });
}
 
void Map1FRoom1Pot0::Update()
{

}
void Map1FRoom1Pot0::Render()
{

}
