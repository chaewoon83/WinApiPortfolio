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
#include "EnemyGlobalFunction.h"
#include "Map1F_2.h"
#include "GameEngineContentsEnum.h"
#include "Map1FBridge.h"


void PlayerLink::IdleUpdate()
{
	TreasureBoxCheck();
	if (true == IsInItemCutScene_)
	{
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveUp") && false == IsBlackScreenOn_)
	{
		PlayerChangeState(PlayerState::MoveUp);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveDown") && false == IsBlackScreenOn_)
	{
		PlayerChangeState(PlayerState::MoveDown);
		return;
	}
	if (true == GameEngineInput::GetInst()->IsPress("MoveRight") && false == IsBlackScreenOn_)
	{
		PlayerChangeState(PlayerState::MoveRight);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft") && false == IsBlackScreenOn_)
	{
		PlayerChangeState(PlayerState::MoveLeft);
		return;
	}

	DamagedCheck();

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

	PotCarryCheck();
	if (true == IsCarry_)
	{
		return;
	}
}

void PlayerLink::WieldUpdate()
{
	DamagedCheck();
	if (true == IsKnockback_)
	{
		return;
	}
	if (true == GameEngineInput::GetInst()->IsDown("Attack"))
	{
		if (PlayerState::WieldRight == PlayerCurState_)
		{
			PlayerPrevState_ = PlayerCurState_;
			PlayerChangeState(PlayerState::WieldRight_1);
			return;
		}

		if (PlayerState::WieldRight_1 == PlayerCurState_)
		{
			PlayerPrevState_ = PlayerCurState_;
			PlayerChangeState(PlayerState::WieldRight);
			return;
		}

		if (PlayerState::WieldLeft == PlayerCurState_)
		{
			PlayerPrevState_ = PlayerCurState_;
			PlayerChangeState(PlayerState::WieldLeft_1);
			return;
		}

		if (PlayerState::WieldLeft_1 == PlayerCurState_)
		{
			PlayerPrevState_ = PlayerCurState_;
			PlayerChangeState(PlayerState::WieldLeft);
			return;
		}

		if (PlayerState::WieldUp == PlayerCurState_)
		{
			PlayerPrevState_ = PlayerCurState_;
			PlayerChangeState(PlayerState::WieldUp_1);
			return;
		}

		if (PlayerState::WieldUp_1 == PlayerCurState_)
		{
			PlayerPrevState_ = PlayerCurState_;
			PlayerChangeState(PlayerState::WieldUp);
			return;
		}

		if (PlayerState::WieldDown == PlayerCurState_)
		{
			PlayerPrevState_ = PlayerCurState_;
			PlayerChangeState(PlayerState::WieldDown_1);
			return;
		}

		if (PlayerState::WieldDown_1 == PlayerCurState_)
		{
			PlayerPrevState_ = PlayerCurState_;
			PlayerChangeState(PlayerState::WieldDown);
			return;
		}
	}

	AnimationTimer_ += GameEngineTime::GetDeltaTime(0);
	/////// Create Attack Collision
	if (PlayerState::WieldRight == PlayerCurState_ ||
		PlayerState::WieldRight_1 == PlayerCurState_)
	{
		WieldRightUpdate();
	}
	if (PlayerState::WieldLeft == PlayerCurState_ ||
		PlayerState::WieldLeft_1 == PlayerCurState_)
	{
		WieldLeftUpdate();
	}
	if (PlayerState::WieldUp == PlayerCurState_ ||
		PlayerState::WieldUp_1 == PlayerCurState_)
	{
		WieldUpUpdate();
	}
	if (PlayerState::WieldDown == PlayerCurState_ ||
		PlayerState::WieldDown_1 == PlayerCurState_)
	{
		WieldDownUpdate();
	}

	//////End Of Animation
	if (PlayerRenderer_->IsEndAnimation())
	{
		AnimationTimer_ = 0.0f;
		if (nullptr != SwordCollision_)
		{
			SwordCollision_->Off();
		}
		if (true == GameEngineInput::GetInst()->IsPress("Attack"))
		{
			if (PlayerState::WieldRight == PlayerCurState_)
			{
				PlayerPrevState_ = PlayerCurState_;
				PlayerChangeState(PlayerState::ChargingIdleRight);
				return;
			}
			if (PlayerState::WieldLeft == PlayerCurState_)
			{
				PlayerPrevState_ = PlayerCurState_;
				PlayerChangeState(PlayerState::ChargingIdleLeft);
				return;
			}
			if (PlayerState::WieldUp == PlayerCurState_)
			{
				PlayerPrevState_ = PlayerCurState_;
				PlayerChangeState(PlayerState::ChargingIdleUp);
				return;
			}
			if (PlayerState::WieldDown == PlayerCurState_)
			{
				PlayerPrevState_ = PlayerCurState_;
				PlayerChangeState(PlayerState::ChargingIdleDown);
				return;
			}
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
	if (true == IsKnockback_)
	{

		return;
	}

	/// ///////////////Throw
	if (true == GameEngineInput::GetInst()->IsDown("Interact"))
	{
		GameEngineSound::SoundPlayOneShot("throw.mp3");
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


		MoveCarryFunction();

		DamagedCheck();
		if (true == IsKnockback_)
		{

			return;
		}


		//////////////////Throw
		if (true == GameEngineInput::GetInst()->IsDown("Interact"))
		{
			GameEngineSound::SoundPlayOneShot("throw.mp3");
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
	if (0 == PlayerRenderer_->GetAnimationIndex())
	{
		SwordCollision_->On();
		SwordCollision_->SetScale({ 32, 48 });
		SwordCollision_ ->SetPivot({ 16, -24 });
	}

	if (1 == PlayerRenderer_->GetAnimationIndex())
	{
		SwordCollision_->SetScale({ 72, 52 });
		SwordCollision_->SetPivot({ 36, -26 });
	}

	if (2 == PlayerRenderer_->GetAnimationIndex())
	{
		SwordCollision_->SetScale({ 98, 26 });
		SwordCollision_->SetPivot({ 49, 13 });
	}

	if (3 == PlayerRenderer_->GetAnimationIndex())
	{
		SwordCollision_->SetScale({ 82, 42 });
		SwordCollision_->SetPivot({ 41, 21 });
	}

	if (4 == PlayerRenderer_->GetAnimationIndex())
	{
		SwordCollision_->SetScale({ 58, 82 });
		SwordCollision_->SetPivot({ 29, 41 });
	}
}

void PlayerLink::WieldLeftUpdate()
{
	if (0 == PlayerRenderer_->GetAnimationIndex())
	{
		SwordCollision_->On();
		SwordCollision_->SetScale({ 32, 48 });
		SwordCollision_->SetPivot({ -16, -24 });
	}

	if (1 == PlayerRenderer_->GetAnimationIndex())
	{
		SwordCollision_->SetScale({ 72, 52 });
		SwordCollision_->SetPivot({ -36, -26 });
	}

	if (2 == PlayerRenderer_->GetAnimationIndex())
	{
		SwordCollision_->SetScale({ 98, 26 });
		SwordCollision_->SetPivot({ -49, 13 });
	}

	if (3 == PlayerRenderer_->GetAnimationIndex())
	{
		SwordCollision_->SetScale({ 82, 42 });
		SwordCollision_->SetPivot({ -41, 21 });
	}

	if (4 == PlayerRenderer_->GetAnimationIndex())
	{
		SwordCollision_->SetScale({ 58, 82 });
		SwordCollision_->SetPivot({ -29, 41 });
	}

}

void PlayerLink::WieldUpUpdate()
{
	if (0 == PlayerRenderer_->GetAnimationIndex())
	{
		SwordCollision_->On();
		SwordCollision_->SetScale({ 56, 25 });
		SwordCollision_->SetPivot({ 28,-13 });
	}

	if (1 == PlayerRenderer_->GetAnimationIndex())
	{
		SwordCollision_->SetScale({ 50, 77 });
		SwordCollision_->SetPivot({ 25, -39 });
	}

	if (2 == PlayerRenderer_->GetAnimationIndex())
	{
		SwordCollision_->SetScale({ 32, 98 });
		SwordCollision_->SetPivot({ -16, -49 });
	}

	if (3 == PlayerRenderer_->GetAnimationIndex())
	{
		SwordCollision_->SetScale({ 56, 78 });
		SwordCollision_->SetPivot({ -28, -39 });
	}

	if (4 == PlayerRenderer_->GetAnimationIndex())
	{
		SwordCollision_->SetScale({ 88, 50 });
		SwordCollision_->SetPivot({ -44, -25 });
	}

}

void PlayerLink::WieldDownUpdate()
{
	if (0 == PlayerRenderer_->GetAnimationIndex())
	{
		SwordCollision_->On();
		SwordCollision_->SetScale({ 56, 18 });
		SwordCollision_->SetPivot({ -28,14 });
	}

	if (1 == PlayerRenderer_->GetAnimationIndex())
	{
		SwordCollision_->SetScale({ 60, 58 });
		SwordCollision_->SetPivot({ -30, 29 });
	}

	if (2 == PlayerRenderer_->GetAnimationIndex())
	{
		SwordCollision_->SetScale({ 24, 86 });
		SwordCollision_->SetPivot({ -4, 43 });
	}

	if (3 == PlayerRenderer_->GetAnimationIndex())
	{
		SwordCollision_->SetScale({ 30, 98 });
		SwordCollision_->SetPivot({ 15, 49 });
	}

	if (4 == PlayerRenderer_->GetAnimationIndex())
	{
		SwordCollision_->SetScale({ 66, 78 });
		SwordCollision_->SetPivot({ 33, 49 });
	}

	if (5 == PlayerRenderer_->GetAnimationIndex())
	{
		SwordCollision_->SetScale({ 82, 70 });
		SwordCollision_->SetPivot({ 41, 35 });
	}

}

void PlayerLink::ChargingUpdate()
{
	DamagedCheck();
	if (true == IsKnockback_)
	{
		return;
	}
	CurChargeTime_ += GameEngineTime::GetDeltaTime(0);

	/////// Create Sword Collision
	if (PlayerState::ChargingIdleRight == PlayerCurState_ &&
		false == IsSwordCollisionOn_)
	{
		ChargingRight();
	}
	if (PlayerState::ChargingIdleLeft == PlayerCurState_ &&
		false == IsSwordCollisionOn_)
	{
		ChargingLeft();
	}
	if (PlayerState::ChargingIdleUp == PlayerCurState_ &&
		false == IsSwordCollisionOn_)
	{
		ChargingUp();
	}
	if (PlayerState::ChargingIdleDown == PlayerCurState_ &&
		false == IsSwordCollisionOn_)
	{
		ChargingDown();
	}

	////////////////////////When Move While Charge
	if (false == IsMoveKeyFree() && PlayerState::ChargingIdleRight == PlayerCurState_)
	{
		PlayerChangeState(PlayerState::ChargingMoveRight);
		return;
	}

	if (false == IsMoveKeyFree() && PlayerState::ChargingIdleLeft == PlayerCurState_)
	{
		PlayerChangeState(PlayerState::ChargingMoveLeft);
		return;
	}

	if (false == IsMoveKeyFree() && PlayerState::ChargingIdleUp == PlayerCurState_)
	{
		PlayerChangeState(PlayerState::ChargingMoveUp);
		return;
	}

	if (false == IsMoveKeyFree() && PlayerState::ChargingIdleDown == PlayerCurState_)
	{
		PlayerChangeState(PlayerState::ChargingMoveDown);
		return;
	}


	////////////////////////When Charge Off Idle
	if ((false == GameEngineInput::GetInst()->IsPress("Attack") && ChargeTime_ > CurChargeTime_ ) || false == IsInChargingState_)
	{
		IsSwordCollisionOn_ = false;
		SwordCollision_->Off();
		IsInChargingState_ = false;
		if (PlayerState::ChargingIdleRight == PlayerCurState_)
		{
			PlayerPrevState_ = PlayerCurState_;
			if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
			{
				PlayerChangeState(PlayerState::MoveRight);
				return;
			}
			else
			{
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
				if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
				{
					PlayerChangeState(PlayerState::MoveLeft);
					return;
				}

				PlayerChangeState(PlayerState::IdleRight);
				return;
			}
		}

		if (PlayerState::ChargingIdleLeft == PlayerCurState_)
		{
			PlayerPrevState_ = PlayerCurState_;
			if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
			{
				PlayerChangeState(PlayerState::MoveLeft);
				return;
			}
			else
			{
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

				PlayerChangeState(PlayerState::IdleLeft);
				return;
			}
		}
		if (PlayerState::ChargingIdleUp == PlayerCurState_)
		{
			PlayerPrevState_ = PlayerCurState_;
			if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
			{
				PlayerChangeState(PlayerState::MoveUp);
				return;
			}
			else
			{
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

				if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
				{
					PlayerChangeState(PlayerState::MoveDown);
					return;
				}
				PlayerChangeState(PlayerState::IdleUp);
				return;
			}

		}

		if (PlayerState::ChargingIdleDown == PlayerCurState_)
		{
			PlayerPrevState_ = PlayerCurState_;
			if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
			{
				PlayerChangeState(PlayerState::MoveDown);
				return;
			}
			else
			{
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

				if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
				{
					PlayerChangeState(PlayerState::MoveUp);
					return;
				}
				PlayerChangeState(PlayerState::IdleDown);
				return;
			}
		}

	}


	////////////////////////When Charge Off Wield
	if (false == GameEngineInput::GetInst()->IsPress("Attack") && ChargeTime_ < CurChargeTime_)
	{
		IsSwordCollisionOn_ = false;
		SwordCollision_->Off();
		IsInChargingState_ = false;
		if (PlayerState::ChargingIdleRight == PlayerCurState_)
		{
			PlayerChangeState(PlayerState::ChargeWieldRight);
			return;
		}

		if (PlayerState::ChargingIdleLeft == PlayerCurState_)
		{
			PlayerChangeState(PlayerState::ChargeWieldLeft);
			return;
		}
		if (PlayerState::ChargingIdleUp == PlayerCurState_)
		{
			PlayerChangeState(PlayerState::ChargeWieldUp);
			return;
		}
		if (PlayerState::ChargingIdleDown == PlayerCurState_)
		{
			PlayerChangeState(PlayerState::ChargeWieldDown);
			return;
		}
	}
}

void PlayerLink::ChargingMoveUpdate()
{
	MoveFunction();
	DamagedCheck();
	if (true == IsKnockback_)
	{
		return;
	}
	CurChargeTime_ += GameEngineTime::GetDeltaTime(0);

	////////////////////////When Move While Charge
	// 이니셜라이징 한다 IsInChargingState_ = true; 로 바꿔줌 여기서
	if (true == IsMoveKeyFree() && PlayerState::ChargingMoveRight == PlayerCurState_)
	{
		PlayerChangeState(PlayerState::ChargingIdleRight);
		return;
	}

	if (true == IsMoveKeyFree() && PlayerState::ChargingMoveLeft == PlayerCurState_)
	{
		PlayerChangeState(PlayerState::ChargingIdleLeft);
		return;
	}

	if (true == IsMoveKeyFree() && PlayerState::ChargingMoveUp == PlayerCurState_)
	{
		PlayerChangeState(PlayerState::ChargingIdleUp);
		return;
	}

	if (true == IsMoveKeyFree() && PlayerState::ChargingMoveDown == PlayerCurState_)
	{
		PlayerChangeState(PlayerState::ChargingIdleDown);
		return;
	}




	////////////////////////When Charge Off Idle
	if ((false == GameEngineInput::GetInst()->IsPress("Attack") && ChargeTime_ > CurChargeTime_) || false ==  IsInChargingState_)
	{
		IsSwordCollisionOn_ = false;
		SwordCollision_->Off();
		IsInChargingState_ = false;
		if (PlayerState::ChargingMoveRight == PlayerCurState_)
		{
			PlayerPrevState_ = PlayerCurState_;
			if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
			{
				PlayerChangeState(PlayerState::MoveRight);
				return;
			}
			else
			{
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
				if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
				{
					PlayerChangeState(PlayerState::MoveLeft);
					return;
				}

				PlayerChangeState(PlayerState::IdleRight);
				return;
			}
		}

		if (PlayerState::ChargingMoveLeft == PlayerCurState_)
		{
			PlayerPrevState_ = PlayerCurState_;
			if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
			{
				PlayerChangeState(PlayerState::MoveLeft);
				return;
			}
			else
			{
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

				PlayerChangeState(PlayerState::IdleLeft);
				return;
			}
		}
		if (PlayerState::ChargingMoveUp == PlayerCurState_)
		{
			PlayerPrevState_ = PlayerCurState_;
			if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
			{
				PlayerChangeState(PlayerState::MoveUp);
				return;
			}
			else
			{
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

				if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
				{
					PlayerChangeState(PlayerState::MoveDown);
					return;
				}
				PlayerChangeState(PlayerState::IdleUp);
				return;
			}

		}

		if (PlayerState::ChargingMoveDown == PlayerCurState_)
		{
			PlayerPrevState_ = PlayerCurState_;
			if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
			{
				PlayerChangeState(PlayerState::MoveDown);
				return;
			}
			else
			{
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

				if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
				{
					PlayerChangeState(PlayerState::MoveUp);
					return;
				}
				PlayerChangeState(PlayerState::IdleDown);
				return;
			}
		}

	}


	////////////////////////When Charge Off Wield
	if (false == GameEngineInput::GetInst()->IsPress("Attack") && ChargeTime_ < CurChargeTime_)
	{
		IsSwordCollisionOn_ = false;
		SwordCollision_->Off();
		IsInChargingState_ = false;
		if (PlayerState::ChargingIdleRight == PlayerCurState_)
		{
			PlayerChangeState(PlayerState::ChargeWieldRight);
			return;
		}

		if (PlayerState::ChargingIdleLeft == PlayerCurState_)
		{
			PlayerChangeState(PlayerState::ChargeWieldLeft);
			return;
		}
		if (PlayerState::ChargingIdleUp == PlayerCurState_)
		{
			PlayerChangeState(PlayerState::ChargeWieldUp);
			return;
		}
		if (PlayerState::ChargingIdleDown == PlayerCurState_)
		{
			PlayerChangeState(PlayerState::ChargeWieldDown);
			return;
		}
	}
}
void PlayerLink::ChargingRight()
{
	IsInChargingState_ = true;
	IsSwordCollisionOn_ = true;
	SwordCollision_->On();
	SwordCollision_->SetScale({ 64, 24 });
	SwordCollision_->SetPivot({ 32, 12 });
}
void PlayerLink::ChargingLeft()
{
	IsInChargingState_ = true;
	IsSwordCollisionOn_ = true;
	SwordCollision_->On();
	SwordCollision_->SetScale({ 64, 24 });
	SwordCollision_->SetPivot({ -32, 12 });
}
void PlayerLink::ChargingUp()
{
	IsInChargingState_ = true;
	IsSwordCollisionOn_ = true;
	SwordCollision_->On();
	SwordCollision_->SetScale({ 22, 60 });
	SwordCollision_->SetPivot({ -11, -30 });
}
void PlayerLink::ChargingDown()
{
	IsInChargingState_ = true;
	IsSwordCollisionOn_ = true;
	SwordCollision_->On();
	SwordCollision_->SetScale({ 36, 74 });
	SwordCollision_->SetPivot({ 18, 37 });
}

void PlayerLink::ChargeWieldUpdate()
{
	{
		if (0 == PlayerRenderer_->GetAnimationIndex())
		{
			SwordCollision_->On();
			SwordCollision_->SetPivot({0, 0});
			SwordCollision_->SetScale({160, 160});

		}
	}
	////////////////////////When Charge Off Idle
	if (true == PlayerRenderer_->IsEndAnimation())
	{
		IsSwordCollisionOn_ = false;
		SwordCollision_->Off();
		IsInChargingState_ = false;
		if (PlayerState::ChargeWieldRight == PlayerCurState_)
		{
			PlayerPrevState_ = PlayerCurState_;
			if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
			{
				PlayerChangeState(PlayerState::MoveRight);
				return;
			}
			else
			{
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
				if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
				{
					PlayerChangeState(PlayerState::MoveLeft);
					return;
				}

				PlayerChangeState(PlayerState::IdleRight);
				return;
			}
		}

		if (PlayerState::ChargeWieldLeft == PlayerCurState_)
		{
			PlayerPrevState_ = PlayerCurState_;
			if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
			{
				PlayerChangeState(PlayerState::MoveLeft);
				return;
			}
			else
			{
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

				PlayerChangeState(PlayerState::IdleLeft);
				return;
			}
		}
		if (PlayerState::ChargeWieldUp == PlayerCurState_)
		{
			PlayerPrevState_ = PlayerCurState_;
			if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
			{
				PlayerChangeState(PlayerState::MoveUp);
				return;
			}
			else
			{
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

				if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
				{
					PlayerChangeState(PlayerState::MoveDown);
					return;
				}
				PlayerChangeState(PlayerState::IdleUp);
				return;
			}

		}

		if (PlayerState::ChargeWieldDown == PlayerCurState_)
		{
			PlayerPrevState_ = PlayerCurState_;
			if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
			{
				PlayerChangeState(PlayerState::MoveDown);
				return;
			}
			else
			{
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

				if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
				{
					PlayerChangeState(PlayerState::MoveUp);
					return;
				}
				PlayerChangeState(PlayerState::IdleDown);
				return;
			}
		}

	}
}


void PlayerLink::DamagedUpdate()
{
	CurKnockbackTime_ += GameEngineTime::GetDeltaTime(0);
	int Black = RGB(0, 0, 0);
	if (true == PosAndColorCheck(Black, MapColImage_))
	{
		KnockBackMoveFunction(KnockBackSpeed_);
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
		PotCarryCheck();
		if (true == IsCarry_)
		{
			return;
		}
		MoveFunction(CurSpeed_);

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
void PlayerLink::MoveFunction(float _Speed)
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
		float4 Map1f_2_Scale = float4{ 0, -4128 };
		if (false == IsMap1F_2)
		{
			MyPos += Map1f_2_Scale;
		}
		float4 MyPosTopRight = MyPos + float4{ 30.0f, -20.0f };
		float4 MyPosTopLeft = MyPos + float4{ -30.0f, -20.0f };
		float4 MyPosBotRight = MyPos + float4{ 30.0f, 42.0f };
		float4 MyPosBotLeft = MyPos + float4{ -30.0f, 42.0f };
		float4 MyPosRight = MyPos + float4{ 30.0f, 0.0f };
		float4 MyPosLeft = MyPos + float4{ -30.0f, 0.0f };
		float4 MyPosTop = MyPos + float4{ 0.0f, -20.0f };
		float4 MyPosBot = MyPos + float4{ 0.0f, 42.0f };
		float4 NextPos = MyPos + (MoveDir * GameEngineTime::GetDeltaTime(0) * _Speed);
		float4 NextRealPos = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime(0) * _Speed);
		float4 CheckPosTopRight = NextPos + float4{ 30.0f, -20.0f };
		float4 CheckPosTopLeft = NextPos + float4{ -30.0f, -20.0f };
		float4 CheckPosBotRight = NextPos + float4{ 30.0f, 42.0f };
		float4 CheckPosBotLeft = NextPos + float4{ -30.0f, 42.0f };
		float4 CheckPosRight = NextPos + float4{ 30.0f, 0.0f };
		float4 CheckPosLeft = NextPos + float4{ -30.0f, 0.0f };
		float4 CheckPosTop = NextPos + float4{ 0.0f, -20.0f };
		float4 CheckPosBot = NextPos + float4{ 0.0f, 42.0f };

		int ColorNextTopRight = CheckColMap(CheckPosTopRight)->GetImagePixel(CheckPosTopRight);
		int ColorNextTopLeft = CheckColMap(CheckPosTopLeft)->GetImagePixel(CheckPosTopLeft);
		int ColorNextBotRight = CheckColMap(CheckPosBotRight)->GetImagePixel(CheckPosBotRight);
		int ColorNextBotLeft = CheckColMap(CheckPosBotLeft)->GetImagePixel(CheckPosBotLeft);
		int ColorNextRight = CheckColMap(CheckPosRight)->GetImagePixel(CheckPosRight);
		int ColorNextLeft = CheckColMap(CheckPosLeft)->GetImagePixel(CheckPosLeft);
		int ColorNextTop = CheckColMap(CheckPosTop)->GetImagePixel(CheckPosTop);
		int ColorNextBot = CheckColMap(CheckPosBot)->GetImagePixel(CheckPosBot);


		//int ColorNextTopRight = MapColImage_->GetImagePixel(CheckPosTopRight);
		//int ColorNextTopLeft = MapColImage_->GetImagePixel(CheckPosTopLeft);
		//int ColorNextBotRight = MapColImage_->GetImagePixel(CheckPosBotRight);
		//int ColorNextBotLeft = MapColImage_->GetImagePixel(CheckPosBotLeft);
		//int ColorNextRight = MapColImage_->GetImagePixel(CheckPosRight);
		//int ColorNextLeft = MapColImage_->GetImagePixel(CheckPosLeft);
		//int ColorNextTop = MapColImage_->GetImagePixel(CheckPosTop);
		//int ColorNextBot = MapColImage_->GetImagePixel(CheckPosBot);


		if (Black != ColorNextTopRight &&
			Black != ColorNextTopLeft &&
			Black != ColorNextBotRight &&
			Black != ColorNextBotLeft &&
			Black != ColorNextRight &&
			Black != ColorNextLeft &&
			Black != ColorNextTop &&
			Black != ColorNextBot)
		{
			if (false == PlayerMoveCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
			{
				MoveDir.Normal2D();
				SetMove(MoveDir * GameEngineTime::GetDeltaTime(0) * _Speed);
			}
			else
			{
				if (true == MoveRight)
				{
					//if (false == PlayerTopRightCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect) &&
					//	false == PlayerBotRightCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					//{
					//	SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime(0) * _Speed);
					//}

					if (false == PlayerRightCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime(0) * _Speed);
					}

					if (true == PlayerTopRightCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						if (false == PlayerMiddleHorCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
						{
							SetMove(float4::DOWN * GameEngineTime::GetDeltaTime(0) * _Speed);
						}
					}

					if (true == PlayerBotRightCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						if (false == PlayerMiddleHorCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
						{
							SetMove(float4::UP * GameEngineTime::GetDeltaTime(0) * _Speed);
						}
					}
				}

				if (true == MoveLeft)
				{
					//if (false == PlayerTopLeftCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect) &&
					//	false == PlayerBotLeftCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					//{
					//	SetMove(float4::LEFT * GameEngineTime::GetDeltaTime(0) * _Speed);
					//}

					if (false == PlayerLeftCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						SetMove(float4::LEFT * GameEngineTime::GetDeltaTime(0) * _Speed);
					}

					if (true == PlayerTopLeftCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						if (false == PlayerMiddleHorCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
						{
							SetMove(float4::DOWN * GameEngineTime::GetDeltaTime(0) * _Speed);
						}
					}

					if (true == PlayerBotLeftCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						if (false == PlayerMiddleHorCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
						{
							SetMove(float4::UP * GameEngineTime::GetDeltaTime(0) * _Speed);
						}
					}
				}
				if (true == MoveUp)
				{
					//if (false == PlayerTopRightCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect) &&
					//	false == PlayerTopLeftCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					//{
					//	SetMove(float4::UP * GameEngineTime::GetDeltaTime(0) * _Speed);
					//}

					if (false == PlayerTopCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						SetMove(float4::UP * GameEngineTime::GetDeltaTime(0) * _Speed);
					}

					if (true == PlayerTopLeftCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						if (false == PlayerMiddleVerCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
						{
							SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime(0) * _Speed);
						}
					}

					if (true == PlayerTopRightCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						if (false == PlayerMiddleVerCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
						{
							SetMove(float4::LEFT * GameEngineTime::GetDeltaTime(0) * _Speed);
						}
					}
				}
				if (true == MoveDown)
				{
					//if (false == PlayerBotRightCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect) &&
					//	false == PlayerBotLeftCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					//{
					//	SetMove(float4::DOWN * GameEngineTime::GetDeltaTime(0) * _Speed);
					//}

					if (false == PlayerBotCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						SetMove(float4::DOWN * GameEngineTime::GetDeltaTime(0) * _Speed);
					}


					if (true == PlayerBotRightCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						if (false == PlayerMiddleVerCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
						{
							SetMove(float4::LEFT * GameEngineTime::GetDeltaTime(0) * _Speed);
						}
					}

					if (true == PlayerBotLeftCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						if (false == PlayerMiddleVerCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
						{
							SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime(0) * _Speed);
						}
					}

				}
			}
		}
		else
		{
		if (true == MoveRight && (false == PlayerMoveCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect)))
		{
			if (Black != MapColImage_->GetImagePixel({ MyPosTopRight.x + (MoveDir * GameEngineTime::GetDeltaTime(0) * _Speed).x, MyPosTop.y }) &&
				Black != MapColImage_->GetImagePixel({ MyPosBotRight.x + (MoveDir * GameEngineTime::GetDeltaTime(0) * _Speed).x, MyPosBot.y }) &&
				Black != MapColImage_->GetImagePixel({ MyPosRight.x + (MoveDir * GameEngineTime::GetDeltaTime(0) * _Speed).x, MyPosRight.y }))
			{
				{
					SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime(0) * _Speed);
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
						SetMove(float4::UP * GameEngineTime::GetDeltaTime(0) * _Speed);
						return;
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
					SetMove(float4::DOWN * GameEngineTime::GetDeltaTime(0) * _Speed);
				}
			}
		}

		if (true == MoveLeft && (false == PlayerMoveCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect)))
		{
			if (Black != MapColImage_->GetImagePixel({ MyPosTopLeft.x + (MoveDir * GameEngineTime::GetDeltaTime(0) * _Speed).x, MyPosTopLeft.y }) &&
				Black != MapColImage_->GetImagePixel({ MyPosBotLeft.x + (MoveDir * GameEngineTime::GetDeltaTime(0) * _Speed).x, MyPosBotLeft.y }) &&
				Black != MapColImage_->GetImagePixel({ MyPosLeft.x + (MoveDir * GameEngineTime::GetDeltaTime(0) * _Speed).x, MyPosLeft.y }))
			{
				SetMove(float4::LEFT * GameEngineTime::GetDeltaTime(0) * _Speed);
			}

			if (Black != MapColImage_->GetImagePixel(CheckPosLeft) &&
				Black != MapColImage_->GetImagePixel(CheckPosTopLeft) &&
				Black != MapColImage_->GetImagePixel(CheckPosTopRight) &&
				Black != MapColImage_->GetImagePixel(CheckPosBotRight))
			{
				if (false == MoveUp)
				{
					SetMove(float4::UP * GameEngineTime::GetDeltaTime(0) * _Speed);
					return;
				}
			}
			if (Black != MapColImage_->GetImagePixel(CheckPosLeft) &&
				Black != MapColImage_->GetImagePixel(CheckPosBotLeft) &&
				Black != MapColImage_->GetImagePixel(CheckPosTopRight) &&
				Black != MapColImage_->GetImagePixel(CheckPosBotRight))
			{
				if (false == MoveDown)
				{
					SetMove(float4::DOWN * GameEngineTime::GetDeltaTime(0) * _Speed);
				}
			}
		}

		if (true == MoveUp && (false == PlayerMoveCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect)))
		{
			if (Black != MapColImage_->GetImagePixel({ MyPosTopRight.x, MyPosTop.y + (MoveDir * GameEngineTime::GetDeltaTime(0) * _Speed).y }) &&
				Black != MapColImage_->GetImagePixel({ MyPosTopLeft.x, MyPosTop.y + (MoveDir * GameEngineTime::GetDeltaTime(0) * _Speed).y }) &&
				Black != MapColImage_->GetImagePixel({ MyPosTop.x, MyPosTop.y + (MoveDir * GameEngineTime::GetDeltaTime(0) * _Speed).y }))
			{
				SetMove(float4::UP * GameEngineTime::GetDeltaTime(0) * (_Speed - 100));
			}

			if (Black != MapColImage_->GetImagePixel(CheckPosTop) &&
				Black != MapColImage_->GetImagePixel(CheckPosTopRight) &&
				Black != MapColImage_->GetImagePixel(CheckPosBotRight) &&
				Black != MapColImage_->GetImagePixel(CheckPosBotLeft))
			{
				if (false == MoveRight)
				{
					SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime(0) * (_Speed));
					return;
				}
			}

			if (Black != MapColImage_->GetImagePixel(CheckPosTop) &&
				Black != MapColImage_->GetImagePixel(CheckPosTopLeft) &&
				Black != MapColImage_->GetImagePixel(CheckPosBotRight) &&
				Black != MapColImage_->GetImagePixel(CheckPosBotLeft))
			{
				if (false == MoveLeft)
				{
					SetMove(float4::LEFT * GameEngineTime::GetDeltaTime(0) * (_Speed));
				}
			}
		}

		if (true == MoveDown && (false == PlayerMoveCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect)))
		{
			if (Black != MapColImage_->GetImagePixel({ MyPosBotRight.x, MyPosBot.y + (MoveDir * GameEngineTime::GetDeltaTime() * _Speed).y }) &&
				Black != MapColImage_->GetImagePixel({ MyPosBotLeft.x, MyPosBot.y + (MoveDir * GameEngineTime::GetDeltaTime() * _Speed).y }) &&
				Black != MapColImage_->GetImagePixel({ MyPosBot.x, MyPosBot.y + (MoveDir * GameEngineTime::GetDeltaTime() * _Speed).y }))
			{
				SetMove(float4::DOWN * GameEngineTime::GetDeltaTime(0) * (_Speed));
			}

			if (Black != MapColImage_->GetImagePixel(CheckPosBot) &&
				Black != MapColImage_->GetImagePixel(CheckPosBotRight) &&
				Black != MapColImage_->GetImagePixel(CheckPosTopRight) &&
				Black != MapColImage_->GetImagePixel(CheckPosTopLeft))
			{
				if (false == MoveRight)
				{
					SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime(0) * (_Speed));
					return;
				}
			}

			if (Black != MapColImage_->GetImagePixel(CheckPosBot) &&
				Black != MapColImage_->GetImagePixel(CheckPosBotLeft) &&
				Black != MapColImage_->GetImagePixel(CheckPosTopRight) &&
				Black != MapColImage_->GetImagePixel(CheckPosTopLeft))
			{
				if (false == MoveLeft)
				{
					SetMove(float4::LEFT * GameEngineTime::GetDeltaTime(0) * (_Speed));
				}
			}
		}
		}
	}
}

void PlayerLink::MoveCarryFunction()
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
		int White = RGB(255, 255, 255);
		float4 MyPos = GetPosition();
		float4 Map1f_2_Scale = float4{ 0, -4128 };
		if (false == IsMap1F_2)
		{
			MyPos += Map1f_2_Scale;
		}
		float4 MyPosTopRight = MyPos + float4{ 32.0f, -21.0f };
		float4 MyPosTopLeft = MyPos + float4{ -32.0f, -21.0f };
		float4 MyPosBotRight = MyPos + float4{ 32.0f, 43.0f };
		float4 MyPosBotLeft = MyPos + float4{ -32.0f, 43.0f };
		float4 MyPosRight = MyPos + float4{ 32.0f, 0.0f };
		float4 MyPosLeft = MyPos + float4{ -32.0f, 0.0f };
		float4 MyPosTop = MyPos + float4{ 0.0f, -21.0f };
		float4 MyPosBot = MyPos + float4{ 0.0f, 43.0f };
		float4 NextPos = MyPos + (MoveDir * GameEngineTime::GetDeltaTime(0) * CurSpeed_);
		float4 NextRealPos = GetPosition() + (MoveDir * GameEngineTime::GetDeltaTime(0) * CurSpeed_);
		float4 CheckPosTopRight = NextPos + float4{ 32.0f, -21.0f };
		float4 CheckPosTopLeft = NextPos + float4{ -32.0f, -21.0f };
		float4 CheckPosBotRight = NextPos + float4{ 32.0f, 43.0f };
		float4 CheckPosBotLeft = NextPos + float4{ -32.0f, 43.0f };
		float4 CheckPosRight = NextPos + float4{ 32.0f, 0.0f };
		float4 CheckPosLeft = NextPos + float4{ -32.0f, 0.0f };
		float4 CheckPosTop = NextPos + float4{ 0.0f, -21.0f };
		float4 CheckPosBot = NextPos + float4{ 0.0f, 43.0f };


		int ColorNextTopRight = CheckCarryColMap(CheckPosTopRight)->GetImagePixel(CheckPosTopRight);
		int ColorNextTopLeft = CheckCarryColMap(CheckPosTopLeft)->GetImagePixel(CheckPosTopLeft);
		int ColorNextBotRight = CheckCarryColMap(CheckPosBotRight)->GetImagePixel(CheckPosBotRight);
		int ColorNextBotLeft = CheckCarryColMap(CheckPosBotLeft)->GetImagePixel(CheckPosBotLeft);
		int ColorNextRight = CheckCarryColMap(CheckPosRight)->GetImagePixel(CheckPosRight);
		int ColorNextLeft = CheckCarryColMap(CheckPosLeft)->GetImagePixel(CheckPosLeft);
		int ColorNextTop = CheckCarryColMap(CheckPosTop)->GetImagePixel(CheckPosTop);
		int ColorNextBot = CheckCarryColMap(CheckPosBot)->GetImagePixel(CheckPosBot);


		if (Black != ColorNextTopRight &&
			Black != ColorNextTopLeft &&
			Black != ColorNextBotRight &&
			Black != ColorNextBotLeft &&
			Black != ColorNextRight &&
			Black != ColorNextLeft &&
			Black != ColorNextTop &&
			Black != ColorNextBot)
		{
			if (false == PlayerMoveCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
			{
				MoveDir.Normal2D();
				SetMove(MoveDir * GameEngineTime::GetDeltaTime(0) * CurSpeed_);
			}
			else
			{
				if (true == MoveRight)
				{
					if (false == PlayerTopRightCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect) &&
						false == PlayerBotRightCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime(0) * CurSpeed_);
					}

					if (true == PlayerTopRightCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						if (false == PlayerMiddleHorCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
						{
							SetMove(float4::DOWN * GameEngineTime::GetDeltaTime(0) * CurSpeed_);
						}
					}

					if (true == PlayerBotRightCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						if (false == PlayerMiddleHorCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
						{
							SetMove(float4::UP * GameEngineTime::GetDeltaTime(0) * CurSpeed_);
						}
					}
				}

				if (true == MoveLeft)
				{
					if (false == PlayerTopLeftCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect) &&
						false == PlayerBotLeftCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						SetMove(float4::LEFT * GameEngineTime::GetDeltaTime(0) * CurSpeed_);
					}

					if (true == PlayerTopLeftCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						if (false == PlayerMiddleHorCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
						{
							SetMove(float4::DOWN * GameEngineTime::GetDeltaTime(0) * CurSpeed_);
						}
					}

					if (true == PlayerBotLeftCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						if (false == PlayerMiddleHorCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
						{
							SetMove(float4::UP * GameEngineTime::GetDeltaTime(0) * CurSpeed_);
						}
					}
				}
				if (true == MoveUp)
				{
					if (false == PlayerTopRightCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect) &&
						false == PlayerTopLeftCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						SetMove(float4::UP * GameEngineTime::GetDeltaTime(0) * CurSpeed_);
					}

					if (true == PlayerTopLeftCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						if (false == PlayerMiddleVerCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
						{
							SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime(0) * CurSpeed_);
						}
					}

					if (true == PlayerTopRightCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						if (false == PlayerMiddleVerCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
						{
							SetMove(float4::LEFT * GameEngineTime::GetDeltaTime(0) * CurSpeed_);
						}
					}
				}
				if (true == MoveDown)
				{
					if (false == PlayerBotRightCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect) &&
						false == PlayerBotLeftCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						SetMove(float4::DOWN * GameEngineTime::GetDeltaTime(0) * CurSpeed_);
					}

					if (true == PlayerBotRightCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						if (false == PlayerMiddleVerCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
						{
							SetMove(float4::LEFT * GameEngineTime::GetDeltaTime(0) * CurSpeed_);
						}
					}

					if (true == PlayerBotLeftCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						if (false == PlayerMiddleVerCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
						{
							SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime(0) * CurSpeed_);
						}
					}

				}
			}
		}
		else
		{

			if (true == MoveRight && (false == PlayerMoveCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect)))
			{
				if (Black != MapCarryColImage_->GetImagePixel({ MyPosTopRight.x + (MoveDir * GameEngineTime::GetDeltaTime(0) * CurSpeed_).x, MyPosTop.y }) &&
					Black != MapCarryColImage_->GetImagePixel({ MyPosBotRight.x + (MoveDir * GameEngineTime::GetDeltaTime(0) * CurSpeed_).x, MyPosBot.y }) &&
					Black != MapCarryColImage_->GetImagePixel({ MyPosRight.x + (MoveDir * GameEngineTime::GetDeltaTime(0) * CurSpeed_).x, MyPosRight.y }))
				{
					{
						SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime(0) * CurSpeed_);
					}
				}

				if (Black != MapCarryColImage_->GetImagePixel(CheckPosRight) &&
					Black != MapCarryColImage_->GetImagePixel(CheckPosTopRight) &&
					Black != MapCarryColImage_->GetImagePixel(CheckPosTopLeft) &&
					Black != MapCarryColImage_->GetImagePixel(CheckPosLeft))
				{
					{
						if (false == MoveUp)
						{
							SetMove(float4::UP * GameEngineTime::GetDeltaTime(0) * CurSpeed_);
						}
					}

				}

				if (Black != MapCarryColImage_->GetImagePixel(CheckPosRight) &&
					Black != MapCarryColImage_->GetImagePixel(CheckPosBotRight) &&
					Black != MapCarryColImage_->GetImagePixel(CheckPosTopLeft) &&
					Black != MapCarryColImage_->GetImagePixel(CheckPosBotLeft))
				{
					if (false == MoveDown)
					{
						SetMove(float4::DOWN * GameEngineTime::GetDeltaTime(0) * CurSpeed_);
					}
				}
			}

			if (true == MoveLeft && (false == PlayerMoveCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect)))
			{
				if (Black != MapCarryColImage_->GetImagePixel({ MyPosTopLeft.x + (MoveDir * GameEngineTime::GetDeltaTime(0) * CurSpeed_).x, MyPosTopLeft.y }) &&
					Black != MapCarryColImage_->GetImagePixel({ MyPosBotLeft.x + (MoveDir * GameEngineTime::GetDeltaTime(0) * CurSpeed_).x, MyPosBotLeft.y }) &&
					Black != MapCarryColImage_->GetImagePixel({ MyPosLeft.x + (MoveDir * GameEngineTime::GetDeltaTime(0) * CurSpeed_).x, MyPosLeft.y }))
				{
					SetMove(float4::LEFT * GameEngineTime::GetDeltaTime(0) * CurSpeed_);
				}

				if (Black != MapCarryColImage_->GetImagePixel(CheckPosLeft) &&
					Black != MapCarryColImage_->GetImagePixel(CheckPosTopLeft) &&
					Black != MapCarryColImage_->GetImagePixel(CheckPosTopRight) &&
					Black != MapCarryColImage_->GetImagePixel(CheckPosBotRight))
				{
					if (false == MoveUp)
					{
						SetMove(float4::UP * GameEngineTime::GetDeltaTime(0) * CurSpeed_);
					}
				}
				if (Black != MapCarryColImage_->GetImagePixel(CheckPosLeft) &&
					Black != MapCarryColImage_->GetImagePixel(CheckPosBotLeft) &&
					Black != MapCarryColImage_->GetImagePixel(CheckPosTopRight) &&
					Black != MapCarryColImage_->GetImagePixel(CheckPosBotRight))
				{
					if (false == MoveDown)
					{
						SetMove(float4::DOWN * GameEngineTime::GetDeltaTime(0) * CurSpeed_);
					}
				}
			}

			if (true == MoveUp && (false == PlayerMoveCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect)))
			{
				if (Black != MapCarryColImage_->GetImagePixel({ MyPosTopRight.x, MyPosTop.y + (MoveDir * GameEngineTime::GetDeltaTime(0) * CurSpeed_).y }) &&
					Black != MapCarryColImage_->GetImagePixel({ MyPosTopLeft.x, MyPosTop.y + (MoveDir * GameEngineTime::GetDeltaTime(0) * CurSpeed_).y }) &&
					Black != MapCarryColImage_->GetImagePixel({ MyPosTop.x, MyPosTop.y + (MoveDir * GameEngineTime::GetDeltaTime(0) * CurSpeed_).y }))
				{
					SetMove(float4::UP * GameEngineTime::GetDeltaTime(0) * CurSpeed_);
				}

				if (Black != MapCarryColImage_->GetImagePixel(CheckPosTop) &&
					Black != MapCarryColImage_->GetImagePixel(CheckPosTopRight) &&
					Black != MapCarryColImage_->GetImagePixel(CheckPosBotRight) &&
					Black != MapCarryColImage_->GetImagePixel(CheckPosBotLeft))
				{
					if (false == MoveRight)
					{
						SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime(0) * CurSpeed_);
					}
				}

				if (Black != MapCarryColImage_->GetImagePixel(CheckPosTop) &&
					Black != MapCarryColImage_->GetImagePixel(CheckPosTopLeft) &&
					Black != MapCarryColImage_->GetImagePixel(CheckPosBotRight) &&
					Black != MapCarryColImage_->GetImagePixel(CheckPosBotLeft))
				{
					if (false == MoveLeft)
					{
						SetMove(float4::LEFT * GameEngineTime::GetDeltaTime(0) * CurSpeed_);
					}
				}
			}

			if (true == MoveDown && (false == PlayerMoveCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect)))
			{
				if (Black != MapCarryColImage_->GetImagePixel({ MyPosBotRight.x, MyPosBot.y + (MoveDir * GameEngineTime::GetDeltaTime(0) * CurSpeed_).y }) &&
					Black != MapCarryColImage_->GetImagePixel({ MyPosBotLeft.x, MyPosBot.y + (MoveDir * GameEngineTime::GetDeltaTime(0) * CurSpeed_).y }) &&
					Black != MapCarryColImage_->GetImagePixel({ MyPosBot.x, MyPosBot.y + (MoveDir * GameEngineTime::GetDeltaTime(0) * CurSpeed_).y }))
				{
					SetMove(float4::DOWN * GameEngineTime::GetDeltaTime(0) * CurSpeed_);
				}

				if (Black != MapCarryColImage_->GetImagePixel(CheckPosBot) &&
					Black != MapCarryColImage_->GetImagePixel(CheckPosBotRight) &&
					Black != MapCarryColImage_->GetImagePixel(CheckPosTopRight) &&
					Black != MapCarryColImage_->GetImagePixel(CheckPosTopLeft))
				{
					if (false == MoveRight)
					{
						SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime(0) * CurSpeed_);
					}
				}

				if (Black != MapCarryColImage_->GetImagePixel(CheckPosBot) &&
					Black != MapCarryColImage_->GetImagePixel(CheckPosBotLeft) &&
					Black != MapCarryColImage_->GetImagePixel(CheckPosTopRight) &&
					Black != MapCarryColImage_->GetImagePixel(CheckPosTopLeft))
				{
					if (false == MoveLeft)
					{
						SetMove(float4::LEFT * GameEngineTime::GetDeltaTime(0) * CurSpeed_);
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
	SwordSoundPlayer_.Stop();
	SwordSoundPlayer_ = GameEngineSound::SoundPlayControl("fightersword.mp3");
	AnimationTimer_ = 0.0f;
	SwordCollision_->Off();
	PlayerPrevState_ = PlayerState::WieldRight;
	PlayerRenderer_->ChangeAnimationReset("Wield_Right");
}

void PlayerLink::WieldLeftStart()
{
	SwordSoundPlayer_.Stop();
		SwordSoundPlayer_ = GameEngineSound::SoundPlayControl("fightersword.mp3");;
	AnimationTimer_ = 0.0f;
	SwordCollision_->Off();
	PlayerPrevState_ = PlayerState::WieldLeft;
	PlayerRenderer_->ChangeAnimationReset("Wield_Left");
}

void PlayerLink::WieldUpStart()
{
	SwordSoundPlayer_.Stop();
	SwordSoundPlayer_ = GameEngineSound::SoundPlayControl("fightersword.mp3");
	AnimationTimer_ = 0.0f;
	SwordCollision_->Off();
	PlayerPrevState_ = PlayerState::WieldUp;
	PlayerRenderer_->ChangeAnimationReset("Wield_Up");
}

void PlayerLink::WieldDownStart()
{
	SwordSoundPlayer_.Stop();
	SwordSoundPlayer_ = GameEngineSound::SoundPlayControl("fightersword.mp3");
	AnimationTimer_ = 0.0f;
	SwordCollision_->Off();
	PlayerPrevState_ = PlayerState::WieldDown;
	PlayerRenderer_->ChangeAnimationReset("Wield_Down");
}

void PlayerLink::ChargingIdleRightStart()
{
	PlayerRenderer_->ChangeAnimationReset("Charge_Idle_Right");
}

void PlayerLink::ChargingIdleLeftStart()
{
	PlayerRenderer_->ChangeAnimationReset("Charge_Idle_Left");
}

void PlayerLink::ChargingIdleUpStart()
{
	PlayerRenderer_->ChangeAnimationReset("Charge_Idle_Up");
}

void PlayerLink::ChargingIdleDownStart()
{
	PlayerRenderer_->ChangeAnimationReset("Charge_Idle_Down");
}

void PlayerLink::ChargingMoveRightStart()
{
	PlayerRenderer_->ChangeAnimationReset("Charge_Move_Right");
}

void PlayerLink::ChargingMoveLeftStart()
{
	PlayerRenderer_->ChangeAnimationReset("Charge_Move_Left");
}

void PlayerLink::ChargingMoveUpStart()
{
	PlayerRenderer_->ChangeAnimationReset("Charge_Move_Up");
}

void PlayerLink::ChargingMoveDownStart()
{
	PlayerRenderer_->ChangeAnimationReset("Charge_Move_Down");
}

void PlayerLink::ChargeWieldRightStart()
{
	PlayerRenderer_->ChangeAnimationReset("Charge_Wield_Right");
}

void PlayerLink::ChargeWieldLeftStart()
{
	PlayerRenderer_->ChangeAnimationReset("Charge_Wield_Left");
}

void PlayerLink::ChargeWieldUpStart()
{
	PlayerRenderer_->ChangeAnimationReset("Charge_Wield_Up");
}

void PlayerLink::ChargeWieldDownStart()
{
	PlayerRenderer_->ChangeAnimationReset("Charge_Wield_Down");
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
	GameEngineSound::SoundPlayOneShot("lift.mp3");
	PlayerRenderer_->ChangeAnimationReset("Carry_Start_Right");
}

void PlayerLink::CarryStartLeftStart()
{
	GameEngineSound::SoundPlayOneShot("lift.mp3");
	PlayerRenderer_->ChangeAnimationReset("Carry_Start_Left");
}

void PlayerLink::CarryStartUpStart()
{
	GameEngineSound::SoundPlayOneShot("lift.mp3");
	PlayerRenderer_->ChangeAnimationReset("Carry_Start_Up");
}

void PlayerLink::CarryStartDownStart()
{
	GameEngineSound::SoundPlayOneShot("lift.mp3");
	PlayerRenderer_->ChangeAnimationReset("Carry_Start_Down");
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
	if (true == PlayerCollision_->CollisionResult("MonsterHitBox", ColList, CollisionType::Rect, CollisionType::Rect) && 
		PlayerStairsState::Top == CurStairs_ &&
		false == IsKnockback_ && 
		false == IsBlink_)
	{
		GetDamaged();
		PlayerPrevState_ = PlayerCurState_;
		IsKnockback_ = true;
		IsBlink_ = true;
		IsCarry_ = false;
		HitActor_ = ColList[0]->GetActor();
		KnockbackDir_ = GetPosition() - HitActor_->GetPosition();
		KnockbackDir_.Normal2D();
		if (PlayerState::IdleRight == PlayerCurState_ ||
			PlayerState::MoveRight == PlayerCurState_ ||
			PlayerState::WieldRight == PlayerCurState_ ||
			PlayerState::CarryIdleRight == PlayerPrevState_ ||
			PlayerState::CarryMoveRight == PlayerPrevState_ ||
			PlayerState::ChargingIdleRight == PlayerPrevState_ ||
			PlayerState::ChargingMoveRight == PlayerPrevState_)
		{
			PlayerChangeState(PlayerState::DamagedRight);
			return;
		}
		if (PlayerState::IdleLeft == PlayerCurState_ ||
			PlayerState::MoveLeft == PlayerCurState_ ||
			PlayerState::WieldLeft == PlayerCurState_ ||
			PlayerState::CarryIdleLeft == PlayerPrevState_ ||
			PlayerState::CarryMoveLeft == PlayerPrevState_ ||
			PlayerState::ChargingIdleLeft == PlayerPrevState_ ||
			PlayerState::ChargingMoveLeft == PlayerPrevState_)
		{
			PlayerChangeState(PlayerState::DamagedLeft);
			return;
		}
		if (PlayerState::IdleUp == PlayerCurState_ ||
			PlayerState::MoveUp == PlayerCurState_ ||
			PlayerState::WieldUp == PlayerCurState_ ||
			PlayerState::CarryIdleUp == PlayerPrevState_ ||
			PlayerState::CarryMoveUp == PlayerPrevState_ ||
			PlayerState::ChargingIdleUp == PlayerPrevState_ ||
			PlayerState::ChargingMoveUp== PlayerPrevState_)
		{
			PlayerChangeState(PlayerState::DamagedUp);
			return;
		}
		if (PlayerState::IdleDown == PlayerCurState_ ||
			PlayerState::MoveDown == PlayerCurState_ ||
			PlayerState::WieldDown == PlayerCurState_ ||
			PlayerState::CarryIdleDown == PlayerPrevState_ ||
			PlayerState::CarryMoveDown == PlayerPrevState_ ||
			PlayerState::ChargingIdleDown == PlayerPrevState_ ||
			PlayerState::ChargingMoveDown == PlayerPrevState_)
		{
			PlayerChangeState(PlayerState::DamagedDown);
			return;
		}
	}

	if (true == PlayerCollision_->CollisionResult("MonsterB1FHitBox", ColList, CollisionType::Rect, CollisionType::Rect) &&
		PlayerStairsState::Bot == CurStairs_ &&
		false == IsKnockback_ &&
		false == IsBlink_)
	{
		GetDamaged();
		PlayerPrevState_ = PlayerCurState_;
		IsKnockback_ = true;
		IsBlink_ = true;
		IsCarry_ = false;
		HitActor_ = ColList[0]->GetActor();
		KnockbackDir_ = GetPosition() - HitActor_->GetPosition();
		KnockbackDir_.Normal2D();
		if (PlayerState::IdleRight == PlayerCurState_ ||
			PlayerState::MoveRight == PlayerCurState_ ||
			PlayerState::WieldRight == PlayerCurState_ ||
			PlayerState::CarryIdleRight == PlayerPrevState_ ||
			PlayerState::CarryMoveRight == PlayerPrevState_)
		{
			PlayerChangeState(PlayerState::DamagedRight);
			return;
		}
		if (PlayerState::IdleLeft == PlayerCurState_ ||
			PlayerState::MoveLeft == PlayerCurState_ ||
			PlayerState::WieldLeft == PlayerCurState_ ||
			PlayerState::CarryIdleLeft == PlayerPrevState_ ||
			PlayerState::CarryMoveLeft == PlayerPrevState_)
		{
			PlayerChangeState(PlayerState::DamagedLeft);
			return;
		}
		if (PlayerState::IdleUp == PlayerCurState_ ||
			PlayerState::MoveUp == PlayerCurState_ ||
			PlayerState::WieldUp == PlayerCurState_ ||
			PlayerState::CarryIdleUp == PlayerPrevState_ ||
			PlayerState::CarryMoveUp == PlayerPrevState_)
		{
			PlayerChangeState(PlayerState::DamagedUp);
			return;
		}
		if (PlayerState::IdleDown == PlayerCurState_ ||
			PlayerState::MoveDown == PlayerCurState_ ||
			PlayerState::WieldDown == PlayerCurState_ ||
			PlayerState::CarryIdleDown == PlayerPrevState_ ||
			PlayerState::CarryMoveDown == PlayerPrevState_)
		{
			PlayerChangeState(PlayerState::DamagedDown);
			return;
		}
	}
}

void PlayerLink::PotCarryCheck()
{
	std::vector<GameEngineCollision*> ColList;
	if (true == PlayerMoveCollision_->CollisionResult("PotCarry", ColList, CollisionType::Rect, CollisionType::Rect) && true == GameEngineInput::GetInst()->IsDown("Interact"))
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

void PlayerLink::TreasureBoxCheck()
{
	std::vector<GameEngineCollision*> ColList;
	if (true == PlayerHigherBodyCollision_->CollisionResult("TreasureBox", ColList, CollisionType::Rect, CollisionType::Rect) &&
		true == GameEngineInput::GetInst()->IsDown("Interact") && false == IsInItemCutScene_ && CameraState::Room8 == CameraState_)
	{
		BGMSoundPlayer_.Stop();
		GameEngineSound::SoundPlayOneShot("itemget.mp3");
		IsInItemCutScene_ = true;
		Map1F_2::Room8TreasureBox_->Death();
		Map1F_2::Room8TreasureBoxCol_->Death();
		GameEngineTime::GetInst()->SetTimeScale(0, 0.0f);
		int IntValue = (static_cast<int>(CameraState_) + 2) / 2;
		GameEngineTime::GetInst()->SetTimeScale(IntValue, 0.0f);
		return;
	}

	if (true == PlayerHigherBodyCollision_->CollisionResult("TreasureBox", ColList, CollisionType::Rect, CollisionType::Rect) &&
		true == GameEngineInput::GetInst()->IsDown("Interact") && false == IsInItemCutScene_ && CameraState::Room4 == CameraState_)
	{
		BGMSoundPlayer_.Stop();
		GameEngineSound::SoundPlayOneShot("itemget.mp3");
		IsInItemCutScene_ = true;
		Map1F_2::Room4TreasureBox_->Death();
		Map1F_2::Room4TreasureBoxCol_->Death();
		GameEngineTime::GetInst()->SetTimeScale(0, 0.0f);
		int IntValue = (static_cast<int>(CameraState_) + 2) / 2;
		GameEngineTime::GetInst()->SetTimeScale(IntValue, 0.0f);
		return;
	}

	if (true == PlayerHigherBodyCollision_->CollisionResult("TreasureBox", ColList, CollisionType::Rect, CollisionType::Rect) &&
		true == GameEngineInput::GetInst()->IsDown("Interact") && false == IsInItemCutScene_ && CameraState::Room3 == CameraState_)
	{
		BGMSoundPlayer_.Stop();
		GameEngineSound::SoundPlayOneShot("itemget.mp3");
		IsInItemCutScene_ = true;
		Map1F_2::Room3TreasureBox_->Death();
		Map1F_2::Room3TreasureBoxCol_->Death();
		GameEngineTime::GetInst()->SetTimeScale(0, 0.0f);
		int IntValue = (static_cast<int>(CameraState_) + 2) / 2;
		GameEngineTime::GetInst()->SetTimeScale(IntValue, 0.0f);
		return;
	}

	if (true == PlayerHigherBodyCollision_->CollisionResult("TreasureBox", ColList, CollisionType::Rect, CollisionType::Rect) &&
		true == GameEngineInput::GetInst()->IsDown("Interact") && false == IsInItemCutScene_ && CameraState::Room10 == CameraState_)
	{
		BGMSoundPlayer_.Stop();
		GameEngineSound::SoundPlayOneShot("itemget.mp3");
		IsInItemCutScene_ = true;
		Map1F_2::Room10TreasureBox_->Death();
		Map1F_2::Room10TreasureBoxCol_->Death();
		GameEngineTime::GetInst()->SetTimeScale(0, 0.0f);
		int IntValue = (static_cast<int>(CameraState_) + 2) / 2;
		GameEngineTime::GetInst()->SetTimeScale(IntValue, 0.0f);
		return;
	}

	if (true == IsInItemCutScene_)
	{
		CurItemMoveTime_ += GameEngineTime::GetDeltaTime();
		if (ItemMoveTime_ < CurItemMoveTime_)
		{
			if (true == GameEngineInput::GetInst()->IsDown("Interact") && true == IsInItemCutScene_)
			{
				IsInItemCutScene_ = false;
				GameEngineTime::GetInst()->SetTimeScale(0, 1.0f);
				int IntValue = (static_cast<int>(CameraState_) + 2) / 2;
				GameEngineTime::GetInst()->SetTimeScale(IntValue, 1.0f);
				if (CameraState::Room8 == CameraState_)
				{
					BGMSoundPlayer_ = GameEngineSound::SoundPlayControl("dungeon.mp3", -1);
					Map1F_2::Room8ItemRenderer_->Death();
					return;
				}
				if (CameraState::Room4 == CameraState_)
				{
					BGMSoundPlayer_ = GameEngineSound::SoundPlayControl("dungeon.mp3", -1);
					PlayerRupee_ += 50;
					Map1F_2::Room4ItemRenderer_->Death();
					return;
				}
				if (CameraState::Room3 == CameraState_)
				{
					BGMSoundPlayer_ = GameEngineSound::SoundPlayControl("dungeon.mp3", -1);
					IsHaveBigKey_ = true;
					Map1F_2::Room3ItemRenderer_->Death();
					return;
				}
				if (CameraState::Room10 == CameraState_)
				{
					BGMSoundPlayer_ = GameEngineSound::SoundPlayControl("dungeon.mp3", -1);
					Map1F_2::Room10ItemRenderer_->Death();
					return;
				}
			}
		}
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
		PlayerState::MoveUp == PlayerPrevState_ ||
		PlayerState::WieldUp == PlayerPrevState_ ||
		PlayerState::CarryIdleUp == PlayerPrevState_ ||
		PlayerState::CarryMoveUp == PlayerPrevState_ ||
		PlayerState::ChargingIdleUp == PlayerPrevState_||
		PlayerState::ChargingMoveUp == PlayerPrevState_)
	{
		PlayerChangeState(PlayerState::IdleUp);
		return;
	}
	if (PlayerState::IdleDown == PlayerPrevState_ ||
		PlayerState::MoveDown == PlayerPrevState_ ||
		PlayerState::WieldDown == PlayerPrevState_ ||
		PlayerState::CarryIdleDown == PlayerPrevState_ ||
		PlayerState::CarryMoveDown == PlayerPrevState_ ||
		PlayerState::ChargingIdleDown == PlayerPrevState_ ||
		PlayerState::ChargingMoveDown == PlayerPrevState_)
	{
		PlayerChangeState(PlayerState::IdleDown);
		return;
	}
	if (PlayerState::IdleRight == PlayerPrevState_ ||
		PlayerState::MoveRight == PlayerPrevState_ ||
		PlayerState::WieldRight == PlayerPrevState_ ||
		PlayerState::CarryIdleRight == PlayerPrevState_ ||
		PlayerState::CarryMoveRight == PlayerPrevState_ ||
		PlayerState::ChargingIdleRight == PlayerPrevState_ ||
		PlayerState::ChargingMoveRight == PlayerPrevState_)
	{
		PlayerChangeState(PlayerState::IdleRight);
		return;
	}
	if (PlayerState::IdleLeft == PlayerPrevState_ ||
		PlayerState::MoveLeft == PlayerPrevState_ ||
		PlayerState::WieldLeft == PlayerPrevState_ ||
		PlayerState::CarryIdleLeft == PlayerPrevState_ ||
		PlayerState::CarryMoveLeft == PlayerPrevState_ ||
		PlayerState::ChargingIdleLeft == PlayerPrevState_ ||
		PlayerState::ChargingMoveLeft == PlayerPrevState_)
	{
		PlayerChangeState(PlayerState::IdleLeft);
		return;
	}
}

GameEngineImage* PlayerLink::CheckColMap(float4& _Pos)
{
	if (0 > _Pos.y )
	{
		_Pos.y = -_Pos.y;
		return MapColImage_2_;
	}

	if (4128 < _Pos.y )
	{
		_Pos.y = 4128 - _Pos.y;
		return MapColImage_1_;
	}

	return MapColImage_;
}

GameEngineImage* PlayerLink::CheckCarryColMap(float4& _Pos)
{
	if (0 > _Pos.y)
	{
		_Pos.y = -_Pos.y;
		return MapCarryColImage_2_;
	}

	if (4128 < _Pos.y)
	{
		_Pos.y = 4128 - _Pos.y;
		return MapCarryColImage_1_;
	}

	return MapCarryColImage_;
}


void PlayerLink::KnockBackMoveFunction(float _Speed)
{
	float4 CheckPos;
	//맵 이미지와 캐릭터의 이미지의 픽셀 위치를 동일하게 맞춰놔야한다
	bool MoveLeft = false;
	bool MoveRight = false;
	bool MoveUp = false;
	bool MoveDown = false;
	EnemyGlobalFunction::MoveDirBoolCheck(MoveRight, MoveLeft, MoveUp, MoveDown, KnockbackDir_);
	//SetMove(MoveDir * GameEngineTime::GetDeltaTime(0) * Speed_);
	{
		int Black = RGB(0, 0, 0);
		float4 MyPos = GetPosition();
		float4 Map1f_2_Scale = float4{ 0, -4128 };
		if (false == IsMap1F_2)
		{
			MyPos += Map1f_2_Scale;
		}
		float4 MyPosTopRight = MyPos + float4{ 32.0f, -21.0f };
		float4 MyPosTopLeft = MyPos + float4{ -32.0f, -21.0f };
		float4 MyPosBotRight = MyPos + float4{ 32.0f, 43.0f };
		float4 MyPosBotLeft = MyPos + float4{ -32.0f, 43.0f };
		float4 MyPosRight = MyPos + float4{ 32.0f, 0.0f };
		float4 MyPosLeft = MyPos + float4{ -32.0f, 0.0f };
		float4 MyPosTop = MyPos + float4{ 0.0f, -21.0f };
		float4 MyPosBot = MyPos + float4{ 0.0f, 43.0f };
		float4 NextPos = MyPos + (KnockbackDir_ * GameEngineTime::GetDeltaTime(0) * _Speed);
		float4 NextRealPos = GetPosition() + (KnockbackDir_ * GameEngineTime::GetDeltaTime(0) * _Speed);
		float4 CheckPosTopRight = NextPos + float4{ 32.0f, -21.0f };
		float4 CheckPosTopLeft = NextPos + float4{ -32.0f, -21.0f };
		float4 CheckPosBotRight = NextPos + float4{ 32.0f, 43.0f };
		float4 CheckPosBotLeft = NextPos + float4{ -32.0f, 43.0f };
		float4 CheckPosRight = NextPos + float4{ 32.0f, 0.0f };
		float4 CheckPosLeft = NextPos + float4{ -32.0f, 0.0f };
		float4 CheckPosTop = NextPos + float4{ 0.0f, -21.0f };
		float4 CheckPosBot = NextPos + float4{ 0.0f, 43.0f };

		int ColorNextTopRight = CheckColMap(CheckPosTopRight)->GetImagePixel(CheckPosTopRight);
		int ColorNextTopLeft = CheckColMap(CheckPosTopLeft)->GetImagePixel(CheckPosTopLeft);
		int ColorNextBotRight = CheckColMap(CheckPosBotRight)->GetImagePixel(CheckPosBotRight);
		int ColorNextBotLeft = CheckColMap(CheckPosBotLeft)->GetImagePixel(CheckPosBotLeft);
		int ColorNextRight = CheckColMap(CheckPosRight)->GetImagePixel(CheckPosRight);
		int ColorNextLeft = CheckColMap(CheckPosLeft)->GetImagePixel(CheckPosLeft);
		int ColorNextTop = CheckColMap(CheckPosTop)->GetImagePixel(CheckPosTop);
		int ColorNextBot = CheckColMap(CheckPosBot)->GetImagePixel(CheckPosBot);


		//int ColorNextTopRight = MapColImage_->GetImagePixel(CheckPosTopRight);
		//int ColorNextTopLeft = MapColImage_->GetImagePixel(CheckPosTopLeft);
		//int ColorNextBotRight = MapColImage_->GetImagePixel(CheckPosBotRight);
		//int ColorNextBotLeft = MapColImage_->GetImagePixel(CheckPosBotLeft);
		//int ColorNextRight = MapColImage_->GetImagePixel(CheckPosRight);
		//int ColorNextLeft = MapColImage_->GetImagePixel(CheckPosLeft);
		//int ColorNextTop = MapColImage_->GetImagePixel(CheckPosTop);
		//int ColorNextBot = MapColImage_->GetImagePixel(CheckPosBot);


		if (Black != ColorNextTopRight &&
			Black != ColorNextTopLeft &&
			Black != ColorNextBotRight &&
			Black != ColorNextBotLeft &&
			Black != ColorNextRight &&
			Black != ColorNextLeft &&
			Black != ColorNextTop &&
			Black != ColorNextBot)
		{
			if (false == PlayerMoveCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
			{
				KnockbackDir_.Normal2D();
				SetMove(KnockbackDir_ * GameEngineTime::GetDeltaTime(0) * _Speed);
			}
			else
			{
				if (true == MoveRight)
				{
					if (false == PlayerTopRightCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect) &&
						false == PlayerBotRightCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime(0) * _Speed);
					}

					if (true == PlayerTopRightCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						if (false == PlayerMiddleHorCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
						{
							SetMove(float4::DOWN * GameEngineTime::GetDeltaTime(0) * _Speed);
						}
					}

					if (true == PlayerBotRightCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						if (false == PlayerMiddleHorCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
						{
							SetMove(float4::UP * GameEngineTime::GetDeltaTime(0) * _Speed);
						}
					}
				}

				if (true == MoveLeft)
				{
					if (false == PlayerTopLeftCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect) &&
						false == PlayerBotLeftCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						SetMove(float4::LEFT * GameEngineTime::GetDeltaTime(0) * _Speed);
					}

					if (true == PlayerTopLeftCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						if (false == PlayerMiddleHorCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
						{
							SetMove(float4::DOWN * GameEngineTime::GetDeltaTime(0) * _Speed);
						}
					}

					if (true == PlayerBotLeftCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						if (false == PlayerMiddleHorCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
						{
							SetMove(float4::UP * GameEngineTime::GetDeltaTime(0) * _Speed);
						}
					}
				}
				if (true == MoveUp)
				{
					if (false == PlayerTopRightCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect) &&
						false == PlayerTopLeftCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						SetMove(float4::UP * GameEngineTime::GetDeltaTime(0) * _Speed);
					}

					if (true == PlayerTopLeftCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						if (false == PlayerMiddleVerCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
						{
							SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime(0) * _Speed);
						}
					}

					if (true == PlayerTopRightCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						if (false == PlayerMiddleVerCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
						{
							SetMove(float4::LEFT * GameEngineTime::GetDeltaTime(0) * _Speed);
						}
					}
				}
				if (true == MoveDown)
				{
					if (false == PlayerBotRightCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect) &&
						false == PlayerBotLeftCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						SetMove(float4::DOWN * GameEngineTime::GetDeltaTime(0) * _Speed);
					}

					if (true == PlayerBotRightCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						if (false == PlayerMiddleVerCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
						{
							SetMove(float4::LEFT * GameEngineTime::GetDeltaTime(0) * _Speed);
						}
					}

					if (true == PlayerBotLeftCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
					{
						if (false == PlayerMiddleVerCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect))
						{
							SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime(0) * _Speed);
						}
					}

				}
			}
		}
		else
		{
			if (true == MoveRight && (false == PlayerMoveCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect)))
			{
				if (Black != MapColImage_->GetImagePixel({ MyPosTopRight.x + (KnockbackDir_ * GameEngineTime::GetDeltaTime(0) * CurSpeed_).x, MyPosTop.y }) &&
					Black != MapColImage_->GetImagePixel({ MyPosBotRight.x + (KnockbackDir_ * GameEngineTime::GetDeltaTime(0) * CurSpeed_).x, MyPosBot.y }) &&
					Black != MapColImage_->GetImagePixel({ MyPosRight.x + (KnockbackDir_ * GameEngineTime::GetDeltaTime(0) * CurSpeed_).x, MyPosRight.y }))
				{
					{
						SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime(0) * _Speed);
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
							SetMove(float4::UP * GameEngineTime::GetDeltaTime(0) * _Speed);
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
						SetMove(float4::DOWN * GameEngineTime::GetDeltaTime(0) * _Speed);
					}
				}
			}

			if (true == MoveLeft && (false == PlayerMoveCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect)))
			{
				if (Black != MapColImage_->GetImagePixel({ MyPosTopLeft.x + (KnockbackDir_ * GameEngineTime::GetDeltaTime(0) * CurSpeed_).x, MyPosTopLeft.y }) &&
					Black != MapColImage_->GetImagePixel({ MyPosBotLeft.x + (KnockbackDir_ * GameEngineTime::GetDeltaTime(0) * CurSpeed_).x, MyPosBotLeft.y }) &&
					Black != MapColImage_->GetImagePixel({ MyPosLeft.x + (KnockbackDir_ * GameEngineTime::GetDeltaTime(0) * CurSpeed_).x, MyPosLeft.y }))
				{
					SetMove(float4::LEFT * GameEngineTime::GetDeltaTime(0) * _Speed);
				}

				if (Black != MapColImage_->GetImagePixel(CheckPosLeft) &&
					Black != MapColImage_->GetImagePixel(CheckPosTopLeft) &&
					Black != MapColImage_->GetImagePixel(CheckPosTopRight) &&
					Black != MapColImage_->GetImagePixel(CheckPosBotRight))
				{
					if (false == MoveUp)
					{
						SetMove(float4::UP * GameEngineTime::GetDeltaTime(0) * _Speed);
					}
				}
				if (Black != MapColImage_->GetImagePixel(CheckPosLeft) &&
					Black != MapColImage_->GetImagePixel(CheckPosBotLeft) &&
					Black != MapColImage_->GetImagePixel(CheckPosTopRight) &&
					Black != MapColImage_->GetImagePixel(CheckPosBotRight))
				{
					if (false == MoveDown)
					{
						SetMove(float4::DOWN * GameEngineTime::GetDeltaTime(0) * _Speed);
					}
				}
			}

			if (true == MoveUp && (false == PlayerMoveCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect)))
			{
				if (Black != MapColImage_->GetImagePixel({ MyPosTopRight.x, MyPosTop.y + (KnockbackDir_ * GameEngineTime::GetDeltaTime(0) * CurSpeed_).y }) &&
					Black != MapColImage_->GetImagePixel({ MyPosTopLeft.x, MyPosTop.y + (KnockbackDir_ * GameEngineTime::GetDeltaTime(0) * CurSpeed_).y }) &&
					Black != MapColImage_->GetImagePixel({ MyPosTop.x, MyPosTop.y + (KnockbackDir_ * GameEngineTime::GetDeltaTime(0) * CurSpeed_).y }))
				{
					SetMove(float4::UP * GameEngineTime::GetDeltaTime(0) * _Speed);
				}

				if (Black != MapColImage_->GetImagePixel(CheckPosTop) &&
					Black != MapColImage_->GetImagePixel(CheckPosTopRight) &&
					Black != MapColImage_->GetImagePixel(CheckPosBotRight) &&
					Black != MapColImage_->GetImagePixel(CheckPosBotLeft))
				{
					if (false == MoveRight)
					{
						SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime(0) * _Speed);
					}
				}

				if (Black != MapColImage_->GetImagePixel(CheckPosTop) &&
					Black != MapColImage_->GetImagePixel(CheckPosTopLeft) &&
					Black != MapColImage_->GetImagePixel(CheckPosBotRight) &&
					Black != MapColImage_->GetImagePixel(CheckPosBotLeft))
				{
					if (false == MoveLeft)
					{
						SetMove(float4::LEFT * GameEngineTime::GetDeltaTime(0) * _Speed);
					}
				}
			}

			if (true == MoveDown && (false == PlayerMoveCollision_->NextPostCollisionCheck("Block", NextRealPos, CollisionType::Rect, CollisionType::Rect)))
			{
				if (Black != MapColImage_->GetImagePixel({ MyPosBotRight.x, MyPosBot.y + (KnockbackDir_ * GameEngineTime::GetDeltaTime() * CurSpeed_).y }) &&
					Black != MapColImage_->GetImagePixel({ MyPosBotLeft.x, MyPosBot.y + (KnockbackDir_ * GameEngineTime::GetDeltaTime() * CurSpeed_).y }) &&
					Black != MapColImage_->GetImagePixel({ MyPosBot.x, MyPosBot.y + (KnockbackDir_ * GameEngineTime::GetDeltaTime() * CurSpeed_).y }))
				{
					SetMove(float4::DOWN * GameEngineTime::GetDeltaTime(0) * _Speed);
				}

				if (Black != MapColImage_->GetImagePixel(CheckPosBot) &&
					Black != MapColImage_->GetImagePixel(CheckPosBotRight) &&
					Black != MapColImage_->GetImagePixel(CheckPosTopRight) &&
					Black != MapColImage_->GetImagePixel(CheckPosTopLeft))
				{
					if (false == MoveRight)
					{
						SetMove(float4::RIGHT * GameEngineTime::GetDeltaTime(0) * _Speed);
					}
				}

				if (Black != MapColImage_->GetImagePixel(CheckPosBot) &&
					Black != MapColImage_->GetImagePixel(CheckPosBotLeft) &&
					Black != MapColImage_->GetImagePixel(CheckPosTopRight) &&
					Black != MapColImage_->GetImagePixel(CheckPosTopLeft))
				{
					if (false == MoveLeft)
					{
						SetMove(float4::LEFT * GameEngineTime::GetDeltaTime(0) * _Speed);
					}
				}
			}
		}
	}
}