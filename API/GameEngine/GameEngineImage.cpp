#include "GameEngineImage.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>

GameEngineImage::GameEngineImage() 
{
}

GameEngineImage::~GameEngineImage() 
{
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
		MsgBoxAssert("ImageDC 생성에 실패했습니다.")
	}

	OldBitMap_ = (HBITMAP)SelectObject(ImageDC_, BitMap_);

	ImageScaleCheck();

	return true;
}

//이미지의 사이즈를 얻어오는 함수
//HBITMAP에서 BITMAP의 정보를 빼온다
void GameEngineImage::ImageScaleCheck()
{
	GetObject(BitMap_, sizeof(BITMAP), &Info_);
}

