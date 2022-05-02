#include "PlayerLink.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineLevel.h> // 레벨을 통해서
#include <GameEngine/GameEngineCollision.h>
#include "Map1F_2.h"
#include "GameEngineContentsEnum.h"
#include "Map1FBridge.h"

/// ///////////////////////////////////// Room State

void PlayerLink::Room1Start()
{
	Map1F_2::Room1TopDoor0_->On();
	Map1F_2::Room1TopDoor0_->ChangeAnimationReset("Close_Top");
	GameEngineTime::GetInst()->SetTimeScale(1, 1.0f);
}

void PlayerLink::Room1Update()
{

	/// ///////////////////////////////////////// Room Check
	int Red = RGB(255, 0, 0);
	int Yellow = RGB(255, 255, 0);
	if (PosOrColorCheck(Red, MapColImage_) && PlayerState::MoveUp == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_)
	{
		PrevCameraState_ = CameraState::Room1;
		AutoMoveDir_ = float4::UP;
		CameraStateChange(CameraState::Room2_Trans);
		return;
	}

	if (PosOrColorCheck(Yellow, MapColImage_) && PlayerState::MoveUp == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_)
	{
		PrevCameraState_ = CameraState::Room1;
		AutoMoveDir_ = float4::UP;
		CameraStateChange(CameraState::Room2_Trans);
		return;
	}
	/// ///////////////////////////////////////// CameraUpdate
	if (false == IsCameraAutoMove_)
	{
		CameraUpdate();
	}

}

void PlayerLink::Room1_Trans_Start()
{
	Map1F_2::Room1TopDoor0_->Off();
	GameEngineTime::GetInst()->SetTimeScale(2, 0.0f);
	RoomSize_[0] = { 2048, 4063 + 4128 };
	RoomSize_[1] = { 4095, 3088 + 4128 };
	IsCameraAutoMove_ = true;
	IsCharacterAutoMove_ = true;
}

void PlayerLink::Room1_Trans_Update()
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

	if (false == IsCameraAutoMove_ && false == IsCharacterAutoMove_)
	{
		CameraStateChange(CameraState::Room1);
	}
}

void PlayerLink::Room2Start()
{
	Map1F_2::Room2TopDoor0_->On();
	Map1F_2::Room2BotDoor0_->On();
	Map1F_2::Room2TopDoor0_->ChangeAnimationReset("Close_Top");
	Map1F_2::Room2BotDoor0_->ChangeAnimationReset("Close_Bot");
	GameEngineTime::GetInst()->SetTimeScale(2, 1.0f);
}

void PlayerLink::Room2Update()
{
	/// ///////////////////////////////////////// Room Check
	int Red = RGB(255, 0, 0);
	int Yellow = RGB(255, 255, 0);

	if (true == PosOrColorCheck(Red, MapColImage_) && PlayerState::MoveDown == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_)
	{
		PrevCameraState_ = CameraState::Room2;
		AutoMoveDir_ = float4::DOWN;
		CameraStateChange(CameraState::Room1_Trans);
		return;
	}

	if (PosOrColorCheck(Yellow, MapColImage_) && PlayerState::MoveDown == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_)
	{
		PrevCameraState_ = CameraState::Room2;
		AutoMoveDir_ = float4::DOWN;
		CameraStateChange(CameraState::Room1_Trans);
		return;
	}

	if (PosOrColorCheck(Red, MapColImage_) && PlayerState::MoveUp == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_)
	{
		PrevCameraState_ = CameraState::Room2;
		AutoMoveDir_ = float4::UP;
		CameraStateChange(CameraState::Room4_Trans);
		return;
	}


	/// ///////////////////////////////////////// CameraUpdate
	if (false == IsCameraAutoMove_)
	{
		CameraUpdate();
	}
}

void PlayerLink::Room2_Trans_Start()
{
	Map1F_2::Room2TopDoor0_->Off();
	Map1F_2::Room2BotDoor0_->Off();
	GameEngineTime::GetInst()->SetTimeScale(1, 0.0f);
	GameEngineTime::GetInst()->SetTimeScale(4, 0.0f);
	IsCameraAutoMove_ = true;
	IsCharacterAutoMove_ = true;
	RoomSize_[0] = { 2048, 2983 + 4128 };
	RoomSize_[1] = { 4095, 2019 + 4128 };
}

void PlayerLink::Room2_Trans_Update()
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

	if (false == IsCameraAutoMove_ && false == IsCharacterAutoMove_)
	{
		CameraStateChange(CameraState::Room2);
	}

}

void PlayerLink::Room4Start()
{
	GameEngineTime::GetInst()->SetTimeScale(2, 0.0f);
	GameEngineTime::GetInst()->SetTimeScale(4, 0.0f);
	GameEngineTime::GetInst()->SetTimeScale(5, 0.0f);
	GameEngineTime::GetInst()->SetTimeScale(10, 0.0f);

	GameEngineTime::GetInst()->SetTimeScale(-1, 1.0f);
	GameEngineTime::GetInst()->SetTimeScale(0, 1.0f);
	GameEngineTime::GetInst()->SetTimeScale(4, 1.0f);
}

