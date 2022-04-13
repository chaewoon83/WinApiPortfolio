#include "TitleLevel.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineSound.h>
#include "GameEngineContentsEnum.h"
#include "TitleLogo.h"
#include "TitleBackGround.h"
#include "TitleTriangle.h"
#include "TitleTimeObject.h"
#include "Title19911992.h"
#include "TitleNintenPresents.h"
#include "TitleSword.h"
#include "TitleZeldaZ.h"
#include "TitleTripleTrigangle.h"
#include "TitleTwinkle.h"

TitleLevel::TitleLevel() 
{
}

TitleLevel::~TitleLevel() 
{
}

void TitleLevel::Loading()
{
	//??
	CreateActor<TitleBackGround>(static_cast<int>(TitleOrder::BACKGROUND));
	CreateActor<TitleTimeObject>(static_cast<int>(TitleOrder::BACKGROUND));
	CreateActor<TitleTripleTrigangle>(static_cast<int>(TitleOrder::OBJECTS));
	CreateActor<TitleNintenPresents>(static_cast<int>(TitleOrder::OBJECTS));
	CreateActor<Title19911992>(static_cast<int>(TitleOrder::OBJECTS));
	CreateActor<TitleLogo>(static_cast<int>(TitleOrder::LOGO));
	CreateActor<TitleTriangle>(static_cast<int>(TitleOrder::TRIANGLES));
	CreateActor<TitleSword>(static_cast<int>(TitleOrder::SWORD));
	CreateActor<TitleZeldaZ>(static_cast<int>(TitleOrder::ZeldaZ));
	CreateActor<TitleTwinkle>(static_cast<int>(TitleOrder::TWINKLE));


}

void TitleLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GameEngine::GetInst().ChangeLevel("PlayMap1F");
	}

}

void TitleLevel::LevelChangeStart()
{
	//GameEngineSound::SoundPlayOneShot("TitleScreen.mp3", 2);
}

