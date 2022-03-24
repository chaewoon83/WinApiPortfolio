#include "GameEngineTime.h"
//실제로 어떤식으로 돌아가는지 공부하기 위해 std의 기능말고 windows.h의 기능을 이용한다
#include <windows.h>


GameEngineTime* GameEngineTime::Inst_ = new GameEngineTime();
GameEngineTime::GameEngineTime() 
{
}

GameEngineTime::~GameEngineTime() 
{
}

void GameEngineTime::Reset()
{
	//LARGE_INTEGER의 union안에 LONGLONG ~~~~ 가 멤버변수로 있기 때문에
	//__int64를 명시적 형변환하여 그대로 쓸 수 있다.(바이트 수가 같기 때문)
	//QueryPerformanceCounter 안에 포인터인데 const가 안붙어있다 -> 넣은 인자값을 바꿔준다
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&PrevCount_));
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&CurrentCount_));
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&SecondCount_));
	Update();
}

void GameEngineTime::Update()
{
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&CurrentCount_));

	RealDeltaTime_ = (static_cast<double>(CurrentCount_) - static_cast<double>(PrevCount)) / static_cast<double>(SecondCount_);
	PrevCount_ = CurrentCount_;
	DeltaTime_ = static_cast<float>(RealDeltaTime_);
}
