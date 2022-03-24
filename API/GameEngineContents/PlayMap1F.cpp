#include "PlayMap1F.h"
#include "PlayerLink.h"
#include "UILayout.h"
#include "UIMagicMeter.h"
#include "UISelectedItem.h"
#include "Map1_1.h"

PlayMap1F::PlayMap1F()
{
}

PlayMap1F::~PlayMap1F()
{
}

void PlayMap1F::Loading()
{
	CreateActor<Map1_1>("Map1_1", 0);
	CreateActor<UILayout>("UILayout", 1);
	CreateActor<UIMagicMeter>("UIMagicMeter", 2);
	CreateActor<UISelectedItem>("UISelectedItem", 2);
	CreateActor<PlayerLink>("PlayerLink", 3);
}

void PlayMap1F::Update()
{

}

void PlayMap1F::LevelChangeStart()
{

}