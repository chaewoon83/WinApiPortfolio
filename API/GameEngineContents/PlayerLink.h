#pragma once
#include <GameEngine/GameEngineActor.h>
#include "GameEngineContentsEnum.h"
// ���� :
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

	GameEngineImage* MapCarryColImage_;
	GameEngineImage* MapCarryColImage_1_;
	GameEngineImage* MapCarryColImage_2_;

private:
	GameEngineImage* CheckColMap(float4& _Pos);
	GameEngineImage* CheckCarryColMap(float4& _Pos);
	static bool IsMap1F_2;

protected:

public:
	static GameEngineActor* MainPlayer_;
	static GameEngineActor* CarryActor_;
	static bool IsCarry_;
private:
	GameEngineActor* HitActor_;
	GameEngineRenderer* PlayerRenderer_;


	float Speed_;
	float KnockBackSpeed_;
	GameEngineImage* MapPasImage_;
	GameEngineImage* MapPasImage_1;
	GameEngineImage* MapPasImage_2;
	GameEngineCollision* PlayerCollision_;
	GameEngineCollision* PlayerLowerBodyCollision_;
	GameEngineCollision* PlayerMoveCollision_;
	GameEngineCollision* PlayerTopRightCollision_;
	GameEngineCollision* PlayerTopLeftCollision_;
	GameEngineCollision* PlayerBotRightCollision_;
	GameEngineCollision* PlayerBotLeftCollision_;
	GameEngineCollision* PlayerMiddleHorCollision_;
	GameEngineCollision* PlayerMiddleVerCollision_;
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


	void MoveFunction();
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

	void PlayerAutoMove();
	void PlayerAutoMove(float _Speed);

	bool IsPlayerMoveState();
	void PlayerSetIdle();
	void PlayerPrevStateCheck();

	void PlayerChangeState(PlayerState _State);
	void PlayerStateUpdate();

	void DamagedCheck();
private:
	void IdleUpdate();

	void WieldUpdate();
	void MoveUpdate();
	void DamagedUpdate();
	void WieldRightUpdate();
	void WieldLeftUpdate();
	void WieldUpUpdate();
	void WieldDownUpdate();
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

	void ResetTimeScale(int _x);
	/////////////////////////////////////////////////////////////////////Staris State
private:
	static PlayerStairsState CurStairs_;

	/////////////////////////////////////////////////////////////////////Combat
	int Hp_;
	bool IsGetDamaged_;
	bool IsKnockback_;
	bool IsBlink_;
	float KnockbackTime_;
	float CurKnockbackTime_;
	float BlinkTime_;
	float CurBlinkTime_;
	float BlinkFreq_;
	float CurBlinkFreq_;
	bool IsAlphaOn_;
	float4 KnockbackDir_;

	void GetDamaged();
	void PotCarryCheck();
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
};

