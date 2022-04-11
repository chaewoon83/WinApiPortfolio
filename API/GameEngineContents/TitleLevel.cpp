#include "TitleLevel.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include "TitleLogo.h"
#include "TitleBackGround.h"
#include "TitleTriangle.h"


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
	CreateActor<TitleTriangle>(2);

}

void TitleLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GameEngine::GetInst().ChangeLevel("PlayMap1F");
	}

}
