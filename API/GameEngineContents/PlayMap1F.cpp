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

#include "Map1FBridgeBackGround.h"

#include "Map1FRoom1Pot0.h"
#include "Map1FRoom10Pot0.h"
#include "Map1FRoom10Pot0B1F.h"
#include "Map1FRoom7Pot0.h"

#include "Map1FRoom6Pot0.h"

#include "Map1FRoom2EnemyPopo0.h"
#include "Map1FRoom5EnemyPopo0.h"

#include "EnemyBlueStalfos.h"
#include "Map1FRoom9EnemyBlueStalfos0.h"
#include "Map1FRoom10EnemyBlueStalfos0.h"

#include "EnemyAntiFairy.h"

#include "BlackScreen.h"

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

	PlayerLink* Player = CreateActor<PlayerLink>(static_cast<int>(PlayLevelOrder::PLAYER));
	PlayerLink::MainPlayer_ = Player;

	CreateActor<Map1F>(static_cast<int>(PlayLevelOrder::BACKGROUND));
	CreateActor<Map1F_2>(static_cast<int>(PlayLevelOrder::BACKGROUND));

	//CreateActor<Room1TopDoor0>(static_cast<int>(PlayLevelOrder::BACKGROUND));

	CreateActor<Map1FRoom2EnemyPopo0>(static_cast<int>(PlayLevelOrder::MONSTER))->SetPopoPos({ 3104, 2503 + 4128 });
	CreateActor<Map1FRoom2EnemyPopo0>(static_cast<int>(PlayLevelOrder::MONSTER))->SetPopoPos({ 3040, 2439 + 4128 });
	CreateActor<Map1FRoom2EnemyPopo0>(static_cast<int>(PlayLevelOrder::MONSTER))->SetPopoPos({ 3104, 2375 + 4128 });
	Map1FRoom5EnemyPopo0* Room5Popo0 = CreateActor<Map1FRoom5EnemyPopo0>(static_cast<int>(PlayLevelOrder::MONSTER));
	Room5Popo0->SetPopoPos({4895, 587 + 4128});
	Room5Popo0->SetPopoTimeScale(5);
	Map1FRoom5EnemyPopo0* Room5Popo1 = CreateActor<Map1FRoom5EnemyPopo0>(static_cast<int>(PlayLevelOrder::MONSTER));
	Room5Popo1->SetPopoPos({ 4639, 779 + 4128 });
	Room5Popo1->SetPopoTimeScale(5);


	//CreateActor<EnemyBlueStalfos>(static_cast<int>(PlayLevelOrder::MONSTER));
	CreateActor<Map1FRoom9EnemyBlueStalfos0>(static_cast<int>(PlayLevelOrder::MONSTER))->SetBlueStalfosPos({ 1439, 2880 });
	CreateActor<Map1FRoom9EnemyBlueStalfos0>(static_cast<int>(PlayLevelOrder::MONSTER))->SetBlueStalfosPos({ 1695, 2880 });
	CreateActor<Map1FRoom9EnemyBlueStalfos0>(static_cast<int>(PlayLevelOrder::MONSTER))->SetBlueStalfosPos({ 1439, 3236 });
	CreateActor<Map1FRoom9EnemyBlueStalfos0>(static_cast<int>(PlayLevelOrder::MONSTER))->SetBlueStalfosPos({ 1695, 3236 });
	Map1FRoom10EnemyBlueStalfos0 * Room10Stalfos0 = CreateActor<Map1FRoom10EnemyBlueStalfos0>(static_cast<int>(PlayLevelOrder::B1FMONSTER));
	Room10Stalfos0->SetBlueStalfosPos({ 2719, 3181 });
	Map1FRoom10EnemyBlueStalfos0* Room10Stalfos1 = CreateActor<Map1FRoom10EnemyBlueStalfos0>(static_cast<int>(PlayLevelOrder::B1FMONSTER));
	Room10Stalfos1->SetBlueStalfosPos({ 3423, 3181 });

	EnemyAntiFairy* Room5AnitiFairy0 = CreateActor<EnemyAntiFairy>(static_cast<int>(PlayLevelOrder::MONSTER));
	Room5AnitiFairy0->SetAntiFairyPos({4319, 388 + 4128});
	Room5AnitiFairy0->SetAntiFairyTimeScale(5);
	EnemyAntiFairy* Room5AnitiFairy1 = CreateActor<EnemyAntiFairy>(static_cast<int>(PlayLevelOrder::MONSTER));
	Room5AnitiFairy1->SetAntiFairyPos({ 4319, 587 + 4128 });
	Room5AnitiFairy1->SetAntiFairyTimeScale(5);

	CreateActor<Map1FBridgeBackGround>(static_cast<int>(PlayLevelOrder::BELOWPLAYER));

	Map1FRoom1Pot0* Room1Pot= nullptr;
	Map1FRoom1Pot0* Room1Pot0 = CreateActor<Map1FRoom1Pot0>(static_cast<int>(PlayLevelOrder::BELOWPLAYER));
	Room1Pot0->SetPotPos({ 2561.0f, 3451.0f + 4128.0f });
	Room1Pot0->SetItemIndex(1);
	Map1FRoom1Pot0* Room1Pot1 = CreateActor<Map1FRoom1Pot0>(static_cast<int>(PlayLevelOrder::BELOWPLAYER));
	Room1Pot1->SetPotPos({ 3041.0f, 3451.0f + 4128.0f });
	Room1Pot1->SetItemIndex(0);
	Map1FRoom1Pot0* Room1Pot2 = CreateActor<Map1FRoom1Pot0>(static_cast<int>(PlayLevelOrder::BELOWPLAYER));
	Room1Pot2->SetPotPos({ 3585.0f, 3451.0f + 4128.0f });
	Room1Pot2->SetItemIndex(1);

	CreateActor<Map1FRoom10Pot0>(static_cast<int>(PlayLevelOrder::BELOWPLAYER))->SetPotPos({ 2248.0f + 24.0f, 3268.0f + 24.0f });
	CreateActor<Map1FRoom10Pot0>(static_cast<int>(PlayLevelOrder::BELOWPLAYER))->SetPotPos({ 2312.0f + 24.0f, 3332.0f + 24.0f });
	CreateActor<Map1FRoom10Pot0>(static_cast<int>(PlayLevelOrder::BELOWPLAYER))->SetPotPos({ 3784.0f + 24.0f, 3332.0f + 24.0f });
	CreateActor<Map1FRoom10Pot0>(static_cast<int>(PlayLevelOrder::BELOWPLAYER))->SetPotPos({ 3848.0f + 24.0f, 3268.0f + 24.0f });

	CreateActor<Map1FRoom10Pot0B1F>(static_cast<int>(PlayLevelOrder::B1FBELOWPLAYER)) -> SetPotPos({2312 + 24, 2788 + 24});
	CreateActor<Map1FRoom10Pot0B1F>(static_cast<int>(PlayLevelOrder::B1FBELOWPLAYER)) -> SetPotPos({2312 + 24, 2852 + 24});
	CreateActor<Map1FRoom10Pot0B1F>(static_cast<int>(PlayLevelOrder::B1FBELOWPLAYER)) -> SetPotPos({3784 + 24, 2788 + 24});
	CreateActor<Map1FRoom10Pot0B1F>(static_cast<int>(PlayLevelOrder::B1FBELOWPLAYER)) -> SetPotPos({3784 + 24, 2852 + 24});

	CreateActor<Map1FRoom7Pot0>(static_cast<int>(PlayLevelOrder::BELOWPLAYER))->SetPotPos({ 168.0f + 24.0f, 3300.0f + 24.0f });
	CreateActor<Map1FRoom7Pot0>(static_cast<int>(PlayLevelOrder::BELOWPLAYER))->SetPotPos({ 807.0f + 24.0f, 3300.0f + 24.0f });
	CreateActor<Map1FRoom7Pot0>(static_cast<int>(PlayLevelOrder::BELOWPLAYER))->SetPotPos({ 488.0f + 24.0f, 3589.0f + 24.0f });
	CreateActor<Map1FRoom7Pot0>(static_cast<int>(PlayLevelOrder::BELOWPLAYER))->SetPotPos({ 168.0f + 24.0f, 3876.0f + 24.0f });
	CreateActor<Map1FRoom7Pot0>(static_cast<int>(PlayLevelOrder::BELOWPLAYER))->SetPotPos({ 808.0f + 24.0f, 3876.0f + 24.0f });

	CreateActor<Map1FRoom6Pot0>(static_cast<int>(PlayLevelOrder::BELOWPLAYER))->SetPotPos({5320 + 24, 356 + 24 + 4128 });


	CreateActor<Map1FRoof>(static_cast<int>(PlayLevelOrder::BACKGROUNDROOF));

	Map1FBridge* BridgeActor = CreateActor<Map1FBridge>(static_cast<int>(PlayLevelOrder::B1FBACKGROUNDROOF));
	Player->SetBridgeActor(BridgeActor);

	CreateActor<BlackScreen>(static_cast<int>(PlayLevelOrder::BLACKBACKGROUND));

	CreateActor<UILayout>(static_cast<int>(PlayLevelOrder::UILAYOUT));
	CreateActor<UIMagicMeter>(static_cast<int>(PlayLevelOrder::UI));
	CreateActor<UISelectedItem>(static_cast<int>(PlayLevelOrder::UI));
	CreateActor<UIHeart>(static_cast<int>(PlayLevelOrder::UI));
	CreateActor<UINumbers>(static_cast<int>(PlayLevelOrder::UI));

	CreateActor<Colmap>(static_cast<int>(PlayLevelOrder::BACKGROUND));
	//플레이어가 레벨을 시작할때마다 시작 지점이 다르기 때문에 Level에서 위치를 정해줘야한다
	// Room11부터 시작
	//Player->SetPosition({4607, 3792});
	// Room7 부터 시작
	//Player->SetPosition({ 512.0f, 2768.0f });
	// Room10부터 시작
	//Player->SetPosition({ 3072.0f, 3800.0f });
	// 정상 시작
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