void PlayerLink::Room4Update()
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
			GameEngineTime::GetInst()->SetTimeScale(4, 0.0f);
			PlayerAutoMove(150.0f);
			return;
		}

		if (false == IsOnStairs_)
		{
			GameEngineTime::GetInst()->SetTimeScale(4, 0.0f);
			PlayerAutoMove();
			return;
		}
	}
	else
	{
		GameEngineTime::GetInst()->SetTimeScale(4, 1.0f);
	}
	

	/// ///////////////////////////////////////// Room Check
	int Red = RGB(255, 0, 0);
	int Yellow = RGB(255, 255, 0);
	int Blue = RGB(0, 0, 255);

	if (PosOrColorCheck(Yellow, MapColImage_) && PlayerState::MoveUp == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_)
	{
		PrevCameraState_ = CameraState::Room4;
		AutoMoveDir_ = float4::UP;
		CameraStateChange(CameraState::Room10_Trans);
		return;
	}

	if (PosOrColorCheck(Yellow, MapColImage_) && PlayerState::MoveLeft == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_)
	{
		PrevCameraState_ = CameraState::Room4;
		AutoMoveDir_ = float4::LEFT;
		CameraStateChange(CameraState::Room3_Trans);
		return;
	}

	if (PosOrColorCheck(Yellow, MapColImage_) && PlayerState::MoveRight == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_)
	{
		PrevCameraState_ = CameraState::Room4;
		AutoMoveDir_ = float4::RIGHT;
		CameraStateChange(CameraState::Room5_Trans);
		return;
	}

	if (PosOrColorCheck(Red, MapColImage_) && PlayerState::MoveDown == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_)
	{
		PrevCameraState_ = CameraState::Room4;
		AutoMoveDir_ = float4::DOWN;
		CameraStateChange(CameraState::Room2_Trans);
		return;
	}

	if (PosOrColorCheck(Blue, MapColImage_) && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_)
	{

		if (PlayerStairsState::Top == CurStairs_)
		{
			MapColImage_ = GameEngineImageManager::GetInst()->Find("EastPalace1F_1_B1F_ColMap.bmp");
			CurStairs_ = PlayerStairsState::Bot;
			IsCharacterAutoMove_ = true;
			IsOnStairs_ = true;
			BridgeActor_->On();
			return;
		}

		if (PlayerStairsState::Bot == CurStairs_)
		{
			MapColImage_ = GameEngineImageManager::GetInst()->Find("EastPalace1F_1_1F_ColMap.bmp");
			CurStairs_ = PlayerStairsState::Top;
			IsCharacterAutoMove_ = true;
			IsOnStairs_ = true;
			BridgeActor_->Off();
			return;
		}
	}
}


void PlayerLink::Room4_Trans_Start()
{
	GameEngineTime::GetInst()->SetTimeScale(2, 0.0f);
	IsCameraAutoMove_ = true;
	IsCharacterAutoMove_ = true;
	RoomSize_[0] = { 2048, 1955 + 4128 };
	RoomSize_[1] = { 4095, 0 + 4128 };
}

void PlayerLink::Room4_Trans_Update()
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

	if (false == IsCameraAutoMove_ && false == IsCharacterAutoMove_)
	{
		CameraStateChange(CameraState::Room4);
	}

}

/// /////////////////////////////////Room10

void PlayerLink::Room10Start()
{
	GameEngineTime::GetInst()->SetTimeScale(-1, 1.0f);
	GameEngineTime::GetInst()->SetTimeScale(0, 1.0f);
	GameEngineTime::GetInst()->SetTimeScale(10, 1.0f);
}

void PlayerLink::Room10Update()
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
			GameEngineTime::GetInst()->SetTimeScale(10, 0.0f);
			PlayerAutoMove(150.0f);
			return;
		}

		if (false == IsOnStairs_)
		{
			GameEngineTime::GetInst()->SetTimeScale(10, 0.0f);
			PlayerAutoMove();
			return;
		}
	}
	else
	{
		GameEngineTime::GetInst()->SetTimeScale(3, 1.0f);
	}


	/// ///////////////////////////////////////// Room Check
	int Red = RGB(255, 0, 0);
	int Yellow = RGB(255, 255, 0);
	int Blue = RGB(0, 0, 255);

	if (PosOrColorCheck(Red, MapColImage_) && PlayerState::MoveUp == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_)
	{
		PrevCameraState_ = CameraState::Room10;
		AutoMoveDir_ = float4::UP;
		CameraStateChange(CameraState::Room14_Trans);
		return;
	}

	if (PosOrColorCheck(Red, MapColImage_) && PlayerState::MoveLeft == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_)
	{
		PrevCameraState_ = CameraState::Room10;
		AutoMoveDir_ = float4::LEFT;
		CameraStateChange(CameraState::Room9_Trans);
		return;
	}

	if (PosOrColorCheck(Red, MapColImage_) && PlayerState::MoveRight == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_)
	{
		PrevCameraState_ = CameraState::Room10;
		AutoMoveDir_ = float4::RIGHT;
		CameraStateChange(CameraState::Room11_Trans);
		return;
	}

	if (PosOrColorCheck(Yellow, MapColImage_) && PlayerState::MoveDown == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_)
	{
		PrevCameraState_ = CameraState::Room10;
		AutoMoveDir_ = float4::DOWN;
		CameraStateChange(CameraState::Room4_Trans);
		return;
	}
}

