#include "PlayerLink.h"
#include <windows.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include "GameEngineContentsEnum.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngineCollision.h>

#include "Map1F.h"
#include "Boomerang.h"

//링크의 크기 == 64x96
//링크 히트박스의 크키 == 64x64


//FIN
//대각선입력 속력 노말라이즈 하기V
//FSM 대입하기V
//걷기애니메이션 추가V
//TODO
//통로 통과 버그 고치기 ( 키 꾹누르면 state가 변화하지 않음)
//공격 애니메이션, 함수 추가
//피격 함수 추가

//통로 세로 길이 384
//통로 가로 길이 320

//파란색 -> 층이동
//노란색 -> 문이동
//빨간색 -> 닫힌 문 이동
PlayerLink::PlayerLink()
	:Speed_(350.0f),
	 PlayerCurState_(PlayerState::DownIdle),
	 CameraState_(CameraState::Room1),
	 IsCameraAutoMove_(false),
	 IsCharacterAutoMove_(false),
	 AutoMoveDir_(float4::ZERO),
	 CurStairs_(StairsState::Top),
	 IsOnStairs_(false)
{
}

PlayerLink::~PlayerLink() 
{
}

void PlayerLink::Start()
{
	//충돌
	PlayerCollision_ = CreateCollision("PlayerHitBox", {64, 64});
	PlayerCollision_->Off();

	//플레이어가 레벨을 시작할때마다 시작 지점이 다르기 때문에 Level에서 위치를 정해줘야한다
	//SetPosition(GameEngineWindow::GetScale().Half());
	PlayerRenderer = CreateRenderer();
	//true 면 루프 false 면 루프아님
	PlayerRenderer->SetPivot({ 0, -11 });

	PlayerRenderer->CreateAnimation("Link_Idle_Right.bmp", "Idle_Right", 0, 1, 0.05f, false);
	PlayerRenderer->CreateAnimation("Link_Idle_Left.bmp", "Idle_Left", 0, 1, 0.05f, false);
	PlayerRenderer->CreateAnimation("Link_Idle_Up.bmp", "Idle_Up", 0, 1, 0.05f, false);
	PlayerRenderer->CreateAnimation("Link_Idle_Down.bmp", "Idle_Down", 0, 1, 0.05f, false);

	PlayerRenderer->CreateAnimation("Link_Walk_Right.bmp", "Walk_Right", 0, 5, 0.05f, true);
	PlayerRenderer->CreateAnimation("Link_Walk_Left.bmp", "Walk_Left", 0, 5, 0.05f, true);
	PlayerRenderer->CreateAnimation("Link_Walk_Up.bmp", "Walk_Up", 0, 7, 0.05f, true);
	PlayerRenderer->CreateAnimation("Link_Walk_Down.bmp", "Walk_Down", 0, 7, 0.05f, true);

	PlayerRenderer->CreateAnimation("Link_Wield_Right.bmp", "Wield_Right", 0, 4, 0.04f, true);
	PlayerRenderer->CreateAnimation("Link_Wield_Left.bmp", "Wield_Left", 0, 4, 0.04f, true);
	PlayerRenderer->CreateAnimation("Link_Wield_Up.bmp", "Wield_Up", 0, 4, 0.04f, true);
	PlayerRenderer->CreateAnimation("Link_Wield_Down.bmp", "Wield_Down", 0, 5, 0.04f, true);

	PlayerRenderer->ChangeAnimation("Idle_Down");

	//아래부터 넣은 렌더러들이 맨 위부터 나온다
	//CreateRenderer("LinkStandStill.bmp");
	//CreateRendererToScale("HPBAR.bmp", float4(100.0f, 20.0f), RenderPivot::CENTER, {0, -100});
	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		//이때 대문자여야 한다
		GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("MoveUp", 'W');
		GameEngineInput::GetInst()->CreateKey("MoveDown", 'S');
		GameEngineInput::GetInst()->CreateKey("Fire", 'K');
		GameEngineInput::GetInst()->CreateKey("Attack", VK_SPACE);
		GameEngineInput::GetInst()->CreateKey("InterAct", VK_LSHIFT);


	}
	MapColImage_ = GameEngineImageManager::GetInst()->Find("EastPalace1F_1_1F_ColMap.bmp");

	if (nullptr == MapColImage_)
	{
		MsgBoxAssert("충돌용 맵을 찾지 못했습니다");
	}

	MapPasImage_ = GameEngineImageManager::GetInst()->Find("EastPalace1F_1_1F_PasMap.bmp");

	if (nullptr == MapPasImage_)
	{
		MsgBoxAssert("통로 맵을 찾지 못했습니다");
	}

	RoomSize_[0] = { 2048, 4063 };
	RoomSize_[1] = { 4095, 3088 };
}
 
