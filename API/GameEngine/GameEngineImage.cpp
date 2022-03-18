#include "GameEngineImage.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEngineWindow.h>
//�̹��� ���̺귯��
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
		MsgBoxAssert("ImageDC ������ �����߽��ϴ�.");
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

//�̹����� ����� ������ �Լ�
//HBITMAP���� BITMAP�� ������ ���´�
void GameEngineImage::ImageScaleCheck()
{
	//DC ������ BITMAP�� �������� �Լ�
	HBITMAP CurrentBitMap = (HBITMAP)GetCurrentObject(ImageDC_, OBJ_BITMAP);
	GetObject(CurrentBitMap, sizeof(BITMAP), &Info_);
}

void GameEngineImage::BitCopy(GameEngineImage* _Other)
{
	BitCopy(_Other, { 0,0 }, { 0,0 }, _Other->GetScale());
}

void GameEngineImage::BitCopy(GameEngineImage* _Other, const float4& _CopyPos, const float4& _OtherPivot, const float4& _OtherPivotScale)
{
	//�����ϴ� �Լ��� ������ �ȴ�
	//�����쿡�� �������ִ� �Ϲ����� dc vs dc�� �����Լ�
	BitBlt(
		ImageDC_, //���⿡ �����ض�
		_CopyPos.ix(), // �� �̹����� �̺κ� x
		_CopyPos.iy(), // �� �̹����� �̺κ� y �� �����ض�
		_OtherPivotScale.ix(), // �� �̹����� �� ũ�⸸ŭ x
		_OtherPivotScale.iy(), // �� �̹����� �� ũ�⸸ŭ y
		_Other->ImageDC_, //���� �Ϸ��� ���
		_OtherPivot.ix(), //���� �Ϸ��� ����� ������ x
		_OtherPivot.iy(), //���� �Ϸ��� ����� ������ y
		SRCCOPY
	);
}

