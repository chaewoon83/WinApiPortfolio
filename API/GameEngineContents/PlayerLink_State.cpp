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
#include "Map1F.h"
#include "GameEngineContentsEnum.h"
#include "Map1FBridge.h"

void PlayerLink::IdleUpdate()
{
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

	DamagedCheck();

	PotCarryCheck();

	if (true == GameEngineInput::GetInst()->IsDown("Attack"))
	{
		if (PlayerState::IdleRight == PlayerCurState_)
		{
			PlayerPrevState_ = PlayerCurState_;
			PlayerChangeState(PlayerState::WieldRight);
			return;
		}

		if (PlayerState::IdleLeft == PlayerCurState_)
		{
			PlayerPrevState_ = PlayerCurState_;
			PlayerChangeState(PlayerState::WieldLeft);
			return;
		}

		if (PlayerState::IdleUp == PlayerCurState_)
		{
			PlayerPrevState_ = PlayerCurState_;
			PlayerChangeState(PlayerState::WieldUp);
			return;
		}

		if (PlayerState::IdleDown == PlayerCurState_)
		{
			PlayerPrevState_ = PlayerCurState_;
			PlayerChangeState(PlayerState::WieldDown);
			return;
		}
	}
}

void PlayerLink::WieldUpdate()
{
	AnimationTimer_ += GameEngineTime::GetDeltaTime(0);
	/////// Create Attack Collision
	if (PlayerState::WieldRight == PlayerCurState_) 
	{
		WieldRightUpdate();
	}
	if (PlayerState::WieldLeft == PlayerCurState_)
	{
		WieldLeftUpdate();
	}
	if (PlayerState::WieldUp == PlayerCurState_)
	{
		WieldUpUpdate();
	}
	if (PlayerState::WieldDown == PlayerCurState_)
	{
		WieldDownUpdate();
	}

	DamagedCheck();

	//////End Of Animation
	if (PlayerRenderer_->IsEndAnimation())
	{
		AnimationTimer_ = 0.0f;
		if (nullptr != SwordCollision_)
		{
			SwordCollision_->Death();
			SwordCollision_ = nullptr;
		}
		PlayerPrevStateCheck();
	}
}
void PlayerLink::CarryStartUpdate()
{
	if (true == PlayerRenderer_->IsEndAnimation())
	{
		if (PlayerState::CarryStartRight == PlayerCurState_)
		{
			PlayerChangeState(PlayerState::CarryMoveRight);
		}
		if (PlayerState::CarryStartLeft == PlayerCurState_)
		{
			PlayerChangeState(PlayerState::CarryMoveLeft);
		}
		if (PlayerState::CarryStartUp == PlayerCurState_)
		{
			PlayerChangeState(PlayerState::CarryMoveUp);
		}
		if (PlayerState::CarryStartDown == PlayerCurState_)
		{
			PlayerChangeState(PlayerState::CarryMoveDown);
		}
	}
}

