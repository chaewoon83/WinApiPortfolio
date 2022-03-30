#include "PlayMap1F.h"
#include "PlayerLink.h"
#include "UILayout.h"
#include "UIMagicMeter.h"
#include "UISelectedItem.h"
#include "Map1F.h"
#include "GameEngineContentsEnum.h"

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
	CreateActor<UILayout>((int)PlayLevelOrder::UI);
	CreateActor<UIMagicMeter>((int)PlayLevelOrder::UI);
	CreateActor<UISelectedItem>((int)PlayLevelOrder::UI);
}

void PlayMap1F::Update()
{

}

void PlayMap1F::LevelChangeStart()
{

}