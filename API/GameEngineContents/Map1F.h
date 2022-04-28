#pragma once
#include <GameEngine/GameEngineActor.h>
#include "GameEngineContentsEnum.h"
// 설명 :
class Map1F : public GameEngineActor
{
public:
	// constrcuter destructer
	Map1F();
	~Map1F();

	// delete Function
	Map1F(const Map1F& _Other) = delete;
	Map1F(Map1F&& _Other) noexcept = delete;
	Map1F& operator=(const Map1F& _Other) = delete;
	Map1F& operator=(Map1F&& _Other) noexcept = delete;

	static GameEngineRenderer* Room1TopDoor0_;
	static GameEngineRenderer* Room2TopDoor0_;
	static GameEngineRenderer* Room2BotDoor0_;
	static GameEngineRenderer* Room3RightKeyDoor0;

	static GameEngineCollision* Room1TopDoor0Col_;
	static GameEngineCollision* Room2TopDoor0Col_;
	static GameEngineCollision* Room2BotDoor0Col_;

	static GameEngineCollision* Room1SwitchCol_;
	//3012,2596 56,40 => 3040,2576
	static GameEngineCollision* Room2SwitchCol_;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	//문을 설치하는 함수
	void DoorAnimationCreate();
	void PlaceDoor();

	CameraState CurRoomState_;

	//////////////////SwitchCheck
	void Room1SwitchCheck();
	bool IsRoom1TimeStop_;
	bool IsRoom1PlayerOnSwitch_;
	bool IsRoom1SwitchOn_;

	void Room2SwitchCheck();
	bool IsRoom2TimeStop_;
	bool IsRoom2PlayerOnSwitch_;
	bool IsRoom2SwitchOn_;
};

