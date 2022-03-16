#include "Zelda.h"
#include "PlayLevel.h"
#include "EndLevel.h"
#include "TitleLevel.h"
#include <GameEngineBase/GameEngineWindow.h>

Zelda::Zelda()
{
}

Zelda::~Zelda()
{
}

void Zelda::GameInit()
{
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100 ,100 }, { 1024, 896 });
	CreateLevel<TitleLevel>("Title");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<EndLevel>("End");
	ChangeLevel("Title");
}
void Zelda::GameLoop()
{

}
void Zelda::GameEnd()
{

}