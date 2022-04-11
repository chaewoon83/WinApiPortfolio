#pragma once
#include "GameEngineImage.h"
#include "GameEngineFolderImage.h"
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

	GameEngineImage* Find(const std::string& _Name);

	//�� �̹����� ����� ���̴�. ������ ä�������� �ʴ�.
	GameEngineImage* Create(const std::string& _Name, const float4& _Scale);
	//HDC �� �̹� �������̱� ������ const reference�� �Ⱥ��δ�
	GameEngineImage* Create(const std::string& _Name, HDC _DC);
	GameEngineImage* Load(const std::string& _Path);
	GameEngineImage* Load(const std::string& _Path, const std::string& _Name);
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


	///////////////////////////////////////////////////////////////////////���� �̹���
public:
	GameEngineFolderImage* FolderImageFind(const std::string& _Name);
	GameEngineFolderImage* FolderImageLoad(const std::string& _Path);
	GameEngineFolderImage* FolderImageLoad(const std::string& _Path, const std::string& _Name);


private:
	std::map<std::string, GameEngineFolderImage*> AllFolderRes;
};

