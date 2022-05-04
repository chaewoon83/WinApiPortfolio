#include "PlayerLink.h"
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineLevel.h> // ������ ���ؼ�
#include <GameEngine/GameEngineCollision.h>
#include "Map1F_2.h"
#include "GameEngineContentsEnum.h"
#include "Map1FBridge.h"
#include "BlackScreen.h"

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
			PlayerRenderer_->SetOrder(static_cast<int>(PlayLevelOrder::B1FPLAYER));
			return;
		}

		if (PlayerStairsState::Bot == CurStairs_)
		{
			MapColImage_ = GameEngineImageManager::GetInst()->Find("EastPalace1F_1_1F_ColMap.bmp");
			CurStairs_ = PlayerStairsState::Top;
			IsCharacterAutoMove_ = true;
			IsOnStairs_ = true;
			BridgeActor_->Off();
			PlayerRenderer_->SetOrder(static_cast<int>(PlayLevelOrder::PLAYER));
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
		GameEngineTime::GetInst()->SetTimeScale(10, 1.0f);
	}


	/// ///////////////////////////////////////// Room Check
	int Red = RGB(255, 0, 0);
	int Yellow = RGB(255, 255, 0);
	int Blue = RGB(0, 0, 255);


	if (PosOrColorCheck(Red, MapColImage_) && PlayerState::MoveLeft == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_ && PlayerStairsState::Top == CurStairs_)
	{
		PrevCameraState_ = CameraState::Room10;
		AutoMoveDir_ = float4::LEFT;
		CameraStateChange(CameraState::Room9_Trans);
		return;
	}

	if (PosOrColorCheck(Red, MapColImage_) && PlayerState::MoveRight == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_ 
		&& PlayerStairsState::Top == CurStairs_ )
	{
		PrevCameraState_ = CameraState::Room10;
		AutoMoveDir_ = float4::RIGHT;
		CameraStateChange(CameraState::Room11_Trans);
		return;
	}

	if (PosOrColorCheck(Yellow, MapColImage_) && PlayerState::MoveRight == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_
		&& PlayerStairsState::Bot == CurStairs_)
	{
		PrevCameraState_ = CameraState::Room10;
		AutoMoveDir_ = float4::RIGHT;
		CameraStateChange(CameraState::Room11_Trans);
		return;
	}


	if (PosOrColorCheck(Yellow, MapColImage_) && PlayerState::MoveDown == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_ && PlayerStairsState::Top == CurStairs_)
	{
		PrevCameraState_ = CameraState::Room10;
		AutoMoveDir_ = float4::DOWN;
		CameraStateChange(CameraState::Room4_Trans);
		return;
	}

	if (PosOrColorCheck(Yellow, MapColImage_) && PlayerState::MoveLeft == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_ && PlayerStairsState::Bot == CurStairs_)
	{
		PrevCameraState_ = CameraState::Room10;
		AutoMoveDir_ = float4::LEFT;
		CameraStateChange(CameraState::Room9_Trans);
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

	if (PosOrColorCheck(Yellow, MapColImage_) && PlayerState::MoveLeft == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_ && PlayerStairsState::Top == CurStairs_)
	{
		PrevCameraState_ = CameraState::Room7;
		AutoMoveDir_ = float4::LEFT;
		CameraStateChange(CameraState::Room7_Trans);
		return;
	}

	if (PosOrColorCheck(Yellow, MapColImage_) && PlayerState::MoveLeft == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_ && PlayerStairsState::Bot == CurStairs_)
	{
		PrevCameraState_ = CameraState::Room8;
		AutoMoveDir_ = float4::LEFT;
		CameraStateChange(CameraState::Room8_Trans);
		return;
	}

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
	RoomSize_[1] = { 2045, 2048 };
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


////////////////////////////////////////////////////// Room7
void PlayerLink::Room7Start()
{

	GameEngineTime::GetInst()->SetTimeScale(-1, 1.0f);
	GameEngineTime::GetInst()->SetTimeScale(0, 1.0f);
	GameEngineTime::GetInst()->SetTimeScale(7, 1.0f);
}
void PlayerLink::Room7Update()
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
		GameEngineTime::GetInst()->SetTimeScale(9, 1.0f);
	}


	/// ///////////////////////////////////////// Room Check
	int Red = RGB(255, 0, 0);
	int Yellow = RGB(255, 255, 0);
	int Blue = RGB(0, 0, 255);

	if (PosOrColorCheck(Red, MapColImage_) && PlayerState::MoveUp == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_)
	{
		PrevCameraState_ = CameraState::Room7;
		AutoMoveDir_ = float4::UP;
		CameraStateChange(CameraState::Room8_Trans);
		return;
	}

	if (PosOrColorCheck(Red, MapColImage_) && PlayerState::MoveRight == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_)
	{
		PrevCameraState_ = CameraState::Room7;
		AutoMoveDir_ = float4::RIGHT;
		CameraStateChange(CameraState::Room9_Trans);
		return;
	}
}


