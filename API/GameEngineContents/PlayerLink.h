#pragma once
#include <GameEngine/GameEngineActor.h>
#include "GameEngineContentsEnum.h"
#include <GameEngineBase/GameEngineSound.h>
// Ό³Έν :
class GameEngineImage;
class GmaeEngineCollision;
class Map1FBridge;




class PlayerLink : public GameEngineActor
{
public:
	// constrcuter destructer
	PlayerLink();
	~PlayerLink();

	// delete Function
	PlayerLink(const PlayerLink& _Other) = delete;
	PlayerLink(PlayerLink&& _Other) noexcept = delete;
	PlayerLink& operator=(const PlayerLink& _Other) = delete;
	PlayerLink& operator=(PlayerLink&& _Other) noexcept = delete;

	Map1FBridge* BridgeActor_;
	void SetBridgeActor(Map1FBridge* _BridgeActor)
	{
		BridgeActor_ = _BridgeActor;
	}
	static GameEngineImage* MapColImage_;
	GameEngineImage* MapColImage_1_;
	GameEngineImage* MapColImage_2_;

	static GameEngineImage* MapCarryColImage_;
	static GameEngineImage* MapCarryColImage_1_;
	static GameEngineImage* MapCarryColImage_2_;
	static GameEngineImage* MapCarryColImage_2_B1F_;

private:
	GameEngineImage* CheckColMap(float4& _Pos);
	GameEngineImage* CheckCarryColMap(float4& _Pos);
	static bool IsMap1F_2;
	static bool IsOnB1F;

protected:

public:
	static GameEngineActor* MainPlayer_;
	static GameEngineActor* CarryActor_;
	static bool IsCarry_;
private:
	GameEngineActor* HitActor_;
	GameEngineRenderer* PlayerRenderer_;
	GameEngineRenderer* ChargeEndEffect_;

	void SpeedCheck(float4 _Pos);
	float CurSpeed_;
	float OriginalSpeed_;
	float KnockBackSpeed_;
	GameEngineImage* MapPasImage_;
	GameEngineImage* MapPasImage_1;
	GameEngineImage* MapPasImage_2;
	GameEngineCollision* PlayerCollision_;
	GameEngineCollision* PlayerLowerBodyCollision_;
	GameEngineCollision* PlayerHigherBodyCollision_;
	GameEngineCollision* PlayerMoveCollision_;
	GameEngineCollision* PlayerTopRightCollision_;
	GameEngineCollision* PlayerTopLeftCollision_;
	GameEngineCollision* PlayerBotRightCollision_;
	GameEngineCollision* PlayerBotLeftCollision_;
	GameEngineCollision* PlayerMiddleHorCollision_;
	GameEngineCollision* PlayerMiddleVerCollision_;
	GameEngineCollision* PlayerRightCollision_;
	GameEngineCollision* PlayerLeftCollision_;
	GameEngineCollision* PlayerTopCollision_;
	GameEngineCollision* PlayerBotCollision_;
	GameEngineCollision* SwordCollision_;
	GameEngineCollision* SwitchCollision_;

	static int CurrentAnimationFrame_;
	float AnimationTimer_;
	float AttackAnimationInterval_;
	int AnimationIndex_;


	void Start() override;
	void Update() override;
	void Render() override;


private:


	void MoveFunction(float _Speed = 350.0f);
	void KnockBackMoveFunction(float _Speed = 350.0f);
	void MoveCarryFunction();
	bool PosOrColorCheck(int _Color, GameEngineImage* _Image);
	bool PosAndColorCheck(int _Color, GameEngineImage* _Image);
	static bool IsOnStairs_;
	void CheckDirection();
	void BlinkUpdate();

private:


	bool IsMoveKeyFree();
	bool IsRightMoveKey();
	bool IsLeftMoveKey();
	bool IsUpMoveKey();
	bool IsDownMoveKey();
	/// ////////////////////////////////////////////////////////////////////Player Movements
private:
	static PlayerState PlayerCurState_;
	static PlayerState PlayerPrevState_;

	bool IsCharacterAutoMove_;
	float4 AutoMoveDir_;

	void PushRoom3Block();
	float PushTime_;
	float CurPushTime_;
	float PushLength_;