void PlayerLink::Room10_Trans_Start()
{
	GameEngineTime::GetInst()->SetTimeScale(4, 0.0f);
	GameEngineTime::GetInst()->SetTimeScale(9, 0.0f);
	GameEngineTime::GetInst()->SetTimeScale(11, 0.0f);
	GameEngineTime::GetInst()->SetTimeScale(14, 0.0f);

	GameEngineTime::GetInst()->SetTimeScale(-1, 1.0f);
	GameEngineTime::GetInst()->SetTimeScale(0, 1.0f);
	IsCameraAutoMove_ = true;
	IsCharacterAutoMove_ = true;
	RoomSize_[0] = { 2048, 4035 };
	RoomSize_[1] = { 4095, 2050 };
}

void PlayerLink::Room10_Trans_Update()
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

	if (false == IsCameraAutoMove_ && false == IsCharacterAutoMove_)
	{
		CameraStateChange(CameraState::Room10);
	}

}

/// /////////////////////////////////Room9

void PlayerLink::Room9Start()
{
	GameEngineTime::GetInst()->SetTimeScale(10, 0.0f);
	GameEngineTime::GetInst()->SetTimeScale(8, 0.0f);
	GameEngineTime::GetInst()->SetTimeScale(2, 0.0f);

	GameEngineTime::GetInst()->SetTimeScale(-1, 1.0f);
	GameEngineTime::GetInst()->SetTimeScale(0, 1.0f);
	GameEngineTime::GetInst()->SetTimeScale(9, 1.0f);
}

void PlayerLink::Room9Update()
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
			GameEngineTime::GetInst()->SetTimeScale(9, 0.0f);
			PlayerAutoMove(150.0f);
			return;
		}

		if (false == IsOnStairs_)
		{
			GameEngineTime::GetInst()->SetTimeScale(9, 0.0f);
			PlayerAutoMove();
			return;
		}
	}
	else
	{
		GameEngineTime::GetInst()->SetTimeScale(3, 1.0f);
	}


	/// ///////////////////////////////////////// Room Check
	int Red = RGB(255, 0, 0);
	int Yellow = RGB(255, 255, 0);
	int Blue = RGB(0, 0, 255);

	//if (PosOrColorCheck(Red, MapColImage_) && PlayerState::MoveUp == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_)
	//{
	//	PrevCameraState_ = CameraState::Room9;
	//	AutoMoveDir_ = float4::UP;
	//	CameraStateChange(CameraState::Room14_Trans);
	//	return;
	//}

	//if (PosOrColorCheck(Red, MapColImage_) && PlayerState::MoveLeft == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_)
	//{
	//	PrevCameraState_ = CameraState::Room9;
	//	AutoMoveDir_ = float4::LEFT;
	//	CameraStateChange(CameraState::Room11_Trans);
	//	return;
	//}

	//if (PosOrColorCheck(Red, MapColImage_) && PlayerState::MoveRight == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_)
	//{
	//	PrevCameraState_ = CameraState::Room9;
	//	AutoMoveDir_ = float4::RIGHT;
	//	CameraStateChange(CameraState::Room9_Trans);
	//	return;
	//}

	if (PosOrColorCheck(Yellow, MapColImage_) && PlayerState::MoveRight == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_)
	{
		PrevCameraState_ = CameraState::Room9;
		AutoMoveDir_ = float4::RIGHT;
		CameraStateChange(CameraState::Room10_Trans);
		return;
	}
}


void PlayerLink::Room9_Trans_Start()
{
	GameEngineTime::GetInst()->SetTimeScale(-1, 1.0f);
	GameEngineTime::GetInst()->SetTimeScale(0, 1.0f);

	GameEngineTime::GetInst()->SetTimeScale(10, 0.0f);
	GameEngineTime::GetInst()->SetTimeScale(7, 0.0f);
	GameEngineTime::GetInst()->SetTimeScale(8, 0.0f);
	GameEngineTime::GetInst()->SetTimeScale(3, 0.0f);
	IsCameraAutoMove_ = true;
	IsCharacterAutoMove_ = true;
	RoomSize_[0] = { 1022, 4035 };
	RoomSize_[1] = { 2045, 2178 };
}

void PlayerLink::Room9_Trans_Update()
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

	if (false == IsCameraAutoMove_ && false == IsCharacterAutoMove_)
	{
		CameraStateChange(CameraState::Room9);
	}
}