#pragma once
#include <Windows.h>
#include <string> 
#include <GameEngineBase/GameEngineMath.h>
// 설명 : 윈도우에 관련된 모든것을 담당하는 클래스
class GameEngineWindow
{
private:
	//singleton
	static GameEngineWindow* Inst_;
public:
	inline static GameEngineWindow& GetInst()
	{
		return *Inst_;
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
	void RegClass(HINSTANCE _hInst);
	void CreateGameWindow(HINSTANCE _hInst, const std::string _Title);
	void ShowGameWindow();
	void MessageLoop(void(*_InitFunction)(), void(*_LoopFunction)());
	void SetWindowScaleAndPosition(float4 _Pos, float4 _Scale);
	void Off();

	static inline HDC& GetHDC()
	{
		return Inst_->HDC_;
	}

	static inline float4& GetScale()
	{
		return Inst_->Scale_;
	}

private:
	std::string Title_;
	bool WindowOn_;
	HINSTANCE hInst_;
	//HDC는 창 이미지 그 자체다
	//창 이미지는 2차원 배열이다. 
	//HDC는 이미지를 표현하기위한 2차원 배열이다
	//접근권한과 수정권한도 겸한다
	HWND hWnd_;
	HDC HDC_;
	float4 Scale_;
protected:

private:

	// constrcuter destructer
	GameEngineWindow();
	~GameEngineWindow();

	// delete Function
	GameEngineWindow(const GameEngineWindow& _Other) = delete;
	GameEngineWindow(GameEngineWindow&& _Other) noexcept = delete;
	GameEngineWindow& operator=(const GameEngineWindow& _Other) = delete;
	GameEngineWindow& operator=(GameEngineWindow&& _Other) noexcept = delete;


};

