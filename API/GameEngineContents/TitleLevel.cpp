#include "TitleLevel.h"
#include "GameEngine/GameEngine.h"
#include "TitleLogo.h"
#include "TitleBackGround.h"
#include <GameEngineBase/GameEngineInput.h>


TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Loading()
{
	//??
	CreateActor<TitleLogo>(1);
	CreateActor<TitleBackGround>(0);
}

void TitleLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GameEngine::GetInst().ChangeLevel("PlayMap1F");
	}

}