void PlayerLink::CarryIdleUpdate()
{
	if (true == IsUpMoveKey())
	{
		PlayerChangeState(PlayerState::CarryMoveUp);
		return;
	}

	if (true == IsDownMoveKey())
	{
		PlayerChangeState(PlayerState::CarryMoveDown);
		return;
	}
	if (true == IsRightMoveKey())
	{
		PlayerChangeState(PlayerState::CarryMoveRight);
		return;
	}

	if (true == IsLeftMoveKey())
	{
		PlayerChangeState(PlayerState::CarryMoveLeft);
		return;
	}


	DamagedCheck();

	/// ///////////////Throw
	if (true == GameEngineInput::GetInst()->IsDown("Interact"))
	{
		IsCarry_ = false;
		PlayerPrevState_ = PlayerCurState_;
		if (PlayerState::CarryIdleRight == PlayerCurState_ && true == GameEngineInput::GetInst()->IsPress("MoveRight"))
		{
			PlayerChangeState(PlayerState::MoveRight);
			return;
		}
		if (PlayerState::CarryIdleLeft == PlayerCurState_ && true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
		{
			PlayerChangeState(PlayerState::MoveLeft);
			return;
		}
		if (PlayerState::CarryIdleUp == PlayerCurState_ && true == GameEngineInput::GetInst()->IsPress("MoveUp"))
		{
			PlayerChangeState(PlayerState::MoveUp);
			return;
		}
		if (PlayerState::CarryIdleDown == PlayerCurState_ && true == GameEngineInput::GetInst()->IsPress("MoveDown"))
		{
			PlayerChangeState(PlayerState::MoveDown);
			return;
		}

		if (PlayerState::CarryIdleRight == PlayerCurState_)
		{
			PlayerChangeState(PlayerState::IdleRight);
			return;
		}
		if (PlayerState::CarryIdleLeft == PlayerCurState_)
		{
			PlayerChangeState(PlayerState::IdleLeft);
			return;
		}
		if (PlayerState::CarryIdleUp == PlayerCurState_)
		{
			PlayerChangeState(PlayerState::IdleUp);
			return;
		}
		if (PlayerState::CarryIdleDown == PlayerCurState_)
		{
			PlayerChangeState(PlayerState::IdleDown);
			return;
		}
	}




}

void PlayerLink::CarryMoveUpdate()
{
	if (false == IsCameraAutoMove_ && false == IsCharacterAutoMove_)
	{

		if (true == IsMoveKeyFree())
		{
			if (PlayerState::CarryMoveRight == PlayerCurState_)
			{
				PlayerChangeState(PlayerState::CarryIdleRight);
				return;
			}
			if (PlayerState::CarryMoveLeft == PlayerCurState_)
			{
				PlayerChangeState(PlayerState::CarryIdleLeft);
				return;
			}
			if (PlayerState::CarryMoveUp == PlayerCurState_)
			{
				PlayerChangeState(PlayerState::CarryIdleUp);
				return;
			}
			if (PlayerState::CarryMoveDown == PlayerCurState_)
			{
				PlayerChangeState(PlayerState::CarryIdleDown);
				return;
			}
		}


		//////////////////Throw
		if (true == GameEngineInput::GetInst()->IsDown("Interact"))
		{
			IsCarry_ = false;
			PlayerPrevState_ = PlayerCurState_;
			if (PlayerState::CarryMoveRight == PlayerCurState_ && true == GameEngineInput::GetInst()->IsPress("MoveRight"))
			{
				PlayerChangeState(PlayerState::MoveRight);
				return;
			}
			if (PlayerState::CarryMoveLeft == PlayerCurState_ && true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
			{
				PlayerChangeState(PlayerState::MoveLeft);
				return;
			}
			if (PlayerState::CarryMoveUp == PlayerCurState_ && true == GameEngineInput::GetInst()->IsPress("MoveUp"))
			{
				PlayerChangeState(PlayerState::MoveUp);
				return;
			}
			if (PlayerState::CarryMoveDown == PlayerCurState_ && true == GameEngineInput::GetInst()->IsPress("MoveDown"))
			{
				PlayerChangeState(PlayerState::MoveDown);
				return;
			}

			if (PlayerState::CarryMoveRight == PlayerCurState_)
			{
				PlayerChangeState(PlayerState::IdleRight);
				return;
			}
			if (PlayerState::CarryMoveLeft == PlayerCurState_)
			{
				PlayerChangeState(PlayerState::IdleLeft);
				return;
			}
			if (PlayerState::CarryMoveUp == PlayerCurState_)
			{
				PlayerChangeState(PlayerState::IdleUp);
				return;
			}
			if (PlayerState::CarryMoveDown == PlayerCurState_)
			{
				PlayerChangeState(PlayerState::IdleDown);
				return;
			}
		}


		DamagedCheck();

		MoveFunction();

		/// ///////////////////////////////////////////////////////////Right
		if (false == GameEngineInput::GetInst()->IsPress("MoveUp") &&
			false == GameEngineInput::GetInst()->IsPress("MoveDown") &&
			true == GameEngineInput::GetInst()->IsPress("MoveRight"))
		{
			PlayerChangeState(PlayerState::CarryMoveRight);
			return;
		}

		if (true == GameEngineInput::GetInst()->IsUp("MoveUp") ||
			true == GameEngineInput::GetInst()->IsUp("MoveDown"))
		{
			if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
			{
				PlayerChangeState(PlayerState::CarryMoveRight);
				return;
			}
		}
		/// ///////////////////////////////////////////////////////////Left
		if (false == GameEngineInput::GetInst()->IsPress("MoveUp") &&
			false == GameEngineInput::GetInst()->IsPress("MoveDown") &&
			true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
		{
			PlayerChangeState(PlayerState::CarryMoveLeft);
			return;
		}

		if (true == GameEngineInput::GetInst()->IsUp("MoveUp") ||
			true == GameEngineInput::GetInst()->IsUp("MoveDown"))
		{
			if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
			{
				PlayerChangeState(PlayerState::CarryMoveLeft);
				return;
			}
		}
		/// ///////////////////////////////////////////////////////////Up
		if (false == GameEngineInput::GetInst()->IsPress("MoveRight") &&
			false == GameEngineInput::GetInst()->IsPress("MoveLeft") &&
			true == GameEngineInput::GetInst()->IsPress("MoveUp"))
		{
			PlayerChangeState(PlayerState::CarryMoveUp);
			return;
		}

		if (true == GameEngineInput::GetInst()->IsUp("MoveRight") ||
			true == GameEngineInput::GetInst()->IsUp("MoveLeft"))
		{
			if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
			{
				PlayerChangeState(PlayerState::CarryMoveUp);
				return;
			}
		}
		/// ///////////////////////////////////////////////////////////Down
		if (
			false == GameEngineInput::GetInst()->IsPress("MoveRight") &&
			false == GameEngineInput::GetInst()->IsPress("MoveLeft") &&
			true == GameEngineInput::GetInst()->IsPress("MoveDown"))
		{
			PlayerChangeState(PlayerState::CarryMoveDown);
			return;
		}

		if (true == GameEngineInput::GetInst()->IsUp("MoveRight") ||
			true == GameEngineInput::GetInst()->IsUp("MoveLeft"))
		{
			if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
			{
				PlayerChangeState(PlayerState::CarryMoveDown);
				return;
			}
		}
	}
}

void PlayerLink::WieldRightUpdate()
{

	if (nullptr == SwordCollision_)
	{
		SwordCollision_ = CreateCollision("Sword", { 32, 48 }, { 16, -24 });
		AnimationIndex_ = 0;
	}

	if (0 == AnimationIndex_ && AttackAnimationInterval_ < AnimationTimer_)
	{
		SwordCollision_->SetScale({ 72, 52 });
		SwordCollision_->SetPivot({ 36, -26 });
		AnimationIndex_ = 1;
	}

	if (1 == AnimationIndex_ && AttackAnimationInterval_ * 2 < AnimationTimer_)
	{
		SwordCollision_->SetScale({ 98, 26 });
		SwordCollision_->SetPivot({ 49, 13 });
		AnimationIndex_ = 2;
	}

	if (2 == AnimationIndex_ && AttackAnimationInterval_ * 3 < AnimationTimer_)
	{
		SwordCollision_->SetScale({ 82, 42 });
		SwordCollision_->SetPivot({ 41, 21 });
		AnimationIndex_ = 3;
	}

	if (3 == AnimationIndex_ && AttackAnimationInterval_ * 4 < AnimationTimer_)
	{
		SwordCollision_->SetScale({ 58, 82 });
		SwordCollision_->SetPivot({ 29, 41 });
		AnimationIndex_ = 4;
	}

}

void PlayerLink::WieldLeftUpdate()
{

	if (nullptr == SwordCollision_)
	{
		SwordCollision_ = CreateCollision("Sword", { -32, 48 }, { -16, -24 });
		AnimationIndex_ = 0;
	}

	if (0 == AnimationIndex_ && AttackAnimationInterval_ < AnimationTimer_)
	{
		SwordCollision_->SetScale({ -72, 52 });
		SwordCollision_->SetPivot({ -36, -26 });
		AnimationIndex_ = 1;
	}

	if (1 == AnimationIndex_ && AttackAnimationInterval_ * 2 < AnimationTimer_)
	{
		SwordCollision_->SetScale({ -98, 26 });
		SwordCollision_->SetPivot({ -49, 13 });
		AnimationIndex_ = 2;
	}

	if (2 == AnimationIndex_ && AttackAnimationInterval_ * 3 < AnimationTimer_)
	{
		SwordCollision_->SetScale({ -82, 42 });
		SwordCollision_->SetPivot({ -41, 21 });
		AnimationIndex_ = 3;
	}

	if (3 == AnimationIndex_ && AttackAnimationInterval_ * 4 < AnimationTimer_)
	{
		SwordCollision_->SetScale({ -58, 82 });
		SwordCollision_->SetPivot({ -29, 41 });
		AnimationIndex_ = 4;
	}

}

void PlayerLink::WieldUpUpdate()
{

	if (nullptr == SwordCollision_)
	{
		//SwordCollision_ = CreateCollision("Sword", { 4,4 });
		SwordCollision_ = CreateCollision("Sword", { 56, 25 }, { 28,-13 });
		AnimationIndex_ = 0;
	}

	if (0 == AnimationIndex_ && AttackAnimationInterval_ < AnimationTimer_)
	{
		SwordCollision_->SetScale({ 50, 77 });
		SwordCollision_->SetPivot({ 25, -39 });
		AnimationIndex_ = 1;
	}

	if (1 == AnimationIndex_ && AttackAnimationInterval_ * 2 < AnimationTimer_)
	{
		SwordCollision_->SetScale({ 32, 98 });
		SwordCollision_->SetPivot({ -16, -49 });
		AnimationIndex_ = 2;
	}

	if (2 == AnimationIndex_ && AttackAnimationInterval_ * 3 < AnimationTimer_)
	{
		SwordCollision_->SetScale({ 56, 78 });
		SwordCollision_->SetPivot({ -28, -39 });
		AnimationIndex_ = 3;
	}

	if (3 == AnimationIndex_ && AttackAnimationInterval_ * 4 < AnimationTimer_)
	{
		SwordCollision_->SetScale({ 88, 50 });
		SwordCollision_->SetPivot({ -44, -25 });
		AnimationIndex_ = 4;
	}

}

void PlayerLink::WieldDownUpdate()
{

	if (nullptr == SwordCollision_)
	{
		SwordCollision_ = CreateCollision("Sword", { 56, 18 }, { -28,14 });
		AnimationIndex_ = 0;
	}

	if (0 == AnimationIndex_ && AttackAnimationInterval_ < AnimationTimer_)
	{
		SwordCollision_->SetScale({ 60, 58 });
		SwordCollision_->SetPivot({ -30, 29 });
		AnimationIndex_ = 1;
	}

	if (1 == AnimationIndex_ && AttackAnimationInterval_ * 2 < AnimationTimer_)
	{
		SwordCollision_->SetScale({ 24, 86 });
		SwordCollision_->SetPivot({ -4, 43 });
		AnimationIndex_ = 2;
	}

	if (2 == AnimationIndex_ && AttackAnimationInterval_ * 3 < AnimationTimer_)
	{
		SwordCollision_->SetScale({ 30, 98 });
		SwordCollision_->SetPivot({ 15, 49 });
		AnimationIndex_ = 3;
	}

	if (3 == AnimationIndex_ && AttackAnimationInterval_ * 4 < AnimationTimer_)
	{
		SwordCollision_->SetScale({ 66, 78 });
		SwordCollision_->SetPivot({ 33, 49 });
		AnimationIndex_ = 4;
	}

	if (4 == AnimationIndex_ && AttackAnimationInterval_ * 5 < AnimationTimer_)
	{
		SwordCollision_->SetScale({ 82, 70 });
		SwordCollision_->SetPivot({ 41, 35 });
		AnimationIndex_ = 5;
	}

}

void PlayerLink::DamagedUpdate()
{
	CurKnockbackTime_ += GameEngineTime::GetDeltaTime(0);
	int Black = RGB(0, 0, 0);
	if (true == PosAndColorCheck(Black, MapColImage_))
	{
		SetMove(KnockbackDir_ * KnockBackSpeed_ * GameEngineTime::GetDeltaTime(0));
	}
	PlayerPrevState_;
	if (KnockbackTime_ < CurKnockbackTime_)
	{
		IsKnockback_ = false;
		PlayerPrevStateCheck();
	}
}

void PlayerLink::MoveUpdate()
{
	if (false == IsCameraAutoMove_ && false == IsCharacterAutoMove_)
	{

		if (true == IsMoveKeyFree())
		{
			if (PlayerState::MoveRight == PlayerCurState_)
			{
				PlayerChangeState(PlayerState::IdleRight);
			}
			if (PlayerState::MoveLeft == PlayerCurState_)
			{
				PlayerChangeState(PlayerState::IdleLeft);
			}
			if (PlayerState::MoveUp == PlayerCurState_)
			{
				PlayerChangeState(PlayerState::IdleUp);
			}
			if (PlayerState::MoveDown == PlayerCurState_)
			{
				PlayerChangeState(PlayerState::IdleDown);
			}
		}

		DamagedCheck();
		if (true == IsKnockback_)
		{
			return;
		}

		MoveFunction();

		//Wield
		if (true == GameEngineInput::GetInst()->IsDown("Attack"))
		{
			if (PlayerState::MoveRight == PlayerCurState_)
			{
				PlayerPrevState_ = PlayerCurState_;
				PlayerChangeState(PlayerState::WieldRight);
				return;
			}

			if (PlayerState::MoveLeft == PlayerCurState_)
			{
				PlayerPrevState_ = PlayerCurState_;
				PlayerChangeState(PlayerState::WieldLeft);
				return;
			}

			if (PlayerState::MoveUp == PlayerCurState_)
			{
				PlayerPrevState_ = PlayerCurState_;
				PlayerChangeState(PlayerState::WieldUp);
				return;
			}

			if (PlayerState::MoveDown == PlayerCurState_)
			{
				PlayerPrevState_ = PlayerCurState_;
				PlayerChangeState(PlayerState::WieldDown);
				return;
			}
		}

		/// ///////////////////////////////////////////////////////////Right
		if (false == GameEngineInput::GetInst()->IsPress("MoveUp") &&
			false == GameEngineInput::GetInst()->IsPress("MoveDown") &&
			true == GameEngineInput::GetInst()->IsPress("MoveRight"))
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
			true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
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
			true == GameEngineInput::GetInst()->IsPress("MoveUp"))
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
			true == GameEngineInput::GetInst()->IsPress("MoveDown"))
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

	//float DeltaTime = GameEngineTime::GetInst()->GetDeltaTime(0)
	//내가 키를 누르고있다면 움직이기
	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir += float4::LEFT;
		MoveLeft = true;
		//SetMove(MoveDir * GameEngineTime::GetDeltaTime(0) * Speed_);
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir += float4::RIGHT;
		MoveRight = true;
		//SetMove(MoveDir * GameEngineTime::GetDeltaTime(0) * Speed_);
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		MoveDir += float4::UP;
		MoveUp = true;
		//SetMove(MoveDir * GameEngineTime::GetDeltaTime(0) * Speed_);
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		MoveDir += float4::DOWN;
		MoveDown = true;
		//SetMove(MoveDir * GameEngineTime::GetDeltaTime(0) * Speed_);
	}

	//SetMove(MoveDir * GameEngineTime::GetDeltaTime(0) * Speed_);
	{
		int Black = RGB(0, 0, 0);
		float4 MyPos = GetPosition();
		float4 MyPosTopRight = MyPos + float4{ 32.0f, -21.0f };
		float4 MyPosTopLeft = MyPos + float4{ -32.0f, -21.0f };
		float4 MyPosBotRight = MyPos + float4{ 32.0f, 43.0f };
		float4 MyPosBotLeft = MyPos + float4{ -32.0f, 43.0f };
		float4 MyPosRight = MyPos + float4{ 32.0f, 0.0f};
		float4 MyPosLeft = MyPos + float4{ -32.0f, 0.0f };
		float4 MyPosTop = MyPos + float4{ 0.0f, -21.0f };
		float4 MyPosBot = MyPos + float4{ 0.0f, 43.0f };
		float4 NextPos = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime(0) * Speed_);
		float4 CheckPosTopRight = NextPos + float4{ 32.0f, -21.0f };
		float4 CheckPosTopLeft = NextPos + float4{ -32.0f, -21.0f};
		float4 CheckPosBotRight = NextPos + float4{ 32.0f, 43.0f };
		float4 CheckPosBotLeft = NextPos + float4{ -32.0f, 43.0f };
		float4 CheckPosRight = NextPos + float4{ 32.0f, 0.0f };
		float4 CheckPosLeft = NextPos + float4{ -32.0f, 0.0f };
		float4 CheckPosTop = NextPos + float4{ 0.0f, -21.0f };
		float4 CheckPosBot = NextPos + float4{ 0.0f, 43.0f };


		int ColorTopRight = MapColImage_->GetImagePixel(CheckPosTopRight);
		int ColorTopLeft = MapColImage_->GetImagePixel(CheckPosTopLeft);
		int ColorBotRight = MapColImage_->GetImagePixel(CheckPosBotRight);
		int ColorBotLeft = MapColImage_->GetImagePixel(CheckPosBotLeft);
		int ColorRight = MapColImage_->GetImagePixel(CheckPosRight);
		int ColorLeft = MapColImage_->GetImagePixel(CheckPosLeft);
		int ColorTop = MapColImage_->GetImagePixel(CheckPosTop);
		int ColorBot = MapColImage_->GetImagePixel(CheckPosBot);
		if (Black != ColorTopRight &&
			Black != ColorTopLeft &&
			Black != ColorBotRight &&
			Black != ColorBotLeft &&
			Black != ColorRight &&
			Black != ColorLeft &&
			Black != ColorTop &&
			Black != ColorBot)
		{
			if (false == PlayerMoveCollision_->NextPostCollisionCheck("Block", NextPos, CollisionType::Rect, CollisionType::Rect))
			{
				MoveDir.Normal2D();
				SetMove(MoveDir * GameEngineTime::GetDeltaTime(0) * Speed_);
			}
			else
			{
				if (true == MoveRight)
				{
					if (false == PlayerTopRightCollision_->NextPostCollisionCheck("Block", NextPos, CollisionType::Rect, CollisionType::Rect) &&
						false == PlayerBotRightCollision_->NextPostCollisionCheck("Block", NextPos, CollisionType::Rect, CollisionType::Rect) &&)
					{
						SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime(0) * Speed_);
					}

					if (true == PlayerTopRightCollision_->NextPostCollisionCheck("Block", NextPos, CollisionType::Rect, CollisionType::Rect))
					{
						if (false == PlayerMiddleHorCollision_->NextPostCollisionCheck("Block", NextPos, CollisionType::Rect, CollisionType::Rect))
						{
							SetMove(float4::DOWN * GameEngineTime::GetDeltaTime(0) * Speed_);
						}
					}

					if (true == PlayerBotRightCollision_->NextPostCollisionCheck("Block", NextPos, CollisionType::Rect, CollisionType::Rect))
					{
						if (false == PlayerMiddleHorCollision_->NextPostCollisionCheck("Block", NextPos, CollisionType::Rect, CollisionType::Rect))
						{
							SetMove(float4::UP * GameEngineTime::GetDeltaTime(0) * Speed_);
						}
					}
				}

				if (true == MoveLeft)
				{
					if (false == PlayerTopLeftCollision_->NextPostCollisionCheck("Block", NextPos, CollisionType::Rect, CollisionType::Rect) &&
						false == PlayerBotLeftCollision_->NextPostCollisionCheck("Block", NextPos, CollisionType::Rect, CollisionType::Rect))
					{
						SetMove(float4::LEFT * GameEngineTime::GetDeltaTime(0) * Speed_);
					}

					if (true == PlayerTopLeftCollision_->NextPostCollisionCheck("Block", NextPos, CollisionType::Rect, CollisionType::Rect))
					{
						if (false == PlayerMiddleHorCollision_->NextPostCollisionCheck("Block", NextPos, CollisionType::Rect, CollisionType::Rect))
						{
							SetMove(float4::DOWN * GameEngineTime::GetDeltaTime(0) * Speed_);
						}
					}

					if (true == PlayerBotLeftCollision_->NextPostCollisionCheck("Block", NextPos, CollisionType::Rect, CollisionType::Rect))
					{
						if (false == PlayerMiddleHorCollision_->NextPostCollisionCheck("Block", NextPos, CollisionType::Rect, CollisionType::Rect))
						{
							SetMove(float4::UP * GameEngineTime::GetDeltaTime(0) * Speed_);
						}
					}
				}
				if (true == MoveUp)
				{
					if (false == PlayerTopRightCollision_->NextPostCollisionCheck("Block", NextPos, CollisionType::Rect, CollisionType::Rect) &&
						false == PlayerTopLeftCollision_->NextPostCollisionCheck("Block", NextPos, CollisionType::Rect, CollisionType::Rect))
					{
						SetMove(float4::UP * GameEngineTime::GetDeltaTime(0) * Speed_);
					}

					if (true == PlayerTopLeftCollision_->NextPostCollisionCheck("Block", NextPos, CollisionType::Rect, CollisionType::Rect))
					{
						if (false == PlayerMiddleVerCollision_->NextPostCollisionCheck("Block", NextPos, CollisionType::Rect, CollisionType::Rect))
						{
							SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime(0) * Speed_);
						}
					}

					if (true == PlayerTopRightCollision_->NextPostCollisionCheck("Block", NextPos, CollisionType::Rect, CollisionType::Rect))
					{
						if (false == PlayerMiddleVerCollision_->NextPostCollisionCheck("Block", NextPos, CollisionType::Rect, CollisionType::Rect))
						{
							SetMove(float4::LEFT * GameEngineTime::GetDeltaTime(0) * Speed_);
						}
					}
				}
				if (true == MoveDown)
				{
					if (false == PlayerBotRightCollision_->NextPostCollisionCheck("Block", NextPos, CollisionType::Rect, CollisionType::Rect) &&
						false == PlayerBotLeftCollision_->NextPostCollisionCheck("Block", NextPos, CollisionType::Rect, CollisionType::Rect))
					{
						SetMove(float4::DOWN * GameEngineTime::GetDeltaTime(0) * Speed_);
					}

					if (true == PlayerBotRightCollision_->NextPostCollisionCheck("Block", NextPos, CollisionType::Rect, CollisionType::Rect))
					{
						if (false == PlayerMiddleVerCollision_->NextPostCollisionCheck("Block", NextPos, CollisionType::Rect, CollisionType::Rect))
						{
							SetMove(float4::LEFT * GameEngineTime::GetDeltaTime(0) * Speed_);
						}
					}

					if (true == PlayerBotLeftCollision_->NextPostCollisionCheck("Block", NextPos, CollisionType::Rect, CollisionType::Rect))
					{
						if (false == PlayerMiddleVerCollision_->NextPostCollisionCheck("Block", NextPos, CollisionType::Rect, CollisionType::Rect))
						{
							SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime(0) * Speed_);
						}
					}

				}
			}
		}
		else
		{

			if (true == MoveRight)
			{
				if (Black != MapColImage_->GetImagePixel({ MyPosTopRight.x + (MoveDir * GameEngineTime::GetDeltaTime(0) * Speed_).x, MyPosTop.y }) &&
					Black != MapColImage_->GetImagePixel({ MyPosBotRight.x + (MoveDir * GameEngineTime::GetDeltaTime(0) * Speed_).x, MyPosBot.y }) &&
					Black != MapColImage_->GetImagePixel({ MyPosRight.x + (MoveDir * GameEngineTime::GetDeltaTime(0) * Speed_).x, MyPosRight.y }))
				{
					{
						SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime(0) * Speed_);
					}
				}

				if (Black != MapColImage_->GetImagePixel(CheckPosRight) &&
					Black != MapColImage_->GetImagePixel(CheckPosTopRight) &&
					Black != MapColImage_->GetImagePixel(CheckPosTopLeft) &&
					Black != MapColImage_->GetImagePixel(CheckPosLeft))
				{
					{
						if (false == MoveUp)
						{
							SetMove(float4::UP * GameEngineTime::GetDeltaTime(0) * Speed_);
						}
					}

				}

				if (Black != MapColImage_->GetImagePixel(CheckPosRight) &&
					Black != MapColImage_->GetImagePixel(CheckPosBotRight) &&
					Black != MapColImage_->GetImagePixel(CheckPosTopLeft) &&
					Black != MapColImage_->GetImagePixel(CheckPosBotLeft))
				{
					if (false == MoveDown)
					{
						SetMove(float4::DOWN * GameEngineTime::GetDeltaTime(0) * Speed_);
					}
				}
			}

			if (true == MoveLeft)
			{
				if (Black != MapColImage_->GetImagePixel({ MyPosTopLeft.x + (MoveDir * GameEngineTime::GetDeltaTime(0) * Speed_).x, MyPosTopLeft.y }) &&
					Black != MapColImage_->GetImagePixel({ MyPosBotLeft.x + (MoveDir * GameEngineTime::GetDeltaTime(0) * Speed_).x, MyPosBotLeft.y }) &&
					Black != MapColImage_->GetImagePixel({ MyPosLeft.x + (MoveDir * GameEngineTime::GetDeltaTime(0) * Speed_).x, MyPosLeft.y }))
				{
					SetMove(float4::LEFT * GameEngineTime::GetDeltaTime(0) * Speed_);
				}

				if (Black != MapColImage_->GetImagePixel(CheckPosLeft) &&
					Black != MapColImage_->GetImagePixel(CheckPosTopLeft) &&
					Black != MapColImage_->GetImagePixel(CheckPosTopRight) &&
					Black != MapColImage_->GetImagePixel(CheckPosBotRight))
				{
					if (false == MoveUp)
					{
						SetMove(float4::UP * GameEngineTime::GetDeltaTime(0) * Speed_);
					}
				}
				if (Black != MapColImage_->GetImagePixel(CheckPosLeft) &&
					Black != MapColImage_->GetImagePixel(CheckPosBotLeft) &&
					Black != MapColImage_->GetImagePixel(CheckPosTopRight) &&
					Black != MapColImage_->GetImagePixel(CheckPosBotRight))
				{
					if (false == MoveDown)
					{
						SetMove(float4::DOWN * GameEngineTime::GetDeltaTime(0) * Speed_);
					}
				}
			}

			if (true == MoveUp)
			{
				if (Black != MapColImage_->GetImagePixel({ MyPosTopRight.x, MyPosTop.y + (MoveDir * GameEngineTime::GetDeltaTime(0) * Speed_).y }) &&
					Black != MapColImage_->GetImagePixel({ MyPosTopLeft.x, MyPosTop.y + (MoveDir * GameEngineTime::GetDeltaTime(0) * Speed_).y }) &&
					Black != MapColImage_->GetImagePixel({ MyPosTop.x, MyPosTop.y + (MoveDir * GameEngineTime::GetDeltaTime(0) * Speed_).y }))
				{
					SetMove(float4::UP * GameEngineTime::GetDeltaTime(0) * Speed_);
				}

				if (Black != MapColImage_->GetImagePixel(CheckPosTop) &&
					Black != MapColImage_->GetImagePixel(CheckPosTopRight) &&
					Black != MapColImage_->GetImagePixel(CheckPosBotRight) &&
					Black != MapColImage_->GetImagePixel(CheckPosBotLeft))
				{
					if (false == MoveRight)
					{
						SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime(0) * Speed_);
					}
				}

				if (Black != MapColImage_->GetImagePixel(CheckPosTop) &&
					Black != MapColImage_->GetImagePixel(CheckPosTopLeft) &&
					Black != MapColImage_->GetImagePixel(CheckPosBotRight) &&
					Black != MapColImage_->GetImagePixel(CheckPosBotLeft))
				{
					if (false == MoveLeft)
					{
						SetMove(float4::LEFT * GameEngineTime::GetDeltaTime(0) * Speed_);
					}
				}
			}

			if (true == MoveDown)
			{
				if (Black != MapColImage_->GetImagePixel({ MyPosBotRight.x, MyPosBot.y + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_).y }) &&
					Black != MapColImage_->GetImagePixel({ MyPosBotLeft.x, MyPosBot.y + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_).y }) &&
					Black != MapColImage_->GetImagePixel({ MyPosBot.x, MyPosBot.y + (MoveDir * GameEngineTime::GetDeltaTime() * Speed_).y }))
				{
					SetMove(float4::DOWN * GameEngineTime::GetDeltaTime(0) * Speed_);
				}

				if (Black != MapColImage_->GetImagePixel(CheckPosBot) &&
					Black != MapColImage_->GetImagePixel(CheckPosBotRight) &&
					Black != MapColImage_->GetImagePixel(CheckPosTopRight) &&
					Black != MapColImage_->GetImagePixel(CheckPosTopLeft))
				{
					if (false == MoveRight)
					{
						SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime(0) * Speed_);
					}
				}

				if (Black != MapColImage_->GetImagePixel(CheckPosBot) &&
					Black != MapColImage_->GetImagePixel(CheckPosBotLeft) &&
					Black != MapColImage_->GetImagePixel(CheckPosTopRight) &&
					Black != MapColImage_->GetImagePixel(CheckPosTopLeft))
				{
					if (false == MoveLeft)
					{
						SetMove(float4::LEFT * GameEngineTime::GetDeltaTime(0) * Speed_);
					}
				}

			}
		}

	}
}