	void PlayerAutoMove();
	void PlayerAutoMove(float _Speed);

	bool IsPlayerMoveState();
	void PlayerPrevStateCheck();

	void PlayerChangeState(PlayerState _State);
	void PlayerStateUpdate();

	void DamagedCheck();
private:
	void IdleUpdate();

	void MoveUpdate();

	void WieldUpdate();
	void WieldRightUpdate();
	void WieldLeftUpdate();
	void WieldUpUpdate();
	void WieldDownUpdate();

	void ChargingUpdate();
	void ChargingMoveUpdate();
	void ChargingRight();
	void ChargingLeft();
	void ChargingUp();
	void ChargingDown();

	void ChargeWieldUpdate();
	void ChargeWieldRight();
	void ChargeWieldLeft();
	void ChargeWieldUp();
	void ChargeWieldDown();

	void DamagedUpdate();

	void CarryStartUpdate();
	void CarryIdleUpdate();
	void CarryMoveUpdate();

	void IdleRightStart();
	void IdleLeftStart();
	void IdleUpStart();
	void IdleDownStart();

	void MoveRightStart();
	void MoveLeftStart();
	void MoveUpStart();
	void MoveDownStart();

	void WieldRightStart();
	void WieldLeftStart();
	void WieldUpStart();
	void WieldDownStart();

	void ChargingIdleRightStart();
	void ChargingIdleLeftStart();
	void ChargingIdleUpStart();
	void ChargingIdleDownStart();

	void ChargingMoveRightStart();
	void ChargingMoveLeftStart();
	void ChargingMoveUpStart();
	void ChargingMoveDownStart();

	void ChargeWieldRightStart();
	void ChargeWieldLeftStart();
	void ChargeWieldUpStart();
	void ChargeWieldDownStart();

	void DamagedRightStart();
	void DamagedLeftStart();
	void DamagedUpStart();
	void DamagedDownStart();

	void CarryStartRightStart();
	void CarryStartLeftStart();
	void CarryStartUpStart();
	void CarryStartDownStart();

	void CarryIdleRightStart();
	void CarryIdleLeftStart();
	void CarryIdleUpStart();
	void CarryIdleDownStart();

	void CarryMoveRightStart();
	void CarryMoveLeftStart();
	void CarryMoveUpStart();
	void CarryMoveDownStart();


	/// ////////////////////////////////////////////////////////////////////Camera Movemnets
private:
	static CameraState CameraState_;
	static CameraState PrevCameraState_;
	float4 RoomSize_[2];
	bool IsCameraAutoMove_;

	void CameraAutoMove();

	void CameraStateChange(CameraState _State);
	void CameraStateUpdate();
	void CameraUpdate();

private:
	void Room1Start();
	void Room1Update();

	void Room1_Trans_Start();
	void Room1_Trans_Update();

	void Room2Start();
	void Room2Update();

	void Room2_Trans_Start();
	void Room2_Trans_Update();

	void Room4Start();
	void Room4Update();

	void Room4_Trans_Start();
	void Room4_Trans_Update();

	void Room10Start();
	void Room10Update();

	void Room10_Trans_Start();
	void Room10_Trans_Update();

	void Room9Start();
	void Room9Update();
			 
	void Room9_Trans_Start();
	void Room9_Trans_Update();

	void Room7Start();
	void Room7Update();

	void Room7_Trans_Start();
	void Room7_Trans_Update();

	void Room8Start();
	void Room8Update();

	void Room8_Trans_Start();
	void Room8_Trans_Update();

	void Room11Start();
	void Room11Update();

	void Room11_Trans_Start();
	void Room11_Trans_Update();

	void Room5Start();
	void Room5Update();

	void Room5_Trans_Start();
	void Room5_Trans_Update();

	void Room6Start();
	void Room6Update();

	void Room6_Trans_Start();
	void Room6_Trans_Update();

	void Room3Start();
	void Room3Update();

	void Room3_Trans_Start();
	void Room3_Trans_Update();

	bool IsBlackScreenOn_;
	bool IsLightBalckScreenOn_;
	int BlackScreenAlpha_;
	float BlackScreenTime_;

