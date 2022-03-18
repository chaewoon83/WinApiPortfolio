#pragma once
#include "GameEngineImage.h"
#include <GameEngineBase/GameEngineMath.h>
#include <map>

// �⺻������ ���ҽ��� �׳� �� �� ������
// �����Ǵ� ���ҽ����� �̸��� �ִٰ� �����ϰ� ����

class GameEngineImageManager
{
	//singleton pattern
private:
	static GameEngineImageManager* Inst_;
public:
	static GameEngineImageManager* GetInst()
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

	//�� �̹����� ����� ���̴�. ������ ä�������� �ʴ�.
	GameEngineImage* Create(const std::string& _Name, float4 _Scale);

	GameEngineImage* Create(const std::string& _Name, HDC _DC);
private:
	// constrcuter destructer
	GameEngineImageManager();
	~GameEngineImageManager();

	// delete Function
	GameEngineImageManager(const GameEngineImageManager& _Other) = delete;
	GameEngineImageManager(GameEngineImageManager&& _Other) noexcept = delete;
	GameEngineImageManager& operator=(const GameEngineImageManager& _Other) = delete;
	GameEngineImageManager& operator=(GameEngineImageManager&& _Other) noexcept = delete;



protected:

private:
	//���� �̸��� �̹����� �ΰ� ������ �� ����.
	//����ٰ� ��� �̹����� ��Ƴ��� �����ϱ⵵ ���ϰ�, ���߿� delete�� �� �� �ִ�
	std::map<std::string, GameEngineImage*> AllRes;
};