//////////////////////////////////////// State

void PlayerLink::IdleRightStart()
{
	// 애니메이션이 바뀐다.
	PlayerRenderer_->ChangeAnimation("Idle_Right");
}

void PlayerLink::IdleLeftStart()
{
	// 애니메이션이 바뀐다.
	PlayerRenderer_->ChangeAnimation("Idle_Left");
}

void PlayerLink::IdleUpStart()
{
	// 애니메이션이 바뀐다.
	PlayerRenderer_->ChangeAnimation("Idle_Up");
}

void PlayerLink::IdleDownStart()
{
	// 애니메이션이 바뀐다.
	PlayerRenderer_->ChangeAnimation("Idle_Down");

}

void PlayerLink::MoveRightStart()
{
	PlayerRenderer_->ChangeAnimation("Walk_Right");
}

void PlayerLink::MoveLeftStart()
{
	PlayerRenderer_->ChangeAnimation("Walk_Left");
}


void PlayerLink::MoveUpStart()
{
	PlayerRenderer_->ChangeAnimation("Walk_Up");
}

void PlayerLink::MoveDownStart()
{
	PlayerRenderer_->ChangeAnimation("Walk_Down");
}

void PlayerLink::WieldRightStart()
{
	PlayerRenderer_->ChangeAnimation("Wield_Right");
}

