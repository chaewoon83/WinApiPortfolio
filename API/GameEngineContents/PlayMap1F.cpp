#include "PlayMap1F.h"
#include "PlayerLink.h"
#include "UILayout.h"
#include "UIMagicMeter.h"
#include "UISelectedItem.h"
#include "UIHeart.h"
#include "UINumbers.h"
#include "Map1F.h"
#include "GameEngineContentsEnum.h"
#include "GameEngine/GameEngine.h"
#include "GameEngineBase/GameEngineInput.h"

PlayMap1F::PlayMap1F()
{
}

PlayMap1F::~PlayMap1F()
{
}

void PlayMap1F::Loading()
{
	CreateActor<Map1F>((int)PlayLevelOrder::BACKGROUND);
	CreateActor<PlayerLink>((int)PlayLevelOrder::PLAYER);
	CreateActor<UILayout>((int)PlayLevelOrder::UILAYOUT);
	CreateActor<UIMagicMeter>((int)PlayLevelOrder::UI);
	CreateActor<UISelectedItem>((int)PlayLevelOrder::UI);
	CreateActor<UIHeart>((int)PlayLevelOrder::UI);
	CreateActor<UINumbers>((int)PlayLevelOrder::UI);
}

void PlayMap1F::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GameEngine::GlobalEngine().ChangeLevel("TitleLevel");
	}
}

void PlayMap1F::LevelChangeStart()
{

}