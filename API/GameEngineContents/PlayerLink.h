#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class GameEngineImage;
class GmaeEngineCollision;
class Map1FBridge;
enum class PlayerState
{
	RightIdle,
	LeftIdle,
	UpIdle,
	DownIdle,
	MoveRight,
	MoveLeft,
	MoveUp,
	MoveDown,
	WieldRight,
	WieldLeft,
	WieldUp,
	WieldDown,
	DamagedRight,
	DamagedLeft,
	DamagedUp,
	DamagedDown,
	Max
};

enum class CameraState
{
	Room1,
	Room2,
	Room3,
	Room4,
	Room5,
	Room6,
	Room7,
	Max
};

enum class StairsState
{
	Top,
	Bot,
	Max
};




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

protected:


private:
	GameEngineActor* HitActor_;

	GameEngineRenderer* PlayerRenderer;

	float Speed_;
	float KnockBackSpeed_;
	GameEngineImage* MapPasImage_;
	GameEngineCollision* PlayerCollision_;
	GameEngineCollision* SwordCollision_;
	GameEngineCollision* SwitchCollision_;

	float AnimationTimer_;
	float AttackAnimationInterval_;
	int AnimationIndex_;


	void Start() override;
	void Update() override;
	void Render() override;


private:


	void MoveFunction();
	bool PosOrColorCheck(int _Color, GameEngineImage* _Image);
	bool PosAndColorCheck(int _Color, GameEngineImage* _Image);
	bool IsOnStairs_;
	void CheckDirection();
	void BlinkUpdate();

private:


	bool IsMoveKeyFree();
	bool IsRightMoveKey();
	bool IsLeftMoveKey();
	bool IsUpMoveKey();
	bool IsDownMoveKey();
	/// ////////////////////////////////////////////////////////////////////Player Movements
public:
	PlayerState PlayerCurState_;
	PlayerState PlayerPrevState_;

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


	/// ////////////////////////////////////////////////////////////////////Camera Movemnets
private:
	CameraState CameraState_;
	float4 RoomSize_[2];
	bool IsCameraAutoMove_;

	void CameraAutoMove();

	void CameraStateChange(CameraState _State);
	void CameraStateUpdate();
	void CameraUpdate();

private:
	void Room1Start();
	void Room1Update();

	void Room2Start();
	void Room2Update();

	void Room3Start();
	void Room3Update();
	/////////////////////////////////////////////////////////////////////Staris State
private:
	StairsState CurStairs_;

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
};