void PlayerLink::WieldLeftStart()
{
	PlayerRenderer_->ChangeAnimation("Wield_Left");
}

void PlayerLink::WieldUpStart()
{
	PlayerRenderer_->ChangeAnimation("Wield_Up");
}

void PlayerLink::WieldDownStart()
{
	PlayerRenderer_->ChangeAnimation("Wield_Down");
}

void PlayerLink::DamagedRightStart()
{
	IsBlink_ = true;
	CurBlinkTime_ = 0.0f;
	CurKnockbackTime_ = 0.0f;
	PlayerRenderer_->ChangeAnimation("Damaged_Right");
}

void PlayerLink::DamagedLeftStart()
{
	IsBlink_ = true;
	CurBlinkTime_ = 0.0f;
	CurKnockbackTime_ = 0.0f;
	PlayerRenderer_->ChangeAnimation("Damaged_Left");
}

void PlayerLink::DamagedUpStart()
{
	IsBlink_ = true;
	CurBlinkTime_ = 0.0f;
	CurKnockbackTime_ = 0.0f;
	PlayerRenderer_->ChangeAnimation("Damaged_Up");
}

void PlayerLink::DamagedDownStart()
{
	IsBlink_ = true;
	CurBlinkTime_ = 0.0f;
	CurKnockbackTime_ = 0.0f;
	PlayerRenderer_->ChangeAnimation("Damaged_Down");
}

