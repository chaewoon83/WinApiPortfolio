#include "PlayLevel.h"
#include "PlayerLink.h"
#include "UILayout.h"
#include "UIMagicMeter.h"
#include "UISelectedItem.h"
#include "Map1_1.h"
#include "GameEngineContentsEnum.h"

PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::Loading()
{
	CreateActor<Map1_1>((int)PlayLevelOrder::BACKGROUND);
	CreateActor<PlayerLink>((int)PlayLevelOrder::PLAYER);
	CreateActor<UILayout>((int)PlayLevelOrder::UI);
	CreateActor<UIMagicMeter>((int)PlayLevelOrder::UI);
	CreateActor<UISelectedItem>((int)PlayLevelOrder::UI);
}

void PlayLevel::Update()
{

}

void PlayLevel::LevelChangeStart()
{

}