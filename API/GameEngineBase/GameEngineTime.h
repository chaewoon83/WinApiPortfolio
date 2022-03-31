#pragma once

// 설명 :
class GameEngineTime
{
private:
	static GameEngineTime* Inst_;
public:
	static GameEngineTime* GetInst()
	{
		return Inst_;
	}

	static void Destroy()
	{
		if (nullptr != Inst_)
		{
			delete Inst_;
			Inst_ = nullptr;
		}
	}
public:
	void Reset();
	void Update();

	//Inst_->DeltaTime_을 리턴 함으로서, static 으로 리턴할 수 있게 된다
	//GameEngineTime::GetInst()->GetDeltaTime()이런식으로 길게 안쓰고
	//GameEngineTime::GetDeltaTime() 이렇게 짧게 쓸 수 있게 된다
	//무조건 Inst_를 할당하기때문에 nullcheck를 하지 않는다

	static inline float GetDeltaTime()
	{
		return Inst_->DeltaTime_;
	}
protected:

private:
	__int64 CurrentCount_;
	__int64 SecondCount_;
	__int64 PrevCount_;
	float DeltaTime_;
	double RealDeltaTime_;
	// constrcuter destructer
	GameEngineTime();
	~GameEngineTime();

	// delete Function
	GameEngineTime(const GameEngineTime& _Other) = delete;
	GameEngineTime(GameEngineTime&& _Other) noexcept = delete;
	GameEngineTime& operator=(const GameEngineTime& _Other) = delete;
	GameEngineTime& operator=(GameEngineTime&& _Other) noexcept = delete;
	
};

