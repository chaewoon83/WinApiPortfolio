#pragma once
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, message, wParam, lParam);
}

// 설명 : 윈도우에 관련된 모든것을 담당하는 클래스
class GameEngineWindow
{
private:
	//singletone
	static GameEngineWindow* Inst_;
public:
	inline static GameEngineWindow& getInst()
	{
		return *Inst_;
	}

	static GameEngineWindow& Destroy()
	{
		if (nullptr == Inst_)
		{
			delete Inst_;
			Inst_ = nullptr;
		}
	}
public:
	void CreateGameWinodw(HINSTANCE _hInst);
	void ShowGameWindow();

private:
	HWND hWnd_;
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

