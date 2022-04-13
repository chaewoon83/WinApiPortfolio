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
#include <GameEngineBase/GameEngineSound.h>

Zelda::Zelda()
{
}

Zelda::~Zelda()
{
}

void Zelda::GameInit()
{
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100 ,100 }, { 1024, 896 });
	//폴더에서 이미지 가져오기
	GetImageFromFolder("Link");
	GetImageFromFolder("Title");
	GetImageFromFolder("UI");
	GetImageFromFolder("Map");


	ImageCutter("Link_Idle_Right.bmp", 2, 1);
	ImageCutter("Link_Idle_Left.bmp", 2, 1);
	ImageCutter("Link_Idle_Up.bmp", 2, 1);
	ImageCutter("Link_Idle_Down.bmp", 2, 1);
	ImageCutter("Link_Walk_Right.bmp", 6, 1);
	ImageCutter("Link_Walk_Left.bmp", 6, 1);
	ImageCutter("Link_Walk_Up.bmp", 8, 1);
	ImageCutter("Link_Walk_Down.bmp", 8, 1);
	ImageCutter("Top_Door_Animation.bmp", 1, 3);
	ImageCutter("Top_Door_Idle_Animation.bmp", 1, 3);
	ImageCutter("Bot_Door_Animation.bmp", 1, 3);
	ImageCutter("Bot_Door_Idle_Animation.bmp", 1, 3);
	ImageCutter("Left_Door_Animation.bmp", 3, 1);
	ImageCutter("Left_Door_Idle_Animation.bmp", 3, 1);
	ImageCutter("Right_Door_Animation.bmp", 3, 1);
	ImageCutter("Right_Door_Idle_Animation.bmp", 3, 1);
	ImageCutter("trianglebmp.bmp", 5, 34);
	ImageCutter("TitleTwinkle.bmp", 11, 1);
	//GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("Link_Walk_Down.bmp");
	//Image->CutCount(8, 1);

	//폴더에서 사운드 가져오기
	GetSoundFromFolder();


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
	ChangeLevel("TitleLevel"); 


}
void Zelda::GameLoop()
{

}
void Zelda::GameEnd()
{

}

void Zelda::GetImageFromFolder(const std::string& _Folder)
{
	GameEngineDirectory ResourcesDir;
	ResourcesDir.MoveParent("API");
	ResourcesDir.Move("Resources");
	ResourcesDir.Move("Image");
	ResourcesDir.Move(_Folder);
	std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile(".bmp");

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}
}

void Zelda::GetSoundFromFolder()
{
	GameEngineDirectory ResourcesDir;
	ResourcesDir.MoveParent("API");
	ResourcesDir.Move("Resources");
	ResourcesDir.Move("Sound");

	std::vector<GameEngineFile> AllImageFileList = ResourcesDir.GetAllFile(".mp3");

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineSound::LoadRes(AllImageFileList[i].GetFullPath());
	}
}

void Zelda::ImageCutter(const std::string& _Image, int _x, int _y)
{
	GameEngineImage* Image = GameEngineImageManager::GetInst()->Find(_Image);
	Image->CutCount(_x, _y);
}