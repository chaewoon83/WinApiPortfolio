#pragma once
#include <GameEngine/GameEngineActor.h>
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

	static GameEngineRenderer* TopDoor1;
	static GameEngineRenderer* TopDoor2;
	static GameEngineRenderer* TopDoor3;
	static GameEngineRenderer* BotDoor1;
	static GameEngineRenderer* RightDoor1;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	//문을 설치하는 함수
	void DoorAnimationCreate();
	void PlaceDoor();


};

