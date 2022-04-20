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
//���߻���� �����ϴ�, �̸��� ��ĥ �� �ֱ⶧��.
//�޸𸮴� ������ΰ���
class GameEngineActor : public GameEngineNameObject, public GameEngineUpdateObject
{
	///////////////////////////////////////////////////////////////Actor Options
public:
	//SetLevel�Լ��� GameEngineLevel������ ȣ�� �� �� �ְԲ� �������
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
	//�����ڿ����� ó�����ϴ� ��������ų� �����Ҷ� ó���Ұ�
	//����� ȣ���ϸ� �ȵ�
	virtual void Start() = 0; // ��� ���Ϳ��� ������ �����ؾ��Ѵ�
	//���������� ������ ����ɶ� ȣ���
	virtual void Update() {} // ���� ���� ���Ϳ��� �����ؾ��Ѵ�
	virtual void Render() {} // ���� ���� ���Ϳ��� �����ؾ��Ѵ�

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
	//����Ʈ ���ڴ� �����ε��� �ϴ� ��� ��ȣ���� ���� �� �ֱ� ������ �Լ��� �ϳ��� �����.
	//����Ʈ ���ڴ� ���𿡼��� ���� �����ϴ�.
	GameEngineRenderer* CreateRenderer(int _Order = static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot _PivotType = RenderPivot::CENTER, const float4& _PivotPos = { 0,0 });
	GameEngineRenderer* CreateRenderer(const std::string& _Image,
		int _Order = static_cast<int>(EngineMax::RENDERORDERMAX),
		RenderPivot _PivotType = RenderPivot::CENTER,
		const float4& _PivotPos = { 0,0 });
	GameEngineRenderer* CreateRendererToScale(const std::string& _Image, const float4& _PivotScale, int _Order = static_cast<int>(EngineMax::RENDERORDERMAX), RenderPivot _PivotType = RenderPivot::CENTER,
		const float4& _PivotPos = { 0,0 });
private:
	//������ ������� ����
	std::list <GameEngineRenderer*>::iterator StartRenderIter;
	std::list <GameEngineRenderer*>::iterator EndRenderIter;

	std::list <GameEngineRenderer*> RenderList_;


	///////////////////////////////////////////////////////////////Collision
public:
	GameEngineCollision* CreateCollision(const std::string& _GroupName, float4 _Scale, float4 _Pivot = { 0, 0 });
private:
	std::list <GameEngineCollision*> CollisionList_;
};