void PlayerLink::CarryStartRightStart()
{
	PlayerRenderer_->ChangeAnimation("Carry_Start_Right");
}

void PlayerLink::CarryStartLeftStart()
{
	PlayerRenderer_->ChangeAnimation("Carry_Start_Left");
}

void PlayerLink::CarryStartUpStart()
{
	PlayerRenderer_->ChangeAnimation("Carry_Start_Up");
}

void PlayerLink::CarryStartDownStart()
{
	PlayerRenderer_->ChangeAnimation("Carry_Start_Down");
}

void PlayerLink::CarryIdleRightStart()
{
	PlayerRenderer_->ChangeAnimation("Carry_Idle_Right");
}

void PlayerLink::CarryIdleLeftStart()
{
	PlayerRenderer_->ChangeAnimation("Carry_Idle_Left");
}

void PlayerLink::CarryIdleUpStart()
{
	PlayerRenderer_->ChangeAnimation("Carry_Idle_Up");
}

void PlayerLink::CarryIdleDownStart()
{
	PlayerRenderer_->ChangeAnimation("Carry_Idle_Down");
}

void PlayerLink::CarryMoveRightStart()
{
	PlayerRenderer_->ChangeAnimation("Carry_Move_Right");
}

void PlayerLink::CarryMoveLeftStart()
{
	PlayerRenderer_->ChangeAnimation("Carry_Move_Left");
}

