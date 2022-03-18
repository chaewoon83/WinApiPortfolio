#pragma once
#include "GameEngineImage.h"
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
public:
	// constrcuter destructer
	GameEngineImageManager();
	~GameEngineImageManager();

	// delete Function
	GameEngineImageManager(const GameEngineImageManager& _Other) = delete;
	GameEngineImageManager(GameEngineImageManager&& _Other) noexcept = delete;
	GameEngineImageManager& operator=(const GameEngineImageManager& _Other) = delete;
	GameEngineImageManager& operator=(GameEngineImageManager&& _Other) noexcept = delete;

	//빈 이미지를 만드는 것이다. 내용은 채워져있지 않다.
	GameEngineImage* Create(const std::string& _Name, float4 _Scale);

	GameEngineImage* Create(const std::string& _Name, HDC _DC);

protected:

private:
	//같은 이름의 이미지가 두개 존재할 수 없다.
	//여기다가 모든 이미지를 모아놔야 관리하기도 편하고, 나중에 delete도 할 수 있다
	std::map<std::string, GameEngineImage*> AllRes;
};

