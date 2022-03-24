#include "Zelda.h"
#include "PlayLevel.h"
#include "EndLevel.h"
#include "TitleLevel.h"
#include "MapLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
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
	GameEngineDirectory ResourcesDir;
	ResourcesDir.MoveParent("API");
	ResourcesDir.Move("Resources");
	ResourcesDir.Move("Image");

	std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile(".bmp");
	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}

	CreateLevel<TitleLevel>("TitleLevel");
	CreateLevel<PlayLevel>("PlayLevel");
	CreateLevel<MapLevel>("MapLevel");
	CreateLevel<EndLevel>("EndLevel");
	ChangeLevel("PlayLevel"); 
}
void Zelda::GameLoop()
{

}
void Zelda::GameEnd()
{

}