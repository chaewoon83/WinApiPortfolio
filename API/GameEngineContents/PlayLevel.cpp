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
	CreateActor<Map1_1>((int)Order::BACKGROUND);
	CreateActor<PlayerLink>((int)Order::PLAYER);
	CreateActor<UILayout>((int)Order::UI);
	CreateActor<UIMagicMeter>((int)Order::UI);
	CreateActor<UISelectedItem>((int)Order::UI);
}

void PlayLevel::Update()
{

}

void PlayLevel::LevelChangeStart()
{

}