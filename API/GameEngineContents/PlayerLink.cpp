#include "PlayerLink.h"
#include <windows.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineCollision.h>

#include "Map1F.h"
#include "Boomerang.h"

//��ũ�� ũ�� == 64x96
//��ũ ��Ʈ�ڽ��� ũŰ == 64x64


//FIN
//�밢���Է� �ӷ� �븻������ �ϱ�V
//FSM �����ϱ�V
//�ȱ�ִϸ��̼� �߰�V
//TODO
//��� ��� ���� ��ġ�� ( Ű �ڴ����� state�� ��ȭ���� ����)
//���� �ִϸ��̼�, �Լ� �߰�
//�ǰ� �Լ� �߰�

//��� ���� ���� 384
//��� ���� ���� 320

//�Ķ��� -> ���̵�
//����� -> ���̵�
//������ -> ���� �� �̵�

GameEngineImage* PlayerLink::MapColImage_ = nullptr;
GameEngineActor* PlayerLink::MainPlayer_ = nullptr;
GameEngineActor* PlayerLink::CarryActor_ = nullptr;
PlayerState PlayerLink::PlayerCurState_ = PlayerState::IdleDown;
PlayerState PlayerLink::PlayerPrevState_ = PlayerState::Max;
CameraState PlayerLink::CameraState_ = CameraState::Room1;
CameraState PlayerLink::PrevCameraState_ = CameraState::Max;
bool PlayerLink::IsCarry_ = false;
int PlayerLink::CurrentAnimationFrame_ = -1;

PlayerLink::PlayerLink()
	:BridgeActor_(nullptr),
	 HitActor_(nullptr),
	 Speed_(350.0f),
	 KnockBackSpeed_(350.0f),

	 IsCameraAutoMove_(false),
	 IsCharacterAutoMove_(false),
	 IsPlayerCanPassDoor_(false),
	 AutoMoveDir_(float4::ZERO),
	 CurStairs_(PlayerStairsState::Top),
	 IsOnStairs_(false),
	 PlayerCollision_(nullptr),
	 SwordCollision_(nullptr),
	 AnimationTimer_(0.0f),
	 AnimationIndex_(0),
	 AttackAnimationInterval_(0.04f),
	 IsGetDamaged_(false),
	 IsKnockback_(false),
	 IsBlink_(false),
	 KnockbackTime_(0.2f),
	 CurKnockbackTime_(0.0f),
	 BlinkTime_(1.5f),
	 CurBlinkTime_(0.0f),
	 BlinkFreq_(0.01f),
	 CurBlinkFreq_(0.0f),
	 IsAlphaOn_(true),
	 Hp_(10)
{
}

PlayerLink::~PlayerLink() 
{
}

