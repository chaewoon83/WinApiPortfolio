#pragma once
#include "GameEngineImage.h"
#include "GameEngineFolderImage.h"
#include <GameEngineBase/GameEngineMath.h>
#include <map>

// 기본적으로 리소스는 그냥 쓸 수 있지만
// 관리되는 리소스들은 이름이 있다고 생각하고 쓴다

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

	//빈 이미지를 만드는 것이다. 내용은 채워져있지 않다.
	GameEngineImage* Create(const std::string& _Name, const float4& _Scale);
	//HDC 는 이미 포인터이기 때문에 const reference를 안붙인다
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
	//같은 이름의 이미지가 두개 존재할 수 없다.
	//여기다가 모든 이미지를 모아놔야 관리하기도 편하고, 나중에 delete도 할 수 있다
	std::map<std::string, GameEngineImage*> AllRes;


	///////////////////////////////////////////////////////////////////////폴더 이미지
public:
	GameEngineFolderImage* FolderImageFind(const std::string& _Name);
	GameEngineFolderImage* FolderImageLoad(const std::string& _Path);
	GameEngineFolderImage* FolderImageLoad(const std::string& _Path, const std::string& _Name);


private:
	std::map<std::string, GameEngineFolderImage*> AllFolderRes;
};

