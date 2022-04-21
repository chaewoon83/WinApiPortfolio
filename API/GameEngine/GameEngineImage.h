#pragma once
#include <GameEngineBase/GameEngineNameObject.h>
#include <GameEngineBase/GameEngineMath.h>
#include <Windows.h>
#include <vector>

// 설명 :
class GameEngineImage : public GameEngineNameObject
{
public:
	// constrcuter destructer
	GameEngineImage();
	~GameEngineImage();

	// delete Function
	GameEngineImage(const GameEngineImage& _Other) = delete;
	GameEngineImage(GameEngineImage&& _Other) noexcept = delete;
	GameEngineImage& operator=(const GameEngineImage& _Other) = delete;
	GameEngineImage& operator=(GameEngineImage&& _Other) noexcept = delete;

	bool Create(float4 _Scale);
	bool Create(HDC _DC);

	bool Load(const std::string& _Path);

	inline float4 GetScale()
	{
		return float4(static_cast<float>(Info_.bmWidth), static_cast<float>(Info_.bmHeight));
	}

	inline HDC ImageDC()
	{
		return ImageDC_;
	}

	// BitBlt
	void BitCopy(GameEngineImage* _Other);
	void BitCopy(GameEngineImage* _Other, const float4& _CopyPos);
	void BitCopyCenter(GameEngineImage* _Other, const float4& _CopyPos);
	void BitCopyCenterPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot);
	void BitCopyBot(GameEngineImage* _Other, const float4& _CopyPos);
	void BitCopyBotPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot);
	void BitCopy(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyScale, const float4& _OtherPivot);

	// Trans
	//void TransCopy(GameEngineImage* _Other);
	//void TransCopy(GameEngineImage* _Other, const float4& _CopyPos);
	//void TransCopyCenter(GameEngineImage* _Other, const float4& _CopyPos);
	//void TransCopyCenterPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot);
	//void TransCopyBot(GameEngineImage* _Other, const float4& _CopyPos);
	//void TransCopyBotPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot);
	void TransCopyCenterScaleAndPos(GameEngineImage* _Other, const float4& _CopyPos, const float4& _RenderPivot, const float4& _RenderScale, unsigned int _TransColor);
	void TransCopyCenterScale(GameEngineImage* _Other, const float4& _CopyPos, const float4& _RenderScale, unsigned int _TransColor);
	void TransCopyCenter(GameEngineImage* _Other, const float4& _CopyPos, unsigned int _TransColor);

	void TransCopy(GameEngineImage* _Other, const float4& _CopyPos,
		const float4& _CopyScale,
		const float4& _OtherPivot, const float4& _OtherScale, unsigned int _TransColor);

	void AlphaCopy(GameEngineImage* _Other, const float4& _CopyPos,
		const float4& _CopyScale,
		const float4& _OtherPivot, const float4& _OtherScale, unsigned int _TransColor);

	void PlgCopy(GameEngineImage* _Other, GameEngineImage* _Filter);

	void Cut(const float4& _CutSize);

	float4 GetCutPivot(size_t _Index)
	{
		return CutPivot_[_Index];
	}

	inline float4 GetCutScale(size_t _Index)
	{
		return CutScale_[_Index];
	}

	inline bool IsCut()
	{
		return 0 != CutPivot_.size();
	}
	//다른크기로 잘라야 할 때가 있기때문에 _CutScale 과 _CutPivot에 백터로 하나하나의 컷의 사이즈를 넣어준다
	void Cut(const float4& _CutScale, const float4& _CutPos)
	{
		CutPivot_.push_back(_CutPos);
		CutScale_.push_back(_CutScale);
	}

	void CutCount(int _x, int _y);

	inline int GetImagePixel(const float4& _Pos)
	{
		return GetImagePixel(_Pos.ix(), _Pos.iy());
	}
	int GetImagePixel(int _x, int _y);


protected:


private:
	HDC ImageDC_;
	HBITMAP BitMap_;
	HBITMAP OldBitMap_;
	BITMAP Info_;

	std::vector<float4> CutPivot_;
	//다른크기로 잘라야 할 때가 있기때문에 백터로 하나하나의 컷의 사이즈를 저장한다
	std::vector<float4> CutScale_;
	float4 CutSize_;

	void ImageScaleCheck();
};

