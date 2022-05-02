#include "GameEngineContentsEnum.h"
#include "GameEngine/GameEngine.h"
#include <GameEngine/GameEngineRenderer.h>
#include "GameEngineBase/GameEngineInput.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineSound.h>
#include "PlayMap1F.h"
#include "PlayerLink.h"
#include "UILayout.h"
#include "UIMagicMeter.h"
#include "UISelectedItem.h"
#include "UIHeart.h"
#include "UINumbers.h"
#include "Map1F.h"
#include "Map1F_2.h"
#include "Map1FRoof.h"
#include "Map1FBridge.h"
#include "EXMap.h"
#include "Background.h"
#include "TitleLevel.h"
#include "EnemyPopo.h"

#include "Map1FBridgeBackGround.h"

#include "Map1FRoom1Pot0.h"
#include "Map1FRoom1Pot1.h"
#include "Map1FRoom1Pot2.h"
#include "Map1FRoom10Pot0.h"
#include "Map1FRoom10Pot1.h"
#include "Map1FRoom10Pot2.h"
#include "Map1FRoom10Pot3.h"

#include "Map1FRoom1EnemyPopo0.h"
#include "Map1FRoom1EnemyPopo1.h"
#include "Map1FRoom1EnemyPopo2.h"

#include "Colmap.h"


PlayMap1F::PlayMap1F()
{
}

PlayMap1F::~PlayMap1F()
{
}


void PlayMap1F::Loading()
{
	// 0 은 플레이어 -1은 문
	// 1 부터 Room1 Room2 ...
	ResetTimeScale();

	CreateActor<Map1F>(static_cast<int>(PlayLevelOrder::BACKGROUND));
	CreateActor<Map1F_2>(static_cast<int>(PlayLevelOrder::BACKGROUND));

	//CreateActor<Room1TopDoor0>(static_cast<int>(PlayLevelOrder::BACKGROUND));

	CreateActor<EnemyPopo>(static_cast<int>(PlayLevelOrder::MONSTER));

	CreateActor<Map1FRoom1EnemyPopo0>(static_cast<int>(PlayLevelOrder::MONSTER));
	CreateActor<Map1FRoom1EnemyPopo1>(static_cast<int>(PlayLevelOrder::MONSTER));
	CreateActor<Map1FRoom1EnemyPopo2>(static_cast<int>(PlayLevelOrder::MONSTER));

	PlayerLink* Player = CreateActor<PlayerLink>(static_cast<int>(PlayLevelOrder::PLAYER));
	PlayerLink::MainPlayer_ = Player;

	CreateActor<Map1FBridgeBackGround>(static_cast<int>(PlayLevelOrder::BELOWPLAYER));

	CreateActor<Map1FRoom1Pot0>(static_cast<int>(PlayLevelOrder::BELOWPLAYER));
	CreateActor<Map1FRoom1Pot1>(static_cast<int>(PlayLevelOrder::BELOWPLAYER));
	CreateActor<Map1FRoom1Pot2>(static_cast<int>(PlayLevelOrder::BELOWPLAYER));
	CreateActor<Map1FRoom10Pot0>(static_cast<int>(PlayLevelOrder::BELOWPLAYER));
	CreateActor<Map1FRoom10Pot1>(static_cast<int>(PlayLevelOrder::BELOWPLAYER));
	CreateActor<Map1FRoom10Pot2>(static_cast<int>(PlayLevelOrder::BELOWPLAYER));
	CreateActor<Map1FRoom10Pot3>(static_cast<int>(PlayLevelOrder::BELOWPLAYER));


	CreateActor<Map1FRoof>(static_cast<int>(PlayLevelOrder::BACKGROUNDROOF));

	Map1FBridge* BridgeActor = CreateActor<Map1FBridge>(static_cast<int>(PlayLevelOrder::BACKGROUNDROOF));
	Player->SetBridgeActor(BridgeActor);


	CreateActor<UILayout>(static_cast<int>(PlayLevelOrder::UILAYOUT));
	CreateActor<UIMagicMeter>(static_cast<int>(PlayLevelOrder::UI));
	CreateActor<UISelectedItem>(static_cast<int>(PlayLevelOrder::UI));
	CreateActor<UIHeart>(static_cast<int>(PlayLevelOrder::UI));
	CreateActor<UINumbers>(static_cast<int>(PlayLevelOrder::UI));

	CreateActor<Colmap>(static_cast<int>(PlayLevelOrder::BACKGROUND));
	//플레이어가 레벨을 시작할때마다 시작 지점이 다르기 때문에 Level에서 위치를 정해줘야한다
	// Room10부터 시작
	//Player->SetPosition({ 3072.0f, 3800.0f });
	Player->SetPosition({3072.0f, 3800.0f + 4128.0f});
	BridgeActor->Off();
}

void PlayMap1F::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("LevelChange"))
	{
		GameEngine::GetInst().ChangeLevel("TitleLevel");
	}
}

void PlayMap1F::ResetTimeScale()
{
	GameEngineTime::GetInst()->SetTimeScale(-1, 1.0f);
	GameEngineTime::GetInst()->SetTimeScale(0, 1.0f);
	GameEngineTime::GetInst()->SetTimeScale(1, 1.0f);
	GameEngineTime::GetInst()->SetTimeScale(2, 0.0f);
	GameEngineTime::GetInst()->SetTimeScale(3, 0.0f);
	GameEngineTime::GetInst()->SetTimeScale(4, 0.0f);
	GameEngineTime::GetInst()->SetTimeScale(5, 0.0f);
	GameEngineTime::GetInst()->SetTimeScale(6, 0.0f);
	GameEngineTime::GetInst()->SetTimeScale(7, 0.0f);
	GameEngineTime::GetInst()->SetTimeScale(8, 0.0f);
	GameEngineTime::GetInst()->SetTimeScale(9, 0.0f);
	GameEngineTime::GetInst()->SetTimeScale(11, 0.0f);
	GameEngineTime::GetInst()->SetTimeScale(12, 0.0f);
	GameEngineTime::GetInst()->SetTimeScale(13, 0.0f);
	GameEngineTime::GetInst()->SetTimeScale(14, 0.0f);
	GameEngineTime::GetInst()->SetTimeScale(15, 0.0f);
	GameEngineTime::GetInst()->SetTimeScale(16, 0.0f);
}