void PlayerLink::Room7_Trans_Start()
{
	GameEngineTime::GetInst()->SetTimeScale(-1, 1.0f);
	GameEngineTime::GetInst()->SetTimeScale(0, 1.0f);

	GameEngineTime::GetInst()->SetTimeScale(9, 0.0f);
	GameEngineTime::GetInst()->SetTimeScale(8, 0.0f);
	IsCameraAutoMove_ = true;
	IsCharacterAutoMove_ = true;
	RoomSize_[0] = { 0, 4035 };
	RoomSize_[1] = { 1021, 3076 };
}

void PlayerLink::Room7_Trans_Update()
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
		CameraStateChange(CameraState::Room7);
	}
}

////////////////////////////////////////////////////// Room8
void PlayerLink::Room8Start()
{

	GameEngineTime::GetInst()->SetTimeScale(-1, 1.0f);
	GameEngineTime::GetInst()->SetTimeScale(0, 1.0f);
	GameEngineTime::GetInst()->SetTimeScale(8, 1.0f);
}
void PlayerLink::Room8Update()
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
			GameEngineTime::GetInst()->SetTimeScale(8, 0.0f);
			PlayerAutoMove(150.0f);
			return;
		}

		if (false == IsOnStairs_)
		{
			GameEngineTime::GetInst()->SetTimeScale(8, 0.0f);
			PlayerAutoMove();
			return;
		}
	}
	else
	{
		GameEngineTime::GetInst()->SetTimeScale(8, 1.0f);
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////// Room Check
	int Red = RGB(255, 0, 0);
	int Yellow = RGB(255, 255, 0);
	int Blue = RGB(0, 0, 255);

	if (PosOrColorCheck(Yellow, MapColImage_) && PlayerState::MoveRight == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_ && PlayerStairsState::Bot == CurStairs_)
	{
		PrevCameraState_ = CameraState::Room8;
		AutoMoveDir_ = float4::RIGHT;
		CameraStateChange(CameraState::Room9_Trans);
		return;
	}

	if (PosOrColorCheck(Yellow, MapColImage_) && PlayerState::MoveDown == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_ /*&& PlayerStairsState::Top == CurStairs_*/)
	{
		PrevCameraState_ = CameraState::Room8;
		AutoMoveDir_ = float4::DOWN;
		CameraStateChange(CameraState::Room7_Trans);
		return;
	}

	if (PosOrColorCheck(Blue, MapColImage_) && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_)
	{
		
		if (PlayerStairsState::Top == CurStairs_)
		{
			MapColImage_ = GameEngineImageManager::GetInst()->Find("EastPalace1F_2_B1F_ColMap.bmp");
			MapPasImage_ = GameEngineImageManager::GetInst()->Find("EastPalace1F_2_B1F_PasMap.bmp");
			MapCarryColImage_ = MapCarryColImage_2_B1F_;
			CurStairs_ = PlayerStairsState::Bot;
			IsCharacterAutoMove_ = true;
			IsOnStairs_ = true;
			BridgeActor_->On();
			PlayerRenderer_->SetOrder(static_cast<int>(PlayLevelOrder::B1FPLAYER));
			return;
		}

		if (PlayerStairsState::Bot == CurStairs_)
		{
			MapColImage_ = GameEngineImageManager::GetInst()->Find("EastPalace1F_2_1F_ColMap.bmp");
			MapPasImage_ = GameEngineImageManager::GetInst()->Find("EastPalace1F_2_1F_PasMap.bmp");
			MapCarryColImage_ = MapCarryColImage_2_;
			CurStairs_ = PlayerStairsState::Top;
			IsCharacterAutoMove_ = true;
			IsOnStairs_ = true;
			BridgeActor_->Off();
			PlayerRenderer_->SetOrder(static_cast<int>(PlayLevelOrder::PLAYER));
			return;
		}
	}
}


