#include "PlayerLink.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>

#include <GameEngine/GameEngineLevel.h> // 레벨을 통해서
#include "PlayMap1F.h"

void PlayerLink::IdleUpdate()
{
	if (true == IsRightMoveKey())
	{
		PlayerChangeState(PlayerState::MoveRight);
		return;
	}

	if (true == IsLeftMoveKey())
	{
		PlayerChangeState(PlayerState::MoveLeft);
		return;
	}

	if (true == IsUpMoveKey())
	{
		PlayerChangeState(PlayerState::MoveUp);
		return;
	}

	if (true == IsDownMoveKey())
	{
		PlayerChangeState(PlayerState::MoveDown);
		return;
	}


	if (true == GameEngineInput::GetInst()->IsDown("Fire"))
	{
		PlayerChangeState(PlayerState::Attack);
		return;
	}
}

void PlayerLink::AttackUpdate()
{

}

//////////////////////////////////////// State

void PlayerLink::IdleRightStart()
{
	// 애니메이션이 바뀐다.
	PlayerRenderer->ChangeAnimation("Idle_Right");
}

void PlayerLink::IdleLeftStart()
{
	// 애니메이션이 바뀐다.
	PlayerRenderer->ChangeAnimation("Idle_Left");
}

void PlayerLink::IdleUpStart()
{
	// 애니메이션이 바뀐다.
	PlayerRenderer->ChangeAnimation("Idle_Up");
}

void PlayerLink::IdleDownStart()
{
	// 애니메이션이 바뀐다.
	PlayerRenderer->ChangeAnimation("Idle_Down");

}

void PlayerLink::MoveRightStart()
{
	PlayerRenderer->ChangeAnimation("Walk_Right");
}

void PlayerLink::MoveLeftStart()
{
	PlayerRenderer->ChangeAnimation("Walk_Left");
}


void PlayerLink::MoveUpStart()
{
	PlayerRenderer->ChangeAnimation("Walk_Up");
}

void PlayerLink::MoveDownStart()
{
	PlayerRenderer->ChangeAnimation("Walk_Down");
}


void PlayerLink::MoveUpdate()
{
	if (false == IsCharacterAutoMove_)
	{
		MoveFunction();
		/// ///////////////////////////////////////////////////////////Right
		if (false == GameEngineInput::GetInst()->IsPress("MoveUp") &&
			false == GameEngineInput::GetInst()->IsPress("MoveDown") &&
			true == IsRightMoveKey())
		{
			PlayerChangeState(PlayerState::MoveRight);
			return;
		}

		if (true == GameEngineInput::GetInst()->IsUp("MoveUp") ||
			true == GameEngineInput::GetInst()->IsUp("MoveDown"))
		{
			if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
			{
				PlayerChangeState(PlayerState::MoveRight);
				return;
			}
		}
		/// ///////////////////////////////////////////////////////////Left
		if (false == GameEngineInput::GetInst()->IsPress("MoveUp") &&
			false == GameEngineInput::GetInst()->IsPress("MoveDown") &&
			true == IsLeftMoveKey())
		{
			PlayerChangeState(PlayerState::MoveLeft);
			return;
		}

		if (true == GameEngineInput::GetInst()->IsUp("MoveUp") ||
			true == GameEngineInput::GetInst()->IsUp("MoveDown"))
		{
			if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
			{
				PlayerChangeState(PlayerState::MoveLeft);
				return;
			}
		}
		/// ///////////////////////////////////////////////////////////Up
		if (false == GameEngineInput::GetInst()->IsPress("MoveRight") &&
			false == GameEngineInput::GetInst()->IsPress("MoveLeft") &&
			true == IsUpMoveKey())
		{
			PlayerChangeState(PlayerState::MoveUp);
			return;
		}

		if (true == GameEngineInput::GetInst()->IsUp("MoveRight") ||
			true == GameEngineInput::GetInst()->IsUp("MoveLeft"))
		{
			if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
			{
				PlayerChangeState(PlayerState::MoveUp);
				return;
			}
		}
		/// ///////////////////////////////////////////////////////////Down
		if (
			false == GameEngineInput::GetInst()->IsPress("MoveRight") &&
			false == GameEngineInput::GetInst()->IsPress("MoveLeft") &&
			true == IsDownMoveKey())
		{
			PlayerChangeState(PlayerState::MoveDown);
			return;
		}

		if (true == GameEngineInput::GetInst()->IsUp("MoveRight") ||
			true == GameEngineInput::GetInst()->IsUp("MoveLeft"))
		{
			if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
			{
				PlayerChangeState(PlayerState::MoveDown);
				return;
			}
		}
		/// ///////////////////////////////////////////////////////////Idle
		if (true == IsMoveKeyFree() && GameEngineInput::GetInst()->IsUp("MoveRight"))
		{
			PlayerChangeState(PlayerState::RightIdle);
			return;
		}

		if (true == IsMoveKeyFree() && GameEngineInput::GetInst()->IsUp("MoveLeft"))
		{
			PlayerChangeState(PlayerState::LeftIdle);
			return;
		}

		if (true == IsMoveKeyFree() && GameEngineInput::GetInst()->IsUp("MoveUp"))
		{
			PlayerChangeState(PlayerState::UpIdle);
			return;
		}

		if (true == IsMoveKeyFree() && GameEngineInput::GetInst()->IsUp("MoveDown"))
		{
			PlayerChangeState(PlayerState::DownIdle);
			return;
		}
	}
}