void PlayerLink::Start()
{
	//�浹
	PlayerCollision_ = CreateCollision("PlayerHitBox", {64, 64});
	PlayerMoveCollision_ = CreateCollision("PlayerHitBox", {64, 64}, {0, 12});
	PlayerTopRightCollision_ = CreateCollision("PlayerTopRightHitBox", {20, 20 }, { 22, -10 });
	PlayerTopLeftCollision_ = CreateCollision("PlayerTopLeftHitBox", { 20, 20 }, { -22, -10 });
	PlayerBotRightCollision_ = CreateCollision("PlayerBotRightHitBox", { 20, 20 }, { 22, 34 });
	PlayerBotLeftCollision_ = CreateCollision("PlayerBotLeftHitBox", { 20, 20 }, { -22, 34 });
	PlayerMiddleHorCollision_ = CreateCollision("PlayerBotLeftHitBox", { 64, 24 }, {0, 12});
	PlayerMiddleVerCollision_ = CreateCollision("PlayerBotLeftHitBox", { 24, 64 }, {0, 12});
	
	//PlayerCollision_->Off();
	//PlayerMoveCollision_->Off();

	//GameEngineRenderer* ExampleRenderer;
	//ExampleRenderer = CreateRenderer();
	//ExampleRenderer->SetImage("Idle.bmp");
	//ExampleRenderer->SetAlpha(100);
	//�÷��̾ ������ �����Ҷ����� ���� ������ �ٸ��� ������ Level���� ��ġ�� ��������Ѵ�
	//SetPosition(GameEngineWindow::GetScale().Half());
	PlayerRenderer_ = CreateRenderer();
	//PlayerRenderer->SetAlpha(50);
	//true �� ���� false �� �����ƴ�
	//PlayerRenderer->SetPivot({ 0, -11 });

	PlayerRenderer_->CreateAnimation("Link_Idle_Right.bmp", "Idle_Right", 0, 1, 0.05f, false);
	PlayerRenderer_->CreateAnimation("Link_Idle_Left.bmp", "Idle_Left", 0, 1, 0.05f, false);
	PlayerRenderer_->CreateAnimation("Link_Idle_Up.bmp", "Idle_Up", 0, 1, 0.05f, false);
	PlayerRenderer_->CreateAnimation("Link_Idle_Down.bmp", "Idle_Down", 0, 1, 0.05f, false);

	PlayerRenderer_->CreateAnimation("Link_Walk_Right.bmp", "Walk_Right", 0, 5, 0.05f, true);
	PlayerRenderer_->CreateAnimation("Link_Walk_Left.bmp", "Walk_Left", 0, 5, 0.05f, true);
	PlayerRenderer_->CreateAnimation("Link_Walk_Up.bmp", "Walk_Up", 0, 7, 0.05f, true);
	PlayerRenderer_->CreateAnimation("Link_Walk_Down.bmp", "Walk_Down", 0, 7, 0.05f, true);

	PlayerRenderer_->CreateAnimation("Link_Wield_Right.bmp", "Wield_Right", 0, 4, AttackAnimationInterval_, true);
	PlayerRenderer_->CreateAnimation("Link_Wield_Left.bmp", "Wield_Left", 0, 4, AttackAnimationInterval_, true);
	PlayerRenderer_->CreateAnimation("Link_Wield_Up.bmp", "Wield_Up", 0, 4, AttackAnimationInterval_, true);
	PlayerRenderer_->CreateAnimation("Link_Wield_Down.bmp", "Wield_Down", 0, 5, AttackAnimationInterval_, true);

	PlayerRenderer_->CreateAnimation("Link_Damaged_Right.bmp", "Damaged_Right", 0, 1, 0.05f, false);
	PlayerRenderer_->CreateAnimation("Link_Damaged_Left.bmp", "Damaged_Left", 0, 1, 0.05f, false);
	PlayerRenderer_->CreateAnimation("Link_Damaged_Up.bmp", "Damaged_Up", 0, 1, 0.05f, false);
	PlayerRenderer_->CreateAnimation("Link_Damaged_Down.bmp", "Damaged_Down", 0, 1, 0.05f, false);

	PlayerRenderer_->CreateAnimation("Link_Carry_Start_Right.bmp", "Carry_Start_Right", 0, 2, 0.2f, true);
	PlayerRenderer_->CreateAnimation("Link_Carry_Start_Left.bmp", "Carry_Start_Left", 0, 2, 0.2f, true);
	PlayerRenderer_->CreateAnimation("Link_Carry_Start_Up.bmp", "Carry_Start_Up", 0, 2, 0.2f, true);
	PlayerRenderer_->CreateAnimation("Link_Carry_Start_Down.bmp", "Carry_Start_Down", 0, 2, 0.2f, true);

	PlayerRenderer_->CreateAnimation("Link_Carry_Idle_Right.bmp", "Carry_Idle_Right", 0, 1, 0.25f, true);
	PlayerRenderer_->CreateAnimation("Link_Carry_Idle_Left.bmp", "Carry_Idle_Left", 0, 1, 0.25f, true);
	PlayerRenderer_->CreateAnimation("Link_Carry_Idle_Up.bmp", "Carry_Idle_Up", 0, 1, 0.25f, true);
	PlayerRenderer_->CreateAnimation("Link_Carry_Idle_Down.bmp", "Carry_Idle_Down", 0, 1, 0.25f, true);

	PlayerRenderer_->CreateAnimation("Link_Carry_Move_Right.bmp", "Carry_Move_Right", 0, 1, 0.1f, true);
	PlayerRenderer_->CreateAnimation("Link_Carry_Move_Left.bmp", "Carry_Move_Left", 0, 1, 0.1f, true);
	PlayerRenderer_->CreateAnimation("Link_Carry_Move_Up.bmp", "Carry_Move_Up", 0, 4, 0.1f, true);
	PlayerRenderer_->CreateAnimation("Link_Carry_Move_Down.bmp", "Carry_Move_Down", 0, 4, 0.1f, true);

	int a = PlayerRenderer_->GetOrder();
	PlayerRenderer_->ChangeAnimation("Idle_Down");

	//�Ʒ����� ���� ���������� �� ������ ���´�
	//CreateRenderer("LinkStandStill.bmp");
	//CreateRendererToScale("HPBAR.bmp", float4(100.0f, 20.0f), RenderPivot::CENTER, {0, -100});
	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		//�̶� �빮�ڿ��� �Ѵ�
		GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("MoveUp", 'W');
		GameEngineInput::GetInst()->CreateKey("MoveDown", 'S');
		GameEngineInput::GetInst()->CreateKey("Attack", 'K');
		GameEngineInput::GetInst()->CreateKey("InterAct", 'L');
		GameEngineInput::GetInst()->CreateKey("Debug", '9');



	}
	MapColImage_ = GameEngineImageManager::GetInst()->Find("EastPalace1F_1_1F_ColMap.bmp");

	if (nullptr == MapColImage_)
	{
		MsgBoxAssert("�浹�� ���� ã�� ���߽��ϴ�");
	}

	MapPasImage_ = GameEngineImageManager::GetInst()->Find("EastPalace1F_1_1F_PasMap.bmp");

	if (nullptr == MapPasImage_)
	{
		MsgBoxAssert("��� ���� ã�� ���߽��ϴ�");
	}

	RoomSize_[0] = { 2048, 4063 };
	RoomSize_[1] = { 4095, 3088 };
}
 
