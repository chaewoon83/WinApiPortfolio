#pragma once
//이미지가 없으면 렌더링을 할 수 없다
#include "GameEngineEnum.h"
#include "GameEngineActorSubObject.h"
//#include "GameEngineImage.h"
// 설명 :
class GameEngineImage;
class GameEngineRenderer : public GameEngineActorSubObject
{
	friend GameEngineActor;
public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	inline void SetType(const RenderPivot& _Type)
	{
		PivotType_ = _Type;
	}

	inline void SetScaleMode(const RenderScaleMode& _Mode)
	{
		ScaleMode_ = _Mode;
	}

	inline void SetScale(const float4& _Scale)
	{
		ScaleMode_ = RenderScaleMode::User;
		RenderScale_ = _Scale;
	}

	void SetImageScale();


	inline void SetPivot(const float4& _Pos)
	{
		RenderPivot_ = _Pos;
	}

	inline void SetTransColor(unsigned int _Color)
	{
		TransColor_ = _Color;
	}

	void SetImage(const std::string& _Name);
	void Render();
	void SetIndex(size_t Index, float4 _Scale = {-1.0f, -1.0f});

protected:

private:
	//bool IsDebugMode_;
	GameEngineImage* Image_;
	RenderPivot PivotType_; //Center Bot etc
	RenderScaleMode ScaleMode_;
	float4 RenderPivot_;
	
	//실제로 그려지는 크기
	float4 RenderScale_;

	float4 RenderImagePivot_;
	//자르는 이미지의 크기
	float4 RenderImageScale_;
	unsigned int TransColor_;
};