void PlayerLink::CarryMoveUpStart()
{
	PlayerRenderer_->ChangeAnimation("Carry_Move_Up");
}

void PlayerLink::CarryMoveDownStart()
{
	PlayerRenderer_->ChangeAnimation("Carry_Move_Down");
}

void PlayerLink::DamagedCheck()
{
	std::vector<GameEngineCollision*> ColList;
	if (true == PlayerCollision_->CollisionResult("MonsterHitBox", ColList, CollisionType::Rect, CollisionType::Rect) && false == IsKnockback_ && false == IsBlink_)
	{
		GetDamaged();
		PlayerPrevState_ = PlayerCurState_;
		IsKnockback_ = true;
		IsBlink_ = true;
		HitActor_ = ColList[0]->GetActor();
		KnockbackDir_ = GetPosition() - HitActor_->GetPosition();
		KnockbackDir_.Normal2D();
		if (PlayerState::IdleRight == PlayerCurState_ ||
			PlayerState::MoveRight == PlayerCurState_ ||
			PlayerState::WieldRight == PlayerCurState_)
		{
			PlayerChangeState(PlayerState::DamagedRight);
			return;
		}
		if (PlayerState::IdleLeft == PlayerCurState_ ||
			PlayerState::MoveLeft == PlayerCurState_ ||
			PlayerState::WieldLeft == PlayerCurState_)
		{
			PlayerChangeState(PlayerState::DamagedLeft);
			return;
		}
		if (PlayerState::IdleUp == PlayerCurState_ ||
			PlayerState::MoveUp == PlayerCurState_ ||
			PlayerState::WieldUp == PlayerCurState_)
		{
			PlayerChangeState(PlayerState::DamagedUp);
			return;
		}
		if (PlayerState::IdleDown == PlayerCurState_ ||
			PlayerState::MoveDown == PlayerCurState_ ||
			PlayerState::WieldDown == PlayerCurState_)
		{
			PlayerChangeState(PlayerState::DamagedDown);
			return;
		}
	}
}

