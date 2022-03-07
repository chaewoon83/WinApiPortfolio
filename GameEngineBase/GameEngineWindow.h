#pragma once
#include <Windows.h>
#include <string> 

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
	void MessageLoop();
	void Off();

	inline HDC GETHDC() const
	{
		return HDC_;
	}

private:
	bool WindowOn_;
	HINSTANCE hInst_;
	HWND hWnd_;
	std::string Title_;
	HDC HDC_;

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

