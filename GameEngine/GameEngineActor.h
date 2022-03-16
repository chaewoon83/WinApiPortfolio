#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>
class GameEngineLevel;

// 설명 :
class GameEngineActor : public GameEngineNameObject
{
public:
	//SetLevel함수를 GameEngineLevel에서만 호출 할 수 있게끔 만들었다
	friend GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineActor();
	virtual ~GameEngineActor();

	// delete Function
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	inline float4 GetPosition()
	{
		return Position_;
	}

	inline float4 GetScale()
	{
		return Scale_;
	}

	inline void SetPosition(float4 _Value)
	{
		Position_ = _Value;
	}

	inline void SetScale(float4 _Value)
	{
		Scale_ = _Value;
	}


protected:
	//생성자에서는 처리못하는 만들어지거나 시작할때 처리할것
	//맘대로 호출하면 안됨
	virtual void Start() = 0; // 모든 엑터에서 무조건 생성해야한다
	//지속적으로 게임이 실행될때 호출됨
	virtual void Update() {} // 때에 따라서 엑터에서 생성해야한다
	virtual void Render() {} // 떼에 따라서 엑터에서 생성해야한다
	void DebugRectRender();
private:
	GameEngineLevel* Level_;
	float4 Position_;
	float4 Scale_;
	inline void SetLevel(GameEngineLevel* _Level)
	{
		Level_ = _Level;
	}

};