void PlayerLink::Room8_Trans_Start()
{
	GameEngineTime::GetInst()->SetTimeScale(-1, 1.0f);
	GameEngineTime::GetInst()->SetTimeScale(0, 1.0f);

	GameEngineTime::GetInst()->SetTimeScale(9, 0.0f);
	GameEngineTime::GetInst()->SetTimeScale(7, 0.0f);
	IsCameraAutoMove_ = true;
	IsCharacterAutoMove_ = true;
	RoomSize_[0] = { 0, 3041 };
	RoomSize_[1] = { 1021, 2048 };
}

void PlayerLink::Room8_Trans_Update()
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
		CameraStateChange(CameraState::Room8);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////// Room11
void PlayerLink::Room11Start()
{

	GameEngineTime::GetInst()->SetTimeScale(-1, 1.0f);
	GameEngineTime::GetInst()->SetTimeScale(0, 1.0f);
	GameEngineTime::GetInst()->SetTimeScale(11, 1.0f);
}
void PlayerLink::Room11Update()
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
			GameEngineTime::GetInst()->SetTimeScale(11, 0.0f);
			PlayerAutoMove(150.0f);
			return;
		}

		if (false == IsOnStairs_)
		{
			GameEngineTime::GetInst()->SetTimeScale(11, 0.0f);
			PlayerAutoMove();
			return;
		}
	}
	else
	{
		GameEngineTime::GetInst()->SetTimeScale(11, 1.0f);
	}


	/// ///////////////////////////////////////// Room Check
	int Red = RGB(255, 0, 0);
	int Yellow = RGB(255, 255, 0);
	int Blue = RGB(0, 0, 255);

	if (PosOrColorCheck(Yellow, MapColImage_) && PlayerState::MoveRight == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_ 
		&& PlayerStairsState::Top == CurStairs_)
	{
		if (2700.0f > GetPosition().y)
		{
			PrevCameraState_ = CameraState::Room11;
			AutoMoveDir_ = float4::RIGHT;
			CameraStateChange(CameraState::Room13_Trans);
			return;
		}
		else
		{
			PrevCameraState_ = CameraState::Room11;
			AutoMoveDir_ = float4::RIGHT;
			CameraStateChange(CameraState::Room12_Trans);
			return;
		}

	}

	if (PosOrColorCheck(Yellow, MapColImage_) && PlayerState::MoveDown == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_ 
		&& PlayerStairsState::Top == CurStairs_)
	{
		PrevCameraState_ = CameraState::Room11;
		AutoMoveDir_ = float4::DOWN;
		CameraStateChange(CameraState::Room5_Trans);
		return;
	}

	if (PosOrColorCheck(Yellow, MapColImage_) && PlayerState::MoveLeft == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_ 
		/* && PlayerStairsState::Bot == CurStairs_*/)
	{
		PrevCameraState_ = CameraState::Room11;
		AutoMoveDir_ = float4::LEFT;
		CameraStateChange(CameraState::Room10_Trans);
		return;
	}


	if (PosOrColorCheck(Blue, MapColImage_) && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_)
	{

		if (PlayerStairsState::Top == CurStairs_)
		{
			MapColImage_ = GameEngineImageManager::GetInst()->Find("EastPalace1F_2_B1F_ColMap.bmp");
			MapPasImage_ = GameEngineImageManager::GetInst()->Find("EastPalace1F_2_B1F_PasMap.bmp");
			MapCarryColImage_ = MapCarryColImage_2_B1F_;
			CurStairs_ = PlayerStairsState::Bot;
			IsCharacterAutoMove_ = true;
			IsOnStairs_ = true;
			BridgeActor_->On();
			PlayerRenderer_->SetOrder(static_cast<int>(PlayLevelOrder::B1FPLAYER));
			return;
		}

		if (PlayerStairsState::Bot == CurStairs_)
		{
			MapColImage_ = GameEngineImageManager::GetInst()->Find("EastPalace1F_2_1F_ColMap.bmp");
			MapPasImage_ = GameEngineImageManager::GetInst()->Find("EastPalace1F_2_1F_PasMap.bmp");
			MapCarryColImage_ = MapCarryColImage_2_;
			CurStairs_ = PlayerStairsState::Top;
			IsCharacterAutoMove_ = true;
			IsOnStairs_ = true;
			BridgeActor_->Off();
			PlayerRenderer_->SetOrder(static_cast<int>(PlayLevelOrder::PLAYER));
			return;
		}
	}
}


