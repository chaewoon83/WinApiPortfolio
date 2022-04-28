#pragma once
#include <GameEngine/GameEngineActor.h>
#include "GameEngineContentsEnum.h"
// 설명 :
class Map1F_2 : public GameEngineActor
{
public:
	// constrcuter destructer
	Map1F_2();
	~Map1F_2();

	// delete Function
	Map1F_2(const Map1F_2& _Other) = delete;
	Map1F_2(Map1F_2&& _Other) noexcept = delete;
	Map1F_2& operator=(const Map1F_2& _Other) = delete;
	Map1F_2& operator=(Map1F_2&& _Other) noexcept = delete;

	static GameEngineRenderer* Room1TopDoor0_;
	static GameEngineRenderer* Room2TopDoor0_;
	static GameEngineRenderer* Room2BotDoor0_;
	static GameEngineRenderer* Room10RightDoor0_;
	static GameEngineRenderer* Room10LeftDoor0_;
	static GameEngineRenderer* Room3RightKeyDoor0;

	static GameEngineCollision* Room1TopDoor0Col_;
	static GameEngineCollision* Room2TopDoor0Col_;
	static GameEngineCollision* Room2BotDoor0Col_;
	static GameEngineCollision* Room10RightDoor0Col_;
	static GameEngineCollision* Room10LeftDoor0Col_;


	//3012,2596 56,40 => 3040,2576


protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	//문을 설치하는 함수
	void DoorAnimationCreate();
	void PlaceDoor();

	CameraState CurRoomState_;

	//////////////////Room1
	static GameEngineCollision* Room1SwitchCol_;
	void Room1SwitchCheck();
	bool IsRoom1TimeStop_;
	bool IsRoom1PlayerOnSwitch_;
	bool IsRoom1SwitchOn_;

	//////////////////Room2
	static GameEngineCollision* Room2SwitchCol_;
	void Room2SwitchCheck();
	bool IsRoom2TimeStop_;
	bool IsRoom2PlayerOnSwitch_;
	bool IsRoom2SwitchOn_;

	//////////////////Room4
	void Room4BallGen();
	int Room4BallNumbers_;
	float Room4BallCreateFreq_;
	float Room4CurBallCreateFreq_;

	//////////////////Room10
	static GameEngineCollision* Room10SwitchCol_1_;
	static GameEngineCollision* Room10SwitchCol_2_;
	void Room10SwitchCheck();
	bool IsRoom10TimeStop_;
	bool IsRoom10PlayerOnSwitch_;
	bool IsRoom10SwitchOn_;

};

