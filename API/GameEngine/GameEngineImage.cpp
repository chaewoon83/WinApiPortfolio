#include "GameEngineImage.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>
//이미지 라이브러리
#pragma comment(lib, "msimg32.lib")


GameEngineImage::GameEngineImage() 
	:ImageDC_(nullptr)
{
}

GameEngineImage::~GameEngineImage() 
{
	if (nullptr != BitMap_)
	{
		DeleteObject(BitMap_);
		BitMap_ = nullptr;
	}

	if (nullptr != OldBitMap_)
	{
		DeleteObject(OldBitMap_);
		OldBitMap_ = nullptr;
	}

	if (nullptr != ImageDC_)
	{
		DeleteObject(ImageDC_);
		ImageDC_ = nullptr;
	}
}

bool GameEngineImage::Create(float4 _Scale)
{
	if (true == _Scale.IsZero2D())
	{
		MsgBoxAssert("크기가 0인 이미지를 제작하려고 했습니다.");
		return false;
	}
	//나중에 GameEngineWindow::GetHDC()가 아니라 BackBuffer로 바뀔듯(?)
	//자기가 그려질 DC를 받는거지 권한을 받는건 아니다
	//크기가 정해진 비어있는 BitMap을 만든다 
	BitMap_ = CreateCompatibleBitmap(GameEngineWindow::GetHDC(), _Scale.ix(), _Scale.iy());
	//비어있는 DC를 만든다 그안에 (1,1)크기의 HBitMap이 같이 생성된다
	ImageDC_ = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC_)
	{
		MsgBoxAssert("ImageDC 생성에 실패했습니다.");
		return false;
	}

	OldBitMap_ = (HBITMAP)SelectObject(ImageDC_, BitMap_);

	ImageScaleCheck();

	return true;
}

bool GameEngineImage::Create(HDC _DC)
{
	ImageDC_ = _DC;
	ImageScaleCheck();
	return true;
}

//이미지의 사이즈를 얻어오는 함수
//HBITMAP에서 BITMAP의 정보를 빼온다
void GameEngineImage::ImageScaleCheck()
{
	//DC 내부의 BITMAP을 꺼내오는 함수
	HBITMAP CurrentBitMap = (HBITMAP)GetCurrentObject(ImageDC_, OBJ_BITMAP);
	GetObject(CurrentBitMap, sizeof(BITMAP), &Info_);
}

void GameEngineImage::BitCopy(GameEngineImage* _Other)
{
	BitCopy(_Other, { 0,0 }, { 0,0 }, _Other->GetScale());
}

void GameEngineImage::BitCopy(GameEngineImage* _Other, const float4& _CopyPos, const float4& _OtherPivot, const float4& _OtherPivotScale)
{
	//복사하는 함수는 제공이 된다
	//윈도우에서 지원해주는 일반적인 dc vs dc의 복사함수
	BitBlt(
		ImageDC_, //여기에 복사해라
		_CopyPos.ix(), // 내 이미지의 이부분 x
		_CopyPos.iy(), // 내 이미지의 이부분 y 에 복사해라
		_OtherPivotScale.ix(), // 내 이미지의 이 크기만큼 x
		_OtherPivotScale.iy(), // 내 이미지의 이 크기만큼 y
		_Other->ImageDC_, //복사 하려는 대상
		_OtherPivot.ix(), //복사 하려는 대상의 시작점 x
		_OtherPivot.iy(), //복사 하려는 대상의 시작점 y
		SRCCOPY
	);
}

