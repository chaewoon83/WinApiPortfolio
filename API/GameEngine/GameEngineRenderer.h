#pragma once
//�̹����� ������ �������� �� �� ����
#include "GameEngineEnum.h"
#include "GameEngineActorSubObject.h"
#include <map>
//#include "GameEngineImage.h"
// ���� :
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

	inline void SetPivotType(const RenderPivot& _Type)
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
	inline GameEngineImage* GetImage()
	{
		return Image_;
	}
	void Render();
	void SetIndex(size_t Index, float4 _Scale = {-1.0f, -1.0f});

protected:

private:
	friend class FrameAnimation;
	//bool IsDebugMode_;
	GameEngineImage* Image_;
	RenderPivot PivotType_; //Center Bot etc
	RenderScaleMode ScaleMode_;
	float4 RenderPivot_;
	
	//������ �׷����� ũ��
	float4 RenderScale_;
	//�߸��� �̹��� ������
	float4 RenderImagePivot_;
	//�ڸ��� �̹����� ũ��
	float4 RenderImageScale_;
	unsigned int TransColor_;

//////////////////////////////////////////////////////////////////////////////////////////////Animation

private:
	class FrameAnimation
	{
	public:
		GameEngineRenderer* Renderer_;
		GameEngineImage* Image_;
		int CurrentFrame_;
		int StartFrame_;
		int EndFrame_;
		float InterTime_;
		float CurrentInterTime_;
		bool Loop_;

	public:
		FrameAnimation()
			:Image_(nullptr),
			CurrentFrame_(-1),
			StartFrame_(-1),
			EndFrame_(-1),
			InterTime_(0.1f),
			CurrentInterTime_(0.1f),
			Loop_(true)
		{
		};
		void Update();
		void Reset()
		{
			CurrentFrame_ = StartFrame_;
			CurrentInterTime_ = InterTime_;
		}
	};


public:
	void ChangeAnimation(const std::string& _Name);
	void CreateAnimation(const std::string& _Image, const std::string& _Name, int _StartIndex, int _EndIndex, 
		float _InterTime, bool _Loop = true);

private:
	std::map<std::string, FrameAnimation> Animations_;
	FrameAnimation* CurrentAnimation_;
};
