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
#include "Map1FRoom4Pot0.h"
#include "Map1FRoom10Pot0.h"
#include "Map1FRoom10Pot0B1F.h"
#include "Map1FRoom7Pot0.h"

#include "Map1FRoom6Pot0.h"

#include "Map1FRoom2EnemyPopo0.h"
#include "Map1FRoom5EnemyPopo0.h"

#include "EnemyBlueStalfos.h"
#include "Map1FRoom9EnemyBlueStalfos0.h"
#include "Map1FRoom10EnemyBlueStalfos0.h"
#include "Map1FRoom6EnemyBlueStalfos0.h"

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

	Player_ = CreateActor<PlayerLink>(static_cast<int>(PlayLevelOrder::PLAYER));
	PlayerLink::MainPlayer_ = Player_;
	
		//플레이어가 레벨을 시작할때마다 시작 지점이 다르기 때문에 Level에서 위치를 정해줘야한다
		// Room10부터 시작
		Player_->SetPosition({ 2687, 778 + 4128 });
		// Room11부터 시작
		//Player_->SetPosition({ 4607, 3792 });
		// Room7 부터 시작
		//Player_->SetPosition({ 512.0f, 2768.0f });
		// Room10부터 시작
		//Player_->SetPosition({ 3072.0f, 3800.0f });
		// 정상 시작
		//Player_->SetPosition({3072.0f, 3800.0f + 4128.0f});
	

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

	Map1FRoom6EnemyBlueStalfos0* Room6Stalfos0 = CreateActor<Map1FRoom6EnemyBlueStalfos0>(static_cast<int>(PlayLevelOrder::MONSTER));
	Room6Stalfos0->SetBlueStalfosPos({ 5407, 331 + 4128});
	Map1FRoom6EnemyBlueStalfos0* Room6Stalfos1 = CreateActor<Map1FRoom6EnemyBlueStalfos0>(static_cast<int>(PlayLevelOrder::MONSTER));
	Room6Stalfos1->SetBlueStalfosPos({ 5695, 412 + 4128 });
	Map1FRoom6EnemyBlueStalfos0* Room6Stalfos2 = CreateActor<Map1FRoom6EnemyBlueStalfos0>(static_cast<int>(PlayLevelOrder::MONSTER));
	Room6Stalfos2->SetBlueStalfosPos({ 5563, 651 + 4128 });


	EnemyAntiFairy* Room5AnitiFairy0 = CreateActor<EnemyAntiFairy>(static_cast<int>(PlayLevelOrder::MONSTER));
	Room5AnitiFairy0->SetAntiFairyPos({4319, 388 + 4128});
	Room5AnitiFairy0->SetAntiFairyTimeScale(5);
	EnemyAntiFairy* Room5AnitiFairy1 = CreateActor<EnemyAntiFairy>(static_cast<int>(PlayLevelOrder::MONSTER));
	Room5AnitiFairy1->SetAntiFairyPos({ 4319, 587 + 4128 });
	Room5AnitiFairy1->SetAntiFairyTimeScale(5);

	CreateActor<Map1FBridgeBackGround>(static_cast<int>(PlayLevelOrder::BELOWPLAYER));

	Map1FRoom4Pot0* Room4Pot0 = CreateActor<Map1FRoom4Pot0>(static_cast<int>(PlayLevelOrder::BELOWPLAYER));
	Room4Pot0->SetPotPos({ 3529.0f + 24.0f, 1124.0f + 24.0f + 4128.0f });
	Room4Pot0->SetItemIndex(static_cast<int>(ItemIndex::GreenRupee));
	Map1FRoom4Pot0* Room4Pot1 = CreateActor<Map1FRoom4Pot0>(static_cast<int>(PlayLevelOrder::BELOWPLAYER));
	Room4Pot1->SetPotPos({ 3592.0f + 24.0f, 1124.0f + 24.0f + 4128.0f });
	Room4Pot1->SetItemIndex(static_cast<int>(ItemIndex::BlueRupee));
	Map1FRoom4Pot0* Room4Pot2 = CreateActor<Map1FRoom4Pot0>(static_cast<int>(PlayLevelOrder::BELOWPLAYER));
	Room4Pot2->SetPotPos({ 3720.0f + 24.0f, 1124.0f + 24.0f + 4128.0f });
	Room4Pot2->SetItemIndex(static_cast<int>(ItemIndex::BlueRupee));
	Map1FRoom4Pot0* Room4Pot3 = CreateActor<Map1FRoom4Pot0>(static_cast<int>(PlayLevelOrder::BELOWPLAYER));
	Room4Pot3->SetPotPos({ 3784.0f + 24.0f, 1124.0f + 24.0f + 4128.0f });
	Room4Pot3->SetItemIndex(static_cast<int>(ItemIndex::GreenRupee));


	Map1FRoom1Pot0* Room1Pot0 = CreateActor<Map1FRoom1Pot0>(static_cast<int>(PlayLevelOrder::BELOWPLAYER));
	Room1Pot0->SetPotPos({ 2561.0f, 3451.0f + 4128.0f });
	Room1Pot0->SetItemIndex(static_cast<int>(ItemIndex::GreenRupee));
	Map1FRoom1Pot0* Room1Pot1 = CreateActor<Map1FRoom1Pot0>(static_cast<int>(PlayLevelOrder::BELOWPLAYER));
	Room1Pot1->SetPotPos({ 3041.0f, 3451.0f + 4128.0f });
	Room1Pot1->SetItemIndex(static_cast<int>(ItemIndex::Empty));
	Map1FRoom1Pot0* Room1Pot2 = CreateActor<Map1FRoom1Pot0>(static_cast<int>(PlayLevelOrder::BELOWPLAYER));
	Room1Pot2->SetPotPos({ 3585.0f, 3451.0f + 4128.0f });
	Room1Pot2->SetItemIndex(static_cast<int>(ItemIndex::GreenRupee));

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

	Map1FRoom6Pot0* Room6Pot0 = CreateActor<Map1FRoom6Pot0>(static_cast<int>(PlayLevelOrder::BELOWPLAYER));
	Room6Pot0->SetPotPos({ 5320 + 24, 356 + 24 + 4128 });
	Room6Pot0->SetItemIndex(static_cast<int>(ItemIndex::RecoveryHeart));
	Map1FRoom6Pot0* Room6Pot1 = CreateActor<Map1FRoom6Pot0>(static_cast<int>(PlayLevelOrder::BELOWPLAYER));
	Room6Pot1->SetPotPos({ 5608 + 24, 228 + 24 + 4128 });
	Room6Pot1->SetItemIndex(static_cast<int>(ItemIndex::Empty));
	Map1FRoom6Pot0* Room6Pot2 = CreateActor<Map1FRoom6Pot0>(static_cast<int>(PlayLevelOrder::BELOWPLAYER));
	Room6Pot2->SetPotPos({ 5896 + 24, 356 + 24 + 4128 });
	Room6Pot2->SetItemIndex(static_cast<int>(ItemIndex::Key));
	Map1FRoom6Pot0* Room6Pot3 = CreateActor<Map1FRoom6Pot0>(static_cast<int>(PlayLevelOrder::BELOWPLAYER));
	Room6Pot3->SetPotPos({ 5512 + 24, 484 + 24 + 4128 });
	Room6Pot3->SetItemIndex(static_cast<int>(ItemIndex::Empty));
	Map1FRoom6Pot0* Room6Pot4 = CreateActor<Map1FRoom6Pot0>(static_cast<int>(PlayLevelOrder::BELOWPLAYER));
	Room6Pot4->SetPotPos({ 5705 + 24, 484 + 24 + 4128 });
	Room6Pot4->SetItemIndex(static_cast<int>(ItemIndex::Empty));
	Map1FRoom6Pot0* Room6Pot5 = CreateActor<Map1FRoom6Pot0>(static_cast<int>(PlayLevelOrder::BELOWPLAYER));
	Room6Pot5->SetPotPos({ 5320 + 24, 613 + 24 + 4128 });
	Room6Pot5->SetItemIndex(static_cast<int>(ItemIndex::RecoveryHeart));
	Map1FRoom6Pot0* Room6Pot6 = CreateActor<Map1FRoom6Pot0>(static_cast<int>(PlayLevelOrder::BELOWPLAYER));
	Room6Pot6->SetPotPos({ 5608 + 24, 740 + 24 + 4128 });
	Room6Pot6->SetItemIndex(static_cast<int>(ItemIndex::GreenRupee));
	Map1FRoom6Pot0* Room6Pot7 = CreateActor<Map1FRoom6Pot0>(static_cast<int>(PlayLevelOrder::BELOWPLAYER));
	Room6Pot7->SetPotPos({ 5896 + 24, 612 + 24 + 4128 });
	Room6Pot7->SetItemIndex(static_cast<int>(ItemIndex::BlueRupee));


	CreateActor<Map1FRoof>(static_cast<int>(PlayLevelOrder::BACKGROUNDROOF));

	Map1FBridge* BridgeActor = CreateActor<Map1FBridge>(static_cast<int>(PlayLevelOrder::B1FBACKGROUNDROOF));
	Player_->SetBridgeActor(BridgeActor);

	CreateActor<BlackScreen>(static_cast<int>(PlayLevelOrder::BLACKBACKGROUND));

	CreateActor<UILayout>(static_cast<int>(PlayLevelOrder::UILAYOUT));
	CreateActor<UIMagicMeter>(static_cast<int>(PlayLevelOrder::UI));
	CreateActor<UISelectedItem>(static_cast<int>(PlayLevelOrder::UI));
	CreateActor<UIHeart>(static_cast<int>(PlayLevelOrder::UI));
	CreateActor<UINumbers>(static_cast<int>(PlayLevelOrder::UI));

	CreateActor<Colmap>(static_cast<int>(PlayLevelOrder::BACKGROUND));

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

void PlayMap1F::LevelChangeStart(GameEngineLevel* _NextLevel)
{
	BGMSoundPlayer_ = GameEngineSound::SoundPlayControl("dungeon.mp3", -1);
	Player_->SetBGMSoundPlayer(BGMSoundPlayer_);
}

void PlayMap1F::LevelChangeEnd(GameEngineLevel* _PrevLevel)
{
	BGMSoundPlayer_.Stop();
}
