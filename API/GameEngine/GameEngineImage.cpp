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

bool GameEngineImage::Load(const std::string& _Path)
{
	BitMap_ = static_cast<HBITMAP>(LoadImageA(
		nullptr, // 프로세스 핸들 nullptr 기입시 알아서 디폴트 세팅
		_Path.c_str(), // 절대경로로 때려 박을 예정
		IMAGE_BITMAP,
		0, // 크기정하기
		0,
		LR_LOADFROMFILE
		));
	//BitMap_을 채워준다
	//비어있는 DC를 만든다 그안에 (1,1)크기의 HBitMap이 같이 생성된다

	if (nullptr == BitMap_)
	{
		MsgBoxAssert("이미지 로드에 실패했습니다. \n1. 경로 확인하기, \n2. 디버깅은 제대로 보기")
	}
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

////////////////////////////////////////////////////////////////////////////BitBlt (크기조정x)
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
	//복사하는 함수는 제공이 된다
	//윈도우에서 지원해주는 일반적인 dc vs dc의 복사함수
	//BitBlt은 복사하려는 크기를 정할 수 없다. 내 이미지의 선택된 영역 만큼만 복사대상의 이미지의 크기가 복사된다.
	BitBlt(
		ImageDC_, //여기에 복사해라
		_CopyPos.ix(), // 내 이미지의 시작점 x
		_CopyPos.iy(), // 내 이미지의 시작점 y 에 복사해라
		_CopyScale.ix(), // 내 이미지의 이 크기만큼 x
		_CopyScale.iy(), // 내 이미지의 이 크기만큼 y
		_Other->ImageDC_, //복사 하려는 대상
		_OtherPivot.ix(), //복사 하려는 대상의 시작점 x
		_OtherPivot.iy(), //복사 하려는 대상의 시작점 y
		SRCCOPY
	);
}

////////////////////////////////////////////////////////////////////////////TransBlt

//이미지 크기를 늘였다 줄였다 할 수 있지만 리소스를 먹기때문에 렉을 유발할 수 있다

void GameEngineImage::TransCopy(GameEngineImage* _Other, const float4& _CopyPos, const float4& _CopyScale
	, const float4& _OtherPivot, const float4& _OtherScale, unsigned int _TransColor)
{
	//복사하는 함수는 제공이 된다
	//윈도우에서 지원해주는 일반적인 dc vs dc의 복사함수
	TransparentBlt(
		ImageDC_, //여기에 복사해라
		_CopyPos.ix(), // 내 이미지의 이부분 x
		_CopyPos.iy(), // 내 이미지의 이부분 y 에 복사해라
		_CopyScale.ix(), // 내 이미지의 x 크기만큼
		_CopyScale.iy(), // 내 이미지의 y 크기만큼
		_Other->ImageDC_, //복사 하려는 대상
		_OtherPivot.ix(), //복사 하려는 대상의 시작점 x
		_OtherPivot.iy(), //복사 하려는 대상의 시작점 y
		_OtherScale.ix(), //복사 하려는 대상의 x 크기
		_OtherScale.iy(), //복사 하려는 대상의 y 크기
		_TransColor // 투명화할 색깔 
	);
}

//////////////////////////알파카피

void GameEngineImage::AlphaCopy(GameEngineImage* _Other, const float4& _CopyPos,
	const float4& _CopyScale,
	const float4& _OtherPivot, const float4& _OtherScale, unsigned int _Alpha)
{
	BLENDFUNCTION Func;
	Func.BlendOp = AC_SRC_OVER;
	Func.BlendFlags = 0;
	Func.SourceConstantAlpha = _Alpha;
	Func.AlphaFormat = AC_SRC_ALPHA;


	AlphaBlend(
		ImageDC_, // 여기에 복사(우리 윈도우이미지)
		_CopyPos.ix(), // 윈도우 이미지의 위치 x에서부터 y
		_CopyPos.iy(), // 윈도우 이미지의 위치 x에서부터 y
		_CopyScale.ix(), // 내 이미지의 이 크기만큼 x
		_CopyScale.iy(), // 내 이미지의 이 크기만큼 y
		_Other->ImageDC_, // 복사하려는 대상은(거기에 그려지는 이미지가 뭔데?커비)
		_OtherPivot.ix(), // 복사하려는 대상의 시작점X 위치
		_OtherPivot.iy(),// 복사하려는 대상의 시작점Y
		_OtherScale.ix(), // 복사하려는 대상의 시작점X 크기
		_OtherScale.iy(),// 복사하려는 대상의 시작점Y
		Func // 복사하라는 명령
	);

}

//회전
void GameEngineImage::PlgCopy(GameEngineImage* _Other, GameEngineImage* _Filter)
{
	// 3개의 포인트를 넣어줘야 합니다.

	POINT Test;

	PlgBlt(
		ImageDC_, // 여기에 복사(우리 윈도우이미지)
		&Test,
		_Other->ImageDC_,
		0, // 윈도우 이미지의 위치 x에서부터 y
		0, // 윈도우 이미지의 위치 x에서부터 y
		0, // 내 이미지의 이 크기만큼 x
		0, // 내 이미지의 이 크기만큼 y
		_Filter->BitMap_, // 복사하려는 대상은(거기에 그려지는 이미지가 뭔데?커비)
		0, // 복사하려는 대상의 시작점X 위치
		0// 복사하려는 대상의 시작점Y
	);
}


void GameEngineImage::Cut(const float4& _CutSize)
{
	if (0 != (GetScale().ix() % _CutSize.ix()))
	{
		MsgBoxAssert("이미지를 자를 수 있는 수치가 딱 맞아 떨어지지 않습니다")
	}
	if (0 != (GetScale().iy() % _CutSize.iy()))
	{
		MsgBoxAssert("이미지를 자를 수 있는 수치가 딱 맞아 떨어지지 않습니다")
	}

	int XCount = GetScale().ix() / _CutSize.ix();
	int YCount = GetScale().iy() / _CutSize.iy();

	// { (0,0), (0,128), (0,256), (128,0) , .....} 이미지를 자르기위한 좌표를 만드는 for문이다
	for (int y = 0; y < YCount; y++)
	{
		for (int x = 0; x < XCount; x++)
		{
			CutPivot_.push_back({static_cast<float>( x * _CutSize.ix()), static_cast<float>(y * _CutSize.iy())});
			CutScale_.push_back(_CutSize);
		}
	}

}

void GameEngineImage::CutCount(int _x, int _y)
{
	float4 Scale = { GetScale().x / _x, GetScale().y / _y };
	Cut(Scale);
}

int GameEngineImage::GetImagePixel(int _x, int _y)
{
	//이미지 밖의 색은 검은색으로 설정해놓는다
	if (0> _x)
	{
		return RGB(0, 0, 0);
	}

	if ( 0 > _y)
	{
		return RGB(0, 0, 0);
	}

	if (GetScale().ix() <= _x)
	{
		return RGB(0, 0, 0);
	}

	if (GetScale().iy() <= _y)
	{
		return RGB(0, 0, 0);
	}
	return GetPixel(ImageDC_, _x, _y);
}