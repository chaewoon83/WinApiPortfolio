#include "Zelda.h"
#include "EndLevel.h"
#include "TitleLevel.h"
#include "MapLevel.h"
#include "PlayMapB1F.h"
#include "PlayMap1F.h"
#include "PlayMap2F.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineBase/GameEngineinput.h>
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
	ResourcesDir.Move("Link");

	std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile(".bmp");
	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}


	ResourcesDir.MoveParent("Image");
	ResourcesDir.Move("Title");
	AllImageFileList = ResourcesDir.GetAllFile(".bmp");

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}

	ResourcesDir.MoveParent("Image");
	ResourcesDir.Move("UI");
	AllImageFileList = ResourcesDir.GetAllFile(".bmp");

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}

	ResourcesDir.MoveParent("Image");
	ResourcesDir.Move("Map");
	AllImageFileList = ResourcesDir.GetAllFile(".bmp");

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}


	GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("Link_Walk_Down.bmp");
	Image->CutCount(8, 1);



	if (false == GameEngineInput::GetInst()->IsKey("LevelChange"))
	{
		GameEngineInput::GetInst()->CreateKey("LevelChange", '0');
	}

	CreateLevel<TitleLevel>("TitleLevel");
	CreateLevel<MapLevel>("MapLevel");
	CreateLevel<EndLevel>("EndLevel");
	CreateLevel<PlayMapB1F>("PlayMapB1F");
	CreateLevel<PlayMap1F>("PlayMap1F");
	CreateLevel<PlayMap2F>("PlayMap2F");
	ChangeLevel("PlayMap1F"); 


}
void Zelda::GameLoop()
{

}
void Zelda::GameEnd()
{

}