void PlayerLink::PotCarryCheck()
{
	std::vector<GameEngineCollision*> ColList;
	if (true == PlayerCollision_->CollisionResult("PotCarry", ColList, CollisionType::Rect, CollisionType::Rect) && true == GameEngineInput::GetInst()->IsDown("Interact"))
	{
		IsCarry_ = true;
		PlayerPrevState_ = PlayerCurState_;
		CarryActor_ = ColList[0]->GetActor();
		if (PlayerState::IdleRight == PlayerCurState_ ||
			PlayerState::MoveRight == PlayerCurState_)
		{
			PlayerChangeState(PlayerState::CarryStartRight);
			return;
		}
		if (PlayerState::IdleLeft == PlayerCurState_ ||
			PlayerState::MoveLeft == PlayerCurState_)
		{
			PlayerChangeState(PlayerState::CarryStartLeft);
			return;
		}
		if (PlayerState::IdleUp == PlayerCurState_ ||
			PlayerState::MoveUp == PlayerCurState_)
		{
			PlayerChangeState(PlayerState::CarryStartUp);
			return;
		}
		if (PlayerState::IdleDown == PlayerCurState_ ||
			PlayerState::MoveDown == PlayerCurState_)
		{
			PlayerChangeState(PlayerState::CarryStartDown);
			return;
		}
	}
}

