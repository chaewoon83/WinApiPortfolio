#include "Zelda.h"
#include "PlayLevel.h"
#include "EndLevel.h"
#include "TitleLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>

Zelda::Zelda()
{
}

Zelda::~Zelda()
{
}

void Zelda::GameInit()
{
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100 ,100 }, { 1024, 896 });
	//모든 리소스를 로드 할 예정
	GameEngineImageManager::GetInst()->Load("C:\\Users\\balex\\source\\repos\\WinApiPortfolio\\API\\Resources\\Image\\Idle.bmp", "Idle.bmp");
	CreateLevel<TitleLevel>("Title");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<EndLevel>("End");
	ChangeLevel("Play"); 
}
void Zelda::GameLoop()
{

}
void Zelda::GameEnd()
{

}