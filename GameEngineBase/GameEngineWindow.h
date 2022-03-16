#pragma once
#include <Windows.h>
#include <string> 
#include <GameEngineBase/GameEngineMath.h>
// ���� : �����쿡 ���õ� ������ ����ϴ� Ŭ����
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
	//HDC�� â �̹��� �� ��ü��
	//â �̹����� 2���� �迭�̴�. 
	//HDC�� �̹����� ǥ���ϱ����� 2���� �迭�̴�
	//���ٱ��Ѱ� �������ѵ� ���Ѵ�
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