void PlayerLink::Room11_Trans_Start()
{
	GameEngineTime::GetInst()->SetTimeScale(-1, 1.0f);
	GameEngineTime::GetInst()->SetTimeScale(0, 1.0f);

	GameEngineTime::GetInst()->SetTimeScale(10, 0.0f);
	GameEngineTime::GetInst()->SetTimeScale(12, 0.0f);
	GameEngineTime::GetInst()->SetTimeScale(13, 0.0f);
	IsCameraAutoMove_ = true;
	IsCharacterAutoMove_ = true;
	RoomSize_[0] = { 4096, 4035 };
	RoomSize_[1] = { 5117, 2048 };
}

void PlayerLink::Room11_Trans_Update()
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
		CameraStateChange(CameraState::Room11);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////// Room5
void PlayerLink::Room5Start()
{

	GameEngineTime::GetInst()->SetTimeScale(-1, 0.0f);
	GameEngineTime::GetInst()->SetTimeScale(0, 1.0f);
	GameEngineTime::GetInst()->SetTimeScale(5, 1.0f);
	BlackScreenAlpha_ = 255;
	BlackScreen::Renderer_->SetAlpha(BlackScreenAlpha_);
	BlackScreen::Renderer_->On();
	IsLightBalckScreenOn_ = false;
}
void PlayerLink::Room5Update()
{
	if (false == IsLightBalckScreenOn_)
	{
		ScreenTurnBright(BlackScreen::Renderer_, IsLightBalckScreenOn_);
		return;
	}

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
			GameEngineTime::GetInst()->SetTimeScale(5, 0.0f);
			PlayerAutoMove(150.0f);
			return;
		}

		if (false == IsOnStairs_)
		{
			GameEngineTime::GetInst()->SetTimeScale(5, 0.0f);
			PlayerAutoMove();
			return;
		}
	}
	else
	{
		GameEngineTime::GetInst()->SetTimeScale(5, 1.0f);
	}


	/// ///////////////////////////////////////// Room Check
	int Red = RGB(255, 0, 0);
	int Yellow = RGB(255, 255, 0);
	int Blue = RGB(0, 0, 255);

	//if (PosOrColorCheck(Yellow, MapColImage_) && PlayerState::MoveRight == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_
	//	&& PlayerStairsState::Top == CurStairs_)
	//{
	//	if (2700.0f > GetPosition().y)
	//	{
	//		PrevCameraState_ = CameraState::Room5;
	//		AutoMoveDir_ = float4::RIGHT;
	//		CameraStateChange(CameraState::Room13_Trans);
	//		return;
	//	}
	//	else
	//	{
	//		PrevCameraState_ = CameraState::Room5;
	//		AutoMoveDir_ = float4::RIGHT;
	//		CameraStateChange(CameraState::Room12_Trans);
	//		return;
	//	}

	//}

	//if (PosOrColorCheck(Yellow, MapColImage_) && PlayerState::MoveDown == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_
	//	&& PlayerStairsState::Top == CurStairs_)
	//{
	//	PrevCameraState_ = CameraState::Room5;
	//	AutoMoveDir_ = float4::DOWN;
	//	CameraStateChange(CameraState::Room5_Trans);
	//	return;
	//}

	//if (PosOrColorCheck(Yellow, MapColImage_) && PlayerState::MoveLeft == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_
	//	/* && PlayerStairsState::Bot == CurStairs_*/)
	//{
	//	PrevCameraState_ = CameraState::Room5;
	//	AutoMoveDir_ = float4::LEFT;
	//	CameraStateChange(CameraState::Room10_Trans);
	//	return;
	//}

}


