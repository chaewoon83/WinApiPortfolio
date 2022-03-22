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

bool GameEngineImage::Load(const std::string& _Path)
{
	BitMap_ = static_cast<HBITMAP>(LoadImageA(
		nullptr, // ���μ��� �ڵ� nullptr ���Խ� �˾Ƽ� ����Ʈ ����
		_Path.c_str(), // �����η� ���� ���� ����
		IMAGE_BITMAP,
		0, // ũ�����ϱ�
		0,
		LR_LOADFROMFILE
		));
	//BitMap_�� ä���ش�
	//����ִ� DC�� ����� �׾ȿ� (1,1)ũ���� HBitMap�� ���� �����ȴ�

	if (nullptr == BitMap_)
	{
		MsgBoxAssert("�̹��� �ε忡 �����߽��ϴ�. \n1. ��� Ȯ���ϱ�, \n2. ������� ����� ����")
	}
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

////////////////////////////////////////////////////////////////////////////BitBlt (ũ������x)
void GameEngineImage::BitCopy(GameEngineImage* _Other)
{
	BitCopy(_Other, { 0, 0 }, _Other->GetScale(), float4{ 0, 0 });
}

void GameEngineImage::BitCopy(GameEngineImage* _Other, const float4& _CopyPos)
{
	BitCopy(_Other, _CopyPos, _Other->GetScale(), float4{ 0, 0 });
}

void GameEngineImage::BitCopyCenter(GameEngineImage* _Other, const float4& _CopyPos)
{
	BitCopy(_Other, _CopyPos - _Other->GetScale().Half(), _Other->GetScale(), float4{ 0, 0 });
}

void GameEngineImage::BitCopyCenterPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot)
{
	BitCopy(_Other, _CopyPos - _Other->GetScale().Half() + _CopyPivot, _Other->GetScale(), float4{ 0, 0 });
}

void GameEngineImage::BitCopyBot(GameEngineImage* _Other, const float4& _CopyPos)
{
	float4 ImagePivot = _Other->GetScale().Half();
	ImagePivot.y = _Other->GetScale().y;

	BitCopy(_Other, _CopyPos - ImagePivot, _Other->GetScale(), float4{ 0, 0 });
}

void GameEngineImage::BitCopyBotPivot(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyPivot)
{
	float4 ImagePivot = _Other->GetScale().Half();
	ImagePivot.y = _Other->GetScale().y;

	BitCopy(_Other, _CopyPos - ImagePivot + _CopyPivot, _Other->GetScale(), float4{ 0, 0 });
}

void GameEngineImage::BitCopy(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyScale, const float4& _OtherPivot)
{
	//�����ϴ� �Լ��� ������ �ȴ�
	//�����쿡�� �������ִ� �Ϲ����� dc vs dc�� �����Լ�
	//BitBlt�� �����Ϸ��� ũ�⸦ ���� �� ����. �� �̹����� ���õ� ���� ��ŭ�� �������� �̹����� ũ�Ⱑ ����ȴ�.
	BitBlt(
		ImageDC_, //���⿡ �����ض�
		_CopyPos.ix(), // �� �̹����� ������ x
		_CopyPos.iy(), // �� �̹����� ������ y �� �����ض�
		_CopyScale.ix(), // �� �̹����� �� ũ�⸸ŭ x
		_CopyScale.iy(), // �� �̹����� �� ũ�⸸ŭ y
		_Other->ImageDC_, //���� �Ϸ��� ���
		_OtherPivot.ix(), //���� �Ϸ��� ����� ������ x
		_OtherPivot.iy(), //���� �Ϸ��� ����� ������ y
		SRCCOPY
	);
}

////////////////////////////////////////////////////////////////////////////TransBlt

//�̹��� ũ�⸦ �ÿ��� �ٿ��� �� �� ������ ���ҽ��� �Ա⶧���� ���� ������ �� �ִ�
void GameEngineImage::TransCopyCenterScale(GameEngineImage* _Other, const float4& _CopyPos, const float4& _RenderScale, unsigned int _TransColor)
{
	TransCopy(_Other, _CopyPos - _Other->GetScale().Half(), _RenderScale, { 0, 0 }, _Other->GetScale(), _TransColor);
}

void GameEngineImage::TransCopyCenter(GameEngineImage* _Other, const float4& _CopyPos, unsigned int _TransColor)
{
	TransCopy(_Other, _CopyPos - _Other->GetScale().Half(), _Other->GetScale(), { 0, 0 }, _Other->GetScale(), _TransColor);
}

void GameEngineImage::TransCopy(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyScale
	, const float4& _OtherPivot, const float4& _OtherScale, unsigned int _TransColor)
{
	//�����ϴ� �Լ��� ������ �ȴ�
	//�����쿡�� �������ִ� �Ϲ����� dc vs dc�� �����Լ�
	TransparentBlt(
		ImageDC_, //���⿡ �����ض�
		_CopyPos.ix(), // �� �̹����� �̺κ� x
		_CopyPos.iy(), // �� �̹����� �̺κ� y �� �����ض�
		_CopyScale.ix(), // �� �̹����� x ũ�⸸ŭ
		_CopyScale.iy(), // �� �̹����� y ũ�⸸ŭ
		_Other->ImageDC_, //���� �Ϸ��� ���
		_OtherPivot.ix(), //���� �Ϸ��� ����� ������ x
		_OtherPivot.iy(), //���� �Ϸ��� ����� ������ y
		_OtherScale.ix(), //���� �Ϸ��� ����� x ũ��
		_OtherScale.iy(), //���� �Ϸ��� ����� y ũ��
		_TransColor // ����ȭ�� ���� 
	);
}