/// ///////////////////////////////////// Room State

void PlayerLink::Room1Start()
{
	Map1F::Room1TopDoor0->ChangeAnimation("Close_Top");
	Map1F::Room1Door0Col_ = CreateCollision("Block", { 128,96 }, { 3072, 3248 });
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
	GameEngineTime::GetInst()->SetTimeScale(2, 0.0f);
	RoomSize_[0] = { 2048, 4063 };
	RoomSize_[1] = { 4095, 3088 };
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
		CameraStateChange(CameraState::Room3_Trans);
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
	GameEngineTime::GetInst()->SetTimeScale(1, 0.0f);
	GameEngineTime::GetInst()->SetTimeScale(3, 0.0f);
	IsCameraAutoMove_ = true;
	IsCharacterAutoMove_ = true;
	RoomSize_[0] = { 2048, 2983 };
	RoomSize_[1] = { 4095, 2019 };
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

void PlayerLink::Room3Start()
{
	GameEngineTime::GetInst()->SetTimeScale(3, 1.0f);
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

	if (PosOrColorCheck(Yellow, MapColImage_) && PlayerState::MoveUp == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_)
	{
		PrevCameraState_ = CameraState::Room3;
		AutoMoveDir_ = float4::UP;
		CameraStateChange(CameraState::Room7_Trans);
		return;
	}

	if (PosOrColorCheck(Yellow, MapColImage_) && PlayerState::MoveLeft == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_)
	{
		PrevCameraState_ = CameraState::Room3;
		AutoMoveDir_ = float4::LEFT;
		CameraStateChange(CameraState::Room4_Trans);
		return;
	}

	if (PosOrColorCheck(Yellow, MapColImage_) && PlayerState::MoveRight == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_)
	{
		PrevCameraState_ = CameraState::Room3;
		AutoMoveDir_ = float4::RIGHT;
		CameraStateChange(CameraState::Room5_Trans);
		return;
	}

	if (PosOrColorCheck(Red, MapColImage_) && PlayerState::MoveDown == PlayerCurState_ && false == IsCharacterAutoMove_ && false == IsCameraAutoMove_)
	{
		PrevCameraState_ = CameraState::Room3;
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


void PlayerLink::Room3_Trans_Start()
{
	GameEngineTime::GetInst()->SetTimeScale(2, 0.0f);
	IsCameraAutoMove_ = true;
	IsCharacterAutoMove_ = true;
	RoomSize_[0] = { 2048, 1955 };
	RoomSize_[1] = { 4095, 0 };
}

void PlayerLink::Room3_Trans_Update()
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
		CameraStateChange(CameraState::Room3);
	}

}

void PlayerLink::PlayerPrevStateCheck()
{
	if (PlayerState::MoveRight == PlayerPrevState_ &&
		true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		PlayerChangeState(PlayerState::MoveRight);
		return;
	}

	if (PlayerState::MoveLeft == PlayerPrevState_ &&
		true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		PlayerChangeState(PlayerState::MoveLeft);
		return;
	}

	if (PlayerState::MoveUp == PlayerPrevState_ &&
		true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		PlayerChangeState(PlayerState::MoveUp);
		return;
	}

	if (PlayerState::MoveDown == PlayerPrevState_ &&
		true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		PlayerChangeState(PlayerState::MoveDown);
		return;
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		PlayerChangeState(PlayerState::MoveUp);
		return;
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		PlayerChangeState(PlayerState::MoveDown);
		return;
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		PlayerChangeState(PlayerState::MoveRight);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		PlayerChangeState(PlayerState::MoveLeft);
		return;
	}

	if (PlayerState::IdleUp == PlayerPrevState_ ||
		PlayerState::MoveUp == PlayerPrevState_)
	{
		PlayerChangeState(PlayerState::IdleUp);
		return;
	}
	if (PlayerState::IdleDown == PlayerPrevState_ ||
		PlayerState::MoveDown == PlayerPrevState_)
	{
		PlayerChangeState(PlayerState::IdleDown);
		return;
	}
	if (PlayerState::IdleRight == PlayerPrevState_ ||
		PlayerState::MoveRight == PlayerPrevState_)
	{
		PlayerChangeState(PlayerState::IdleRight);
		return;
	}
	if (PlayerState::IdleLeft == PlayerPrevState_ ||
		PlayerState::MoveLeft == PlayerPrevState_)
	{
		PlayerChangeState(PlayerState::IdleLeft);
		return;
	}
}