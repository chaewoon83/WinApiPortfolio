#pragma once
#include <vector>
#include <windows.h>
#include <map>
#include <string>
// ���� : ������ ��ǲ�� ���õ� ��ɵ��� �ٷ�� Ŭ����
class GameEngineInput
{
	friend class GameEngineWindow;
private:
	class GameEngineKey
	{
		friend GameEngineInput;

		bool Down_; //���� Ű�� ��������
		bool Press_; // �� ���ķ� ���������� ������ ������
		bool Up_; // �����ٰ� Ű�� ������
		bool Free_; // �ȴ����� ������

		//Ű�� ���� �ð�
		float Time_;
		//Ű �Է��� �Ѱ����� �޴´�
		int Key_;

		bool KeyCheck()
		{
			//Key���� ���ȴ��� �ȴ��ȴ��� üũ�Ѵ� (Key_ ���� ������ �Ǹ� 0�� �ƴϰ� �ȴ�)
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
	//�̸��� �����ֱ����� map
	std::map<std::string, GameEngineKey> AllInputKey_;
};

