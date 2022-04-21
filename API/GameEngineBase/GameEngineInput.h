#pragma once
#include <vector>
#include <windows.h>
#include <map>
#include <string>
// 설명 : 게임의 인풋에 관련된 기능들을 다루는 클래스
class GameEngineInput
{
	friend class GameEngineWindow;
private:
	class GameEngineKey
	{
		friend GameEngineInput;

		bool Down_; //최초 키를 눌렀을떄
		bool Press_; // 그 이후로 지속적으로 누르고 있을떄
		bool Up_; // 누르다가 키를 땟을때
		bool Free_; // 안누르고 있을때

		//키가 눌린 시간
		float Time_;
		//키 입력을 한개씩만 받는다
		int Key_;

		bool KeyCheck()
		{
			//Key값이 눌렸는지 안눌렸는지 체크한다 (Key_ 값이 눌리게 되면 0이 아니게 된다)
			return 0 != GetAsyncKeyState(Key_);
		}

		void Update(float _DeltaTime);

		void Reset()
		{
			Down_ = false;
			Press_ = false;
			Up_ = false;
			Free_ = true;
		}

		//GameEngineKey()
		//	:Key_(_Key)
		//	, Down_(false)
		//	, Press_(false)
		//	, Up_(false)
		//	, Free_(true)
		//{

		//}
	};

private:
	static GameEngineInput* Inst_;
public:
	static GameEngineInput* GetInst()
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

	void Update(float _DeltaTime);

	float GetTime(const std::string& _Name);

	bool IsDown(const std::string& _Name);
	bool IsPress(const std::string& _Name);
	bool IsUp(const std::string& _Name);
	bool IsFree(const std::string& _Name);
	bool IsKey(const std::string& _Name);

	inline int GetMouseWheel()
	{
		return CurWheelValue;
	}


	//"PlayerAttack", "A"
	void CreateKey(const std::string& _Name, int _key);

protected:

private:
	int WheelValue;
	int CurWheelValue;

	// constrcuter destructer
	GameEngineInput();
	~GameEngineInput();

	// delete Function
	GameEngineInput(const GameEngineInput& _Other) = delete;
	GameEngineInput(GameEngineInput&& _Other) noexcept = delete;
	GameEngineInput& operator=(const GameEngineInput& _Other) = delete;
	GameEngineInput& operator=(GameEngineInput&& _Other) noexcept = delete;
	//이름을 지어주기위한 map
	std::map<std::string, GameEngineKey> AllInputKey_;
};

