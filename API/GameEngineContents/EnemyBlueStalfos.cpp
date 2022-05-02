//#include "EnemyBlueStalfos.h"
//#include "PlayerLink.h"
//#include <windows.h>
//#include <GameEngineBase/GameEngineWindow.h>
//#include <GameEngine/GameEngineCollision.h>
//#include <GameEngine/GameEngineRenderer.h>
//#include <GameEngine/GameEngineImage.h>
//#include <GameEngineBase/GameEngineRandom.h>
//#include "EnemyGlobalFunction.h"
//#include "GlobalRandom.h"
//#include "ItemGreenRupee.h"
//#include "ItemBlueRupee.h"
//
//
////TODO
////1. 벽에 부딫혔을때 움찔움찔
////2. 한 방향으로 7-10번씩 움직임
//
//
//EnemyBlueStalfos::EnemyBlueStalfos()
//	:BlueStalfosHeadRenderer_(nullptr),
//	 BlueStalfosBodyRenderer_(nullptr),
//	 BlueStalfosCol_(nullptr),
//	 BlueStalfosMoveCol_(nullptr),
//	 BlueStalfosPos_({ 3104, 2503 + 4128 }),
//	 TimeScale_(10),
//	 IsInvincible_(false),
//	 IsDeath_(false),
//	 InvincibleTime_(0.3f),
//	 CurInvincibleTime_(0.0f),
//	 Hp_(2),
//	 IsGetDamaged_(false),
//	 IsKnockback_(false),
//	 IsBlink_(false),
//	 MoveTimes_(0),
//	 CurMoveTimes_(0),
//	 MoveFreq_(0.25f),
//	 CurMoveFreq_(0.0f),
//	 RestTime_(3.0f),
//	 CurRestTime_(0.0f),
//	 KnockbackTime_(0.15f),
//	 CurKnockbackTime_(0.0f),
//	 BlinkTime_(0.3f),
//	 CurBlinkTime_(0.0f),
//	 BlinkFreq_(0.02f),
//	 CurBlinkFreq_(0.0f),
//	 TimeAfterDeath_(2.0f),
//	 CurTimeAfterDeath_(0.0f),
//	 IsAlphaOn_(true),
//	 KnockbackDir_(float4::ZERO),
//	 MoveDir_(float4::ZERO),
//	 KnockBackSpeed_(800.0f),
//	 BlueStalfosCurState_(BlueStalfosState::LookAroundDown)
//{
//}
//
//
///// 10 times killed Popo, 2 times 1rupee, 1 time 5rupee;
//EnemyBlueStalfos::~EnemyBlueStalfos()
//{
//}
//
//void EnemyBlueStalfos::Start()
//{
//	SetPosition(BlueStalfosPos_);
//	BlueStalfosHeadRenderer_ = CreateRenderer();
//	BlueStalfosHeadRenderer_->SetPivot({ 0, -28 });
//	BlueStalfosHeadRenderer_->CreateAnimationTimeKey("EnemyBlueStalfosRightHead.bmp.bmp", "Right_Head", TimeScale_, 0, 0, 0.15f, false);
//	BlueStalfosHeadRenderer_->CreateAnimationTimeKey("EnemyBlueStalfosLeftHead.bmp.bmp", "Left_Head", TimeScale_, 0, 0, 0.15f, false);
//	BlueStalfosHeadRenderer_->CreateAnimationTimeKey("EnemyBlueStalfosUpHead.bmp.bmp", "Up_Head", TimeScale_, 0, 0, 0.15f, false);
//	BlueStalfosHeadRenderer_->CreateAnimationTimeKey("EnemyBlueStalfosDownHead.bmp.bmp", "Down_Head", TimeScale_, 0, 0, 0.15f, false);
//	BlueStalfosHeadRenderer_->ChangeAnimation("Down_Head");;
//	BlueStalfosBodyRenderer_ = CreateRenderer();
//	BlueStalfosBodyRenderer_->SetPivot({ 0, 24 });
//	BlueStalfosBodyRenderer_->CreateAnimationTimeKey("EnemyBlueStalfosRightBody.bmp", "Right_Body", TimeScale_, 0, 1, 0.3f, true);
//	BlueStalfosBodyRenderer_->CreateAnimationTimeKey("EnemyBlueStalfosLeftBody.bmp", "Left_Body", TimeScale_, 0, 1, 0.3f, true);
//	BlueStalfosBodyRenderer_->CreateAnimationTimeKey("EnemyBlueStalfosUpBody.bmp", "Up_Body", TimeScale_, 0, 1, 0.3f, true);
//	BlueStalfosBodyRenderer_->CreateAnimationTimeKey("EnemyBlueStalfosDownBody.bmp", "Down_Body", TimeScale_, 0, 1, 0.3f, true);
//	BlueStalfosBodyRenderer_->ChangeAnimation("Down_Body");
//	//죽는 애니메이션은 플레이어와 함께한다
//	BlueStalfosHeadRenderer_->CreateAnimationTimeKey("EnemyDeathEffect.bmp", "DeathEffect", 0, 0, 6, 0.15f, false);
//	BlueStalfosHeadRenderer_->ChangeAnimation("Idle");
//
//	//DeathEffectRenderer_ = CreateRenderer();
//	//DeathEffectRenderer_->CreateAnimation("EnemyDeathEffect.bmp", "DeathEffect", 0, 6, 0.15f, false);
//
//	BlueStalfosCol_ = CreateCollision("MonsterHitBox", { 48, 56 }, { 0, -28 });
//	BlueStalfosMoveCol_ = CreateCollision("MonsterMoveBox", { 48, 56 }, { 0, -28 });
//
//}
//
//void EnemyBlueStalfos::Update()
//{
//	BlueStalfosStateUpdate();
//	EnemyGlobalFunction::BlueStalfosBlinkUpdate(TimeScale_, IsBlink_, IsAlphaOn_, BlinkTime_, 
//		CurBlinkTime_, BlinkFreq_, CurBlinkFreq_, BlueStalfosCurState_, BlueStalfosHeadRenderer_, BlueStalfosBodyRenderer_);
//}
//
//void EnemyBlueStalfos::Render()
//{
//
//}
//
//void EnemyBlueStalfos::GetDamaged()
//{
//
//	if (true == IsInvincible_)
//	{
//		CurInvincibleTime_ += GameEngineTime::GetDeltaTime(2);
//		if (InvincibleTime_ < CurInvincibleTime_)
//		{
//			IsInvincible_ = false;
//			CurInvincibleTime_ = 0.0f;
//		}
//	}
//	if (false == IsInvincible_ && false == IsDeath_)
//	{
//		std::vector<GameEngineCollision*> ColList;
//		if (true == PopoCol_->CollisionResult("Sword", ColList, CollisionType::Rect, CollisionType::Rect))
//		{
//			Hp_ -= 1;
//			IsInvincible_ = true;
//			IsBlink_ = true;
//			IsKnockback_ = true;
//			IsBlink_ = true;
//			HitActor_ = ColList[0]->GetActor();
//			KnockbackDir_ = GetPosition() - HitActor_->GetPosition();
//			KnockbackDir_.Normal2D();
//			BlueStalfosChangeState(PopoState::Knockbacked);
//		}
//
//		if (true == PopoCol_->CollisionResult("PotHitBox", ColList, CollisionType::Rect, CollisionType::Rect))
//		{
//			Hp_ -= 1;
//			IsInvincible_ = true;
//
//			IsKnockback_ = true;
//			IsBlink_ = true;
//			HitActor_ = ColList[0]->GetActor();
//			KnockbackDir_ = GetPosition() - HitActor_->GetPosition();
//			KnockbackDir_.Normal2D();
//			ColList[0]->Off();
//			PopoChangeState(PopoState::Knockbacked);
//		}
//
//		if (0 >= Hp_)
//		{
//			IsInvincible_ = true;
//			IsDeath_ = true;
//
//			PopoCol_->Death();
//
//			return;
//		}
//	}
//
//}
//
//void EnemyBlueStalfos::IdleStart()
//{
//	//PopoRenderer_->ChangeAnimation("Idle");
//	CurMoveFreq_ = MoveFreq_;
//}
//
//void EnemyBlueStalfos::KnockbackedStart()
//{
//}
//
//void EnemyBlueStalfos::DeathStart()
//{
//	PopoMoveCol_->Death();
//	PopoRenderer_->SetAlpha(255);
//	PopoRenderer_->ChangeAnimation("DeathEffect");
//	//DeathEffectRenderer_->ChangeAnimation("DeathEffect");
//}
//
//void EnemyBlueStalfos::IdleUpdate()
//{
//	GetDamaged();
//	GameEngineTime* A = GameEngineTime::GetInst();
//	CurRestTime_ += GameEngineTime::GetDeltaTime(TimeScale_);
//	if (MoveTimes_ == CurMoveTimes_)
//	{
//		CurMoveTimes_ = 0;
//		int RandomInt = GlobalRandom::RandomIntGenerate(7, 9);
//		MoveTimes_ = RandomInt;
//		RandomInt = GlobalRandom::RandomIntGenerate(1, 8);
//		MoveDirCheck(RandomInt);
//		CurRestTime_ = 0;
//	}
//	if (RestTime_ < CurRestTime_)
//	{
//		CurMoveFreq_ += GameEngineTime::GetDeltaTime(TimeScale_);
//		if (MoveFreq_ < CurMoveFreq_)
//		{
//			CurMoveTimes_ += 1;
//			CurMoveFreq_ = 0.0f;
//			float4 NextPosition = GetPosition() + (MoveDir_ * 10);
//			int White = RGB(255, 255, 255);
//			if (true == PosAndColorCheck(White, PlayerLink::MapColImage_))
//			{
//				SetPosition(GetPosition() + (MoveDir_ * 10));
//			}
//		}
//	}
//}
//
//void EnemyBlueStalfos::KnockbackedUpdate()
//{
//	CurKnockbackTime_ += GameEngineTime::GetDeltaTime(TimeScale_);
//	int White = RGB(255, 255, 255);
//	if (true == PosAndColorCheck(White, PlayerLink::MapColImage_))
//	{
//		EnemyGlobalFunction::MoveFunction(TimeScale_, KnockBackSpeed_, KnockbackDir_, PopoMoveCol_, this);
//	}
//	if (KnockbackTime_ < CurKnockbackTime_)
//	{
//		IsKnockback_ = false;
//	}
//	if (true == IsDeath_ && true == IsInvincible_ && KnockbackTime_ * 0.3f < CurKnockbackTime_)
//	{
//		PopoChangeState(PopoState::Death);
//		return;
//	}
//	if (false == IsKnockback_)
//	{
//		CurKnockbackTime_ = 0.0f;
//		PopoChangeState(PopoState::Idle);
//		return;
//	}
//}
//
//void EnemyBlueStalfos::DeathUpdate()
//{
//	if (true == IsDeath_ && true == PopoRenderer_->IsEndAnimation())
//	{
//		GameEngineRandom Random;
//		//Max 10
//		int RandomInt = Random.RandomInt(1, 10);
//		//if (2 >= RandomInt)
//		//{
//		//	ItemGreenRupee* Ptr = GetLevel()->CreateActor<ItemGreenRupee>((int)PlayLevelOrder::PLAYER);
//		//	Ptr->SetPosition(GetPosition());
//		//}
//
//		//if (2 <= RandomInt && 3 >= RandomInt)
//		//{
//		//	ItemGreenRupee* Ptr = GetLevel()->CreateActor<ItemGreenRupee>((int)PlayLevelOrder::PLAYER);
//		//	Ptr->SetPosition(GetPosition());
//		//}
//
//		{
//			ItemBlueRupee* Ptr = GetLevel()->CreateActor<ItemBlueRupee>((int)PlayLevelOrder::PLAYER);
//			Ptr->SetPosition(GetPosition());
//		}
//
//		Death();
//	}
//}
//
//
//
//
//void EnemyBlueStalfos::BlueStalfosChangeState(BlueStalfosState _State)
//{
//	if (BlueStalfosCurState_ != _State)
//	{
//		switch (_State)
//		{
//		case BlueStalfosState::Idle:
//			IdleStart();
//			break;
//		case BlueStalfosState::LookAround:
//			LookAroundStart();
//			break;
//		case BlueStalfosState::Walk:
//			WalkStart();
//			break;
//		case BlueStalfosState::Jump:
//			JumpStart();
//			break;
//		case BlueStalfosState::Knockbacked:
//			KnockbackedStart();
//			break;
//		case BlueStalfosState::Death:
//			DeathStart();
//			break;
//		case BlueStalfosState::Max:
//			break;
//		default:
//			break;
//		}
//	}
//	BlueStalfosCurState_ = _State;
//}
//
//void EnemyBlueStalfos::BlueStalfosStateUpdate()
//{
//	switch (BlueStalfosCurState_)
//	{
//	case BlueStalfosState::Idle:
//		IdleUpdate();
//		break;
//	case BlueStalfosState::LookAround:
//		LookAroundUpdate();
//		break;
//	case BlueStalfosState::Walk:
//		WalkUpdate();
//		break;
//	case BlueStalfosState::Jump:
//		JumpUpdate();
//		break;
//	case BlueStalfosState::Knockbacked:
//		KnockbackedUpdate();
//		break;
//	case BlueStalfosState::Death:
//		DeathUpdate();
//		break;
//	case BlueStalfosState::Max:
//		break;
//	default:
//		break;
//	}
//}
//
//bool EnemyBlueStalfos::PosAndColorCheck(int _Color, GameEngineImage* _Image)
//{
//	float4 MyPos = GetPosition();
//	float4 Map1f_2_Scale = float4{ 0, -4128 };
//	if (false == dynamic_cast<PlayerLink*>(PlayerLink::MainPlayer_)->GetIsMap1F_2())
//	{
//		MyPos += Map1f_2_Scale;
//	}
//	float4 MyPosTopRight = MyPos + float4{ 32.0f, -32.0f };
//	float4 MyPosTopLeft = MyPos + float4{ -32.0f, -32.0f };
//	float4 MyPosBotRight = MyPos + float4{ 32.0f, 32.0f };
//	float4 MyPosBotLeft = MyPos + float4{ -32.0f, 32.0f };
//	float4 MyPosRight = MyPos + float4{ 32.0f, 0.0f };
//	float4 MyPosLeft = MyPos + float4{ -32.0f, 0.0f };
//	float4 MyPosTop = MyPos + float4{ 0.0f, -32.0f };
//	float4 MyPosBot = MyPos + float4{ 0.0f, 32.0f };
//
//	int ColorTopRight = _Image->GetImagePixel(MyPosTopRight);
//	int ColorTopLeft = _Image->GetImagePixel(MyPosTopLeft);
//	int ColorBotRight = _Image->GetImagePixel(MyPosBotRight);
//	int ColorBotLeft = _Image->GetImagePixel(MyPosBotLeft);
//	int ColorRight = _Image->GetImagePixel(MyPosRight);
//	int ColorLeft = _Image->GetImagePixel(MyPosLeft);
//	int ColorTop = _Image->GetImagePixel(MyPosTop);
//	int ColorBot = _Image->GetImagePixel(MyPosBot);
//
//
//
//	if (_Color == ColorTopRight &&
//		_Color == ColorTopLeft &&
//		_Color == ColorBotRight &&
//		_Color == ColorBotLeft &&
//		_Color == ColorRight &&
//		_Color == ColorLeft &&
//		_Color == ColorBot &&
//		_Color == ColorTop)
//	{
//		return true;
//	}
//	return false;
//}
//
//void EnemyBlueStalfos::MoveDirCheck(int _RandomInt)
//{
//	if (1 == _RandomInt)
//	{
//		MoveDir_ = float4{ 0, 1 };
//	}
//	if (2 == _RandomInt)
//	{
//		MoveDir_ = float4{ 1, 1 };
//	}
//	if (3 == _RandomInt)
//	{
//		MoveDir_ = float4{ 1, 0 };
//	}
//	if (4 == _RandomInt)
//	{
//		MoveDir_ = float4{ 1, -1 };
//	}
//	if (5 == _RandomInt)
//	{
//		MoveDir_ = float4{ 0, -1 };
//	}
//	if (6 == _RandomInt)
//	{
//		MoveDir_ = float4{ -1, -1 };
//	}
//	if (7 == _RandomInt)
//	{
//		MoveDir_ = float4{ -1,0 };
//	}
//	if (8 == _RandomInt)
//	{
//		MoveDir_ = float4{ -1, 1 };
//	}
//}
//
//