void PlayerLink::Update()
{
	if (GameEngineInput::GetInst()->IsDown("Debug"))
	{
		GetLevel()->IsDebugModeSwitch();
	}
	PlayerStateUpdate();
	CameraStateUpdate();
	//�ִϸ��̼� ������ �ޱ�
	CurrentAnimationFrame_ = PlayerRenderer_->GetCurrentAnimationFrame();
	BlinkUpdate();
	
	float4 Postion = GetPosition();

	//��� ��� ����

	//{
	//	if (true == GameEngineInput::GetInst()->IsDown("Fire"))
	//	{
	//		Boomerang* Ptr = GetLevel()->CreateActor<Boomerang>((int)PlayLevelOrder::PLAYER);
	//		Ptr->SetPosition(GetPosition());
	//	}
	//}	
	
	//3016,3468 48x40
	//3040,3488
	//�浹 ����
	{
		std::vector<GameEngineCollision*> ColList;

		if (true == PlayerCollision_->CollisionResult("Switch", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			Map1F::Room1TopDoor0->ChangeAnimation("Open_Top");
			IsPlayerCanPassDoor_;
			ColList[0]->Death();
		}
	}

}
//�������� �� ���� ���͵��� �����Լ��� ȣ���Ѵ�
void PlayerLink::Render()
{

}

bool PlayerLink::IsMoveKeyFree()
{
	if (false == GameEngineInput::GetInst()->IsPress("MoveRight") &&
		false == GameEngineInput::GetInst()->IsPress("MoveLeft") &&
		false == GameEngineInput::GetInst()->IsPress("MoveUp") &&
		false == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		return true;
	}

	return false;
}

bool PlayerLink::IsRightMoveKey()
{
	if (true == GameEngineInput::GetInst()->IsDown("MoveRight"))
	{
		return true;
	}

	return false;
}

bool PlayerLink::IsLeftMoveKey()
{
	if (true == GameEngineInput::GetInst()->IsDown("MoveLeft"))
	{
		return true;
	}

	return false;
}

bool PlayerLink::IsUpMoveKey()
{
	if (true == GameEngineInput::GetInst()->IsDown("MoveUp"))
	{
		return true;
	}

	return false;
}

bool PlayerLink::IsDownMoveKey()
{
	if (true == GameEngineInput::GetInst()->IsDown("MoveDown"))
	{
		return true;
	}

	return false;
}

void PlayerLink::CameraUpdate()
{
	{
		GetLevel()->SetCameraPos(GetPosition() - GameEngineWindow::GetInst().GetScale().Half());
		float4 CurCameraPos = GetLevel()->GetCameraPos();

		if (RoomSize_[0].x > CurCameraPos.x)
		{
			CurCameraPos.x = RoomSize_[0].x;
			GetLevel()->SetCameraPos(CurCameraPos);
		}

		if (RoomSize_[0].y - GameEngineWindow::GetInst().GetScale().y < CurCameraPos.y)
		{
			int a = 0;
			CurCameraPos.y = RoomSize_[0].y - GameEngineWindow::GetInst().GetScale().y;
			GetLevel()->SetCameraPos(CurCameraPos);
		}


		if (RoomSize_[1].x - GameEngineWindow::GetInst().GetScale().x < CurCameraPos.x)
		{
			CurCameraPos.x = RoomSize_[1].x - GameEngineWindow::GetScale().x;
			GetLevel()->SetCameraPos(CurCameraPos);
		}

		if (RoomSize_[1].y > CurCameraPos.y)
		{
			CurCameraPos.y = RoomSize_[1].y;
			GetLevel()->SetCameraPos(CurCameraPos);
		}
	}
}

void PlayerLink::CameraStateChange(CameraState _State)
{
	if (CameraState_ != _State)
	{
		switch (_State)
		{
		case CameraState::Room1:
			Room1Start();
			break;
		case CameraState::Room1_Trans:
			Room1_Trans_Start();
			break;
		case CameraState::Room2:
			Room2Start();
			break;
		case CameraState::Room2_Trans:
			Room2_Trans_Start();
			break;
		case CameraState::Room3:
			Room3Start();
			break;
		case CameraState::Room3_Trans:
			Room3_Trans_Start();
			break;
		case CameraState::Max:
			break;
		default:
			break;
		}
	}
	CameraState_ = _State;
}

void PlayerLink::CameraStateUpdate()
{
	switch (CameraState_)
	{
	case CameraState::Room1:
		Room1Update();
		break;
	case CameraState::Room1_Trans:
		Room1_Trans_Update();
		break;
	case CameraState::Room2:
		Room2Update();
		break;
	case CameraState::Room2_Trans:
		Room2_Trans_Update();
		break;
	case CameraState::Room3:
		Room3Update();
		break;
	case CameraState::Room3_Trans:
		Room3_Trans_Update();
		break;
	case CameraState::Max:
		break;
	default:
		break;
	}
}

bool PlayerLink::PosOrColorCheck(int _Color, GameEngineImage* _Image)
{
	float4 MyPos = GetPosition();
	float4 MyPosTopRight = MyPos + float4{ 32.0f, -21.0f };
	float4 MyPosTopLeft = MyPos + float4{ -32.0f, -21.0f };
	float4 MyPosBotRight = MyPos + float4{ 32.0f, 43.0f };
	float4 MyPosBotLeft = MyPos + float4{ -32.0f, 43.0f };
	float4 MyPosRight = MyPos + float4{ +32.0f,  0.0f };
	float4 MyPosLeft = MyPos + float4{ -32.0f, 0.0f };
	float4 MyPosTop = MyPos + float4{ 0.0f, -21.0f };
	float4 MyPosBot = MyPos + float4{ 0.0f, 43.0f };

	int ColorTopRight = _Image->GetImagePixel(MyPosTopRight);
	int ColorTopLeft = _Image->GetImagePixel(MyPosTopLeft);
	int ColorBotRight = _Image->GetImagePixel(MyPosBotRight);
	int ColorBotLeft = _Image->GetImagePixel(MyPosBotLeft);
	int ColorRight = _Image->GetImagePixel(MyPosRight);
	int ColorLeft = _Image->GetImagePixel(MyPosLeft);
	int ColorTop = _Image->GetImagePixel(MyPosTop);
	int ColorBot = _Image->GetImagePixel(MyPosBot);
	if (_Color == ColorTopRight ||
		_Color == ColorTopLeft ||
		_Color == ColorBotRight ||
		_Color == ColorBotLeft ||
		_Color == ColorRight ||
		_Color == ColorLeft ||
		_Color == ColorBot ||
		_Color == ColorTop)
	{
		return true;
	}
	return false;
}

bool PlayerLink::PosAndColorCheck(int _Color, GameEngineImage* _Image)
{
	float4 MyPos = GetPosition();
	float4 MyPosTopRight = MyPos + float4{ 32.0f, -21.0f };
	float4 MyPosTopLeft = MyPos + float4{ -32.0f, -21.0f };
	float4 MyPosBotRight = MyPos + float4{ 32.0f, 43.0f };
	float4 MyPosBotLeft = MyPos + float4{ -32.0f, 43.0f };
	float4 MyPosRight = MyPos + float4{ +32.0f,  0.0f };
	float4 MyPosLeft = MyPos + float4{ -32.0f, 0.0f };
	float4 MyPosTop = MyPos + float4{ 0.0f, -21.0f };
	float4 MyPosBot = MyPos + float4{ 0.0f, 43.0f };

	int ColorTopRight = _Image->GetImagePixel(MyPosTopRight);
	int ColorTopLeft = _Image->GetImagePixel(MyPosTopLeft);
	int ColorBotRight = _Image->GetImagePixel(MyPosBotRight);
	int ColorBotLeft = _Image->GetImagePixel(MyPosBotLeft);
	int ColorRight = _Image->GetImagePixel(MyPosRight);
	int ColorLeft = _Image->GetImagePixel(MyPosLeft);
	int ColorTop = _Image->GetImagePixel(MyPosTop);
	int ColorBot = _Image->GetImagePixel(MyPosBot);
	if (_Color != ColorTopRight &&
		_Color != ColorTopLeft &&
		_Color != ColorBotRight &&
		_Color != ColorBotLeft &&
		_Color != ColorRight &&
		_Color != ColorLeft &&
		_Color != ColorBot &&
		_Color != ColorTop)
	{
		return true;
	}
	return false;
}

void PlayerLink::CameraAutoMove()
{
	if (AutoMoveDir_.CompareInt2D(float4::RIGHT))
	{
		float4 CurCameraPos = GetLevel()->GetCameraPos();

		GetLevel()->SetCameraPos(CurCameraPos + AutoMoveDir_ * GameEngineTime::GetDeltaTime() * 800);

		float Time = GameEngineTime::GetDeltaTime();


		if (RoomSize_[0].x < GetLevel()->GetCameraPos().x)
		{
			IsCameraAutoMove_ = false;
		}
	}

	if (AutoMoveDir_.CompareInt2D(float4::LEFT))
	{
		float4 CurCameraPos = GetLevel()->GetCameraPos();

		GetLevel()->SetCameraPos(CurCameraPos + AutoMoveDir_ * GameEngineTime::GetDeltaTime() * 800);

		float Time = GameEngineTime::GetDeltaTime();


		if (RoomSize_[1].x - GameEngineWindow::GetInst().GetScale().x > GetLevel()->GetCameraPos().y)
		{
			IsCameraAutoMove_ = false;
		}
	}
	if (AutoMoveDir_.CompareInt2D(float4::UP))
	{
		float4 CurCameraPos = GetLevel()->GetCameraPos();

		GetLevel()->SetCameraPos(CurCameraPos + AutoMoveDir_ * GameEngineTime::GetDeltaTime() * 800);

		float Time = GameEngineTime::GetDeltaTime();


		if (RoomSize_[0].y - GameEngineWindow::GetInst().GetScale().y > GetLevel()->GetCameraPos().y)
		{
			IsCameraAutoMove_ = false;
		}
	}

	if (AutoMoveDir_.CompareInt2D(float4::DOWN))
	{
		float4 CurCameraPos = GetLevel()->GetCameraPos();

		GetLevel()->SetCameraPos(CurCameraPos + AutoMoveDir_ * GameEngineTime::GetDeltaTime() * 800);

		float Time = GameEngineTime::GetDeltaTime();


		if (RoomSize_[1].y < GetLevel()->GetCameraPos().y)
		{
			IsCameraAutoMove_ = false;
		}
	}


}

bool PlayerLink::IsPlayerMoveState()
{
	if (PlayerState::MoveRight == PlayerCurState_ ||
		PlayerState::MoveLeft == PlayerCurState_ || 
		PlayerState::MoveUp == PlayerCurState_ || 
		PlayerState::MoveDown == PlayerCurState_)
	{
		return true;
	}
	return false;
}

void PlayerLink::PlayerSetIdle()
{

}

void PlayerLink::PlayerAutoMove()
{
	CheckDirection();
	SetMove(AutoMoveDir_ * GameEngineTime::GetDeltaTime() * Speed_);
	int Red = RGB(255, 0, 0);
	if (PosAndColorCheck(Red, MapPasImage_))
	{
		IsCharacterAutoMove_ = false;
	}
}

void PlayerLink::PlayerAutoMove(float _Speed)
{
	CheckDirection();
	SetMove(AutoMoveDir_ * GameEngineTime::GetDeltaTime() * _Speed);
	int Red = RGB(255, 0, 0);
	if (PosAndColorCheck(Red, MapPasImage_))
	{
		IsCharacterAutoMove_ = false;
	}
}

void PlayerLink::CheckDirection()
{
	if (PlayerState::MoveRight == PlayerCurState_)
	{
		AutoMoveDir_ = float4::RIGHT;
	}
	if (PlayerState::MoveLeft == PlayerCurState_)
	{
		AutoMoveDir_ = float4::LEFT;
	}
	if (PlayerState::MoveUp == PlayerCurState_)
	{
		AutoMoveDir_ = float4::UP;
	}
	if (PlayerState::MoveDown == PlayerCurState_)
	{
		AutoMoveDir_ = float4::DOWN;
	}
}

/////////////////////////////////////////////////////////////////////Combat

void PlayerLink::GetDamaged()
{
	Hp_ -= 1;
}

void PlayerLink::BlinkUpdate()
{

	if (true == IsBlink_)
	{
		CurBlinkTime_  += GameEngineTime::GetDeltaTime();
		CurBlinkFreq_ += GameEngineTime::GetDeltaTime();
		if (BlinkFreq_ < CurBlinkFreq_)
		{
			CurBlinkFreq_ = 0.0f;
			if (false == IsAlphaOn_)
			{
				PlayerRenderer_->SetAlpha(255);
				IsAlphaOn_ = true;
			}
			else
			{
				PlayerRenderer_->SetAlpha(0);
				IsAlphaOn_ = false;
			}
		}

		if (BlinkTime_ < CurBlinkTime_)
		{

			IsBlink_ = false;
			CurBlinkTime_ = 0.0f;
			CurBlinkFreq_ = 0.0f;
			IsAlphaOn_ = true;
			PlayerRenderer_->SetAlpha(255);
		}
	}

}


/// //////////////////////////// State Change, Update
 
void PlayerLink::PlayerChangeState(PlayerState _State)
{
	if (PlayerCurState_ != _State)
	{
		switch (_State)
		{
		case PlayerState::IdleRight:
			IdleRightStart();
			break;
		case PlayerState::IdleLeft:
			IdleLeftStart();
			break;
		case PlayerState::IdleUp:
			IdleUpStart();
			break;
		case PlayerState::IdleDown:
			IdleDownStart();
			break;
		case PlayerState::MoveRight:
			MoveRightStart();
			break;
		case PlayerState::MoveLeft:
			MoveLeftStart();
			break;
		case PlayerState::MoveUp:
			MoveUpStart();
			break;
		case PlayerState::MoveDown:
			MoveDownStart();
			break;
		case PlayerState::WieldRight:
			WieldRightStart();
			break;
		case PlayerState::WieldLeft:
			WieldLeftStart();
			break;
		case PlayerState::WieldUp:
			WieldUpStart();
			break;
		case PlayerState::WieldDown:
			WieldDownStart();
			break;
		case PlayerState::DamagedRight:
			DamagedRightStart();
			break;
		case PlayerState::DamagedLeft:
			DamagedLeftStart();
			break;
		case PlayerState::DamagedUp:
			DamagedUpStart();
			break;
		case PlayerState::DamagedDown:
			DamagedDownStart();
			break;
		case PlayerState::CarryStartRight:
			CarryStartRightStart();
			break;
		case PlayerState::CarryStartLeft:
			CarryStartLeftStart();
			break;
		case PlayerState::CarryStartUp:
			CarryStartUpStart();
			break;
		case PlayerState::CarryStartDown:
			CarryStartDownStart();
			break;
		case PlayerState::CarryIdleRight:
			CarryIdleRightStart();
			break;
		case PlayerState::CarryIdleLeft:
			CarryIdleLeftStart();
			break;
		case PlayerState::CarryIdleUp:
			CarryIdleUpStart();
			break;
		case PlayerState::CarryIdleDown:
			CarryIdleDownStart();
			break;
		case PlayerState::CarryMoveRight:
			CarryMoveRightStart();
			break;
		case PlayerState::CarryMoveLeft:
			CarryMoveLeftStart();
			break;
		case PlayerState::CarryMoveUp:
			CarryMoveUpStart();
			break;
		case PlayerState::CarryMoveDown:
			CarryMoveDownStart();
			break;
		case PlayerState::Max:
			break;
		default:
			break;
		}
	}

	PlayerCurState_ = _State;
}

void PlayerLink::PlayerStateUpdate()
{
	switch (PlayerCurState_)
	{
	case PlayerState::IdleRight:
	case PlayerState::IdleLeft:
	case PlayerState::IdleUp:
	case PlayerState::IdleDown:
		IdleUpdate();
		break;
	case PlayerState::MoveRight:
	case PlayerState::MoveLeft:
	case PlayerState::MoveUp:
	case PlayerState::MoveDown:
		MoveUpdate();
		break;
	case PlayerState::WieldRight:
	case PlayerState::WieldLeft:
	case PlayerState::WieldUp:
	case PlayerState::WieldDown:
		WieldUpdate();
		break;
	case PlayerState::DamagedRight:
	case PlayerState::DamagedLeft:
	case PlayerState::DamagedUp:
	case PlayerState::DamagedDown:
		DamagedUpdate();
		break;
	case PlayerState::CarryStartRight:
	case PlayerState::CarryStartLeft:
	case PlayerState::CarryStartUp:
	case PlayerState::CarryStartDown:
		CarryStartUpdate();
		break;
	case PlayerState::CarryIdleRight:
	case PlayerState::CarryIdleLeft:
	case PlayerState::CarryIdleUp:
	case PlayerState::CarryIdleDown:
		CarryIdleUpdate();
		break;
	case PlayerState::CarryMoveRight:
	case PlayerState::CarryMoveLeft:
	case PlayerState::CarryMoveUp:
	case PlayerState::CarryMoveDown:
		CarryMoveUpdate();
		break;
	case PlayerState::Max:
		break;
	default:
		break;
	}
}