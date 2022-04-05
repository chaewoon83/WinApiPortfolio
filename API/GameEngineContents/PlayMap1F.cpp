#include "PlayMap1F.h"
#include "PlayerLink.h"
#include "UILayout.h"
#include "UIMagicMeter.h"
#include "UISelectedItem.h"
#include "UIHeart.h"
#include "UINumbers.h"
#include "Map1F.h"
#include "Map1FRoof.h"
#include "EXMap.h"
#include "Background.h"
#include "GameEngineContentsEnum.h"
#include "GameEngine/GameEngine.h"
#include <GameEngine/GameEngineRenderer.h>
#include "GameEngineBase/GameEngineInput.h"
#include <GameEngineBase/GameEngineWindow.h>

PlayMap1F::PlayMap1F()
{
}

PlayMap1F::~PlayMap1F()
{
}

void PlayMap1F::Loading()
{
	CreateActor<Map1F>((int)PlayLevelOrder::BACKGROUND);
	CreateActor<Map1FRoof>((int)PlayLevelOrder::BACKGROUNDROOF);
	//CreateActor<Map1F>((int)PlayLevelOrder::BACKGROUND);
	PlayerLink* Player = CreateActor<PlayerLink>((int)PlayLevelOrder::PLAYER);
	CreateActor<UILayout>((int)PlayLevelOrder::UILAYOUT);
	CreateActor<UIMagicMeter>((int)PlayLevelOrder::UI);
	CreateActor<UISelectedItem>((int)PlayLevelOrder::UI);
	CreateActor<UIHeart>((int)PlayLevelOrder::UI);
	CreateActor<UINumbers>((int)PlayLevelOrder::UI);
	//플레이어가 레벨을 시작할때마다 시작 지점이 다르기 때문에 Level에서 위치를 정해줘야한다
	Player->SetPosition({3072.0f, 3800.0f});

}

void PlayMap1F::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GameEngine::GetInst().ChangeLevel("TitleLevel");
	}
}

void PlayMap1F::LevelChangeStart()
{

}