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
	TotalImageGetFromFolder();

	//이미지 자르기
	TotalImageCut();

	//GameEngineImage* Image = GameEngineImageManager::GetInst()->Find("Link_Walk_Down.bmp");
	//Image->CutCount(8, 1);w

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

void Zelda::TotalImageGetFromFolder()
{
	GetImageFromFolder("Link");
	GetImageFromFolder("Title");
	GetImageFromFolder("UI");
	GetImageFromFolder("Map");
	GetImageFromFolder("Enemy");
	GetImageFromFolder("Item");
}

void Zelda::TotalImageCut()
{
	//Link
	ImageCutter("Link_Idle_Right.bmp", 2, 1);
	ImageCutter("Link_Idle_Left.bmp", 2, 1);
	ImageCutter("Link_Idle_Up.bmp", 2, 1);
	ImageCutter("Link_Idle_Down.bmp", 2, 1);

	ImageCutter("Link_Walk_Right.bmp", 6, 1);
	ImageCutter("Link_Walk_Left.bmp", 6, 1);
	ImageCutter("Link_Walk_Up.bmp", 8, 1);
	ImageCutter("Link_Walk_Down.bmp", 8, 1);

	ImageCutter("Link_Wield_Right.bmp", 5, 1);
	ImageCutter("Link_Wield_Left.bmp", 5, 1);
	ImageCutter("Link_Wield_Up.bmp", 5, 1);
	ImageCutter("Link_Wield_Down.bmp", 6, 1);

	ImageCutter("Link_Damaged_Right.bmp", 2, 1);
	ImageCutter("Link_Damaged_Left.bmp", 2, 1);
	ImageCutter("Link_Damaged_Up.bmp", 2, 1);
	ImageCutter("Link_Damaged_Down.bmp", 2, 1);

	ImageCutter("Link_Carry_Start_Right.bmp", 3, 1);
	ImageCutter("Link_Carry_Start_Left.bmp", 3, 1);
	ImageCutter("Link_Carry_Start_Up.bmp", 3, 1);
	ImageCutter("Link_Carry_Start_Down.bmp", 3, 1);
	ImageCutter("Link_Carry_Idle_Right.bmp", 2, 1);
	ImageCutter("Link_Carry_Idle_Left.bmp", 2, 1);
	ImageCutter("Link_Carry_Idle_Up.bmp", 2, 1);
	ImageCutter("Link_Carry_Idle_Down.bmp", 2, 1);
	ImageCutter("Link_Carry_Move_Right.bmp", 2, 1);
	ImageCutter("Link_Carry_Move_Left.bmp", 2, 1);
	ImageCutter("Link_Carry_Move_Up.bmp", 5, 1);
	ImageCutter("Link_Carry_Move_Down.bmp", 5, 1);

	ImageCutter("Link_Charge_Attack_Right.bmp", 12, 1);
	ImageCutter("Link_Charge_Attack_Left.bmp", 12, 1);
	ImageCutter("Link_Charge_Attack_Up.bmp", 12, 1);
	ImageCutter("Link_Charge_Attack_Down.bmp", 12, 1);

	ImageCutter("Link_Charge_Right.bmp", 1, 1);
	ImageCutter("Link_Charge_Left.bmp", 1, 1);
	ImageCutter("Link_Charge_Up.bmp", 1, 1);
	ImageCutter("Link_Charge_Down.bmp", 1, 1);

	ImageCutter("Link_Charge_Move_Right.bmp", 2, 1);
	ImageCutter("Link_Charge_Move_Left.bmp", 2, 1);
	ImageCutter("Link_Charge_Move_Up.bmp", 3, 1);
	ImageCutter("Link_Charge_Move_Down.bmp", 3, 1);

	ImageCutter("Link_Charge_End_Effect.bmp", 2, 1);


	//Map Object
	ImageCutter("Right_Door_Open_Animation.bmp", 3, 1);
	ImageCutter("Right_Door_Close_Animation.bmp", 3, 1);
	ImageCutter("Right_Door_Idle_Animation.bmp", 3, 1);
	ImageCutter("Left_Door_Open_Animation.bmp", 3, 1);
	ImageCutter("Left_Door_Close_Animation.bmp", 3, 1);
	ImageCutter("Left_Door_Idle_Animation.bmp", 3, 1);
	ImageCutter("Top_Door_Open_Animation.bmp", 1, 3);
	ImageCutter("Top_Door_Close_Animation.bmp", 1, 3);
	ImageCutter("Top_Door_Idle_Animation.bmp", 1, 3);
	ImageCutter("Bot_Door_Open_Animation.bmp", 1, 3);
	ImageCutter("Bot_Door_Close_Animation.bmp", 1, 3);
	ImageCutter("Bot_Door_Idle_Animation.bmp", 1, 3);
	ImageCutter("Pot_Destroyed.bmp", 8, 1);
	ImageCutter("Pot.bmp", 1, 1);

	//Title
	ImageCutter("trianglebmp.bmp", 5, 34);
	ImageCutter("TitleTwinkle.bmp", 11, 1);

	//Enemy
	ImageCutter("EnemyDeathEffect.bmp", 7, 1);

	ImageCutter("EnemySummonEffect.bmp", 2, 1);

	ImageCutter("EnemyPopo.bmp", 3, 1);

	ImageCutter("EnemyBall.bmp", 2, 1); 
	ImageCutter("EnemyGargantuanBall.bmp", 2, 1); 

	ImageCutter("EnemyAntiFairy.bmp", 5, 1);


	ImageCutter("EnemyBlueStalfosRightHead.bmp", 1, 1);
	ImageCutter("EnemyBlueStalfosLeftHead.bmp", 1, 1);
	ImageCutter("EnemyBlueStalfosUpHead.bmp", 1, 1);
	ImageCutter("EnemyBlueStalfosDownHead.bmp", 1, 1);
	ImageCutter("EnemyBlueStalfosRightBody.bmp", 2, 1);
	ImageCutter("EnemyBlueStalfosLeftBody.bmp", 2, 1);
	ImageCutter("EnemyBlueStalfosUpBody.bmp", 2, 1);
	ImageCutter("EnemyBlueStalfosDownBody.bmp", 2, 1);
	ImageCutter("EnemyBlueStalfosRightBodyIdle.bmp", 1, 1);
	ImageCutter("EnemyBlueStalfosLeftBodyIdle.bmp", 1, 1);
	ImageCutter("EnemyBlueStalfosUpBodyIdle.bmp", 1, 1);
	ImageCutter("EnemyBlueStalfosDownBodyIdle.bmp", 1, 1);
	ImageCutter("EnemyBlueStalfosJumpRightBody.bmp", 1, 1);
	ImageCutter("EnemyBlueStalfosJumpLeftBody.bmp", 1, 1);
	ImageCutter("EnemyBlueStalfosJumpUpBody.bmp", 1, 1);
	ImageCutter("EnemyBlueStalfosJumpDownBody.bmp", 1, 1);

	//Light
	ImageCutter("MapLightScreen0Right.bmp", 1, 1);
	ImageCutter("MapLightScreen0Left.bmp", 1, 1);
	ImageCutter("MapLightScreen0Up.bmp", 1, 1);
	ImageCutter("MapLightScreen0Down.bmp", 1, 1);
	ImageCutter("MapLightScreen1Right.bmp", 1, 1);
	ImageCutter("MapLightScreen1Left.bmp", 1, 1);
	ImageCutter("MapLightScreen1Up.bmp", 1, 1);
	ImageCutter("MapLightScreen1Down.bmp", 1, 1);

	//Item
	ImageCutter("ItemGreenRupee.bmp", 3, 1);
	ImageCutter("ItemBlueRupee.bmp", 3, 1);
	ImageCutter("ItemRedRupee.bmp", 3, 1);

	//UI
	ImageCutter("UIFullHeart.bmp", 1, 1);
	ImageCutter("UIHalfHeart.bmp", 1, 1);
	ImageCutter("UIEmptyHeart.bmp", 1, 1);
	ImageCutter("UI0.bmp", 1, 1);
	ImageCutter("UI1.bmp", 1, 1);
	ImageCutter("UI2.bmp", 1, 1);
	ImageCutter("UI3.bmp", 1, 1);
	ImageCutter("UI4.bmp", 1, 1);
	ImageCutter("UI5.bmp", 1, 1);
	ImageCutter("UI6.bmp", 1, 1);
	ImageCutter("UI7.bmp", 1, 1);
	ImageCutter("UI8.bmp", 1, 1);
	ImageCutter("UI9.bmp", 1, 1);
}