void PlayerLink::MoveFunction()
{
	float4 CheckPos;
	float4 MoveDir = float4::ZERO;
	//맵 이미지와 캐릭터의 이미지의 픽셀 위치를 동일하게 맞춰놔야한다
	bool MoveLeft = false;
	bool MoveRight = false;
	bool MoveUp = false;
	bool MoveDown = false;

	//float DeltaTime = GameEngineTime::GetInst()->GetDeltaTime()
	//내가 키를 누르고있다면 움직이기
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir += float4::LEFT;
		MoveLeft = true;
		//SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir += float4::RIGHT;
		MoveRight = true;
		//SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		MoveDir += float4::UP;
		MoveUp = true;
		//SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		MoveDir += float4::DOWN;
		MoveDown = true;
		//SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	}

	//SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
	{
		int Black = RGB(0, 0, 0);
		float4 MyPos = GetPosition();
		float4 MyPosTopRight = MyPos + float4{ 32.0f, -32.0f };
		float4 MyPosTopLeft = MyPos + float4{ -32.0f, -32.0f };
		float4 MyPosBotRight = MyPos + float4{ 32.0f, 32.0f };
		float4 MyPosBotLeft = MyPos + float4{ -32.0f, 32.0f };
		float4 NextPos = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		float4 CheckPosTopRight = NextPos + float4{ 32.0f, -32.0f };
		float4 CheckPosTopLeft = NextPos + float4{ -32.0f, -32.0f };
		float4 CheckPosBotRight = NextPos + float4{ 32.0f, 32.0f };
		float4 CheckPosBotLeft = NextPos + float4{ -32.0f, 32.0f };
		float4 CheckPosRight = NextPos + float4{ 32.0f, 0.0f };
		float4 CheckPosLeft = NextPos + float4{ -32.0f, 0.0f };
		float4 CheckPosTop = NextPos + float4{ 0.0f, -32.0f };
		float4 CheckPosBot = NextPos + float4{ 0.0f, 32.0f };


		int ColorTopRight = MapColImage_->GetImagePixel(CheckPosTopRight);
		int ColorTopLeft = MapColImage_->GetImagePixel(CheckPosTopLeft);
		int ColorBotRight = MapColImage_->GetImagePixel(CheckPosBotRight);
		int ColorBotLeft = MapColImage_->GetImagePixel(CheckPosBotLeft);
		if (Black != ColorTopRight &&
			Black != ColorTopLeft &&
			Black != ColorBotRight &&
			Black != ColorBotLeft)
		{
			SetMove(MoveDir * GameEngineTime::GetDeltaTime() * Speed_);
		}
		else
		{
			if (true == MoveLeft)
			{
				if (Black != MapColImage_->GetImagePixel({ MyPosTopLeft.x + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_).x, MyPosTopLeft.y }) &&
					Black != MapColImage_->GetImagePixel({ MyPosBotLeft.x + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_).x, MyPosBotLeft.y }))
				{
					SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * Speed_);
				}

				if (Black != MapColImage_->GetImagePixel(CheckPosLeft) &&
					Black != MapColImage_->GetImagePixel(CheckPosTopLeft) &&
					Black != MapColImage_->GetImagePixel(CheckPosTopRight) &&
					Black != MapColImage_->GetImagePixel(CheckPosBotRight))
				{
					if (false == MoveUp)
					{
						SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
					}
				}
				if (Black != MapColImage_->GetImagePixel(CheckPosLeft) &&
					Black != MapColImage_->GetImagePixel(CheckPosBotLeft) &&
					Black != MapColImage_->GetImagePixel(CheckPosTopRight) &&
					Black != MapColImage_->GetImagePixel(CheckPosBotRight))
				{
					if (false == MoveDown)
					{
						SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);
					}
				}
			}

			if (true == MoveRight)
			{
				if (Black != MapColImage_->GetImagePixel({ MyPosTopRight.x + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_).x, MyPosTopRight.y }) &&
					Black != MapColImage_->GetImagePixel({ MyPosBotRight.x + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_).x, MyPosBotRight.y }))
				{
					SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * Speed_);
				}

				if (Black != MapColImage_->GetImagePixel(CheckPosRight) &&
					Black != MapColImage_->GetImagePixel(CheckPosTopRight) &&
					Black != MapColImage_->GetImagePixel(CheckPosTopLeft) &&
					Black != MapColImage_->GetImagePixel(CheckPosBotLeft))
				{
					if (false == MoveUp)
					{
						SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
					}
				}
				if (Black != MapColImage_->GetImagePixel(CheckPosRight) &&
					Black != MapColImage_->GetImagePixel(CheckPosBotRight) &&
					Black != MapColImage_->GetImagePixel(CheckPosTopLeft) &&
					Black != MapColImage_->GetImagePixel(CheckPosBotLeft))
				{
					if (false == MoveDown)
					{
						SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);
					}
				}
			}

			if (true == MoveUp)
			{
				if (Black != MapColImage_->GetImagePixel({ MyPosTopRight.x, MyPosTopRight.y + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_).y }) &&
					Black != MapColImage_->GetImagePixel({ MyPosTopLeft.x, MyPosTopLeft.y + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_).y }))
				{
					SetMove(float4::UP * GameEngineTime::GetDeltaTime() * Speed_);
				}

				if (Black != MapColImage_->GetImagePixel(CheckPosTop) &&
					Black != MapColImage_->GetImagePixel(CheckPosTopRight) &&
					Black != MapColImage_->GetImagePixel(CheckPosBotRight) &&
					Black != MapColImage_->GetImagePixel(CheckPosBotLeft))
				{
					if (false == MoveRight)
					{
						SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * Speed_);
					}
				}

				if (Black != MapColImage_->GetImagePixel(CheckPosTop) &&
					Black != MapColImage_->GetImagePixel(CheckPosTopLeft) &&
					Black != MapColImage_->GetImagePixel(CheckPosBotRight) &&
					Black != MapColImage_->GetImagePixel(CheckPosBotLeft))
				{
					if (false == MoveLeft)
					{
						SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * Speed_);
					}
				}
			}

			if (true == MoveDown)
			{
				if (Black != MapColImage_->GetImagePixel({ MyPosBotRight.x, MyPosBotRight.y + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_).y }) &&
					Black != MapColImage_->GetImagePixel({ MyPosBotLeft.x, MyPosBotLeft.y + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_).y }))
				{
					SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_);
				}

				if (Black != MapColImage_->GetImagePixel(CheckPosBot) &&
					Black != MapColImage_->GetImagePixel(CheckPosBotRight) &&
					Black != MapColImage_->GetImagePixel(CheckPosTopRight) &&
					Black != MapColImage_->GetImagePixel(CheckPosTopLeft))
				{
					if (false == MoveRight)
					{
						SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime() * Speed_);
					}
				}

				if (Black != MapColImage_->GetImagePixel(CheckPosBot) &&
					Black != MapColImage_->GetImagePixel(CheckPosBotLeft) &&
					Black != MapColImage_->GetImagePixel(CheckPosTopRight) &&
					Black != MapColImage_->GetImagePixel(CheckPosTopLeft))
				{
					if (false == MoveLeft)
					{
						SetMove(float4::LEFT * GameEngineTime::GetDeltaTime() * Speed_);
					}
				}

			}
		}

	}
}

