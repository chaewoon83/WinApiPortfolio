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
	static GameEngineRenderer* Room2TopDoor0;
	static GameEngineRenderer* Room2BotDoor0;
	static GameEngineRenderer* Room3RightKeyDoor0;
	static GameEngineCollision* SwitchCol_;
	static GameEngineCollision* Room1Door0Col_;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	//문을 설치하는 함수
	void DoorAnimationCreate();
	void PlaceDoor();

	bool IsRoom1TopDoor0On_;
	CameraState CurRoomState_;
};

