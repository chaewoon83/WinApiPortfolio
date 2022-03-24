#include "GameEngineTime.h"
//������ ������� ���ư����� �����ϱ� ���� std�� ��ɸ��� windows.h�� ����� �̿��Ѵ�
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
	//LARGE_INTEGER�� union�ȿ� LONGLONG ~~~~ �� ��������� �ֱ� ������
	//__int64�� ����� ����ȯ�Ͽ� �״�� �� �� �ִ�.(����Ʈ ���� ���� ����)
	//QueryPerformanceCounter �ȿ� �������ε� const�� �Ⱥپ��ִ� -> ���� ���ڰ��� �ٲ��ش�
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
