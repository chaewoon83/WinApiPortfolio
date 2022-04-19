#pragma once
#include <GameEngine/GameEngineActor.h>
// ���� :
class GameEngineImage;
class GmaeEngineCollision;
class Map1FBridge;
enum class PlayerState
{
	RightIdle,
	LeftIdle,
	UpIdle,
	DownIdle,
	WieldRight,
	WieldLeft,
	WieldUp,
	WieldDown,
	MoveRight,
	MoveLeft,
	MoveUp,
	MoveDown,
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

protected:


private:

	GameEngineRenderer* PlayerRenderer;

	float Speed_;
	GameEngineImage* MapColImage_;
	GameEngineImage* MapPasImage_;
	GameEngineCollision* PlayerCollision_;
	GameEngineCollision* SwitchCollision_;

	void Start() override;
	void Update() override;
	void Render() override;


private:


	void MoveFunction();
	bool PosOrColorCheck(int _Color, GameEngineImage* _Image);
	bool PosAndColorCheck(int _Color, GameEngineImage* _Image);
	bool IsOnStairs_;
	void CheckDirection();

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
	void PlayerChangeState(PlayerState _State);
	void PlayerStateUpdate();
private:
	void IdleUpdate();

	void WieldUpdate();
	void MoveUpdate();

	void IdleRightStart();
	void IdleLeftStart();
	void IdleUpStart();
	void IdleDownStart();
	void WieldRightStart();
	void WieldLeftStart();
	void WieldUpStart();
	void WieldDownStart();
	void MoveRightStart();
	void MoveLeftStart();
	void MoveUpStart();
	void MoveDownStart();


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
};

