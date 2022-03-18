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
		MsgBoxAssert("ũ�Ⱑ 0�� �̹����� �����Ϸ��� �߽��ϴ�.");
		return false;
	}
	//���߿� GameEngineWindow::GetHDC()�� �ƴ϶� BackBuffer�� �ٲ��(?)
	//�ڱⰡ �׷��� DC�� �޴°��� ������ �޴°� �ƴϴ�
	//ũ�Ⱑ ������ ����ִ� BitMap�� ����� 
	BitMap_ = CreateCompatibleBitmap(GameEngineWindow::GetHDC(), _Scale.ix(), _Scale.iy());
	//����ִ� DC�� ����� �׾ȿ� (1,1)ũ���� HBitMap�� ���� �����ȴ�
	ImageDC_ = CreateCompatibleDC(nullptr);

	if (nullptr == ImageDC_)
	{
		MsgBoxAssert("ImageDC ������ �����߽��ϴ�.")
	}

	OldBitMap_ = (HBITMAP)SelectObject(ImageDC_, BitMap_);

	ImageScaleCheck();

	return true;
}

//�̹����� ����� ������ �Լ�
//HBITMAP���� BITMAP�� ������ ���´�
void GameEngineImage::ImageScaleCheck()
{
	GetObject(BitMap_, sizeof(BITMAP), &Info_);
}

