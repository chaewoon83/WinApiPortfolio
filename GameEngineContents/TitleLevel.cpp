#include "TitleLevel.h"
#include "GameEngine/GameEngine.h"
#include "TitleLogo.h"


TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Loading()
{
	//??
	//CreateActor<TitleLogo>();
	//CreateActor<TitleBackGround>();
}

void TitleLevel::Update()
{
	GameEngine::GlobalEngine().ChangeLevel("Play");
}
