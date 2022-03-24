#pragma once
#include <vector>
#include <windows.h>
#include <map>
#include <string>
// ���� : ������ ��ǲ�� ���õ� ��ɵ��� �ٷ�� Ŭ����
class GameEngineInput
{
private:
	class GameEngineKey
	{
		friend GameEngineInput;

		bool Down_; //���� Ű�� ��������
		bool Press_; // �� ���ķ� ���������� ������ ������
		bool Up_; // �����ٰ� Ű�� ������
		bool Free_; // �ȴ����� ������

		//Ű �Է��� �Ѱ����� �޴´�
		int Key_;

		bool KeyCheck()
		{
			//Key���� ���ȴ��� �ȴ��ȴ��� üũ�Ѵ� (Key_ ���� ������ �Ǹ� 0�� �ƴϰ� �ȴ�)
			return 0 != GetAsyncKeyState(Key_);
		}

		void Update();

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

	void Update();

	bool IsDown(std::string _Name);
	bool IsPress(std::string _Name);
	bool IsUp(std::string _Name);
	bool IsFree(std::string _Name);
	bool IsKey(std::string _Name);


	//"PlayerAttack", "A"
	void CreateKey(std::string _Name, int _key);

protected:

private:
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

