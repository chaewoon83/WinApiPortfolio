#include "PlayLevel.h"
#include "PlayerLink.h"
#include "UILayout.h"
#include "UIMagicMeter.h"
#include "UISelectedItem.h"
#include "Map1_1.h"

PlayLevel::PlayLevel() 
{
}

PlayLevel::~PlayLevel() 
{
}

void PlayLevel::Loading()
{
	CreateActor<Map1_1>("Map1_1", 0);
	CreateActor<UILayout>("UILayout", 1);
	CreateActor<UIMagicMeter>("UIMagicMeter", 2);
	CreateActor<UISelectedItem>("UISelectedItem", 2);
	CreateActor<PlayerLink>("PlayerLink", 3);
}

void PlayLevel::Update()
{

}

void PlayLevel::LevelChangeStart()
{

}