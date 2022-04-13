#pragma once
//�̹����� ������ �������� �� �� ����
#include "GameEngineEnum.h"
#include "GameEngineActorSubObject.h"
#include <map>
//#include "GameEngineImage.h"
// ���� :
class GameEngineImage;
class GameEngineFolderImage;
class GameEngineRenderer : public GameEngineActorSubObject
{
	friend GameEngineActor;
	friend GameEngineLevel;
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
	// ������ �����ϰ� �̹��� �������� ���� ������, SetImage()���� ȣ���Ͽ� ����Ѵ�.
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

	void SetIndex(size_t Index, float4 _Scale = { -1.0f, -1.0f });

	void CameraEffectOff()
	{
		IsCameraEffect_ = false;
	}

	void CameraEffectOn()
	{
		IsCameraEffect_ = true;
	}

	void SetOrder(int _Order) override;

protected:
	// EngineImage�� TransCopy �� �̹����� ����ۿ� �׸���.
	void Render();
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
	//����ȭ�� ����
	unsigned int TransColor_;
	// �ش� �������� ī�޶� ���� ����
	bool IsCameraEffect_;

	//////////////////////////////////////////////////////////////////////////////////////////////Animation

private:
	class FrameAnimation : public GameEngineNameObject
	{
	public:
		GameEngineRenderer* Renderer_;
		GameEngineImage* Image_;
		GameEngineFolderImage* FolderImage_;

		int TimeKey;
		int CurrentFrame_;
		int StartFrame_;
		int EndFrame_;
		float InterTime_;
		float CurrentInterTime_;
		bool Loop_ = false;
		bool IsEnd;

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
		//ó�� ��� ���·� ����� ��
		void Reset()
		{
			IsEnd = false;
			CurrentFrame_ = StartFrame_;
			CurrentInterTime_ = InterTime_;
		}
	};


public:
	void ChangeAnimation(const std::string& _Name);
	void CreateAnimation(const std::string& _Image, const std::string& _Name, int _StartIndex, int _EndIndex,
		float _InterTime, bool _Loop = true);
	void CreateFolderAnimation(const std::string& _Image, const std::string& _Name, int _StartIndex, int _EndIndex, float _InterTime,
		bool _Loop = true);

	void CreateFolderAnimationTimeKey(const std::string& _Image, const std::string& _Name, int _TimeScaleKey, int _StartIndex, int _EndIndex, float _InterTime, bool _Loop = true);

	bool IsEndAnimation();

	bool IsAnimationName(const std::string& _Name);

private:
	std::map<std::string, FrameAnimation> Animations_;
	FrameAnimation* CurrentAnimation_;
};