void PlayerLink::AttackStart()
{

}

void PlayerLink::Room1Start()
{
	RoomSize_[0] = { 2048, 4063 };
	RoomSize_[1] = { 4095, 3088 };
	IsCameraAutoMove_ = true;
	IsCharacterAutoMove_ = true;
}

void PlayerLink::Room1Update()
{
	/// ///////////////////////////////////////// Room Transition
	if (true == IsCameraAutoMove_)
	{
		CameraAutoMove();
	}

	if (true == IsCharacterAutoMove_)
	{
		PlayerAutoMove();
	}

	/// ///////////////////////////////////////// Room Check
	int Red = RGB(255, 0, 0);
	int Yellow = RGB(255, 255, 0);
	if (PosOrColorCheck(Red, MapColImage_) && PlayerState::MoveUp == PlayerCurState_ && false == IsCharacterAutoMove_)
	{
		AutoMoveDir_ = float4::UP;
		CameraStateChange(CameraState::Room2);
		return;
	}

	if (PosOrColorCheck(Yellow, MapColImage_) && PlayerState::MoveUp == PlayerCurState_ && false == IsCharacterAutoMove_)
	{
		AutoMoveDir_ = float4::UP;
		CameraStateChange(CameraState::Room2);
		return;
	}

	/// ///////////////////////////////////////// CameraUpdate
	if (false == IsCameraAutoMove_)
	{
		CameraUpdate();
	}
}