void PlayerLink::Room5_Trans_Start()
{
	GameEngineTime::GetInst()->SetTimeScale(-1, 1.0f);
	GameEngineTime::GetInst()->SetTimeScale(0, 1.0f);

	GameEngineTime::GetInst()->SetTimeScale(4, 0.0f);
	GameEngineTime::GetInst()->SetTimeScale(6, 0.0f);
	GameEngineTime::GetInst()->SetTimeScale(11, 0.0f);
	IsCameraAutoMove_ = true;
	IsCharacterAutoMove_ = true;
	if (false == IsBlackScreenOn_)
	{
		BlackScreenAlpha_ = 0;
		BlackScreen::Renderer_->On();
		BlackScreen::Renderer_->SetAlpha(BlackScreenAlpha_);

	}

	if (true == IsBlackScreenOn_)
	{
		BlackScreenAlpha_ = 255;
		BlackScreen::Renderer_->Off();
		BlackScreen::Renderer_->SetAlpha(BlackScreenAlpha_);
	}

	RoomSize_[0] = { 4096, 991 + 4128};
	RoomSize_[1] = { 5117,  0 + 4128 };
}

void PlayerLink::Room5_Trans_Update()
{
	/// ///////////////////////////////////////// Room Transition
	if (false == IsBlackScreenOn_)
	{
		GameEngineTime::GetInst()->SetTimeScale(0, 0.0f);	
		ScreenTurnBlack(BlackScreen::Renderer_, IsBlackScreenOn_);
	}
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
		CameraStateChange(CameraState::Room5);
	}
}

void PlayerLink::ScreenTurnBlack(GameEngineRenderer* _Renderer, bool& _IsIamgeOn)
{
	BlackScreenTime_ += GameEngineTime::GetDeltaTime() * 255.0f;
	BlackScreenAlpha_ = static_cast<int> (BlackScreenTime_);
	_Renderer->SetAlpha(BlackScreenAlpha_);
	if (255 < BlackScreenAlpha_)
	{
		GameEngineTime::GetInst()->SetTimeScale(0, 1.0f);
		BlackScreenTime_ = 0.0f;
		_IsIamgeOn = true;
		return;
	}
}

void PlayerLink::ScreenTurnBright(GameEngineRenderer* _Renderer, bool& _IsIamgeOn)
{
	BlackScreenTime_ -= GameEngineTime::GetDeltaTime() * 255.0f;
	BlackScreenAlpha_ = 255 + static_cast<int> (BlackScreenTime_);
	_Renderer->SetAlpha(BlackScreenAlpha_);
	if (0 > BlackScreenAlpha_)
	{
		GameEngineTime::GetInst()->SetTimeScale(0, 1.0f);
		BlackScreenTime_ = 0.0f;
		_IsIamgeOn = true;
		_Renderer->Off();
		return;
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
		case CameraState::Room4:
			Room4Start();
			break;
		case CameraState::Room4_Trans:
			Room4_Trans_Start();
			break;
		case CameraState::Room10:
			Room10Start();
			break;
		case CameraState::Room10_Trans:
			Room10_Trans_Start();
			break;
		case CameraState::Room9:
			Room9Start();
			break;
		case CameraState::Room9_Trans:
			Room9_Trans_Start();
			break;
		case CameraState::Room7:
			Room7Start();
			break;
		case CameraState::Room7_Trans:
			Room7_Trans_Start();
			break;
		case CameraState::Room8:
			Room8Start();
			break;
		case CameraState::Room8_Trans:
			Room8_Trans_Start();
			break;
		case CameraState::Room11:
			Room11Start();
			break;
		case CameraState::Room11_Trans:
			Room11_Trans_Start();
			break;
		case CameraState::Room5:
			Room5Start();
			break;
		case CameraState::Room5_Trans:
			Room5_Trans_Start();
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
	case CameraState::Room4:
		Room4Update();
		break;
	case CameraState::Room4_Trans:
		Room4_Trans_Update();
		break;
	case CameraState::Room10:
		Room10Update();
		break;
	case CameraState::Room10_Trans:
		Room10_Trans_Update();
		break;
	case CameraState::Room9:
		Room9Update();
		break;
	case CameraState::Room9_Trans:
		Room9_Trans_Update();
		break;
	case CameraState::Room7:
		Room7Update();
		break;
	case CameraState::Room7_Trans:
		Room7_Trans_Update();
		break;
	case CameraState::Room8:
		Room8Update();
		break;
	case CameraState::Room8_Trans:
		Room8_Trans_Update();
		break;
	case CameraState::Room11:
		Room11Update();
		break;
	case CameraState::Room11_Trans:
		Room11_Trans_Update();
		break;
	case CameraState::Room5:
		Room5Update();
		break;
	case CameraState::Room5_Trans:
		Room5_Trans_Update();
		break;
	case CameraState::Max:
		break;
	default:
		break;
	}
}