void PlayerLink::Update()
{
	CameraStateUpdate();
	PlayerStateUpdate();

	float4 Postion = GetPosition();

	//장비 사용 관련

	//{
	//	if (true == GameEngineInput::GetInst()->IsDown("Fire"))
	//	{
	//		Boomerang* Ptr = GetLevel()->CreateActor<Boomerang>((int)PlayLevelOrder::PLAYER);
	//		Ptr->SetPosition(GetPosition());
	//	}
	//}	
	
	//3016,3468 48x40
	//3040,3488
	//충돌 관련
	{
		std::vector<GameEngineCollision*> ColList;

		if (true == PlayerCollision_->CollisionResult("Switch", ColList, CollisionType::Rect, CollisionType::Rect))
		{
			for (size_t i = 0; i < ColList.size(); i++)
			{
				Map1F::TopDoor1->ChangeAnimation("Top");
				ColList[i]->Death();
			}

			int a = 0;
		}
	}

}
//렌더러가 다 돌고 액터들의 랜더함수를 호출한다
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

void PlayerLink::PlayerChangeState(PlayerState _State)
{
	if (PlayerCurState_ != _State)
	{
		switch (_State)
		{
		case PlayerState::RightIdle:
			IdleRightStart();
			break;
		case PlayerState::LeftIdle:
			IdleLeftStart();
			break;
		case PlayerState::UpIdle:
			IdleUpStart();
			break;
		case PlayerState::DownIdle:
			IdleDownStart();
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
	case PlayerState::RightIdle:
	case PlayerState::LeftIdle:
	case PlayerState::UpIdle:
	case PlayerState::DownIdle:
		IdleUpdate();
		break;
	case PlayerState::WieldRight:
	case PlayerState::WieldLeft:
	case PlayerState::WieldUp:
	case PlayerState::WieldDown:
		WieldUpdate();
		break;
	case PlayerState::MoveRight:
		MoveUpdate();
		break;
	case PlayerState::MoveLeft:
		MoveUpdate();
		break;
	case PlayerState::MoveUp:
		MoveUpdate();
		break;
	case PlayerState::MoveDown:
		MoveUpdate();
		break;
	case PlayerState::Max:
		break;
	default:
		break;
	}
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
		case CameraState::Room2:
			Room2Start();
			break;
		case CameraState::Room3:
			Room3Start();
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
	case CameraState::Room2:
		Room2Update();
		break;
	case CameraState::Room3:
		Room3Update();
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
	float4 MyPosTopRight = MyPos + float4{ 32.0f, -32.0f };
	float4 MyPosTopLeft = MyPos + float4{ -32.0f, -32.0f };
	float4 MyPosBotRight = MyPos + float4{ 32.0f, 32.0f };
	float4 MyPosBotLeft = MyPos + float4{ -32.0f, 32.0f };
	float4 MyPosRight = MyPos + float4{ +32.0f,  0.0f };
	float4 MyPosLeft = MyPos + float4{ -32.0f, 0.0f };
	float4 MyPosTop = MyPos + float4{ 0.0f, -32.0f };
	float4 MyPosBot = MyPos + float4{ 0.0f, 32.0f };

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
	float4 MyPosTopRight = MyPos + float4{ 32.0f, -32.0f };
	float4 MyPosTopLeft = MyPos + float4{ -32.0f, -32.0f };
	float4 MyPosBotRight = MyPos + float4{ 32.0f, 32.0f };
	float4 MyPosBotLeft = MyPos + float4{ -32.0f, 32.0f };
	float4 MyPosRight = MyPos + float4{ +32.0f,  0.0f };
	float4 MyPosLeft = MyPos + float4{ -32.0f, 0.0f };
	float4 MyPosTop = MyPos + float4{ 0.0f, -32.0f };
	float4 MyPosBot = MyPos + float4{ 0.0f, 32.0f };

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