void PlayerLink::Room2Start()
{
	IsCameraAutoMove_ = true;
	IsCharacterAutoMove_ = true;
	RoomSize_[0] = { 2048, 2983 };
	RoomSize_[1] = { 4095, 2019 };
}

void PlayerLink::Room2Update()
{
	/// ///////////////////////////////////////// Room Transition
	if (true == IsCameraAutoMove_)
	{
		CameraAutoMove();
	}

	if (true == IsCharacterAutoMove_)
	{
		PlayerAutoMove();
	}

	/// ///////////////////////////////////////// Room Check
	int Red = RGB(255, 0, 0);
	int Yellow = RGB(255, 255, 0);

	if (PosOrColorCheck(Red, MapColImage_) && PlayerState::MoveDown == PlayerCurState_ && false == IsCharacterAutoMove_)
	{
		AutoMoveDir_ = float4::DOWN;
		CameraStateChange(CameraState::Room1);
		return;
	}

	if (PosOrColorCheck(Yellow, MapColImage_) && PlayerState::MoveDown == PlayerCurState_ && false == IsCharacterAutoMove_)
	{
		AutoMoveDir_ = float4::DOWN;
		CameraStateChange(CameraState::Room1);
		return;
	}

	if (PosOrColorCheck(Red, MapColImage_) && PlayerState::MoveUp == PlayerCurState_ && false == IsCharacterAutoMove_)
	{
		AutoMoveDir_ = float4::UP;
		CameraStateChange(CameraState::Room3);
		return;
	}


	/// ///////////////////////////////////////// CameraUpdate
	if (false == IsCameraAutoMove_)
	{
		CameraUpdate();
	}
}

void PlayerLink::Room3Start()
{
	IsCameraAutoMove_ = true;
	IsCharacterAutoMove_ = true;
	RoomSize_[0] = { 2048, 1955 };
	RoomSize_[1] = { 4095, 0 };
}

void PlayerLink::Room3Update()
{
	/// ///////////////////////////////////////// Room Transition
	if (true == IsCameraAutoMove_)
	{
		CameraAutoMove();
	}

	if (false == IsCameraAutoMove_)
	{
		CameraUpdate();
	}

	if (true == IsCharacterAutoMove_)
	{
		if (true == IsOnStairs_)
		{
			PlayerAutoMove(150.0f);
			return;
		}

		if (false == IsOnStairs_)
		{
			PlayerAutoMove();
			return;
		}
	}

	/// ///////////////////////////////////////// Room Check
	int Red = RGB(255, 0, 0);
	int Yellow = RGB(255, 255, 0);
	int Blue = RGB(0, 0, 255);

	if (PosOrColorCheck(Yellow, MapColImage_) && PlayerState::MoveUp == PlayerCurState_ )
	{
		AutoMoveDir_ = float4::UP;
		CameraStateChange(CameraState::Room7);
		return;
	}

	if (PosOrColorCheck(Yellow, MapColImage_) && PlayerState::MoveLeft == PlayerCurState_)
	{
		AutoMoveDir_ = float4::LEFT;
		CameraStateChange(CameraState::Room4);
		return;
	}

	if (PosOrColorCheck(Yellow, MapColImage_) && PlayerState::MoveRight == PlayerCurState_)
	{
		AutoMoveDir_ = float4::RIGHT;
		CameraStateChange(CameraState::Room5);
		return;
	}

	if (PosOrColorCheck(Blue, MapColImage_))
	{


		if (StairsState::Top == CurStairs_)
		{
			MapColImage_ = GameEngineImageManager::GetInst()->Find("EastPalace1F_1_B1F_ColMap.bmp");
			CurStairs_ = StairsState::Bot;
			IsCharacterAutoMove_ = true;
			IsOnStairs_ = true;
			return;
		}

		if (StairsState::Bot == CurStairs_)
		{
			MapColImage_ = GameEngineImageManager::GetInst()->Find("EastPalace1F_1_1F_ColMap.bmp");
			CurStairs_ = StairsState::Top;
			IsCharacterAutoMove_ = true;
			IsOnStairs_ = true;
			return;
		}
	}
}