	GameEngineRenderer* LigthBlackScreen0_Main_;
	GameEngineRenderer* LigthBlackScreen1_Main_; 

	void ScreenTurnBlack(GameEngineRenderer* _Renderer, bool& _IsIamgeOn);
	void ScreenTurnBright(GameEngineRenderer* _Renderer, bool& _IsIamgeOn);
	/////////////////////////////////////////////////////////////////////Staris State
private:
	static PlayerStairsState CurStairs_;

	/////////////////////////////////////////////////////////////////////Combat
	int MaxHp_;
	static int Hp_;
	bool IsGetDamaged_;
	bool IsKnockback_;
	float KnockbackTime_;
	float CurKnockbackTime_;
	bool IsBlink_;
	float BlinkTime_;
	float CurBlinkTime_;
	float BlinkFreq_;
	float CurBlinkFreq_;
	bool IsAlphaOn_;
	bool IsSwordCollisionOn_;
	static bool IsInChargingState_;
	float4 KnockbackDir_;

	static float ItemMoveTime_;
	static float CurItemMoveTime_;
	static bool IsInItemCutScene_;

	void TreasureBoxCheck();
	void GetDamaged();
	void PotCarryCheck();

	/////////////////////////////////////////////////////////////////////Charge
	float ChargeTime_;
	float CurChargeTime_;

	/////////////////////////////////////////////////////////////////////ItemCollect
	static int PlayerRupee_;
	static int PlayerBomb_;
	static int PlayerArrow_;
	static int PlayerKey_;
	static bool IsHaveBigKey_;

	void HPCheck();
	bool IsHpLowSoundActive_;
	void ItemCollectUpdate();
	////////////////////////////////////////////////////////////////////// Sound
	
	GameEngineSoundPlayer SwordSoundPlayer_;
	GameEngineSoundPlayer BGMSoundPlayer_;
	GameEngineSoundPlayer HpLowSoundPlayer_;
	GameEngineSoundPlayer ObjectMovingSoundPlayer_;
	bool IsObjectMovingSoundPlayerOn_;
	/////////////////////////////////////////////////////////////////////Getter
public:
	inline static PlayerState GetPlayerCurState()
	{
		return PlayerCurState_;
	}
	inline static PlayerState GetPlayerPrevState()
	{
		return PlayerPrevState_;
	}
	inline static bool GetIsCarry()
	{
		return IsCarry_;
	}
	inline static CameraState GetPlayerCurRoomState()	{
		return CameraState_;
	}
	inline static CameraState GetPlayerPrevRoomState()
	{
		return PrevCameraState_;
	}
	inline static int GetCurrentAnimationFrame_()
	{
		return CurrentAnimationFrame_;
	}
	inline static PlayerStairsState GetPlayerStairsState()
	{
		return CurStairs_;
	}
	inline static bool GetIsOnStairs()
	{
		return IsOnStairs_;
	}
	inline static bool GetIsMap1F_2()
	{
		return IsMap1F_2;
	}

	inline static bool GetIsInItemCutScene()
	{
		return IsInItemCutScene_;
	}

	inline static float GetItemMoveTime()
	{
		return CurItemMoveTime_;
	}
	inline static float GetCurItemMoveTime()
	{
		return IsInItemCutScene_;
	}

	inline static int GetPlayerHp()
	{
		return Hp_;
	}

	inline static int GetPlayerRupee()
	{
		return PlayerRupee_;
	}
	inline static int GetPlayerBomb()
	{
		return PlayerBomb_;
	}
	inline static int GetPlayerArrow()
	{
		return PlayerArrow_;
	}
	inline static int GetPlayerKey()
	{
		return PlayerKey_;
	}

	inline static int UseKey()
	{
		return PlayerKey_ -= 1;
	}
	inline static bool GetPlayerIsHaveBigKey()
	{
		return IsHaveBigKey_;
	}

	/////////////////////////////////////////////////////////////////////Setter
	void SetBGMSoundPlayer(GameEngineSoundPlayer _SoundPlayer)
	{
		BGMSoundPlayer_ = _SoundPlayer;
	}

	static void SetIsInChargingStateOff()
	{
		IsInChargingState_ = false;
	}
};

