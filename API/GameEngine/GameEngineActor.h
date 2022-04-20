#pragma once
#include "GameEngineLevel.h"
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineUpdateObject.h>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineEnum.h"
#include <list>

class GameEngineLevel;
class GameEngineRenderer;
class GameEngineCollision;
//다중상속은 위험하다, 이름이 겹칠 수 있기때문.
//메모리는 순서대로간다
class GameEngineActor : public GameEngineNameObject, public GameEngineUpdateObject
{
	///////////////////////////////////////////////////////////////Actor Options
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

	inline GameEngineLevel* GetLevel()
	{
		return Level_;
	}

	inline float4 GetCameraEffectPosition()
	{
		return Position_ - GetLevel()->GetCameraPos();
	}

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
	inline void SetMove(float4 _Value)
	{
		Position_ += _Value;
	}

	inline void SetScale(float4 _Value)
	{
		Scale_ = _Value;
	}

	void SetOrder(int _Order) override;


protected:
	//생성자에서는 처리못하는 만들어지거나 시작할때 처리할것
	//맘대로 호출하면 안됨
	virtual void Start() = 0; // 모든 엑터에서 무조건 생성해야한다
	//지속적으로 게임이 실행될때 호출됨
	virtual void Update() {} // 때에 따라서 엑터에서 생성해야한다
	virtual void Render() {} // 떼에 따라서 엑터에서 생성해야한다

	virtual void LevelChangeStart() {}
	virtual void LevelChangeEnd() {}

	void Release();
	void DebugRectRender();
	void LevelRegist(std::string _RegistName = "");
private:
	GameEngineLevel* Level_;
	float4 Position_;
	float4 Scale_;
	inline void SetLevel(GameEngineLevel* _Level)
	{
		Level_ = _Level;
	}


	///////////////////////////////////////////////////////////////Render Options
public:
	//디폴트 인자는 오버로딩을 하는 경우 모호함이 생길 수 있기 때문에 함수를 하나만 만든다.
	//디폴트 인자는 선언에서만 구현 가능하다.
	GameEngineRenderer* CreateRenderer(int _Order = static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot _PivotType = RenderPivot::CENTER, const float4& _PivotPos = { 0,0 });
	GameEngineRenderer* CreateRenderer(const std::string& _Image,
		int _Order = static_cast<int>(EngineMax::RENDERORDERMAX),
		RenderPivot _PivotType = RenderPivot::CENTER,
		const float4& _PivotPos = { 0,0 });
	GameEngineRenderer* CreateRendererToScale(const std::string& _Image, const float4& _PivotScale, int _Order = static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot _PivotType = RenderPivot::CENTER,
		const float4& _PivotPos = { 0,0 });
private:
	//딴데서 사용하지 말것
	std::list <GameEngineRenderer*>::iterator StartRenderIter;
	std::list <GameEngineRenderer*>::iterator EndRenderIter;

	std::list <GameEngineRenderer*> RenderList_;


	///////////////////////////////////////////////////////////////Collision
public:
	GameEngineCollision* CreateCollision(const std::string& _GroupName, float4 _Scale, float4 _Pivot = { 0, 0 });
private:
	std::list <GameEngineCollision*> CollisionList_;
};

