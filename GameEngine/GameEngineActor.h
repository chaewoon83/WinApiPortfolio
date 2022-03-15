#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>

// 설명 :
class GameEngineActor : public GameEngineNameObject
{
private:
	float4 float1;
public:
	// constrcuter destructer
	GameEngineActor();
	virtual ~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

protected:
	//생성자에서는 처리못하는 만들어지거나 시작할때 처리할것
	virtual void Start() = 0; // 모든 엑터에서 무조건 생성해야한다
	//지속적으로 게임이 실행될때 호출됨
	virtual void Update() {}
	virtual void Render() {}
private:

};

